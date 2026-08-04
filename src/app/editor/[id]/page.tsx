"use client";

import Link from "next/link";
import { useParams } from "next/navigation";
import { useCallback, useEffect, useMemo, useState } from "react";
import Teleprompter from "@/components/Teleprompter";
import { DELIVERY_PROFILES, formatDuration } from "@/lib/duration";
import type { DeliveryProfileId } from "@/lib/duration";
import { estimateScript } from "@/lib/script/estimate";
import { scriptText } from "@/lib/script/types";
import type { Script } from "@/lib/script/types";
import { getScript, saveScript } from "@/lib/storage";

const MAX_FIT_PASSES = 3;
const TOLERANCE = 5;

export default function EditorPage() {
  const params = useParams<{ id: string }>();
  const [script, setScript] = useState<Script | null>(null);
  const [loaded, setLoaded] = useState(false);
  const [mode, setMode] = useState<"edit" | "run">("edit");
  const [busy, setBusy] = useState(false);
  const [status, setStatus] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);
  const [copied, setCopied] = useState(false);

  useEffect(() => {
    setScript(getScript(params.id));
    setLoaded(true);
  }, [params.id]);

  const update = useCallback((next: Script) => {
    setScript(next);
    saveScript(next);
  }, []);

  const estimate = useMemo(
    () => (script ? estimateScript(script) : null),
    [script],
  );

  async function refit() {
    if (!script) return;
    setBusy(true);
    setError(null);
    let current = script;
    let gain: number | undefined;

    try {
      for (let pass = 1; pass <= MAX_FIT_PASSES; pass += 1) {
        setStatus(`Ajustez durata (pasul ${pass} din ${MAX_FIT_PASSES})…`);
        const res = await fetch("/api/fit", {
          method: "POST",
          headers: { "content-type": "application/json" },
          body: JSON.stringify({ script: current, gain }),
        });
        const data = await res.json();
        if (!res.ok) throw new Error(data.error ?? "Ajustarea a eșuat.");

        current = data.script;
        gain = data.gain;
        update(current);

        if (data.withinTolerance) break;
        if (
          data.stoppedBecause === "no-adjustable-sections" ||
          data.stoppedBecause === "no-progress"
        ) {
          break;
        }
      }
    } catch (e) {
      setError(e instanceof Error ? e.message : "Ceva a mers prost.");
    } finally {
      setBusy(false);
      setStatus(null);
    }
  }

  async function copyAll() {
    if (!script) return;
    try {
      await navigator.clipboard.writeText(scriptText(script));
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    } catch {
      setError("Nu am putut copia în clipboard.");
    }
  }

  if (!loaded) return <p className="text-muted">Se încarcă…</p>;

  if (!script) {
    return (
      <div className="flex flex-col gap-4">
        <h1 className="display text-2xl text-cream">Discursul nu există</h1>
        <p className="text-muted">
          Poate a fost șters, sau a fost salvat în alt browser — discursurile
          stau local, nu pe server.
        </p>
        <Link href="/" className="text-brass hover:underline">
          ← înapoi acasă
        </Link>
      </div>
    );
  }

  const delta = estimate ? estimate.totalSeconds - script.targetSeconds : 0;
  const onTarget = Math.abs(delta) <= TOLERANCE;

  if (mode === "run") {
    return (
      <div className="flex flex-col gap-4">
        <button
          onClick={() => setMode("edit")}
          className="self-start text-sm text-muted transition-colors hover:text-cream"
        >
          ← înapoi la editor
        </button>
        <Teleprompter
          text={scriptText(script)}
          profile={script.profile}
          targetSeconds={script.targetSeconds}
        />
      </div>
    );
  }

  return (
    <div className="flex flex-col gap-8">
      <div className="flex flex-wrap items-start justify-between gap-4">
        <div className="min-w-0">
          <input
            value={script.title}
            onChange={(e) => update({ ...script, title: e.target.value })}
            className="display w-full bg-transparent text-3xl text-cream outline-none"
            aria-label="Titlul discursului"
          />
          <p className="mt-1 text-xs text-faint">
            salvat local · {new Date(script.updatedAt).toLocaleString("ro-RO")}
          </p>
        </div>

        <div className="text-right">
          <div className="tabular text-4xl text-cream">
            {estimate ? formatDuration(estimate.totalSeconds) : "—"}
          </div>
          <div
            className={`tabular text-sm ${onTarget ? "text-sage" : "text-rust"}`}
          >
            țintă {formatDuration(script.targetSeconds)} ({delta > 0 ? "+" : ""}
            {Math.round(delta)}s)
          </div>
        </div>
      </div>

      <div className="flex flex-wrap items-end gap-4 rounded-lg border border-line bg-surface p-4">
        <label className="flex flex-col gap-1">
          <span className="text-xs text-muted">Durată țintă</span>
          <input
            type="number"
            min={30}
            max={1800}
            step={15}
            value={script.targetSeconds}
            onChange={(e) =>
              update({ ...script, targetSeconds: Number(e.target.value) })
            }
            className="tabular w-24 rounded-md border border-line bg-surface-2 px-2 py-1.5 text-cream outline-none focus:border-brass-dim"
          />
        </label>

        <label className="flex flex-col gap-1">
          <span className="text-xs text-muted">Stil</span>
          <select
            value={script.profile}
            onChange={(e) =>
              update({
                ...script,
                profile: e.target.value as DeliveryProfileId,
              })
            }
            className="rounded-md border border-line bg-surface-2 px-2 py-1.5 text-cream outline-none focus:border-brass-dim"
          >
            {Object.values(DELIVERY_PROFILES).map((p) => (
              <option key={p.id} value={p.id}>
                {p.label}
              </option>
            ))}
          </select>
        </label>

        <button
          onClick={refit}
          disabled={busy}
          className="rounded-md border border-brass-dim px-4 py-2 text-sm text-brass transition-colors hover:bg-brass/10 disabled:opacity-40"
        >
          {busy ? "Se ajustează…" : "Ajustează la țintă"}
        </button>

        <button
          onClick={() => setMode("run")}
          className="rounded-md bg-brass px-4 py-2 text-sm font-medium text-ink transition-opacity hover:opacity-90"
        >
          Repetă cu teleprompterul
        </button>

        <button
          onClick={copyAll}
          className="ml-auto text-sm text-muted transition-colors hover:text-cream"
        >
          {copied ? "copiat ✓" : "copiază tot"}
        </button>
      </div>

      {status && <p className="text-sm text-muted">{status}</p>}
      {error && (
        <p className="rounded-lg border border-rust/40 bg-rust/10 p-4 text-sm text-rust">
          {error}
        </p>
      )}

      <p className="text-sm text-faint">
        Blochează o secțiune ca să nu fie atinsă când ajustezi durata. Restul se
        rescriu chirurgical, nu de la zero.
      </p>

      <div className="flex flex-col gap-5">
        {script.sections.map((section) => {
          const sectionEstimate = estimate?.sections.find(
            (s) => s.sectionId === section.id,
          );
          const sectionDelta = sectionEstimate
            ? sectionEstimate.seconds - sectionEstimate.targetSeconds
            : 0;
          return (
            <div
              key={section.id}
              className={`rounded-lg border bg-surface p-4 ${
                section.locked ? "border-brass-dim" : "border-line"
              }`}
            >
              <div className="mb-3 flex flex-wrap items-center gap-3">
                <h2 className="display text-lg text-cream">{section.title}</h2>
                <span className="tabular text-sm text-muted">
                  {sectionEstimate ? formatDuration(sectionEstimate.seconds) : "—"}
                </span>
                <span
                  className={`tabular text-xs ${
                    Math.abs(sectionDelta) <= 3 ? "text-sage" : "text-faint"
                  }`}
                >
                  țintă{" "}
                  {sectionEstimate
                    ? formatDuration(sectionEstimate.targetSeconds)
                    : "—"}
                </span>
                <label className="ml-auto flex cursor-pointer items-center gap-2 text-xs text-muted">
                  <input
                    type="checkbox"
                    checked={section.locked}
                    onChange={(e) =>
                      update({
                        ...script,
                        sections: script.sections.map((s) =>
                          s.id === section.id
                            ? { ...s, locked: e.target.checked }
                            : s,
                        ),
                      })
                    }
                    className="accent-brass"
                  />
                  blocată
                </label>
              </div>
              <textarea
                value={section.text}
                rows={Math.max(3, Math.ceil(section.text.length / 90))}
                onChange={(e) =>
                  update({
                    ...script,
                    sections: script.sections.map((s) =>
                      s.id === section.id ? { ...s, text: e.target.value } : s,
                    ),
                  })
                }
                className="w-full resize-y rounded-md border border-line bg-surface-2 p-3 leading-relaxed text-cream outline-none focus:border-brass-dim"
              />
              {sectionEstimate && (
                <p className="mt-2 text-xs text-faint">
                  {sectionEstimate.words} cuvinte · {sectionEstimate.syllables}{" "}
                  silabe
                </p>
              )}
            </div>
          );
        })}
      </div>
    </div>
  );
}
