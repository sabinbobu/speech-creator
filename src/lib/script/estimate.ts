import { estimate } from "@/lib/duration";
import type { DeliveryProfileId } from "@/lib/duration";
import type { Script, ScriptEstimate, Section, SectionEstimate } from "./types";

/**
 * Estimate a script section by section.
 *
 * Per-section numbers are the point: a speech that is 40 seconds long overall
 * can still be unusable because the story runs three minutes and the closing
 * gets nine seconds. The editor shows both.
 */
export function estimateScript(script: Script): ScriptEstimate {
  const profile: DeliveryProfileId = script.profile;
  const totalWeight = script.sections.reduce(
    (sum, s) => sum + Math.max(0, s.weight),
    0,
  );

  const sections: SectionEstimate[] = script.sections.map((section) => {
    const e = estimate(section.text, { profile });
    const share = totalWeight > 0 ? Math.max(0, section.weight) / totalWeight : 0;
    return {
      sectionId: section.id,
      seconds: e.totalMs / 1000,
      words: e.wordCount,
      syllables: e.syllables,
      targetSeconds: script.targetSeconds * share,
    };
  });

  const totalSeconds = sections.reduce((sum, s) => sum + s.seconds, 0);

  return {
    totalSeconds,
    targetSeconds: script.targetSeconds,
    deltaSeconds: totalSeconds - script.targetSeconds,
    sections,
  };
}

export function sectionSeconds(
  section: Section,
  profile: DeliveryProfileId,
): number {
  return estimate(section.text, { profile }).totalMs / 1000;
}
