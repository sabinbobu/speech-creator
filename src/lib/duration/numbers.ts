/**
 * Romanian numeral expansion.
 *
 * Numerals have to be spoken before they can be timed: "2026" is four
 * characters but eight syllables ("do-uă mii do-uă-zeci și șa-se"). Counting
 * syllables on the digits themselves would make every date and statistic in a
 * speech land short.
 */

const UNITS = [
  "zero",
  "unu",
  "doi",
  "trei",
  "patru",
  "cinci",
  "șase",
  "șapte",
  "opt",
  "nouă",
];

/** Feminine forms, used when counting "sute"/"mii"/"milioane". */
const UNITS_FEM = [
  "zero",
  "una",
  "două",
  "trei",
  "patru",
  "cinci",
  "șase",
  "șapte",
  "opt",
  "nouă",
];

const TEENS = [
  "zece",
  "unsprezece",
  "doisprezece",
  "treisprezece",
  "paisprezece",
  "cincisprezece",
  "șaisprezece",
  "șaptesprezece",
  "optsprezece",
  "nouăsprezece",
];

const TENS = [
  "",
  "",
  "douăzeci",
  "treizeci",
  "patruzeci",
  "cincizeci",
  "șaizeci",
  "șaptezeci",
  "optzeci",
  "nouăzeci",
];

function underHundred(n: number, feminine: boolean): string {
  if (n < 10) return feminine ? UNITS_FEM[n] : UNITS[n];
  if (n < 20) return TEENS[n - 10];
  const tens = Math.floor(n / 10);
  const rest = n % 10;
  if (rest === 0) return TENS[tens];
  return `${TENS[tens]} și ${feminine ? UNITS_FEM[rest] : UNITS[rest]}`;
}

function underThousand(n: number, feminine: boolean): string {
  if (n < 100) return underHundred(n, feminine);
  const hundreds = Math.floor(n / 100);
  const rest = n % 100;
  let head: string;
  if (hundreds === 1) head = "o sută";
  else head = `${UNITS_FEM[hundreds]} sute`;
  if (rest === 0) return head;
  return `${head} ${underHundred(rest, feminine)}`;
}

/**
 * Spell a non-negative integer in Romanian. Handles up to 999 999 999, which
 * comfortably covers anything that shows up in a speech.
 */
export function numberToRomanian(value: number, feminine = false): string {
  if (!Number.isFinite(value)) return "";
  const n = Math.floor(Math.abs(value));

  if (n === 0) return "zero";

  const parts: string[] = [];

  const millions = Math.floor(n / 1_000_000);
  const thousands = Math.floor((n % 1_000_000) / 1000);
  const rest = n % 1000;

  if (millions > 0) {
    parts.push(
      millions === 1 ? "un milion" : `${underThousand(millions, true)} milioane`,
    );
  }
  if (thousands > 0) {
    parts.push(
      thousands === 1 ? "o mie" : `${underThousand(thousands, true)} mii`,
    );
  }
  if (rest > 0) {
    parts.push(underThousand(rest, feminine));
  }

  return parts.join(" ");
}

/**
 * Replace every digit run in a token with its spoken Romanian form, so the
 * syllable counter sees words instead of digits. Decimal separators are read
 * as "virgulă", matching Romanian convention.
 */
export function expandNumbers(token: string): string {
  if (!/\d/.test(token)) return token;

  // Times such as "5:00" are read as "cinci zero zero" in a rehearsal context;
  // splitting on the colon keeps each part sane.
  return token.replace(/\d+(?:[.,]\d+)?/g, (match) => {
    const decimalMatch = match.match(/^(\d+)[.,](\d+)$/);
    if (decimalMatch) {
      const whole = numberToRomanian(Number(decimalMatch[1]));
      const fraction = numberToRomanian(Number(decimalMatch[2]));
      return `${whole} virgulă ${fraction}`;
    }
    return numberToRomanian(Number(match));
  });
}
