/**
 * Model bench: which OpenAI model should Cadență use?
 *
 * Runs the real generation task — same prompts, same strict schema, same
 * Romanian intake — against each candidate and measures the three things that
 * decide the product:
 *
 *   1. does strict structured output work at all
 *   2. how close the draft lands to the requested duration (fewer fit passes =
 *      cheaper and faster, and Vercel Hobby caps functions at 60s)
 *   3. latency
 *
 * Quality of the Romanian still needs a human eye, so the first section of each
 * model's output is printed for reading.
 *
 *   set -a; . ./.env.local; set +a && npx tsx eval/model-bench.ts
 */

import { estimateSeconds, formatDuration } from "../src/lib/duration";
import { generateSections } from "../src/lib/llm";
import { getTemplate } from "../src/lib/templates";

const CANDIDATES = process.env.BENCH_MODELS?.split(",") ?? [
  "gpt-5.6-sol",
  "gpt-5.5",
  "gpt-5.4",
  "gpt-5.2",
  "gpt-5.1",
  "gpt-4.1",
  "gpt-4o",
];

const TARGET_SECONDS = 180;
const PROFILE = "rar" as const;

const INTAKE = {
  cine: "Ana și Mihai",
  relatie: "Sunt sora Anei. Am crescut în aceeași cameră 18 ani.",
  moment:
    "În octombrie 2019, la 2 noaptea, Ana m-a sunat din gară la Cluj să-mi spună că a cunoscut pe cineva care râde la aceleași glume proaste ca ea.",
  gluma:
    "Mihai zice „doar cinci minute” de fiecare dată când pleacă undeva. Nu a fost niciodată cinci minute.",
  admiri:
    "Se ceartă seara și se împacă tot seara. Nu i-am văzut niciodată plecând supărați la culcare.",
  final: "Recunoștință",
};

interface Row {
  model: string;
  ok: boolean;
  seconds?: number;
  errorPct?: number;
  words?: number;
  latencyMs: number;
  note: string;
  sample?: string;
}

async function bench(modelId: string): Promise<Row> {
  const template = getTemplate("nunta");
  const totalWeight = template.sections.reduce((s, x) => s + x.weight, 0);
  const sections = template.sections.map((s, i) => ({
    id: `s${i}`,
    title: s.title,
    brief: s.brief,
    seconds: (TARGET_SECONDS * s.weight) / totalWeight,
  }));

  process.env.OPENAI_MODEL = modelId;
  const started = Date.now();

  try {
    const written = await generateSections({
      occasion: "nunta",
      targetSeconds: TARGET_SECONDS,
      profile: PROFILE,
      intake: INTAKE,
      sections,
    });

    const latencyMs = Date.now() - started;
    const text = written.map((w) => w.text.trim()).join("\n\n");
    const seconds = estimateSeconds(text, { profile: PROFILE });
    const words = text.split(/\s+/).filter(Boolean).length;

    return {
      model: modelId,
      ok: true,
      seconds,
      errorPct: ((seconds - TARGET_SECONDS) / TARGET_SECONDS) * 100,
      words,
      latencyMs,
      note: `${written.length} secțiuni`,
      sample: written[0]?.text.trim().slice(0, 300),
    };
  } catch (error) {
    return {
      model: modelId,
      ok: false,
      latencyMs: Date.now() - started,
      note:
        error instanceof Error
          ? error.message.replace(/\s+/g, " ").slice(0, 90)
          : "eroare necunoscută",
    };
  }
}

async function main() {
  console.log(`\n  Model bench — discurs de nuntă, țintă ${formatDuration(TARGET_SECONDS)}\n`);

  const rows: Row[] = [];
  for (const candidate of CANDIDATES) {
    process.stdout.write(`  ${candidate.padEnd(16)} … `);
    const row = await bench(candidate);
    rows.push(row);
    console.log(
      row.ok
        ? `${formatDuration(row.seconds!)} (${row.errorPct! > 0 ? "+" : ""}${row.errorPct!.toFixed(1)}%)  ${(row.latencyMs / 1000).toFixed(1)}s`
        : `EȘEC — ${row.note}`,
    );
  }

  console.log("\n  ─────────────────────────────────────────────────────────────");
  console.log("  model             durată    eroare    cuvinte   latență");
  console.log("  ─────────────────────────────────────────────────────────────");
  for (const r of rows) {
    if (!r.ok) {
      console.log(`  ${r.model.padEnd(16)}  —         —         —         ${(r.latencyMs / 1000).toFixed(1)}s   ${r.note}`);
      continue;
    }
    console.log(
      `  ${r.model.padEnd(16)}  ${formatDuration(r.seconds!).padStart(6)}    ` +
        `${(r.errorPct! > 0 ? "+" : "") + r.errorPct!.toFixed(1)}%`.padStart(8) +
        `   ${String(r.words).padStart(5)}     ${(r.latencyMs / 1000).toFixed(1)}s`,
    );
  }

  const working = rows.filter((r) => r.ok);
  if (working.length > 0) {
    const best = [...working].sort(
      (a, b) => Math.abs(a.errorPct!) - Math.abs(b.errorPct!),
    )[0];
    const fastest = [...working].sort((a, b) => a.latencyMs - b.latencyMs)[0];
    console.log(
      `\n  cel mai aproape de țintă: ${best.model} (${best.errorPct! > 0 ? "+" : ""}${best.errorPct!.toFixed(1)}%)`,
    );
    console.log(`  cel mai rapid:            ${fastest.model} (${(fastest.latencyMs / 1000).toFixed(1)}s)`);
  }

  console.log("\n  ── mostre (deschiderea, pentru citit) ──");
  for (const r of working) {
    console.log(`\n  [${r.model}]\n  ${r.sample?.replace(/\n/g, "\n  ")}`);
  }
  console.log("");
}

main().catch((error) => {
  console.error(error);
  process.exit(1);
});
