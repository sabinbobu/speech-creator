"use client";

import { Suspense, useMemo, useState } from "react";
import { useRouter, useSearchParams } from "next/navigation";
import { DELIVERY_PROFILES, formatDuration } from "@/lib/duration";
import type { DeliveryProfileId } from "@/lib/duration";
import type { Occasion, Script } from "@/lib/script/types";
import { saveScript } from "@/lib/storage";
import { OCCASION_LIST, getTemplate, validateIntake } from "@/lib/templates";

/**
 * The intake.
 *
 * This screen is the actual product. Generated speeches sound generic because
 * the input is generic — so the app refuses to generate until the speaker has
 * handed over the things only they know. Every question here exists to pull out
 * one specific, unfakeable detail.
 */

const MAX_FIT_PASSES = 3;

function ComposeInner() {
  const router = useRouter();
  const params = useSearchParams();

  const initialOccasion = (params.get("ocazie") as Occasion) ?? "nunta";
  const [occasion, setOccasion] = useState<Occasion>(
    OCCASION_LIST.some((o) => o.id === initialOccasion) ? initialOccasion : "nunta",
  );

  const template = useMemo(() => getTemplate(occasion), [occasion]);

  const [targetSeconds, setTargetSeconds] = useState(template.defaultSeconds);
  const [profile, setProfile] = useState<DeliveryProfileId>(
    template.defaultProfile,
  );
  const [intake, setIntake] = useState<Record<string, string>>({});
  const [touched, setTouched] = useState(false);
  const [busy, setBusy] = useState(false);
  const [status, setStatus] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);

  const validation = validateIntake(occasion, intake);

  function switchOccasion(next: Occasion) {
    const t = getTemplate(next);
    setOccasion(next);
    setTargetSeconds(t.defaultSeconds);
    setProfile(t.defaultProfile);
    setIntake({});
    setTouched(false);
    setError(null);
  }

  async function generate() {
    setTouched(true);
    if (!validation.ok) return;

    setBusy(true);
    setError(null);

    try {
      setStatus("Scriu prima variantă…");
      const res = await fetch("/api/generate", {
        method: "POST",
        headers: { "content-type": "application/json" },
        body: JSON.stringify({ occasion, targetSeconds, profile, intake }),
      });
      const data = await res.json();
      if (!res.ok) throw new Error(data.error ?? "Generarea a eșuat.");

      let script: Script = data.script;
      let gain: number | undefined;

      // The fit loop runs one pass per request so no single call sits through
      // three model round-trips. The gain carries across, so the loop keeps
      // learning the model's length bias instead of restarting each pass.
      for (let pass = 1; pass <= MAX_FIT_PASSES; pass += 1) {
        setStatus(`Ajustez durata (pasul ${pass} din ${MAX_FIT_PASSES})…`);
        const fitRes = await fetch("/api/fit", {
          method: "POST",
          headers: { "content-type": "application/json" },
          body: JSON.stringify({ script, gain }),
        });
        const fitData = await fitRes.json();
        if (!fitRes.ok) throw new Error(fitData.error ?? "Ajustarea a eșuat.");

        script = fitData.script;
        gain = fitData.gain;

        if (fitData.withinTolerance) break;
        if (
          fitData.stoppedBecause === "no-adjustable-sections" ||
          fitData.stoppedBecause === "no-progress"
        ) {
          break;
        }
      }

      saveScript(script);
      router.push(`/editor/${script.id}`);
    } catch (e) {
      setError(e instanceof Error ? e.message : "Ceva a mers prost.");
      setBusy(false);
      setStatus(null);
    }
  }

  return (
    <div className="flex max-w-3xl flex-col gap-8">
      <div>
        <h1 className="display text-3xl text-cream">Discurs nou</h1>
        <p className="mt-2 text-muted">
          Șase întrebări. Răspunsurile scurte dau discursuri generice — scrie ca
          și cum i-ai povesti unui prieten.
        </p>
      </div>

      <fieldset className="flex flex-col gap-3">
        <legend className="mb-2 text-sm text-muted">Ocazia</legend>
        <div className="grid gap-3 sm:grid-cols-3">
          {OCCASION_LIST.map((o) => (
            <button
              key={o.id}
              type="button"
              onClick={() => switchOccasion(o.id)}
              className={`rounded-lg border p-4 text-left transition-colors ${
                occasion === o.id
                  ? "border-brass bg-surface-2"
                  : "border-line bg-surface hover:border-brass-dim"
              }`}
            >
              <div className="display text-cream">{o.label}</div>
              <div className="mt-1 text-xs text-muted">{o.blurb}</div>
            </button>
          ))}
        </div>
      </fieldset>

      <div className="flex flex-wrap gap-6">
        <label className="flex flex-col gap-2">
          <span className="text-sm text-muted">Durată țintă</span>
          <select
            value={targetSeconds}
            onChange={(e) => setTargetSeconds(Number(e.target.value))}
            className="rounded-md border border-line bg-surface px-3 py-2 text-cream outline-none focus:border-brass-dim"
          >
            {template.durationOptions.map((s) => (
              <option key={s} value={s}>
                {formatDuration(s)}
              </option>
            ))}
          </select>
        </label>

        <label className="flex flex-col gap-2">
          <span className="text-sm text-muted">Stil de livrare</span>
          <select
            value={profile}
            onChange={(e) => setProfile(e.target.value as DeliveryProfileId)}
            className="rounded-md border border-line bg-surface px-3 py-2 text-cream outline-none focus:border-brass-dim"
          >
            {Object.values(DELIVERY_PROFILES).map((p) => (
              <option key={p.id} value={p.id}>
                {p.label}
              </option>
            ))}
          </select>
        </label>
      </div>

      <div className="flex flex-col gap-6">
        {template.questions.map((q, i) => {
          const value = intake[q.id] ?? "";
          const missing = touched && validation.missing.includes(q.id);
          const short = touched && validation.tooShort.includes(q.id);
          const Field = q.multiline ? "textarea" : "input";
          return (
            <label key={q.id} className="flex flex-col gap-2">
              <span className="flex items-baseline gap-2">
                <span className="tabular text-xs text-brass-dim">
                  {String(i + 1).padStart(2, "0")}
                </span>
                <span className="text-cream">{q.question}</span>
              </span>
              <span className="text-xs leading-relaxed text-faint">{q.hint}</span>
              <Field
                value={value}
                rows={q.multiline ? 3 : undefined}
                onChange={(
                  e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>,
                ) => setIntake((prev) => ({ ...prev, [q.id]: e.target.value }))}
                placeholder={q.placeholder}
                className={`w-full resize-y rounded-lg border bg-surface p-3 leading-relaxed text-cream outline-none placeholder:text-faint/60 focus:border-brass-dim ${
                  missing || short ? "border-rust" : "border-line"
                }`}
              />
              {missing && (
                <span className="text-xs text-rust">
                  Fără răspunsul ăsta, discursul iese generic.
                </span>
              )}
              {short && (
                <span className="text-xs text-rust">
                  Prea scurt — mai dă un detaliu concret (minimum {q.minLength}{" "}
                  caractere).
                </span>
              )}
            </label>
          );
        })}
      </div>

      {error && (
        <p className="rounded-lg border border-rust/40 bg-rust/10 p-4 text-sm text-rust">
          {error}
        </p>
      )}

      <div className="flex items-center gap-4">
        <button
          onClick={generate}
          disabled={busy}
          className="rounded-md bg-brass px-5 py-2.5 font-medium text-ink transition-opacity hover:opacity-90 disabled:cursor-not-allowed disabled:opacity-40"
        >
          {busy ? "Se lucrează…" : "Scrie discursul"}
        </button>
        {status && <span className="text-sm text-muted">{status}</span>}
        {!busy && touched && !validation.ok && (
          <span className="text-sm text-rust">
            Mai sunt răspunsuri de completat.
          </span>
        )}
      </div>
    </div>
  );
}

export default function ComposePage() {
  return (
    <Suspense fallback={<p className="text-muted">Se încarcă…</p>}>
      <ComposeInner />
    </Suspense>
  );
}
