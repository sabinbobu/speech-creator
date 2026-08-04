import { estimateSeconds } from "../src/lib/duration";
import type { DeliveryProfileId } from "../src/lib/duration";

/**
 * A synthetic stand-in for the language model.
 *
 * It produces Romanian-shaped text of a requested length, but misses that
 * length the way a real model does: with a consistent directional bias plus
 * per-call noise. That is what the fit loop actually has to survive, and it
 * lets the eval run offline and deterministically instead of costing a hundred
 * live model calls per run.
 */

/** mulberry32 — small, fast, and reproducible from a seed. */
export function rng(seed: number): () => number {
  let a = seed >>> 0;
  return () => {
    a = (a + 0x6d2b79f5) >>> 0;
    let t = a;
    t = Math.imul(t ^ (t >>> 15), t | 1);
    t ^= t + Math.imul(t ^ (t >>> 7), t | 61);
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

const VOCAB = [
  "astăzi", "aici", "împreună", "familia", "prietenii", "povestea", "începe",
  "atunci", "când", "ne-am", "cunoscut", "toată", "lumea", "râdea", "nimeni",
  "nu", "știa", "ce", "urmează", "au", "trecut", "șapte", "ani", "de", "seara",
  "aceea", "din", "gară", "și", "încă", "vorbim", "despre", "ea", "cu", "aceeași",
  "bucurie", "vă", "doresc", "să", "aveți", "răbdare", "unul", "cu", "celălalt",
  "în", "zilele", "bune", "dar", "mai", "ales", "în", "cele", "grele",
];

const PUNCT = [",", ".", "", "", "", ".", "", ","];

/**
 * Build text that lands as close as possible to `seconds` under the given
 * profile, by appending words until the estimate crosses the goal.
 */
export function textOfSeconds(
  seconds: number,
  profile: DeliveryProfileId,
  random: () => number,
): string {
  if (seconds <= 0) return "";
  const words: string[] = [];
  let guard = 0;

  while (guard < 20000) {
    const word = VOCAB[Math.floor(random() * VOCAB.length)];
    const punct = PUNCT[Math.floor(random() * PUNCT.length)];
    words.push(word + punct);
    guard += 1;

    // Checking every word is exact but slow; check in small batches and then
    // trim back, which lands within a word of the goal.
    if (words.length % 5 === 0) {
      if (estimateSeconds(words.join(" "), { profile }) >= seconds) break;
    }
  }

  while (
    words.length > 1 &&
    estimateSeconds(words.slice(0, -1).join(" "), { profile }) >= seconds
  ) {
    words.pop();
  }

  return words.join(" ");
}

export interface SyntheticWriterOptions {
  bias: number;
  noise: number;
  profile: DeliveryProfileId;
  seed: number;
}

/** A rewriter that hits `requested * bias * (1 +/- noise)`. */
export function syntheticWriter(options: SyntheticWriterOptions) {
  const random = rng(options.seed);
  return async (requestedSeconds: number): Promise<string> => {
    const jitter = 1 + (random() * 2 - 1) * options.noise;
    const actual = Math.max(1, requestedSeconds * options.bias * jitter);
    return textOfSeconds(actual, options.profile, random);
  };
}
