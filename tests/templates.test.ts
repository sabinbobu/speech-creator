import { describe, expect, it } from "vitest";
import { OCCASION_LIST, getTemplate, validateIntake } from "@/lib/templates";

describe("occasion templates", () => {
  it("covers the three occasions the plan names", () => {
    expect(OCCASION_LIST.map((o) => o.id).sort()).toEqual([
      "dezbatere",
      "nunta",
      "prezentare",
    ]);
  });

  it.each(OCCASION_LIST)("$label asks exactly six questions", (template) => {
    // Six is the number in the plan: enough to get specifics, few enough that
    // a person with a wedding in two days actually finishes the form.
    expect(template.questions).toHaveLength(6);
  });

  it.each(OCCASION_LIST)("$label has unique question ids", (template) => {
    const ids = template.questions.map((q) => q.id);
    expect(new Set(ids).size).toBe(ids.length);
  });

  it.each(OCCASION_LIST)("$label ends by asking for the intended effect", (template) => {
    // The last question drives the closing line, so it has to be there.
    expect(template.questions[template.questions.length - 1].id).toBe("final");
  });

  it.each(OCCASION_LIST)("$label sections carry positive weight", (template) => {
    expect(template.sections.length).toBeGreaterThan(2);
    template.sections.forEach((s) => expect(s.weight).toBeGreaterThan(0));
  });

  it.each(OCCASION_LIST)("$label offers its default duration", (template) => {
    expect(template.durationOptions).toContain(template.defaultSeconds);
  });

  it("gives the wedding template the most time for the story", () => {
    const wedding = getTemplate("nunta");
    const heaviest = [...wedding.sections].sort((a, b) => b.weight - a.weight)[0];
    expect(heaviest.kind).toBe("poveste");
  });
});

describe("validateIntake", () => {
  const answers = (overrides: Record<string, string> = {}) => ({
    cine: "Ana și Mihai",
    relatie: "Sunt sora Anei, am crescut împreună.",
    moment:
      "În octombrie 2019, la 2 noaptea, m-a sunat din gară la Cluj să-mi spună că a cunoscut pe cineva.",
    gluma:
      "Mihai zice „doar cinci minute” de fiecare dată. Nu a fost niciodată cinci minute.",
    admiri:
      "Se ceartă și se împacă în aceeași seară, nu pleacă supărați la culcare.",
    final: "Recunoștință",
    ...overrides,
  });

  it("accepts a complete intake", () => {
    expect(validateIntake("nunta", answers()).ok).toBe(true);
  });

  it("reports a blank answer as missing", () => {
    const result = validateIntake("nunta", answers({ moment: "" }));
    expect(result.ok).toBe(false);
    expect(result.missing).toContain("moment");
  });

  it("treats whitespace as blank", () => {
    const result = validateIntake("nunta", answers({ gluma: "    " }));
    expect(result.missing).toContain("gluma");
  });

  it("rejects an answer too short to be specific", () => {
    // This is the whole point of the gate: "sunt oameni buni" passes a
    // required-field check and produces a speech about nobody.
    const result = validateIntake("nunta", answers({ moment: "e un om bun" }));
    expect(result.ok).toBe(false);
    expect(result.tooShort).toContain("moment");
    expect(result.missing).not.toContain("moment");
  });

  it("treats an entirely empty intake as missing, not short", () => {
    const result = validateIntake("nunta", {});
    expect(result.missing).toHaveLength(6);
    expect(result.tooShort).toHaveLength(0);
  });

  it("validates each occasion against its own questions", () => {
    // Wedding answers must not satisfy the debate template.
    expect(validateIntake("dezbatere", answers()).ok).toBe(false);
  });
});
