"use client";

import { useCallback, useEffect, useMemo, useRef, useState } from "react";
import {
  DELIVERY_PROFILES,
  estimate,
  formatDuration,
} from "@/lib/duration";
import type { DeliveryProfileId, WordTiming } from "@/lib/duration";

/**
 * The karaoke teleprompter.
 *
 * Every word gets its own duration, computed from its syllables plus the pause
 * that follows it. A fixed words-per-minute crawl — what every other prompter
 * does — drifts against the speaker within about thirty seconds, because
 * "azi" and "binecuvântare" are not the same amount of speaking.
 *
 * The timeline is precomputed once per (text, profile, tempo) and the animation
 * frame only reads from it, so scrolling stays smooth on a phone propped up on
 * a table.
 */

/** Last word whose start has passed. Stays put during the pause after it. */
function indexAt(words: WordTiming[], elapsedMs: number): number {
  if (words.length === 0 || elapsedMs < 0) return -1;
  let lo = 0;
  let hi = words.length - 1;
  let best = -1;
  while (lo <= hi) {
    const mid = (lo + hi) >> 1;
    if (words[mid].startMs <= elapsedMs) {
      best = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return best;
}

/** Pauses shorter than this are part of normal speech, not a visible beat. */
const VISIBLE_PAUSE_MS = 240;

function PauseMark({ ms }: { ms: number }) {
  // Three tiers rather than a continuous scale: a speaker glancing at this
  // needs "breathe" / "stop" / "let it land", not a precise millisecond count.
  const dots = ms >= 700 ? 3 : ms >= 380 ? 2 : 1;
  return (
    <span
      aria-hidden
      className="mx-1 inline-flex select-none items-center gap-0.5 align-middle"
      title={`pauză ${Math.round(ms)} ms`}
    >
      {Array.from({ length: dots }).map((_, i) => (
        <span key={i} className="inline-block h-1 w-1 rounded-full bg-brass-dim" />
      ))}
    </span>
  );
}

export interface TeleprompterProps {
  text: string;
  profile?: DeliveryProfileId;
  /** Shown under the clock so the speaker sees the gap against the target. */
  targetSeconds?: number;
}

export default function Teleprompter({
  text,
  profile = "normal",
  targetSeconds,
}: TeleprompterProps) {
  const [tempo, setTempo] = useState(1);
  const [playing, setPlaying] = useState(false);
  const [index, setIndex] = useState(-1);
  const [elapsedSeconds, setElapsedSeconds] = useState(0);

  const elapsedRef = useRef(0);
  const originRef = useRef(0);
  const frameRef = useRef<number | null>(null);
  const activeRef = useRef<HTMLSpanElement | null>(null);

  const timeline = useMemo(
    () => estimate(text, { profile, tempo }),
    [text, profile, tempo],
  );

  const words = timeline.words;
  const totalMs = timeline.totalMs;

  const paragraphs = useMemo(() => {
    const groups: WordTiming[][] = [];
    for (const word of words) {
      if (!groups[word.paragraph]) groups[word.paragraph] = [];
      groups[word.paragraph].push(word);
    }
    return groups.filter(Boolean);
  }, [words]);

  const stop = useCallback(() => {
    if (frameRef.current !== null) {
      cancelAnimationFrame(frameRef.current);
      frameRef.current = null;
    }
  }, []);

  // The animation loop. setState with an unchanged value is a no-op in React,
  // so this only re-renders when the highlighted word or the whole second
  // actually changes — a few times a second, not sixty.
  useEffect(() => {
    if (!playing) {
      stop();
      return;
    }

    originRef.current = performance.now() - elapsedRef.current;

    const tick = (now: number) => {
      const elapsed = now - originRef.current;
      elapsedRef.current = elapsed;

      setIndex(indexAt(words, elapsed));
      setElapsedSeconds(Math.floor(elapsed / 1000));

      if (elapsed >= totalMs) {
        elapsedRef.current = totalMs;
        setPlaying(false);
        return;
      }
      frameRef.current = requestAnimationFrame(tick);
    };

    frameRef.current = requestAnimationFrame(tick);
    return stop;
  }, [playing, words, totalMs, stop]);

  // Changing tempo rebuilds the timeline. Re-anchor the clock to the current
  // word's new start so the speaker doesn't get thrown to a different place in
  // the script mid-sentence.
  const handleTempo = useCallback(
    (next: number) => {
      const current = index;
      setTempo(next);
      if (current >= 0) {
        const rescaled = estimate(text, { profile, tempo: next });
        const word = rescaled.words[current];
        if (word) {
          elapsedRef.current = word.startMs;
          originRef.current = performance.now() - word.startMs;
          setElapsedSeconds(Math.floor(word.startMs / 1000));
        }
      }
    },
    [index, text, profile],
  );

  const restart = useCallback(() => {
    elapsedRef.current = 0;
    originRef.current = performance.now();
    setIndex(-1);
    setElapsedSeconds(0);
  }, []);

  useEffect(() => {
    activeRef.current?.scrollIntoView({ block: "center", behavior: "smooth" });
  }, [index]);

  // Space and R, so the speaker can drive it without hunting for a button.
  useEffect(() => {
    const onKey = (event: KeyboardEvent) => {
      const target = event.target as HTMLElement | null;
      if (target && /^(INPUT|TEXTAREA|SELECT)$/.test(target.tagName)) return;
      if (event.code === "Space") {
        event.preventDefault();
        setPlaying((p) => !p);
      } else if (event.key.toLowerCase() === "r") {
        event.preventDefault();
        setPlaying(false);
        restart();
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [restart]);

  const remainingMs = Math.max(0, totalMs - elapsedRef.current);
  const delta =
    targetSeconds !== undefined ? totalMs / 1000 - targetSeconds : null;

  if (words.length === 0) {
    return (
      <p className="rounded-lg border border-line bg-surface p-6 text-muted">
        Lipește un text ca să pornești teleprompterul.
      </p>
    );
  }

  return (
    <div className="flex flex-col gap-4">
      {/* Controls */}
      <div className="sticky top-0 z-10 flex flex-wrap items-center gap-3 rounded-lg border border-line bg-surface/95 p-3 backdrop-blur">
        <button
          onClick={() => setPlaying((p) => !p)}
          className="rounded-md bg-brass px-4 py-2 text-sm font-medium text-ink transition-opacity hover:opacity-90"
        >
          {playing ? "Pauză" : elapsedRef.current > 0 ? "Continuă" : "Pornește"}
        </button>
        <button
          onClick={() => {
            setPlaying(false);
            restart();
          }}
          className="rounded-md border border-line px-3 py-2 text-sm text-muted transition-colors hover:text-cream"
        >
          De la capăt
        </button>

        <div className="flex items-center gap-2">
          <label htmlFor="tempo" className="text-xs text-faint">
            Ritm
          </label>
          <input
            id="tempo"
            type="range"
            min={70}
            max={140}
            step={1}
            value={Math.round(tempo * 100)}
            onChange={(e) => handleTempo(Number(e.target.value) / 100)}
            className="w-28 accent-brass"
          />
          <span className="tabular w-12 text-xs text-muted">
            {tempo.toFixed(2)}×
          </span>
        </div>

        <div className="ml-auto flex items-baseline gap-3">
          <span className="tabular text-lg text-cream">
            {formatDuration(elapsedSeconds)}
          </span>
          <span className="text-xs text-faint">/</span>
          <span className="tabular text-sm text-muted">
            {formatDuration(totalMs / 1000)}
          </span>
          {delta !== null && (
            <span
              className={`tabular text-xs ${
                Math.abs(delta) <= 5 ? "text-sage" : "text-rust"
              }`}
              title="Diferența față de durata cerută"
            >
              {delta > 0 ? "+" : ""}
              {Math.round(delta)}s
            </span>
          )}
        </div>
      </div>

      {/* Script. Paragraphs stay separate blocks: a speaker glancing back at
          the page needs the shape of the speech, and a single wall of text is
          exactly what a prompter is supposed to prevent. */}
      <div className="display flex flex-col gap-6 rounded-lg border border-line bg-surface px-6 py-10 text-2xl leading-relaxed sm:text-3xl sm:leading-relaxed">
        {paragraphs.map((paragraph, p) => (
          <p key={p}>
            {paragraph.map((word) => {
              const spoken = word.index < index;
              const active = word.index === index;
              return (
                <span key={word.index}>
                  <span
                    ref={active ? activeRef : undefined}
                    data-active={active || undefined}
                    className={
                      active
                        ? "rounded bg-brass/20 px-0.5 text-brass"
                        : spoken
                          ? "text-faint"
                          : "text-cream"
                    }
                  >
                    {word.text}
                  </span>
                  {word.pauseAfterMs >= VISIBLE_PAUSE_MS ? (
                    <PauseMark ms={word.pauseAfterMs} />
                  ) : (
                    " "
                  )}
                </span>
              );
            })}
          </p>
        ))}
      </div>

      <div className="flex flex-wrap gap-x-6 gap-y-1 text-xs text-faint">
        <span>
          {timeline.wordCount} cuvinte · {timeline.syllables} silabe
        </span>
        <span>
          pauze {(timeline.pauseMs / 1000).toFixed(1)}s (
          {Math.round((timeline.pauseMs / timeline.totalMs) * 100)}%)
        </span>
        <span>rămân {formatDuration(remainingMs / 1000)}</span>
        <span className="ml-auto">
          {DELIVERY_PROFILES[profile].label} · spațiu = start/stop · R = de la capăt
        </span>
      </div>
    </div>
  );
}
