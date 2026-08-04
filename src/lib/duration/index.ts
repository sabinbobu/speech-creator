export {
  DELIVERY_PROFILES,
  DEFAULT_PROFILE_ID,
  WORD_OVERHEAD_MS,
  resolveProfile,
} from "./calibration";
export type { DeliveryProfile, DeliveryProfileId } from "./calibration";

export { PAUSE_TABLE, pauseForPunctuation } from "./pauses";
export type { PauseKind } from "./pauses";

export { countSyllables, countSyllablesInText, normalizeWord } from "./syllables";
export { numberToRomanian, expandNumbers } from "./numbers";

export {
  estimate,
  estimateSeconds,
  approximateWordsForSeconds,
  formatDuration,
  formatDelta,
  EMPTY_ESTIMATE,
} from "./estimate";
export type {
  DurationEstimate,
  EstimateOptions,
  WordTiming,
} from "./estimate";
