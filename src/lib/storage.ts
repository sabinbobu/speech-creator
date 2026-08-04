"use client";

import type { Script } from "@/lib/script/types";

/**
 * V0 persistence: localStorage, nothing else.
 *
 * No accounts, no database, no payments. The plan is explicit that a V0 with
 * auth and billing never ships, and none of the three differentiators need a
 * server to work.
 */

const KEY = "cadenta.scripts.v1";

function read(): Script[] {
  if (typeof window === "undefined") return [];
  try {
    const raw = window.localStorage.getItem(KEY);
    if (!raw) return [];
    const parsed = JSON.parse(raw);
    return Array.isArray(parsed) ? (parsed as Script[]) : [];
  } catch {
    // A corrupted entry should not brick the app on load.
    return [];
  }
}

function write(scripts: Script[]): void {
  if (typeof window === "undefined") return;
  try {
    window.localStorage.setItem(KEY, JSON.stringify(scripts));
  } catch {
    // Quota exceeded or private mode — the session still works in memory.
  }
}

export function listScripts(): Script[] {
  return read().sort((a, b) => b.updatedAt.localeCompare(a.updatedAt));
}

export function getScript(id: string): Script | null {
  return read().find((s) => s.id === id) ?? null;
}

export function saveScript(script: Script): void {
  const all = read();
  const index = all.findIndex((s) => s.id === script.id);
  const next = { ...script, updatedAt: new Date().toISOString() };
  if (index === -1) all.push(next);
  else all[index] = next;
  write(all);
}

export function deleteScript(id: string): void {
  write(read().filter((s) => s.id !== id));
}
