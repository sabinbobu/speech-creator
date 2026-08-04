import { describe, expect, it } from "vitest";
import {
  estimate,
  estimateSeconds,
  formatDelta,
  formatDuration,
} from "@/lib/duration/estimate";
import { PAUSE_TABLE } from "@/lib/duration/pauses";
import { DELIVERY_PROFILES } from "@/lib/duration/calibration";

describe("estimate", () => {
  it("returns an empty timeline for empty text", () => {
    const e = estimate("   \n\n  ");
    expect(e.totalMs).toBe(0);
    expect(e.words).toHaveLength(0);
  });

  it("accounts for every millisecond as either speech or silence", () => {
    const e = estimate("Astăzi, aici, începe o poveste. Una adevărată.");
    expect(e.totalMs).toBeCloseTo(e.speakingMs + e.pauseMs, 5);
  });

  it("lays words out on a strictly advancing timeline", () => {
    const e = estimate("Dragii mei, vă mulțumesc că sunteți aici.");
    for (let i = 1; i < e.words.length; i += 1) {
      expect(e.words[i].startMs).toBeGreaterThan(e.words[i - 1].startMs);
    }
    const last = e.words[e.words.length - 1];
    expect(e.totalMs).toBeCloseTo(last.startMs + last.durationMs + last.pauseAfterMs, 5);
  });

  it("charges longer words more time than short ones", () => {
    const short = estimate("azi");
    const long = estimate("binecuvântare");
    expect(long.totalMs).toBeGreaterThan(short.totalMs * 2);
  });

  it("attaches punctuation pauses to the word they follow", () => {
    const e = estimate("bine, rău");
    expect(e.words[0].pauseKind).toBe("comma");
    expect(e.words[0].pauseAfterMs).toBeCloseTo(PAUSE_TABLE.comma, 5);
    expect(e.words[1].pauseAfterMs).toBe(0);
  });

  it("gives a paragraph break the full landing pause", () => {
    const e = estimate("Prima parte.\n\nA doua parte.");
    const boundary = e.words.find((w) => w.pauseKind === "paragraph");
    expect(boundary).toBeDefined();
    expect(boundary!.pauseAfterMs).toBeCloseTo(PAUSE_TABLE.paragraph, 5);
  });

  it("does not stack a paragraph pause on top of the sentence pause", () => {
    // "parte." already buys 400ms; the paragraph tops it up to 800, not 1200.
    const e = estimate("Prima parte.\n\nA doua.");
    const boundary = e.words.find((w) => w.pauseKind === "paragraph")!;
    expect(boundary.pauseAfterMs).toBeCloseTo(PAUSE_TABLE.paragraph, 5);
  });

  it("honours an explicit [pauză] marker without emitting a word for it", () => {
    const plain = estimate("Te iubesc.");
    const withBeat = estimate("Te iubesc. [pauză]");
    expect(withBeat.wordCount).toBe(plain.wordCount);
    expect(withBeat.totalMs).toBeCloseTo(plain.totalMs + PAUSE_TABLE.explicit, 5);
  });

  it("counts a numeral as its spoken length", () => {
    const digits = estimate("2026");
    const words = estimate("două mii douăzeci și șase");
    expect(digits.syllables).toBe(words.syllables);
  });

  it("scales inversely with tempo", () => {
    const base = estimate("Dragii mei, vă mulțumesc.", { tempo: 1 });
    const fast = estimate("Dragii mei, vă mulțumesc.", { tempo: 2 });
    expect(fast.totalMs).toBeCloseTo(base.totalMs / 2, 5);
  });

  it("runs slower on the solemn profile than the energetic one", () => {
    const text = "Astăzi începe o poveste nouă.";
    const slow = estimate(text, { profile: "rar" }).totalMs;
    const quick = estimate(text, { profile: "alert" }).totalMs;
    expect(slow).toBeGreaterThan(quick);
  });

  it("delivers a realistic wedding speech at a defensible rate", () => {
    // Asserting a raw second-count would just re-state the constant. What is
    // worth pinning is the *rate* the engine implies on natural Romanian:
    // overall syllables/sec including pauses, which published figures put
    // between roughly 3.5 and 5 for read and spoken Romanian.
    const text = `
      Dragii mei, astăzi nu sunt aici ca să țin un discurs.
      Sunt aici pentru că acum șapte ani, într-o seară de octombrie,
      Ana m-a sunat și mi-a spus că a cunoscut pe cineva.
      Nu mi-a spus cum îl cheamă. Mi-a spus doar că a râs de trei ori
      în primele cinci minute, ceea ce, pentru cine o cunoaște pe Ana,
      este un record absolut.
      De atunci am văzut cum se construiește ceva greu de explicat
      în cuvinte, dar ușor de recunoscut când îl vezi.
      Vă doresc să râdeți la fel de des și peste treizeci de ani.
    `;
    const e = estimate(text);
    const syllablesPerSecond = e.syllables / (e.totalMs / 1000);
    expect(syllablesPerSecond).toBeGreaterThan(3.5);
    expect(syllablesPerSecond).toBeLessThan(5);

    // Pauses should be a real share of the wall clock, not a rounding error.
    const pauseShare = e.pauseMs / e.totalMs;
    expect(pauseShare).toBeGreaterThan(0.05);
    expect(pauseShare).toBeLessThan(0.3);
  });

  it("uses a defensible speaking rate", () => {
    // Sanity-check the calibrated constant against the syllable rate it
    // implies: Romanian oratory sits roughly between 3.5 and 6 syllables/sec.
    for (const profile of Object.values(DELIVERY_PROFILES)) {
      const syllablesPerSecond = 1000 / profile.msPerSyllable;
      expect(syllablesPerSecond).toBeGreaterThan(3.5);
      expect(syllablesPerSecond).toBeLessThan(6);
    }
  });
});

describe("formatting", () => {
  it("formats a duration as minutes and seconds", () => {
    expect(formatDuration(0)).toBe("0:00");
    expect(formatDuration(65)).toBe("1:05");
    expect(formatDuration(300)).toBe("5:00");
  });

  it("formats the gap against a target", () => {
    expect(formatDelta(300, 300)).toBe("exact");
    expect(formatDelta(305, 300)).toBe("+5s");
    expect(formatDelta(292, 300)).toBe("-8s");
  });
});
