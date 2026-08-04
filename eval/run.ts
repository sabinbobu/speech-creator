/**
 * Eval harness for the duration-constrained rewrite loop.
 *
 * WHAT THIS MEASURES: how close the loop lands to the requested duration, as
 * judged by the duration engine, across 100 hostile cases.
 *
 * WHAT THIS DOES NOT MEASURE: whether the duration engine itself agrees with a
 * stopwatch. That is a separate question and needs human recordings — run
 * `npm run calibrate` for it. A perfect score here with a miscalibrated engine
 * means every speech lands at exactly the wrong length.
 *
 *   npm run eval
 */

import { writeFileSync, mkdirSync } from "node:fs";
import { estimateSeconds } from "../src/lib/duration";
import { estimateScript } from "../src/lib/script/estimate";
import { fitToTarget } from "../src/lib/script/fit";
import type { Script, Section } from "../src/lib/script/types";
import { getTemplate } from "../src/lib/templates";
import { EVAL_CASES } from "./cases";
import type { EvalCase } from "./cases";
import { rng, syntheticWriter, textOfSeconds } from "./writer";

const TOLERANCE_SECONDS = Number(process.env.EVAL_TOLERANCE ?? 5);
/** The plan caps the loop at 3; override to measure what more passes buy. */
const MAX_ITERATIONS = Number(process.env.EVAL_MAX_PASSES ?? 3);

interface CaseResult {
  id: string;
  targetSeconds: number;
  draftSeconds: number;
  finalSeconds: number;
  errorSeconds: number;
  relativeError: number;
  iterations: number;
  withinTolerance: boolean;
  stoppedBecause?: string;
}

function buildDraft(evalCase: EvalCase): Script {
  const template = getTemplate(evalCase.occasion);
  const totalWeight = template.sections.reduce((sum, s) => sum + s.weight, 0);
  const random = rng(evalCase.seed);
  const draftTotal = evalCase.targetSeconds * evalCase.draftFactor;

  const sections: Section[] = template.sections.map((s, i) => ({
    id: `${evalCase.id}-s${i}`,
    title: s.title,
    kind: s.kind,
    text: textOfSeconds(
      (draftTotal * s.weight) / totalWeight,
      evalCase.profile,
      random,
    ),
    locked: false,
    weight: s.weight,
  }));

  const now = new Date(0).toISOString();
  return {
    id: evalCase.id,
    title: evalCase.id,
    occasion: evalCase.occasion,
    targetSeconds: evalCase.targetSeconds,
    profile: evalCase.profile,
    sections,
    createdAt: now,
    updatedAt: now,
    intake: {},
  };
}

async function runCase(evalCase: EvalCase): Promise<CaseResult> {
  const draft = buildDraft(evalCase);
  const draftSeconds = estimateScript(draft).totalSeconds;

  const write = syntheticWriter({
    bias: evalCase.writerBias,
    noise: evalCase.writerNoise,
    profile: evalCase.profile,
    seed: evalCase.seed + 1,
  });

  const result = await fitToTarget(draft, {
    rewriter: (req) => write(req.targetSeconds),
    toleranceSeconds: TOLERANCE_SECONDS,
    maxIterations: MAX_ITERATIONS,
  });

  const errorSeconds = result.finalSeconds - evalCase.targetSeconds;

  return {
    id: evalCase.id,
    targetSeconds: evalCase.targetSeconds,
    draftSeconds,
    finalSeconds: result.finalSeconds,
    errorSeconds,
    relativeError: Math.abs(errorSeconds) / evalCase.targetSeconds,
    iterations: result.iterations.length,
    withinTolerance: result.withinTolerance,
    stoppedBecause: result.stoppedBecause,
  };
}

function percentile(sorted: number[], p: number): number {
  if (sorted.length === 0) return 0;
  const index = Math.min(
    sorted.length - 1,
    Math.max(0, Math.ceil((p / 100) * sorted.length) - 1),
  );
  return sorted[index];
}

async function main() {
  const started = Date.now();
  const results: CaseResult[] = [];

  for (const evalCase of EVAL_CASES) {
    results.push(await runCase(evalCase));
  }

  const absErrors = results.map((r) => Math.abs(r.errorSeconds)).sort((a, b) => a - b);
  const relErrors = results.map((r) => r.relativeError).sort((a, b) => a - b);

  const within5 = results.filter((r) => Math.abs(r.errorSeconds) <= 5).length;
  const within2pct = results.filter((r) => r.relativeError <= 0.02).length;
  const meanAbs = absErrors.reduce((a, b) => a + b, 0) / absErrors.length;
  const meanIterations =
    results.reduce((sum, r) => sum + r.iterations, 0) / results.length;

  // Baseline: what the error would have been with no fit loop at all.
  const baselineAbs =
    results.reduce(
      (sum, r) => sum + Math.abs(r.draftSeconds - r.targetSeconds),
      0,
    ) / results.length;

  const summary = {
    cases: results.length,
    toleranceSeconds: TOLERANCE_SECONDS,
    maxIterations: MAX_ITERATIONS,
    withinToleranceRate: within5 / results.length,
    within2PercentRate: within2pct / results.length,
    meanAbsErrorSeconds: meanAbs,
    p50AbsErrorSeconds: percentile(absErrors, 50),
    p90AbsErrorSeconds: percentile(absErrors, 90),
    maxAbsErrorSeconds: absErrors[absErrors.length - 1],
    p90RelativeError: percentile(relErrors, 90),
    meanIterations,
    baselineMeanAbsErrorSeconds: baselineAbs,
    durationMs: Date.now() - started,
  };

  const fmt = (n: number) => n.toFixed(2);
  console.log("\n  Duration fit-loop eval");
  console.log("  ─────────────────────────────────────────────");
  console.log(`  cases                    ${summary.cases}`);
  console.log(`  tolerance                ±${TOLERANCE_SECONDS}s, max ${MAX_ITERATIONS} passes`);
  console.log("");
  console.log(`  within ±5s               ${(summary.withinToleranceRate * 100).toFixed(0)}%`);
  console.log(`  within ±2%               ${(summary.within2PercentRate * 100).toFixed(0)}%`);
  console.log(`  mean |error|             ${fmt(summary.meanAbsErrorSeconds)}s`);
  console.log(`  p50 |error|              ${fmt(summary.p50AbsErrorSeconds)}s`);
  console.log(`  p90 |error|              ${fmt(summary.p90AbsErrorSeconds)}s`);
  console.log(`  max |error|              ${fmt(summary.maxAbsErrorSeconds)}s`);
  console.log(`  mean passes used         ${fmt(summary.meanIterations)}`);
  console.log("");
  console.log(`  no-loop baseline         ${fmt(summary.baselineMeanAbsErrorSeconds)}s mean |error|`);
  console.log(`  ran in                   ${(summary.durationMs / 1000).toFixed(1)}s`);
  console.log("");

  const worst = [...results]
    .sort((a, b) => Math.abs(b.errorSeconds) - Math.abs(a.errorSeconds))
    .slice(0, 5);
  console.log("  worst 5 cases");
  for (const r of worst) {
    console.log(
      `    ${r.id}  target ${r.targetSeconds}s  draft ${r.draftSeconds.toFixed(0)}s  ` +
        `final ${r.finalSeconds.toFixed(1)}s  err ${r.errorSeconds > 0 ? "+" : ""}` +
        `${r.errorSeconds.toFixed(1)}s  (${r.stoppedBecause})`,
    );
  }
  console.log("");

  mkdirSync(new URL("./results/", import.meta.url), { recursive: true });
  writeFileSync(
    new URL("./results/latest.json", import.meta.url),
    JSON.stringify({ summary, results }, null, 2),
  );
  console.log("  wrote eval/results/latest.json\n");

  // Sanity check that the harness itself is wired up.
  if (estimateSeconds("test") <= 0) {
    console.error("  engine returned zero duration — harness is broken");
    process.exit(1);
  }
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
