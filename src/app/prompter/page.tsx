"use client";

import { useState } from "react";
import Teleprompter from "@/components/Teleprompter";
import { DELIVERY_PROFILES, estimateSeconds, formatDuration } from "@/lib/duration";
import type { DeliveryProfileId } from "@/lib/duration";

/**
 * The standalone teleprompter: paste text, press play. No account, no model
 * call, no generation. This is the demo — it shows the whole thesis (per-word
 * timing, visible pauses, a clock that tells the truth) without anything else
 * having to work first.
 */

const SAMPLE = `Dragii mei, nu o să vă țin mult. [pauză]

Acum șapte ani, într-o seară de octombrie, Ana m-a sunat din gară la Cluj.
Mi-a spus că a cunoscut pe cineva care râde la aceleași glume proaste ca ea.
Atât. Nu mi-a spus cum îl cheamă, nu mi-a spus cu ce se ocupă.
Mi-a spus doar partea aia.

Mihai, tu zici „doar cinci minute” de fiecare dată când pleci undeva.
Nu au fost niciodată cinci minute. Nici azi nu au fost. [pauză]

Dar am văzut ceva la voi doi în anii ăștia.
Vă certați seara și vă împăcați tot seara.
Nu v-am văzut niciodată plecând supărați la culcare.

Vă doresc să râdeți la fel de des și peste treizeci de ani. Să trăiți!`;

export default function PrompterPage() {
  const [text, setText] = useState(SAMPLE);
  const [profile, setProfile] = useState<DeliveryProfileId>("rar");
  const [running, setRunning] = useState(false);

  const seconds = estimateSeconds(text, { profile });

  if (running) {
    return (
      <div className="flex flex-col gap-4">
        <button
          onClick={() => setRunning(false)}
          className="self-start text-sm text-muted transition-colors hover:text-cream"
        >
          ← înapoi la text
        </button>
        <Teleprompter text={text} profile={profile} />
      </div>
    );
  }

  return (
    <div className="flex flex-col gap-6">
      <div>
        <h1 className="display text-3xl text-cream">Teleprompter</h1>
        <p className="mt-2 max-w-2xl text-muted">
          Lipește orice text în română. Îl segmentăm pe cuvinte, calculăm durata
          fiecăruia din silabe și punctuație, apoi îl derulăm în ritmul în care
          se rostește de fapt.
        </p>
      </div>

      <label className="flex flex-col gap-2">
        <span className="text-sm text-muted">Textul discursului</span>
        <textarea
          value={text}
          onChange={(e) => setText(e.target.value)}
          rows={16}
          spellCheck={false}
          className="w-full resize-y rounded-lg border border-line bg-surface p-4 leading-relaxed text-cream outline-none focus:border-brass-dim"
          placeholder="Lipește textul aici…"
        />
        <span className="text-xs text-faint">
          Marchează o pauză intenționată scriind <code>[pauză]</code>. Un rând
          gol înseamnă pauză de paragraf.
        </span>
      </label>

      <div className="flex flex-wrap items-end gap-6">
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

        <div>
          <div className="text-sm text-muted">Durată estimată</div>
          <div className="tabular text-3xl text-brass">
            {formatDuration(seconds)}
          </div>
        </div>

        <button
          onClick={() => setRunning(true)}
          disabled={!text.trim()}
          className="ml-auto rounded-md bg-brass px-5 py-2.5 font-medium text-ink transition-opacity hover:opacity-90 disabled:cursor-not-allowed disabled:opacity-40"
        >
          Pornește teleprompterul
        </button>
      </div>
    </div>
  );
}
