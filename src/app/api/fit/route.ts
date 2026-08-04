import { NextResponse } from "next/server";
import { z } from "zod";
import { fitToTarget } from "@/lib/script/fit";
import { estimateScript } from "@/lib/script/estimate";
import type { Script } from "@/lib/script/types";
import { MissingApiKeyError, RefusedError, rewriteSection } from "@/lib/llm";

export const runtime = "nodejs";
export const maxDuration = 300;

const SectionSchema = z.object({
  id: z.string(),
  title: z.string(),
  kind: z.enum([
    "deschidere",
    "poveste",
    "mesaj",
    "umor",
    "multumiri",
    "inchidere",
    "liber",
  ]),
  text: z.string(),
  locked: z.boolean(),
  weight: z.number(),
});

const ScriptSchema = z.object({
  id: z.string(),
  title: z.string(),
  occasion: z.enum(["nunta", "dezbatere", "prezentare"]),
  targetSeconds: z.number().int().min(30).max(1800),
  profile: z.enum(["rar", "normal", "alert"]),
  sections: z.array(SectionSchema).min(1),
  createdAt: z.string(),
  updatedAt: z.string(),
  intake: z.record(z.string(), z.string()),
});

const BodySchema = z.object({
  script: ScriptSchema,
  /** Bias correction from the previous iteration, so the loop stays continuous. */
  gain: z.number().min(0.1).max(5).optional(),
  toleranceSeconds: z.number().min(1).max(60).optional(),
});

/**
 * Runs a single pass of the fit loop: estimate, decide which unlocked sections
 * need to move, rewrite only those. The client calls this repeatedly (up to
 * three times, per the plan) and shows progress between passes.
 */
export async function POST(request: Request) {
  let body: unknown;
  try {
    body = await request.json();
  } catch {
    return NextResponse.json({ error: "Corp de cerere invalid." }, { status: 400 });
  }

  const parsed = BodySchema.safeParse(body);
  if (!parsed.success) {
    return NextResponse.json(
      { error: "Date invalide.", details: parsed.error.issues },
      { status: 400 },
    );
  }

  const script = parsed.data.script as Script;

  try {
    const result = await fitToTarget(script, {
      rewriter: rewriteSection,
      maxIterations: 1,
      initialGain: parsed.data.gain,
      toleranceSeconds: parsed.data.toleranceSeconds,
    });

    return NextResponse.json({
      script: result.script,
      gain: result.gain,
      withinTolerance: result.withinTolerance,
      finalSeconds: result.finalSeconds,
      stoppedBecause: result.stoppedBecause,
      iteration: result.iterations[0] ?? null,
      estimate: estimateScript(result.script),
    });
  } catch (error) {
    if (error instanceof MissingApiKeyError) {
      return NextResponse.json({ error: error.message }, { status: 503 });
    }
    if (error instanceof RefusedError) {
      return NextResponse.json({ error: error.message }, { status: 422 });
    }
    const message =
      error instanceof Error ? error.message : "Eroare necunoscută la ajustare.";
    return NextResponse.json({ error: message }, { status: 500 });
  }
}
