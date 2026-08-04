"use client";

import Link from "next/link";
import { useEffect, useState } from "react";
import { formatDuration } from "@/lib/duration";
import { estimateScript } from "@/lib/script/estimate";
import type { Script } from "@/lib/script/types";
import { deleteScript, listScripts } from "@/lib/storage";
import { OCCASION_LIST } from "@/lib/templates";

const DIFFERENTIATORS = [
  {
    title: "Durată exactă",
    body: "„5:00 ± 5 secunde”, garantat și verificabil. Motorul numără silabe și pauze, nu cuvinte pe minut.",
  },
  {
    title: "Română nativă",
    body: "Silabe, diftongi, pauze de punctuație și cuvintele de umplutură pe care le folosim de fapt.",
  },
  {
    title: "Te urmărește pe tine",
    body: "Fiecare cuvânt are durata lui. Teleprompterul merge în ritmul vorbirii, nu invers.",
  },
];

export default function HomePage() {
  const [scripts, setScripts] = useState<Script[]>([]);
  const [loaded, setLoaded] = useState(false);

  useEffect(() => {
    setScripts(listScripts());
    setLoaded(true);
  }, []);

  function remove(id: string) {
    deleteScript(id);
    setScripts(listScripts());
  }

  return (
    <div className="flex flex-col gap-14">
      <section className="flex flex-col gap-5">
        <h1 className="display max-w-2xl text-4xl leading-tight text-cream sm:text-5xl sm:leading-tight">
          Nu scriem discursul în locul tău.
          <br />
          <span className="text-brass">Îl facem să încapă în timp.</span>
        </h1>
        <p className="max-w-2xl text-muted">
          Orice model scrie un discurs de cinci minute dintr-un prompt. Partea
          grea e să dureze exact cinci minute când îl rostești tu, cu vocea ta,
          în sala aia.
        </p>
        <div className="flex flex-wrap gap-3">
          <Link
            href="/compose"
            className="rounded-md bg-brass px-5 py-2.5 font-medium text-ink transition-opacity hover:opacity-90"
          >
            Scrie un discurs
          </Link>
          <Link
            href="/prompter"
            className="rounded-md border border-line px-5 py-2.5 text-cream transition-colors hover:border-brass-dim"
          >
            Am deja textul — vreau teleprompterul
          </Link>
        </div>
      </section>

      <section className="grid gap-4 sm:grid-cols-3">
        {DIFFERENTIATORS.map((d) => (
          <div
            key={d.title}
            className="rounded-lg border border-line bg-surface p-5"
          >
            <h2 className="display mb-2 text-lg text-brass">{d.title}</h2>
            <p className="text-sm leading-relaxed text-muted">{d.body}</p>
          </div>
        ))}
      </section>

      <section className="flex flex-col gap-4">
        <h2 className="display text-2xl text-cream">Discursurile tale</h2>
        {!loaded ? (
          <p className="text-sm text-faint">Se încarcă…</p>
        ) : scripts.length === 0 ? (
          <p className="rounded-lg border border-dashed border-line p-6 text-sm text-faint">
            Încă niciunul. Discursurile se salvează local, în browserul tău —
            fără cont și fără server.
          </p>
        ) : (
          <ul className="flex flex-col gap-2">
            {scripts.map((script) => {
              const est = estimateScript(script);
              const delta = est.totalSeconds - script.targetSeconds;
              const onTarget = Math.abs(delta) <= 5;
              return (
                <li
                  key={script.id}
                  className="flex items-center gap-4 rounded-lg border border-line bg-surface px-4 py-3"
                >
                  <div className="min-w-0 flex-1">
                    <Link
                      href={`/editor/${script.id}`}
                      className="display block truncate text-cream hover:text-brass"
                    >
                      {script.title}
                    </Link>
                    <p className="text-xs text-faint">
                      {OCCASION_LIST.find((o) => o.id === script.occasion)?.label}
                      {" · "}
                      {new Date(script.updatedAt).toLocaleDateString("ro-RO")}
                    </p>
                  </div>
                  <div className="text-right">
                    <div className="tabular text-sm text-cream">
                      {formatDuration(est.totalSeconds)}
                    </div>
                    <div
                      className={`tabular text-xs ${onTarget ? "text-sage" : "text-rust"}`}
                    >
                      țintă {formatDuration(script.targetSeconds)}
                    </div>
                  </div>
                  <button
                    onClick={() => remove(script.id)}
                    className="text-xs text-faint transition-colors hover:text-rust"
                    aria-label={`Șterge ${script.title}`}
                  >
                    șterge
                  </button>
                </li>
              );
            })}
          </ul>
        )}
      </section>

      <section className="flex flex-col gap-4">
        <h2 className="display text-2xl text-cream">Pentru ce ocazii</h2>
        <div className="grid gap-4 sm:grid-cols-3">
          {OCCASION_LIST.map((occasion) => (
            <Link
              key={occasion.id}
              href={`/compose?ocazie=${occasion.id}`}
              className="rounded-lg border border-line bg-surface p-5 transition-colors hover:border-brass-dim"
            >
              <h3 className="display mb-1 text-lg text-cream">
                {occasion.label}
              </h3>
              <p className="text-sm text-muted">{occasion.blurb}</p>
              <p className="mt-3 text-xs text-faint">
                implicit {formatDuration(occasion.defaultSeconds)}
              </p>
            </Link>
          ))}
        </div>
      </section>
    </div>
  );
}
