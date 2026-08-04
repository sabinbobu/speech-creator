import { describe, expect, it, vi } from "vitest";
import { estimateSeconds } from "@/lib/duration";
import type { DeliveryProfileId } from "@/lib/duration";
import { fitToTarget, planAdjustments } from "@/lib/script/fit";
import { estimateScript } from "@/lib/script/estimate";
import type { Script, Section } from "@/lib/script/types";

const FILLER = [
  "astăzi",
  "vorbim",
  "despre",
  "un",
  "moment",
  "care",
  "contează",
  "pentru",
  "noi",
  "toți",
  "și",
  "pentru",
  "cei",
  "care",
  "ne-au",
  "adus",
  "aici",
];

/** Build Romanian-ish text that lands close to a requested duration. */
function textOfSeconds(seconds: number, profile: DeliveryProfileId): string {
  const words: string[] = [];
  let i = 0;
  while (estimateSeconds(words.join(" ") + ".", { profile }) < seconds) {
    words.push(FILLER[i % FILLER.length]);
    i += 1;
    if (i > 5000) break;
  }
  return words.join(" ") + ".";
}

/**
 * Stands in for the LLM. `precision` of 1 hits the requested duration; 0.8
 * simulates a model that consistently comes back 20% short.
 */
function makeRewriter(precision = 1) {
  return vi.fn(async ({ targetSeconds, script }: { targetSeconds: number; script: Script }) =>
    textOfSeconds(targetSeconds * precision, script.profile),
  );
}

function section(overrides: Partial<Section> = {}): Section {
  return {
    id: overrides.id ?? `s-${Math.random().toString(36).slice(2, 8)}`,
    title: overrides.title ?? "Secțiune",
    kind: overrides.kind ?? "liber",
    text: overrides.text ?? "",
    locked: overrides.locked ?? false,
    weight: overrides.weight ?? 1,
  };
}

function makeScript(targetSeconds: number, sections: Section[]): Script {
  return {
    id: "script-1",
    title: "Test",
    occasion: "nunta",
    targetSeconds,
    profile: "normal",
    sections,
    createdAt: new Date(0).toISOString(),
    updatedAt: new Date(0).toISOString(),
    intake: {},
  };
}

describe("planAdjustments", () => {
  const opts = { minAdjustSeconds: 1.5, floorSeconds: 3 };

  it("leaves locked sections out of the plan", () => {
    const script = makeScript(60, [
      section({ id: "a", text: textOfSeconds(60, "normal"), locked: true }),
      section({ id: "b", text: textOfSeconds(60, "normal") }),
    ]);
    const plans = planAdjustments(script, opts);
    expect(plans.map((p) => p.section.id)).toEqual(["b"]);
  });

  it("cuts proportionally, taking more from the longer section", () => {
    const script = makeScript(60, [
      section({ id: "long", text: textOfSeconds(90, "normal") }),
      section({ id: "short", text: textOfSeconds(30, "normal") }),
    ]);
    const plans = planAdjustments(script, opts);
    const long = plans.find((p) => p.section.id === "long")!;
    const short = plans.find((p) => p.section.id === "short")!;
    const longCut = long.currentSeconds - long.targetSeconds;
    const shortCut = short.currentSeconds - short.targetSeconds;
    expect(longCut).toBeGreaterThan(shortCut);
  });

  it("skips sections that are already near enough to be worth a rewrite", () => {
    const script = makeScript(60, [section({ id: "a", text: textOfSeconds(60.5, "normal") })]);
    expect(planAdjustments(script, opts)).toHaveLength(0);
  });

  it("never plans a section below the floor", () => {
    const script = makeScript(5, [
      section({ id: "a", text: textOfSeconds(120, "normal") }),
    ]);
    const plans = planAdjustments(script, opts);
    plans.forEach((p) => expect(p.targetSeconds).toBeGreaterThanOrEqual(3));
  });
});

describe("fitToTarget", () => {
  it("does not call the model when the script already fits", async () => {
    const rewriter = makeRewriter();
    const script = makeScript(60, [section({ text: textOfSeconds(59, "normal") })]);

    const result = await fitToTarget(script, { rewriter });

    expect(rewriter).not.toHaveBeenCalled();
    expect(result.withinTolerance).toBe(true);
    expect(result.stoppedBecause).toBe("converged");
    expect(result.iterations).toHaveLength(0);
  });

  it("contracts a speech that runs long", async () => {
    const script = makeScript(120, [
      section({ id: "a", text: textOfSeconds(150, "normal") }),
      section({ id: "b", text: textOfSeconds(90, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter() });

    expect(result.withinTolerance).toBe(true);
    expect(Math.abs(result.finalSeconds - 120)).toBeLessThanOrEqual(5);
  });

  it("expands a speech that runs short", async () => {
    const script = makeScript(300, [
      section({ id: "a", text: textOfSeconds(20, "normal") }),
      section({ id: "b", text: textOfSeconds(15, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter() });

    expect(result.withinTolerance).toBe(true);
    expect(Math.abs(result.finalSeconds - 300)).toBeLessThanOrEqual(5);
  });

  it("converges even when the model is consistently 20% off", async () => {
    const script = makeScript(180, [
      section({ id: "a", text: textOfSeconds(300, "normal") }),
      section({ id: "b", text: textOfSeconds(120, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter(0.8) });

    // This is the whole reason the loop iterates instead of estimating once.
    expect(result.withinTolerance).toBe(true);
    expect(result.iterations.length).toBeLessThanOrEqual(3);
  });

  it("converges when the model is consistently 30% long", async () => {
    const script = makeScript(240, [
      section({ id: "a", text: textOfSeconds(60, "normal") }),
      section({ id: "b", text: textOfSeconds(40, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter(1.3) });

    expect(result.withinTolerance).toBe(true);
  });

  it("learns the model's length bias and compensates on the next pass", async () => {
    const script = makeScript(180, [
      section({ id: "a", text: textOfSeconds(300, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter(0.8) });

    // First pass runs uncompensated; the second knows the model writes short.
    expect(result.iterations[0].gain).toBeCloseTo(1, 5);
    expect(result.iterations[1].gain).toBeLessThan(0.9);
    const second = result.iterations[1].adjustments[0];
    expect(second.requestedSeconds).toBeGreaterThan(second.toSeconds);
  });

  it("leaves locked text byte-for-byte intact", async () => {
    const precious = "Gluma pe care am scris-o eu și nu se atinge nimeni de ea.";
    const script = makeScript(120, [
      section({ id: "locked", text: precious, locked: true }),
      section({ id: "free", text: textOfSeconds(200, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter() });

    expect(result.script.sections.find((s) => s.id === "locked")!.text).toBe(precious);
    expect(result.script.sections.find((s) => s.id === "free")!.text).not.toBe(
      script.sections[1].text,
    );
  });

  it("gives up cleanly when every section is locked", async () => {
    const rewriter = makeRewriter();
    const script = makeScript(60, [
      section({ text: textOfSeconds(200, "normal"), locked: true }),
    ]);

    const result = await fitToTarget(script, { rewriter });

    expect(rewriter).not.toHaveBeenCalled();
    expect(result.withinTolerance).toBe(false);
    expect(result.stoppedBecause).toBe("no-adjustable-sections");
  });

  it("never runs more than the iteration budget", async () => {
    // A rewriter that ignores the target entirely can never converge.
    const stubborn = vi.fn(async () => textOfSeconds(400, "normal"));
    const script = makeScript(60, [section({ text: textOfSeconds(400, "normal") })]);

    const result = await fitToTarget(script, {
      rewriter: stubborn,
      maxIterations: 3,
    });

    expect(result.iterations.length).toBeLessThanOrEqual(3);
    expect(result.withinTolerance).toBe(false);
  });

  it("keeps the original text when a rewrite fails", async () => {
    const original = textOfSeconds(200, "normal");
    const failing = vi.fn(async () => {
      throw new Error("model unavailable");
    });
    const script = makeScript(60, [section({ id: "a", text: original })]);

    const result = await fitToTarget(script, { rewriter: failing });

    expect(result.script.sections[0].text).toBe(original);
    expect(result.withinTolerance).toBe(false);
  });

  it("records what it changed on each pass", async () => {
    const script = makeScript(120, [
      section({ id: "a", title: "Poveste", text: textOfSeconds(220, "normal") }),
    ]);

    const result = await fitToTarget(script, { rewriter: makeRewriter() });
    const first = result.iterations[0];

    expect(first.adjustments[0]).toMatchObject({
      sectionId: "a",
      title: "Poveste",
      direction: "contract",
    });
    expect(first.afterSeconds).toBeLessThan(first.beforeSeconds);
  });

  it("does not mutate the script it was given", async () => {
    const original = textOfSeconds(200, "normal");
    const script = makeScript(60, [section({ id: "a", text: original })]);

    await fitToTarget(script, { rewriter: makeRewriter() });

    expect(script.sections[0].text).toBe(original);
  });
});

describe("estimateScript", () => {
  it("splits the target across sections by weight", () => {
    const script = makeScript(100, [
      section({ id: "a", weight: 3 }),
      section({ id: "b", weight: 1 }),
    ]);
    const e = estimateScript(script);
    expect(e.sections[0].targetSeconds).toBeCloseTo(75, 5);
    expect(e.sections[1].targetSeconds).toBeCloseTo(25, 5);
  });

  it("reports the gap against the target", () => {
    const script = makeScript(60, [section({ text: textOfSeconds(90, "normal") })]);
    const e = estimateScript(script);
    expect(e.deltaSeconds).toBeGreaterThan(20);
  });
});
