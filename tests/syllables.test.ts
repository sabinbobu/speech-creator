import { describe, expect, it } from "vitest";
import { countSyllables, countSyllablesInText, normalizeWord } from "@/lib/duration/syllables";
import { SYLLABLE_CORPUS, SYLLABLE_HELDOUT } from "../eval/syllable-corpus";

describe("normalizeWord", () => {
  it("folds legacy cedilla codepoints onto the comma-below forms", () => {
    expect(normalizeWord("şi")).toBe("și");
    expect(normalizeWord("ţară")).toBe("țară");
  });

  it("strips punctuation and case", () => {
    expect(normalizeWord("Mulțumesc!")).toBe("mulțumesc");
  });
});

describe("countSyllables", () => {
  it("counts simple vowel sequences", () => {
    expect(countSyllables("nuntă")).toBe(2);
    expect(countSyllables("discurs")).toBe(2);
    expect(countSyllables("aniversare")).toBe(5);
  });

  it("treats diphthongs and triphthongs as single nuclei", () => {
    expect(countSyllables("noapte")).toBe(2);
    expect(countSyllables("vreau")).toBe(1);
    expect(countSyllables("mireasă")).toBe(3);
  });

  it("applies the non-syllabic final -i rule", () => {
    expect(countSyllables("lupi")).toBe(1);
    expect(countSyllables("oameni")).toBe(2);
    expect(countSyllables("mari")).toBe(1);
  });

  it("keeps a final -ii as a real nucleus", () => {
    expect(countSyllables("copii")).toBe(2);
  });

  it("opens final-only diphthongs into hiatus when medial", () => {
    // "ii" fuses word-finally but not in the middle of a word.
    expect(countSyllables("copii")).toBe(2);
    expect(countSyllables("viitor")).toBe(3);
    // Same shape for "eu".
    expect(countSyllables("mereu")).toBe(2);
    expect(countSyllables("împreună")).toBe(4);
  });

  it("reads word-final -ie as hiatus after a consonant", () => {
    expect(countSyllables("familie")).toBe(4);
    expect(countSyllables("emoție")).toBe(4);
    // but word-initial ie- is a diphthong
    expect(countSyllables("ieri")).toBe(1);
  });

  it("counts the spoken form of numerals, not their digits", () => {
    // "două mii douăzeci și șase"
    expect(countSyllables("2026")).toBe(countSyllablesInText("două mii douăzeci și șase"));
  });

  it("never returns zero for a real word", () => {
    expect(countSyllables("a")).toBe(1);
    expect(countSyllables("!")).toBe(0);
  });
});

function score(set: ReadonlyArray<readonly [string, number]>) {
  const results = set.map(([word, expected]) => {
    const actual = countSyllables(word);
    return { word, expected, actual, error: actual - expected };
  });
  const misses = results.filter((r) => r.error !== 0);
  return {
    results,
    misses,
    exactRate: (results.length - misses.length) / results.length,
    meanAbsError:
      results.reduce((s, r) => s + Math.abs(r.error), 0) / results.length,
    meanSignedError: results.reduce((s, r) => s + r.error, 0) / results.length,
    // Named on failure so a regression says which words it broke.
    detail: misses
      .map((m) => `${m.word}: got ${m.actual}, want ${m.expected}`)
      .join("\n"),
  };
}

describe.each([
  ["tuning corpus", SYLLABLE_CORPUS],
  ["held-out set", SYLLABLE_HELDOUT],
])("accuracy on the %s", (_name, set) => {
  const s = score(set);

  it("matches the hand-labelled count on at least 95% of words", () => {
    expect(
      s.exactRate,
      `exact match ${(s.exactRate * 100).toFixed(1)}%\n${s.detail}`,
    ).toBeGreaterThanOrEqual(0.95);
  });

  it("keeps mean absolute error under a tenth of a syllable", () => {
    expect(s.meanAbsError, s.detail).toBeLessThanOrEqual(0.1);
  });

  it("stays unbiased, which is what duration accuracy depends on", () => {
    // Random +/-1 errors cancel across a 700-word speech. A systematic lean
    // does not: it would make every speech land consistently long or short.
    expect(Math.abs(s.meanSignedError), s.detail).toBeLessThanOrEqual(0.05);
  });
});
