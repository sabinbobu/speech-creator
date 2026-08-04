import { NextResponse } from "next/server";
import { z } from "zod";
import { estimateScript } from "@/lib/script/estimate";
import { createId } from "@/lib/script/types";
import type { Script, Section } from "@/lib/script/types";
import { getTemplate, validateIntake } from "@/lib/templates";
import { MissingApiKeyError, RefusedError, generateSections } from "@/lib/llm";

export const runtime = "nodejs";
export const maxDuration = 300;

const BodySchema = z.object({
  occasion: z.enum(["nunta", "dezbatere", "prezentare"]),
  targetSeconds: z.number().int().min(30).max(1800),
  profile: z.enum(["rar", "normal", "alert"]),
  title: z.string().max(200).optional(),
  intake: z.record(z.string(), z.string()),
});

/**
 * First draft only. Fitting to the target duration is a separate endpoint so
 * each request stays short enough for a serverless function — see /api/fit.
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

  const { occasion, targetSeconds, profile, intake, title } = parsed.data;

  // The intake gate is a feature, not a formality: a vague intake produces a
  // speech about any couple rather than this one.
  const validation = validateIntake(occasion, intake);
  if (!validation.ok) {
    return NextResponse.json(
      {
        error: "Răspunsurile din intake sunt incomplete.",
        missing: validation.missing,
        tooShort: validation.tooShort,
      },
      { status: 422 },
    );
  }

  const template = getTemplate(occasion);
  const totalWeight = template.sections.reduce((sum, s) => sum + s.weight, 0);

  const planned = template.sections.map((s) => ({
    id: createId(),
    title: s.title,
    kind: s.kind,
    brief: s.brief,
    weight: s.weight,
    seconds: (targetSeconds * s.weight) / totalWeight,
  }));

  try {
    const written = await generateSections({
      occasion,
      targetSeconds,
      profile,
      intake,
      sections: planned.map((s) => ({
        id: s.id,
        title: s.title,
        brief: s.brief,
        seconds: s.seconds,
      })),
    });

    const byId = new Map(written.map((w) => [w.id, w.text]));

    const sections: Section[] = planned.map((s) => ({
      id: s.id,
      title: s.title,
      kind: s.kind,
      text: (byId.get(s.id) ?? "").trim(),
      locked: false,
      weight: s.weight,
    }));

    const now = new Date().toISOString();
    const script: Script = {
      id: createId(),
      title: title?.trim() || template.label,
      occasion,
      targetSeconds,
      profile,
      sections,
      createdAt: now,
      updatedAt: now,
      intake,
    };

    return NextResponse.json({ script, estimate: estimateScript(script) });
  } catch (error) {
    if (error instanceof MissingApiKeyError) {
      return NextResponse.json({ error: error.message }, { status: 503 });
    }
    if (error instanceof RefusedError) {
      return NextResponse.json({ error: error.message }, { status: 422 });
    }
    const message =
      error instanceof Error ? error.message : "Eroare necunoscută la generare.";
    return NextResponse.json({ error: message }, { status: 500 });
  }
}
