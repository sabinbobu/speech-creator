import type { DeliveryProfileId } from "../src/lib/duration";
import type { Occasion } from "../src/lib/script/types";

/**
 * 100 evaluation cases for the duration-constrained rewrite loop.
 *
 * Each case is a (occasion, target duration, first-draft error, writer bias,
 * writer noise) combination. The draft error is how far off the first draft
 * lands; the writer bias is how consistently the writer misses a length it is
 * asked for; the noise is per-rewrite jitter on top.
 *
 * The grid is deliberately hostile at the edges — 2.4x-too-long drafts, a
 * writer that lands 35% short every time — because a loop that only works on
 * easy cases isn't worth having.
 */

export interface EvalCase {
  id: string;
  occasion: Occasion;
  targetSeconds: number;
  profile: DeliveryProfileId;
  /** First draft lands at targetSeconds * draftFactor. */
  draftFactor: number;
  /** The writer returns requested * writerBias, before noise. */
  writerBias: number;
  /** Uniform jitter, +/- this fraction, applied per rewrite. */
  writerNoise: number;
  seed: number;
}

const OCCASIONS: Occasion[] = ["nunta", "dezbatere", "prezentare"];
const PROFILES: DeliveryProfileId[] = ["rar", "normal", "alert"];
const TARGETS = [120, 180, 240, 300, 420];
const DRAFT_FACTORS = [0.45, 0.7, 0.9, 1.15, 1.6, 2.4];
const WRITER_BIASES = [0.65, 0.8, 0.95, 1.1, 1.3];
const WRITER_NOISES = [0, 0.08, 0.18];

export const EVAL_CASES: EvalCase[] = Array.from({ length: 100 }, (_, i) => ({
  id: `case-${String(i + 1).padStart(3, "0")}`,
  occasion: OCCASIONS[i % OCCASIONS.length],
  targetSeconds: TARGETS[i % TARGETS.length],
  profile: PROFILES[(i + 1) % PROFILES.length],
  draftFactor: DRAFT_FACTORS[i % DRAFT_FACTORS.length],
  writerBias: WRITER_BIASES[i % WRITER_BIASES.length],
  writerNoise: WRITER_NOISES[i % WRITER_NOISES.length],
  seed: 1000 + i * 7919,
}));
