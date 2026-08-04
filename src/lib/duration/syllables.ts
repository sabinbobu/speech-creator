/**
 * Romanian syllable counting.
 *
 * Syllables, not words, are the unit of speaking time. Word counts lie badly in
 * Romanian because word length varies so much ("azi" vs "nemaipomenit"), and
 * WPM-based teleprompters inherit that error directly.
 *
 * This is a rule-based counter, not a lexicon. It resolves vowel groups by
 * greedy longest-match against the triphthong and diphthong inventories, then
 * applies the non-syllabic final "-i" rule. Measured against a hand-checked
 * word list it sits around 95% exact (see tests/syllables.test.ts); the
 * residual error is dominated by hiatus that genuinely needs morphology to
 * resolve ("pri-e-teni" vs "prie-teni"), and it washes out across a full
 * speech rather than accumulating.
 */

import { expandNumbers } from "./numbers";

const VOWELS = new Set(["a", "ă", "â", "e", "i", "î", "o", "u", "y"]);

/** Vowel groups that carry a single syllable nucleus. */
const TRIPHTHONGS = new Set([
  "eai",
  "eau",
  "eoa",
  "iai",
  "iau",
  "iei",
  "ieu",
  "ioa",
  "iou",
  "oai",
  "uai",
  "uau",
]);

const DIPHTHONGS = new Set([
  // rising
  "ea",
  "eo",
  "ia",
  "ie",
  "io",
  "iu",
  "oa",
  "ua",
  "uă",
  // falling
  "ai",
  "au",
  "ăi",
  "ău",
  "âi",
  "âu",
  "ei",
  "eu",
  "ii",
  "îi",
  "îu",
  "oi",
  "ou",
  "ui",
]);

/**
 * Morphological hiatus rules.
 *
 * Inherited Romanian words glide ("trea-bă", "sea-ră"); Latinate and prefixed
 * ones open into hiatus at the morpheme seam ("cre-a-ție", "re-a-li-ta-te",
 * "te-a-tru"). The vowel inventory cannot tell those apart — the seam can.
 *
 * Group 1 of each pattern is the part *before* the forced syllable boundary.
 * `minLength` protects short inherited words that share the same letters:
 * "deal" and "rea" must not be split the way "ideal" and "realitate" are.
 */
interface HiatusRule {
  re: RegExp;
  minLength: number;
}

const HIATUS_RULES: HiatusRule[] = [
  // Productive prefixes followed by a vowel-initial stem.
  { re: /^(re)[aăâeiouî]/, minLength: 7 },
  { re: /^(de)[aăâeiouî]/, minLength: 7 },
  { re: /^(pre)[aăâeiou]/, minLength: 8 },
  { re: /^(co)[aăâeiou]/, minLength: 7 },
  { re: /^(pro)[aăâeiou]/, minLength: 8 },
  { re: /^(ne)[aăâeiou]/, minLength: 7 },
  // Latinate stems and suffixes.
  { re: /(pri)(?=et)/, minLength: 6 },
  { re: /(cre)(?=a[țt])/, minLength: 6 },
  { re: /(te)(?=atr)/, minLength: 6 },
  { re: /(de)(?=al)/, minLength: 5 },
  { re: /(i)(?=ad[ăe])/, minLength: 7 },
  { re: /(u)(?=arie)/, minLength: 8 },
  { re: /(i)(?=et[ăa]t)/, minLength: 8 },
  { re: /(i)(?=os[iu]tate)/, minLength: 9 },
];

/**
 * Words whose syllabification no rule captures cleanly. Kept deliberately tiny
 * — a lexicon that grows to paper over the rules stops generalising.
 */
const OVERRIDES = new Map<string, number>([
  ["fiica", 2],
  ["fiice", 2],
  ["fiicei", 2],
  ["fiicele", 3],
  // "a-ici": the initial "ai" is hiatus, not a diphthong, and the final "-i"
  // rule then strips a second nucleus. Too frequent a word to get wrong.
  ["aici", 2],
]);

/** Character offsets where a syllable boundary is forced. */
function forcedBoundaries(word: string): Set<number> {
  const boundaries = new Set<number>();
  for (const { re, minLength } of HIATUS_RULES) {
    if (word.length < minLength) continue;
    const match = word.match(re);
    if (match && match.index !== undefined && match[1]) {
      boundaries.add(match.index + match[1].length);
    }
  }
  return boundaries;
}

/** Normalise legacy cedilla codepoints and strip anything that is not a letter. */
export function normalizeWord(word: string): string {
  return word
    .toLowerCase()
    .replace(/ş/g, "ș")
    .replace(/ţ/g, "ț")
    .replace(/[^a-zăâîșțy]/g, "");
}

function isVowel(ch: string): boolean {
  return VOWELS.has(ch);
}

/**
 * Pairs that fuse into one nucleus only at the end of a word, and open into
 * hiatus anywhere else. This one distinction fixes a large share of the errors:
 * "co-pii" vs "vi-i-tor", "me-reu" vs "îm-pre-u-nă".
 */
const FINAL_ONLY_DIPHTHONGS = new Set(["ii", "eu"]);

/**
 * Number of syllable nuclei inside one maximal run of vowels.
 *
 * `runEnd` is the index just past the run within the whole word, so the
 * position-sensitive rules can tell word-final clusters from medial ones.
 */
function nucleiInVowelRun(
  run: string,
  runStart: number,
  wordLength: number,
): number {
  // Word-final "-ie"/"-ia" after a consonant is hiatus: "fa-mi-li-e",
  // "e-mo-ți-e", "Ro-mâ-ni-a". Word-initial "ie-" is a genuine diphthong
  // ("ieri"), hence the start check; and a longer run like "eia" in "che-ia"
  // never reaches here, so that stays fused.
  if ((run === "ie" || run === "ia") && runStart > 0 && runStart + 2 === wordLength) {
    return 2;
  }

  let count = 0;
  let i = 0;
  while (i < run.length) {
    const three = run.slice(i, i + 3);
    if (i + 3 <= run.length && TRIPHTHONGS.has(three)) {
      count += 1;
      i += 3;
      continue;
    }

    const two = run.slice(i, i + 2);
    if (i + 2 <= run.length && DIPHTHONGS.has(two)) {
      const endsWord = runStart + i + 2 === wordLength;
      if (FINAL_ONLY_DIPHTHONGS.has(two) && !endsWord) {
        // Hiatus: fall through and consume a single vowel.
        count += 1;
        i += 1;
        continue;
      }
      count += 1;
      i += 2;
      continue;
    }

    count += 1;
    i += 1;
  }
  return count;
}

/**
 * Count syllables in a single word. Digits are expanded to their spoken form
 * first, so `countSyllables("2026")` measures the spoken numeral.
 */
export function countSyllables(rawWord: string): number {
  const expanded = expandNumbers(rawWord);

  // Number expansion can produce several words; sum them.
  if (/\s/.test(expanded.trim())) {
    return expanded
      .trim()
      .split(/\s+/)
      .reduce((sum, part) => sum + countSyllables(part), 0);
  }

  const word = normalizeWord(expanded);
  if (word.length === 0) return 0;

  const override = OVERRIDES.get(word);
  if (override !== undefined) return override;

  const boundaries = forcedBoundaries(word);

  /**
   * Count a vowel run, splitting it first at any forced morpheme boundary.
   * Splitting before counting keeps the two mechanisms from double-counting:
   * each sub-run is resolved on its own.
   */
  const countRun = (run: string, start: number): number => {
    const cuts = [start];
    for (let i = start + 1; i < start + run.length; i += 1) {
      if (boundaries.has(i)) cuts.push(i);
    }
    cuts.push(start + run.length);

    let total = 0;
    for (let c = 0; c < cuts.length - 1; c += 1) {
      const from = cuts[c];
      const to = cuts[c + 1];
      total += nucleiInVowelRun(
        run.slice(from - start, to - start),
        from,
        word.length,
      );
    }
    return total;
  };

  let syllables = 0;
  let run = "";
  let runStart = 0;
  for (let i = 0; i < word.length; i += 1) {
    const ch = word[i];
    if (isVowel(ch)) {
      if (run.length === 0) runStart = i;
      run += ch;
    } else if (run.length > 0) {
      syllables += countRun(run, runStart);
      run = "";
    }
  }
  if (run.length > 0) {
    syllables += countRun(run, runStart);
  }

  // Non-syllabic final "-i": the plural / 2nd-person marker in "lupi",
  // "oameni", "mari" is a whispered offglide, not a syllable. A final "ii"
  // ("copii") is a real nucleus and is left alone.
  if (
    syllables > 1 &&
    word.endsWith("i") &&
    !word.endsWith("ii") &&
    word.length >= 2 &&
    !isVowel(word[word.length - 2])
  ) {
    syllables -= 1;
  }

  return Math.max(1, syllables);
}

/** Total syllables across a stretch of text. */
export function countSyllablesInText(text: string): number {
  return text
    .trim()
    .split(/\s+/)
    .filter(Boolean)
    .reduce((sum, token) => sum + countSyllables(token), 0);
}
