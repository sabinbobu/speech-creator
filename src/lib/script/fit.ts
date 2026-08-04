import type { Script, Section } from "./types";
import { estimateScript, sectionSeconds } from "./estimate";

/**
 * The duration-constrained rewrite loop.
 *
 * Generate -> estimate -> contract/expand only the sections that need it ->
 * repeat, at most a few times. Two rules make it work:
 *
 *  1. It never regenerates the whole speech. Regeneration throws away the
 *     personal detail that makes a speech worth delivering, and it makes the
 *     length wander unpredictably. Editing is surgical, per section.
 *  2. Locked sections are untouchable, so the loop can run on a script the
 *     user has already worked on.
 *
 * The rewriter is injected rather than imported: the loop is pure control
 * flow and is tested without an LLM in the room.
 */

export type RewriteDirection = "contract" | "expand";

export interface RewriteRequest {
  section: Section;
  currentSeconds: number;
  targetSeconds: number;
  direction: RewriteDirection;
  /** Whole-script context so the rewrite keeps voice and avoids repetition. */
  script: Script;
}

export type SectionRewriter = (req: RewriteRequest) => Promise<string>;

export interface FitOptions {
  rewriter: SectionRewriter;
  /** How close is close enough. The plan's promise is +/- 5 seconds. */
  toleranceSeconds?: number;
  maxIterations?: number;
  /** Don't spend a rewrite on a section that is nearly right already. */
  minAdjustSeconds?: number;
  /** Never shrink a section below this; it would stop being a section. */
  floorSeconds?: number;
  /**
   * Bias correction carried in from a previous run. The loop is normally run
   * one iteration per HTTP request so a serverless function doesn't sit through
   * three model calls — passing the previous `gain` back keeps the control loop
   * continuous across those requests instead of relearning the bias each time.
   */
  initialGain?: number;
}

export interface FitAdjustment {
  sectionId: string;
  title: string;
  direction: RewriteDirection;
  fromSeconds: number;
  /** The duration this section actually needs to be. */
  toSeconds: number;
  /** What the model was asked for, after bias compensation. */
  requestedSeconds: number;
  achievedSeconds: number;
}

export interface FitIteration {
  index: number;
  beforeSeconds: number;
  afterSeconds: number;
  adjustments: FitAdjustment[];
  /** The bias correction in force during this pass. */
  gain: number;
}

/**
 * Language models miss a length instruction in a consistent direction — ask
 * for 40 seconds and you reliably get 32. Re-asking for the same number just
 * reproduces the same miss, so the loop would stall short of target forever.
 *
 * So the loop measures what the model actually returned against what it was
 * asked for, and compensates on the next pass. `gain` below 1 means the model
 * writes short and gets asked for more. Clamped so one anomalous rewrite
 * cannot send the next request somewhere absurd.
 */
const MIN_GAIN = 0.4;
const MAX_GAIN = 2.5;


export interface FitResult {
  script: Script;
  iterations: FitIteration[];
  finalSeconds: number;
  withinTolerance: boolean;
  /** Feed back into `initialGain` when continuing the loop in a later request. */
  gain: number;
  /** Set when the loop could not proceed, e.g. every section is locked. */
  stoppedBecause?: "no-adjustable-sections" | "no-progress" | "converged" | "max-iterations";
}

export const DEFAULT_TOLERANCE_SECONDS = 5;

/**
 * Spread the required change across the adjustable sections in proportion to
 * their current length, so a 20 second cut takes more out of a long story than
 * out of a short closing line.
 */
export function planAdjustments(
  script: Script,
  options: Required<Pick<FitOptions, "minAdjustSeconds" | "floorSeconds">>,
): Array<{ section: Section; currentSeconds: number; targetSeconds: number }> {
  const estimated = estimateScript(script);
  const needed = script.targetSeconds - estimated.totalSeconds;

  const adjustable = script.sections.filter((s) => !s.locked && s.text.trim());
  if (adjustable.length === 0) return [];

  const byId = new Map(estimated.sections.map((s) => [s.sectionId, s]));
  const adjustableTotal = adjustable.reduce(
    (sum, s) => sum + (byId.get(s.id)?.seconds ?? 0),
    0,
  );
  if (adjustableTotal <= 0) return [];

  const plans: Array<{
    section: Section;
    currentSeconds: number;
    targetSeconds: number;
  }> = [];

  for (const section of adjustable) {
    const current = byId.get(section.id)?.seconds ?? 0;
    const share = current / adjustableTotal;
    const target = Math.max(options.floorSeconds, current + needed * share);
    if (Math.abs(target - current) >= options.minAdjustSeconds) {
      plans.push({ section, currentSeconds: current, targetSeconds: target });
    }
  }

  return plans;
}

export async function fitToTarget(
  script: Script,
  options: FitOptions,
): Promise<FitResult> {
  const tolerance = options.toleranceSeconds ?? DEFAULT_TOLERANCE_SECONDS;
  const maxIterations = options.maxIterations ?? 3;
  const minAdjust = options.minAdjustSeconds ?? 1.5;
  const floor = options.floorSeconds ?? 3;

  let current: Script = { ...script, sections: script.sections.map((s) => ({ ...s })) };
  const iterations: FitIteration[] = [];
  let stoppedBecause: FitResult["stoppedBecause"];
  let gain = Math.min(MAX_GAIN, Math.max(MIN_GAIN, options.initialGain ?? 1));

  for (let i = 0; i < maxIterations; i += 1) {
    const before = estimateScript(current).totalSeconds;

    if (Math.abs(before - current.targetSeconds) <= tolerance) {
      stoppedBecause = "converged";
      break;
    }

    const plans = planAdjustments(current, {
      minAdjustSeconds: minAdjust,
      floorSeconds: floor,
    });

    if (plans.length === 0) {
      stoppedBecause = current.sections.every((s) => s.locked)
        ? "no-adjustable-sections"
        : "no-progress";
      break;
    }

    // The correction in force when this pass started, recorded for the report.
    const gainThisPass = gain;
    const adjustments: FitAdjustment[] = [];
    const nextSections = [...current.sections];

    // Sequential rather than parallel: each rewrite sees the script as the
    // previous one left it, which keeps the model from repeating an image it
    // just used in a neighbouring section.
    let requestedTotal = 0;
    let achievedTotal = 0;
    let attempts = 0;

    for (const plan of plans) {
      const direction: RewriteDirection =
        plan.targetSeconds < plan.currentSeconds ? "contract" : "expand";

      // Ask for what the model has to be asked for in order to land on what
      // the section actually needs.
      const requestedSeconds = Math.max(floor, plan.targetSeconds / gain);

      let rewritten: string;
      try {
        rewritten = await options.rewriter({
          section: plan.section,
          currentSeconds: plan.currentSeconds,
          targetSeconds: requestedSeconds,
          direction,
          script: current,
        });
      } catch {
        // A failed rewrite is survivable: keep the original text and let the
        // next iteration try again rather than losing the whole run.
        continue;
      }

      const text = rewritten.trim();
      if (!text) continue;

      const index = nextSections.findIndex((s) => s.id === plan.section.id);
      if (index === -1) continue;

      const candidate: Section = { ...nextSections[index], text };
      const achievedSeconds = sectionSeconds(candidate, current.profile);

      // The attempt teaches us the writer's bias whether or not we keep the
      // text. Fold it in immediately rather than at the end of the pass, so the
      // remaining sections in this same pass are already asked for corrected
      // numbers — that is what lets a biased writer converge inside the
      // three-pass budget instead of burning a whole pass discovering the bias.
      requestedTotal += requestedSeconds;
      achievedTotal += achievedSeconds;
      attempts += 1;
      gain = Math.min(
        MAX_GAIN,
        Math.max(MIN_GAIN, achievedTotal / requestedTotal),
      );

      // Reject a rewrite that lands further from the target than the text it
      // would replace. A writer that misses badly in the wrong direction —
      // returning a *shorter* section when asked to expand — must not be
      // allowed to make the speech worse.
      const wasOff = Math.abs(plan.currentSeconds - plan.targetSeconds);
      const nowOff = Math.abs(achievedSeconds - plan.targetSeconds);
      if (nowOff >= wasOff) continue;

      nextSections[index] = candidate;

      adjustments.push({
        sectionId: plan.section.id,
        title: plan.section.title,
        direction,
        fromSeconds: plan.currentSeconds,
        toSeconds: plan.targetSeconds,
        requestedSeconds,
        achievedSeconds,
      });
    }

    current = { ...current, sections: nextSections };
    const after = estimateScript(current).totalSeconds;

    iterations.push({
      index: i,
      beforeSeconds: before,
      afterSeconds: after,
      adjustments,
      gain: gainThisPass,
    });

    // A pass that applied nothing is still useful if it measured the writer's
    // bias — the next pass asks for a corrected number and usually lands. Only
    // give up when a pass neither moved the script nor learned anything.
    const learned = Math.abs(gain - gainThisPass) > 0.01;
    if ((adjustments.length === 0 || Math.abs(after - before) < 0.5) && !learned) {
      stoppedBecause = "no-progress";
      break;
    }
    if (attempts === 0) {
      stoppedBecause = "no-progress";
      break;
    }
  }

  const finalSeconds = estimateScript(current).totalSeconds;
  const withinTolerance =
    Math.abs(finalSeconds - current.targetSeconds) <= tolerance;

  if (!stoppedBecause) {
    stoppedBecause = withinTolerance ? "converged" : "max-iterations";
  }

  return {
    script: { ...current, updatedAt: new Date().toISOString() },
    iterations,
    finalSeconds,
    withinTolerance,
    gain,
    stoppedBecause,
  };
}
