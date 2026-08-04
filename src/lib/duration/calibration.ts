/**
 * Calibration constants for the duration engine.
 *
 * `msPerSyllable` is the one number that decides whether the whole product
 * works. It is deliberately isolated here so it can be re-fit from real
 * stopwatch data without touching engine logic — run `npm run calibrate`
 * after recording yourself reading the corpus in `eval/corpus.ts`.
 *
 * The shipped defaults are literature-derived starting points for Romanian
 * oratory (roughly 4.1 / 4.8 / 5.5 syllables per second), NOT values fitted to
 * human recordings. Treat them as a prior to be replaced, not as a measured
 * result. See README "Calibration status".
 */

export interface DeliveryProfile {
  id: DeliveryProfileId;
  label: string;
  /** Milliseconds of articulation per syllable. */
  msPerSyllable: number;
  /** Multiplier applied to every punctuation pause. */
  pauseScale: number;
}

export type DeliveryProfileId = "rar" | "normal" | "alert";

export const DELIVERY_PROFILES: Record<DeliveryProfileId, DeliveryProfile> = {
  rar: {
    id: "rar",
    label: "Rar — solemn, emoționant",
    msPerSyllable: 245,
    pauseScale: 1.15,
  },
  normal: {
    id: "normal",
    label: "Normal — conversațional",
    msPerSyllable: 210,
    pauseScale: 1.0,
  },
  alert: {
    id: "alert",
    label: "Alert — energic, pitch",
    msPerSyllable: 182,
    pauseScale: 0.85,
  },
};

/**
 * Fixed cost per word beyond its syllables: onset/offset articulation and the
 * micro-boundary between words. Small, but across 700 words it is ~13 seconds.
 */
export const WORD_OVERHEAD_MS = 18;

export const DEFAULT_PROFILE_ID: DeliveryProfileId = "normal";

export function resolveProfile(
  id: DeliveryProfileId = DEFAULT_PROFILE_ID,
): DeliveryProfile {
  return DELIVERY_PROFILES[id] ?? DELIVERY_PROFILES[DEFAULT_PROFILE_ID];
}
