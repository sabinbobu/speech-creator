import Anthropic from "@anthropic-ai/sdk";
import { approximateWordsForSeconds, formatDuration } from "@/lib/duration";
import type { RewriteRequest } from "@/lib/script/fit";
import type { Occasion, Script } from "@/lib/script/types";
import { getTemplate } from "@/lib/templates";

/**
 * The only place an LLM is used.
 *
 * The duration engine is deterministic and stays that way — the model writes
 * prose and nothing else. It never decides how long anything is, and it is
 * never asked to regenerate a whole speech once one exists.
 */

const MODEL = "claude-opus-5";

export class MissingApiKeyError extends Error {
  constructor() {
    super(
      "Lipsește ANTHROPIC_API_KEY. Teleprompterul funcționează fără el — " +
        "lipește-ți textul manual în editor.",
    );
    this.name = "MissingApiKeyError";
  }
}

export class RefusedError extends Error {
  constructor(reason?: string | null) {
    super(`Modelul a refuzat cererea${reason ? `: ${reason}` : "."}`);
    this.name = "RefusedError";
  }
}

export function hasApiKey(): boolean {
  return Boolean(process.env.ANTHROPIC_API_KEY);
}

function client(): Anthropic {
  if (!hasApiKey()) throw new MissingApiKeyError();
  return new Anthropic();
}

const SYSTEM = `Ești un scriitor de discursuri și antrenor de livrare, nativ român.

Scrii pentru ureche, nu pentru ochi. Textul tău va fi rostit cu voce tare de o
persoană reală, în fața unei săli reale, cu un cronometru care contează.

Reguli:
- Română curată, cu diacritice. Fără regionalisme forțate, fără englezisme.
- Propoziții scurte. Dacă o propoziție nu poate fi rostită dintr-o respirație,
  taie-o în două.
- Folosește detaliile concrete primite în brief. Ele sunt singurul motiv pentru
  care discursul ăsta nu seamănă cu altul. Numele, ora, locul, replica exactă —
  toate intră în text.
- Interzis: „în această zi specială”, „cuvintele nu pot exprima”, „din adâncul
  inimii”, „o nouă etapă a vieții”, orice formulă care ar putea apărea în
  discursul oricui altcuiva.
- Nu explica gluma după ce o spui.
- Marchează pauzele intenționate cu [pauză] pe linie separată. Folosește-le rar,
  doar unde tăcerea chiar lucrează.
- Nu scrie titluri, etichete de secțiune, indicații de regie sau ghilimele în
  jurul discursului. Doar textul rostit.

Lungimea contează mai mult decât orice altceva. Când primești un număr țintă de
cuvinte, respectă-l — un discurs care depășește timpul e un discurs ratat.`;

const SECTIONS_SCHEMA = {
  type: "object",
  properties: {
    sections: {
      type: "array",
      items: {
        type: "object",
        properties: {
          id: { type: "string", description: "ID-ul secțiunii din brief" },
          text: { type: "string", description: "Textul rostit al secțiunii" },
        },
        required: ["id", "text"],
        additionalProperties: false,
      },
    },
  },
  required: ["sections"],
  additionalProperties: false,
} as const;

export interface GenerateInput {
  occasion: Occasion;
  targetSeconds: number;
  profile: Script["profile"];
  intake: Record<string, string>;
  /** Section ids with their target seconds and brief. */
  sections: Array<{ id: string; title: string; brief: string; seconds: number }>;
}

function intakeBlock(occasion: Occasion, intake: Record<string, string>): string {
  const template = getTemplate(occasion);
  return template.questions
    .map((q) => {
      const answer = (intake[q.id] ?? "").trim();
      if (!answer) return null;
      return `${q.question}\n  → ${answer}`;
    })
    .filter(Boolean)
    .join("\n\n");
}

/** Concatenate the text blocks, ignoring thinking and any other block type. */
function textFrom(content: Array<{ type: string }>): string {
  return content
    .filter((b): b is { type: "text"; text: string } => b.type === "text")
    .map((b) => b.text)
    .join("");
}

/**
 * First pass: write every section at once so the model can carry a single voice
 * across the speech and avoid repeating an image between sections.
 */
export async function generateSections(
  input: GenerateInput,
): Promise<Array<{ id: string; text: string }>> {
  const anthropic = client();

  const sectionBriefs = input.sections
    .map((s) => {
      const words = approximateWordsForSeconds(s.seconds, {
        profile: input.profile,
      });
      return `- id: ${s.id}
  secțiune: ${s.title}
  rol: ${s.brief}
  durată țintă: ${formatDuration(s.seconds)} (aproximativ ${words} de cuvinte)`;
    })
    .join("\n");

  const template = getTemplate(input.occasion);

  const prompt = `Ocazie: ${template.label}
Durata totală țintă: ${formatDuration(input.targetSeconds)}

RĂSPUNSURILE VORBITORULUI (materia primă — folosește-le concret):

${intakeBlock(input.occasion, input.intake)}

SECȚIUNI DE SCRIS:

${sectionBriefs}

Scrie fiecare secțiune. Respectă numărul de cuvinte indicat pentru fiecare —
e singura cale prin care discursul iese la fix. Secțiunile trebuie să curgă una
din alta ca un singur discurs, nu ca cinci fragmente separate.`;

  const response = await anthropic.beta.messages.create({
    model: MODEL,
    max_tokens: 16000,
    // Safety classifiers can decline a request; the default fallback re-runs it
    // on a suitable model instead of handing back an error.
    betas: ["server-side-fallback-2026-07-01"],
    fallbacks: "default",
    thinking: { type: "adaptive" },
    output_config: {
      effort: "high",
      format: { type: "json_schema", schema: SECTIONS_SCHEMA },
    },
    system: SYSTEM,
    messages: [{ role: "user", content: prompt }],
  });

  if (response.stop_reason === "refusal") {
    throw new RefusedError(response.stop_details?.explanation);
  }

  const raw = textFrom(response.content);
  const parsed = JSON.parse(raw) as { sections: Array<{ id: string; text: string }> };
  return parsed.sections;
}

/**
 * Second pass and beyond: one section, one length target, everything else left
 * alone. This is what keeps the fit loop from laundering the speaker's own
 * details out of the speech.
 */
export async function rewriteSection(req: RewriteRequest): Promise<string> {
  const anthropic = client();

  const words = approximateWordsForSeconds(req.targetSeconds, {
    profile: req.script.profile,
    sample: req.section.text,
  });

  const verb =
    req.direction === "contract"
      ? "Scurtează secțiunea"
      : "Extinde secțiunea";

  const guidance =
    req.direction === "contract"
      ? `Taie ce e decorativ: adjective, reformulări, propoziții care repetă o idee
deja spusă. NU tăia detaliile concrete — numele, ora, locul, replica exactă,
gluma. Ele sunt motivul pentru care discursul există.`
      : `Adaugă adâncime în ce e deja acolo: un detaliu senzorial din scena
existentă, o consecință, o replică. NU adăuga idei noi și NU inventa fapte care
nu apar în text sau în restul discursului.`;

  const rest = req.script.sections
    .filter((s) => s.id !== req.section.id && s.text.trim())
    .map((s) => `[${s.title}]\n${s.text.trim()}`)
    .join("\n\n");

  const prompt = `${verb} „${req.section.title}” la aproximativ ${words} de cuvinte
(${formatDuration(req.targetSeconds)} rostit).

${guidance}

Păstrează vocea, ordinea ideilor și tot ce e specific. Răspunde DOAR cu textul
nou al secțiunii, fără titlu și fără explicații.

SECȚIUNEA DE MODIFICAT:
${req.section.text.trim()}

${rest ? `RESTUL DISCURSULUI (context — nu îl rescrie, doar evită să repeți):\n${rest}` : ""}`;

  const response = await anthropic.beta.messages.create({
    model: MODEL,
    max_tokens: 8000,
    betas: ["server-side-fallback-2026-07-01"],
    fallbacks: "default",
    thinking: { type: "adaptive" },
    output_config: { effort: "medium" },
    system: SYSTEM,
    messages: [{ role: "user", content: prompt }],
  });

  if (response.stop_reason === "refusal") {
    throw new RefusedError(response.stop_details?.explanation);
  }

  return textFrom(response.content).trim();
}
