/**
 * The duration estimator.
 *
 * Deterministic, dependency-free, zero LLM. Given text it produces a timeline:
 * when every word starts, how long it is spoken for, and how much silence
 * follows it. The teleprompter consumes that timeline directly, which is why
 * the karaoke highlight tracks real speech instead of a fixed words-per-minute
 * crawl.
 */

import {
  DeliveryProfile,
  DeliveryProfileId,
  WORD_OVERHEAD_MS,
  resolveProfile,
} from "./calibration";
import { PauseKind, PAUSE_TABLE, pauseForPunctuation } from "./pauses";
import { countSyllables } from "./syllables";

export interface WordTiming {
  /** The token exactly as it appears in the script, punctuation included. */
  text: string;
  index: number;
  syllables: number;
  /** Milliseconds from the start of the estimated text. */
  startMs: number;
  /** Articulation time for this word. */
  durationMs: number;
  /** Silence following this word. */
  pauseAfterMs: number;
  pauseKind: PauseKind | null;
  paragraph: number;
}

export interface DurationEstimate {
  totalMs: number;
  /** Time spent articulating words. */
  speakingMs: number;
  /** Time spent in silence. */
  pauseMs: number;
  syllables: number;
  wordCount: number;
  words: WordTiming[];
}

export interface EstimateOptions {
  profile?: DeliveryProfileId | DeliveryProfile;
  /**
   * Live tempo multiplier. 1 is the calibrated rate, 1.2 is 20% faster.
   * Scales articulation and pauses alike.
   */
  tempo?: number;
}

/** Matches an explicit beat the writer asked for: `[pauză]`. */
const EXPLICIT_PAUSE = /^[[(](pauz[ăa]|beat)[\])]$/i;

const LEADING_PUNCT = /^[^\p{L}\p{N}]+/u;
const TRAILING_PUNCT = /[^\p{L}\p{N}]+$/u;

function toProfile(
  profile: EstimateOptions["profile"],
): DeliveryProfile {
  if (profile && typeof profile === "object") return profile;
  return resolveProfile(profile);
}

export const EMPTY_ESTIMATE: DurationEstimate = {
  totalMs: 0,
  speakingMs: 0,
  pauseMs: 0,
  syllables: 0,
  wordCount: 0,
  words: [],
};

/**
 * Build the full timeline for a stretch of text.
 *
 * Paragraph breaks are treated as the strongest pause available: a writer who
 * starts a new paragraph is asking the speaker to land the previous thought.
 */
export function estimate(
  text: string,
  options: EstimateOptions = {},
): DurationEstimate {
  const profile = toProfile(options.profile);
  const tempo = options.tempo && options.tempo > 0 ? options.tempo : 1;

  const msPerSyllable = profile.msPerSyllable / tempo;
  const wordOverhead = WORD_OVERHEAD_MS / tempo;
  const pauseFactor = profile.pauseScale / tempo;

  // A blank line marks a paragraph and earns the landing pause. A single
  // newline is just soft wrapping in the source and must not buy silence,
  // otherwise indented or wrapped text collects phantom pauses per line.
  const paragraphs = text
    .split(/\n[ \t]*\n\s*/)
    .map((p) => p.replace(/\s+/g, " ").trim())
    .filter((p) => p.length > 0);

  if (paragraphs.length === 0) return { ...EMPTY_ESTIMATE, words: [] };

  const words: WordTiming[] = [];
  let cursor = 0;
  let speakingMs = 0;
  let pauseMs = 0;
  let syllables = 0;

  paragraphs.forEach((paragraph, paragraphIndex) => {
    const tokens = paragraph.split(/\s+/).filter(Boolean);

    tokens.forEach((token) => {
      // An explicit pause marker is silence, not a word. Attach it to whatever
      // came before so the timeline stays a flat list of spoken words.
      if (EXPLICIT_PAUSE.test(token)) {
        const ms = PAUSE_TABLE.explicit * pauseFactor;
        const previous = words[words.length - 1];
        if (previous) {
          previous.pauseAfterMs += ms;
          previous.pauseKind = "explicit";
        }
        cursor += ms;
        pauseMs += ms;
        return;
      }

      const trailing = token.match(TRAILING_PUNCT)?.[0] ?? "";
      const core = token.replace(LEADING_PUNCT, "").replace(TRAILING_PUNCT, "");

      // Punctuation-only tokens (a stray dash) still buy a beat.
      if (core.length === 0) {
        const pause = pauseForPunctuation(token);
        if (pause) {
          const ms = pause.ms * pauseFactor;
          const previous = words[words.length - 1];
          if (previous) {
            previous.pauseAfterMs += ms;
            previous.pauseKind = pause.kind;
          }
          cursor += ms;
          pauseMs += ms;
        }
        return;
      }

      const wordSyllables = countSyllables(core);
      const durationMs = wordSyllables * msPerSyllable + wordOverhead;

      const pause = pauseForPunctuation(trailing);
      const pauseAfterMs = pause ? pause.ms * pauseFactor : 0;

      words.push({
        text: token,
        index: words.length,
        syllables: wordSyllables,
        startMs: cursor,
        durationMs,
        pauseAfterMs,
        pauseKind: pause?.kind ?? null,
        paragraph: paragraphIndex,
      });

      cursor += durationMs + pauseAfterMs;
      speakingMs += durationMs;
      pauseMs += pauseAfterMs;
      syllables += wordSyllables;
    });

    // Landing pause between paragraphs. The paragraph break replaces the
    // sentence pause rather than stacking on top of it.
    const isLast = paragraphIndex === paragraphs.length - 1;
    const previous = words[words.length - 1];
    if (!isLast && previous) {
      const target = PAUSE_TABLE.paragraph * pauseFactor;
      const extra = Math.max(0, target - previous.pauseAfterMs);
      previous.pauseAfterMs += extra;
      previous.pauseKind = "paragraph";
      cursor += extra;
      pauseMs += extra;
    }
  });

  return {
    totalMs: cursor,
    speakingMs,
    pauseMs,
    syllables,
    wordCount: words.length,
    words,
  };
}

/** Convenience wrapper when only the number matters. */
export function estimateSeconds(
  text: string,
  options: EstimateOptions = {},
): number {
  return estimate(text, options).totalMs / 1000;
}

/**
 * Roughly how many words fit in a given number of seconds.
 *
 * The generator has to give the model a length it can actually aim at — "write
 * 40 seconds" means nothing to a language model, "write about 95 words" does.
 *
 * When existing text is supplied the ratio is measured from it, which makes the
 * budget self-calibrating: a section dense with long words gets a smaller word
 * budget than one built from short clitics. Without a sample it falls back to
 * the profile's rate at a typical 1.7 syllables per word.
 */
export function approximateWordsForSeconds(
  seconds: number,
  options: EstimateOptions & { sample?: string } = {},
): number {
  const profile = toProfile(options.profile);
  const tempo = options.tempo && options.tempo > 0 ? options.tempo : 1;

  if (options.sample && options.sample.trim()) {
    const measured = estimate(options.sample, options);
    if (measured.wordCount > 0 && measured.totalMs > 0) {
      const wordsPerSecond = measured.wordCount / (measured.totalMs / 1000);
      return Math.max(1, Math.round(seconds * wordsPerSecond));
    }
  }

  const ASSUMED_SYLLABLES_PER_WORD = 1.7;
  const msPerWord =
    (ASSUMED_SYLLABLES_PER_WORD * profile.msPerSyllable + WORD_OVERHEAD_MS) /
    tempo;
  // Leave room for the punctuation pauses a natural sentence carries.
  const withPauses = msPerWord * 1.15;
  return Math.max(1, Math.round((seconds * 1000) / withPauses));
}

/** `305.4` -> `"5:05"`. */
export function formatDuration(seconds: number): string {
  const total = Math.max(0, Math.round(seconds));
  const minutes = Math.floor(total / 60);
  const secs = total % 60;
  return `${minutes}:${secs.toString().padStart(2, "0")}`;
}

/** `305.4` -> `"+5s"` against a 300s target. */
export function formatDelta(actualSeconds: number, targetSeconds: number): string {
  const delta = Math.round(actualSeconds - targetSeconds);
  if (delta === 0) return "exact";
  return `${delta > 0 ? "+" : ""}${delta}s`;
}
