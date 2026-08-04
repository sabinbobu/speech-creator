import type { DeliveryProfileId } from "@/lib/duration";

export type SectionKind =
  | "deschidere"
  | "poveste"
  | "mesaj"
  | "umor"
  | "multumiri"
  | "inchidere"
  | "liber";

export const SECTION_LABELS: Record<SectionKind, string> = {
  deschidere: "Deschidere",
  poveste: "Poveste",
  mesaj: "Mesaj",
  umor: "Moment de umor",
  multumiri: "Mulțumiri",
  inchidere: "Închidere",
  liber: "Secțiune liberă",
};

export interface Section {
  id: string;
  title: string;
  kind: SectionKind;
  text: string;
  /**
   * A locked section is never touched by the fit loop. This is what makes the
   * timing loop safe to run on a script the user has already edited: the joke
   * they wrote themselves survives every pass.
   */
  locked: boolean;
  /** Relative share of the total target this section should occupy. */
  weight: number;
}

export type Occasion = "nunta" | "dezbatere" | "prezentare";

export interface Script {
  id: string;
  title: string;
  occasion: Occasion;
  /** Target length in seconds. The whole product is built around hitting it. */
  targetSeconds: number;
  profile: DeliveryProfileId;
  sections: Section[];
  createdAt: string;
  updatedAt: string;
  /** Answers to the intake questions, kept so a regeneration stays personal. */
  intake: Record<string, string>;
}

export interface SectionEstimate {
  sectionId: string;
  seconds: number;
  words: number;
  syllables: number;
  /** Seconds this section should occupy, from its weight. */
  targetSeconds: number;
}

export interface ScriptEstimate {
  totalSeconds: number;
  targetSeconds: number;
  deltaSeconds: number;
  sections: SectionEstimate[];
}

export function createId(): string {
  // crypto.randomUUID exists in Node 19+ and every browser we target.
  if (typeof crypto !== "undefined" && "randomUUID" in crypto) {
    return crypto.randomUUID();
  }
  return `id-${Math.random().toString(36).slice(2)}-${Date.now()}`;
}

export function scriptText(script: Script): string {
  return script.sections
    .map((s) => s.text.trim())
    .filter(Boolean)
    .join("\n\n");
}
