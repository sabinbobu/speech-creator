/**
 * Punctuation pause table.
 *
 * Pauses are not decoration — in a 5 minute speech they account for roughly a
 * fifth of the wall-clock time. Ignoring them is the single biggest source of
 * error in naive WPM estimators.
 *
 * Values are milliseconds at normal delivery, taken from the plan's baseline
 * (comma ~150, period ~400, paragraph ~800) and extended to the rest of the
 * punctuation a speech actually uses.
 */

export const PAUSE_TABLE = {
  comma: 150,
  semicolon: 250,
  colon: 250,
  dash: 200,
  period: 400,
  question: 450,
  exclamation: 450,
  ellipsis: 500,
  paragraph: 800,
  /** Explicit beat the writer inserted with the `[pauză]` marker. */
  explicit: 700,
} as const;

export type PauseKind = keyof typeof PAUSE_TABLE;

/**
 * Map the punctuation trailing a token to a pause. Returns `null` when the
 * token runs straight into the next one.
 */
export function pauseForPunctuation(trailing: string): {
  kind: PauseKind;
  ms: number;
} | null {
  if (!trailing) return null;

  // Longest / strongest marker wins: "?!" should read as an exclamation, and
  // "..." must not be mistaken for three periods.
  if (/\.{3}|…/.test(trailing)) {
    return { kind: "ellipsis", ms: PAUSE_TABLE.ellipsis };
  }
  if (trailing.includes("!")) {
    return { kind: "exclamation", ms: PAUSE_TABLE.exclamation };
  }
  if (trailing.includes("?")) {
    return { kind: "question", ms: PAUSE_TABLE.question };
  }
  if (trailing.includes(".")) {
    return { kind: "period", ms: PAUSE_TABLE.period };
  }
  if (trailing.includes(";")) {
    return { kind: "semicolon", ms: PAUSE_TABLE.semicolon };
  }
  if (trailing.includes(":")) {
    return { kind: "colon", ms: PAUSE_TABLE.colon };
  }
  if (trailing.includes(",")) {
    return { kind: "comma", ms: PAUSE_TABLE.comma };
  }
  if (/[—–-]/.test(trailing)) {
    return { kind: "dash", ms: PAUSE_TABLE.dash };
  }
  return null;
}
