/**
 * Stopwatch calibration for the duration engine.
 *
 * This is the step that turns the engine from plausible into correct. Nothing
 * else in the product can be trusted until it has been run against a real
 * human voice, because `msPerSyllable` is a claim about how fast people
 * actually talk, and that cannot be derived from first principles.
 *
 *   npm run calibrate
 *
 * For each text: press enter, read it aloud at delivery pace, press enter
 * again. The tool times you, fits the constant, and reports the residual error
 * per text so you can see whether one reading was an outlier.
 */

import { createInterface } from "node:readline/promises";
import { stdin, stdout } from "node:process";
import { writeFileSync, mkdirSync } from "node:fs";
import {
  DELIVERY_PROFILES,
  WORD_OVERHEAD_MS,
  estimate,
  formatDuration,
} from "../src/lib/duration";
import { CALIBRATION_CORPUS } from "./corpus";

const PROFILE = "normal" as const;

interface Reading {
  id: string;
  label: string;
  syllables: number;
  words: number;
  pauseMs: number;
  measuredSeconds: number;
  /** ms per syllable implied by this single reading. */
  implied: number;
}

function impliedMsPerSyllable(
  measuredSeconds: number,
  syllables: number,
  words: number,
  pauseMs: number,
): number {
  // measured = syllables * X + words * overhead + pauses
  // Pauses and per-word overhead are independent of X, so subtract them first.
  const speakingMs = measuredSeconds * 1000 - words * WORD_OVERHEAD_MS - pauseMs;
  return speakingMs / syllables;
}

async function main() {
  const rl = createInterface({ input: stdin, output: stdout });

  console.log("\n  Calibrare motor de durată");
  console.log("  ─────────────────────────────────────────────");
  console.log("  Citește fiecare text cu voce tare, în ritmul în care l-ai");
  console.log("  rosti în fața unei săli. Enter la început, Enter la final.");
  console.log(`  Profil calibrat: ${DELIVERY_PROFILES[PROFILE].label}`);
  console.log(`  Valoare curentă: ${DELIVERY_PROFILES[PROFILE].msPerSyllable} ms/silabă\n`);

  const readings: Reading[] = [];

  for (const item of CALIBRATION_CORPUS) {
    const e = estimate(item.text, { profile: PROFILE });

    console.log("  ─────────────────────────────────────────────");
    console.log(`  ${item.label}`);
    console.log(`  ${e.wordCount} cuvinte · ${e.syllables} silabe`);
    console.log(`  estimare curentă: ${formatDuration(e.totalMs / 1000)}\n`);
    console.log(item.text);
    console.log("");

    await rl.question("  Enter când începi să citești… ");
    const start = Date.now();
    await rl.question("  Enter când ai terminat… ");
    const measuredSeconds = (Date.now() - start) / 1000;

    if (measuredSeconds < 2) {
      console.log("  (prea scurt ca să fie o citire reală — sar peste)\n");
      continue;
    }

    const implied = impliedMsPerSyllable(
      measuredSeconds,
      e.syllables,
      e.wordCount,
      e.pauseMs,
    );

    readings.push({
      id: item.id,
      label: item.label,
      syllables: e.syllables,
      words: e.wordCount,
      pauseMs: e.pauseMs,
      measuredSeconds,
      implied,
    });

    console.log(
      `  măsurat ${formatDuration(measuredSeconds)} · ` +
        `implică ${implied.toFixed(1)} ms/silabă\n`,
    );
  }

  rl.close();

  if (readings.length === 0) {
    console.log("  Nicio citire înregistrată.\n");
    return;
  }

  // Weight by syllable count: a long reading carries more information about
  // the rate than a fifteen-second one.
  const totalSyllables = readings.reduce((s, r) => s + r.syllables, 0);
  const fitted =
    readings.reduce((s, r) => s + r.implied * r.syllables, 0) / totalSyllables;

  console.log("  ─────────────────────────────────────────────");
  console.log("  Rezultat\n");
  console.log("  text                        măsurat   implicat   eroare cu noua constantă");

  let worstRelative = 0;
  for (const r of readings) {
    const predictedMs =
      r.syllables * fitted + r.words * WORD_OVERHEAD_MS + r.pauseMs;
    const relative = (predictedMs / 1000 - r.measuredSeconds) / r.measuredSeconds;
    worstRelative = Math.max(worstRelative, Math.abs(relative));
    console.log(
      `  ${r.label.padEnd(26).slice(0, 26)}  ` +
        `${formatDuration(r.measuredSeconds).padStart(6)}   ` +
        `${r.implied.toFixed(0).padStart(6)} ms   ` +
        `${(relative * 100).toFixed(1).padStart(6)}%`,
    );
  }

  console.log("");
  console.log(`  constantă potrivită:  ${fitted.toFixed(1)} ms/silabă`);
  console.log(`  actuală în cod:       ${DELIVERY_PROFILES[PROFILE].msPerSyllable} ms/silabă`);
  console.log(`  rată implicată:       ${(1000 / fitted).toFixed(2)} silabe/secundă`);
  console.log(`  eroare maximă:        ${(worstRelative * 100).toFixed(1)}%`);
  console.log("");

  if (worstRelative <= 0.05) {
    console.log("  ✓ Sub ±5% pe toate textele. Motorul e calibrat pe vocea ta.");
  } else {
    console.log("  ✗ Peste ±5% pe cel puțin un text. Cauze uzuale:");
    console.log("    - una dintre citiri a fost grăbită sau întreruptă");
    console.log("    - tabelul de pauze nu se potrivește cu felul tău de a vorbi");
    console.log("    Recitește textul cu eroarea cea mai mare și rulează din nou.");
  }

  console.log("");
  console.log("  Pentru a aplica: pune valoarea în msPerSyllable pentru profilul");
  console.log(`  „${PROFILE}" în src/lib/duration/calibration.ts`);
  console.log("");

  mkdirSync(new URL("./results/", import.meta.url), { recursive: true });
  writeFileSync(
    new URL("./results/calibration.json", import.meta.url),
    JSON.stringify(
      {
        profile: PROFILE,
        fittedMsPerSyllable: fitted,
        currentMsPerSyllable: DELIVERY_PROFILES[PROFILE].msPerSyllable,
        worstRelativeError: worstRelative,
        readings,
        measuredAt: new Date().toISOString(),
      },
      null,
      2,
    ),
  );
  console.log("  Salvat în eval/results/calibration.json\n");
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
