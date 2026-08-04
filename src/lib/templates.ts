import type { Occasion, SectionKind } from "@/lib/script/types";
import type { DeliveryProfileId } from "@/lib/duration";

/**
 * Occasion templates and the intake that feeds them.
 *
 * The intake is the product, not the prompt. Generated speeches sound generic
 * because the input is generic — "write a wedding speech for my sister" gives
 * a model nothing that isn't already in a thousand other wedding speeches. So
 * the app refuses to generate until it has extracted the things only this
 * speaker knows: a specific moment, a specific joke, a specific thing they
 * admire. Those details are what the audience remembers, and they are the part
 * a competitor cannot copy.
 */

export interface IntakeQuestion {
  id: string;
  question: string;
  /** Shown under the field: why this question earns its place. */
  hint: string;
  placeholder: string;
  required: boolean;
  /** Answers shorter than this are almost always too vague to use. */
  minLength: number;
  multiline: boolean;
}

export interface TemplateSection {
  title: string;
  kind: SectionKind;
  /** Relative share of the total target duration. */
  weight: number;
  /** What this section has to accomplish; goes to the model verbatim. */
  brief: string;
}

export interface OccasionTemplate {
  id: Occasion;
  label: string;
  blurb: string;
  defaultSeconds: number;
  defaultProfile: DeliveryProfileId;
  durationOptions: number[];
  questions: IntakeQuestion[];
  sections: TemplateSection[];
}

const NUNTA: OccasionTemplate = {
  id: "nunta",
  label: "Nuntă / cununie",
  blurb: "Discurs de naș, părinte, frate sau prieten apropiat.",
  defaultSeconds: 300,
  defaultProfile: "rar",
  durationOptions: [120, 180, 240, 300, 420],
  questions: [
    {
      id: "cine",
      question: "Pe cine sărbătorim și cum îi cheamă?",
      hint: "Numele exacte, așa cum le vei rosti în sală.",
      placeholder: "Ana și Mihai",
      required: true,
      minLength: 2,
      multiline: false,
    },
    {
      id: "relatie",
      question: "Cine ești tu pentru ei?",
      hint: "Publicul trebuie să știe în primele 15 secunde de ce vorbești tu.",
      placeholder: "Sunt sora Anei. Am crescut în aceeași cameră 18 ani.",
      required: true,
      minLength: 10,
      multiline: false,
    },
    {
      id: "moment",
      question: "Un moment concret pe care l-ai trăit cu ei. O zi, un loc, o oră.",
      hint:
        "Cel mai important răspuns din tot formularul. Nu „sunt oameni buni” — ci ce s-a întâmplat, unde, și ce s-a spus.",
      placeholder:
        "În octombrie 2019, la 2 noaptea, Ana m-a sunat din gară la Cluj să-mi spună că a cunoscut pe cineva care râde la aceleași glume proaste ca ea.",
      required: true,
      minLength: 40,
      multiline: true,
    },
    {
      id: "gluma",
      question: "O glumă internă sau un obicei al lor pe care îl știe sala.",
      hint: "Râsul de recunoaștere e cel mai bun sunet dintr-un discurs.",
      placeholder:
        "Mihai zice „doar cinci minute” de fiecare dată când pleacă undeva. Nu a fost niciodată cinci minute.",
      required: true,
      minLength: 20,
      multiline: true,
    },
    {
      id: "admiri",
      question: "Ce admiri concret la ei ca pereche?",
      hint: "Un lucru observabil, nu o calitate abstractă.",
      placeholder:
        "Se ceartă și se împacă în aceeași seară. Nu am văzut niciunul dintre ei plecând supărat la culcare.",
      required: true,
      minLength: 25,
      multiline: true,
    },
    {
      id: "final",
      question: "Ce vrei să simtă sala în ultima secundă?",
      hint: "Un singur cuvânt. Discursul se construiește înapoi de la el.",
      placeholder: "Recunoștință",
      required: true,
      minLength: 3,
      multiline: false,
    },
  ],
  sections: [
    {
      title: "Deschidere",
      kind: "deschidere",
      weight: 1,
      brief:
        "Cine ești și de ce vorbești tu. Scurt, fără „mă numesc și aș vrea să spun câteva cuvinte”. Intră direct.",
    },
    {
      title: "Povestea",
      kind: "poveste",
      weight: 3,
      brief:
        "Momentul concret din intake, spus ca o scenă: unde, când, ce s-a spus. Aici stă tot discursul.",
    },
    {
      title: "Momentul de umor",
      kind: "umor",
      weight: 1.5,
      brief:
        "Gluma internă din intake. O singură glumă, dusă până la capăt, fără să o explici după.",
    },
    {
      title: "Mesajul",
      kind: "mesaj",
      weight: 2,
      brief:
        "Ce admiri la ei, legat de poveste. Trece de la ce a fost la ce urmează.",
    },
    {
      title: "Închiderea",
      kind: "inchidere",
      weight: 1,
      brief:
        "Urarea și toastul. Ultima propoziție trebuie să livreze exact emoția cerută în intake.",
    },
  ],
};

const DEZBATERE: OccasionTemplate = {
  id: "dezbatere",
  label: "Dezbatere / olimpiadă",
  blurb: "Discurs constructiv cu argument, dovadă și răspuns la contraargument.",
  defaultSeconds: 240,
  defaultProfile: "alert",
  durationOptions: [120, 180, 240, 300, 360],
  questions: [
    {
      id: "motiune",
      question: "Care este moțiunea, cuvânt cu cuvânt?",
      hint: "Formularea exactă. Jumătate din dezbateri se pierd pe definiții.",
      placeholder:
        "Această Cameră ar interzice publicitatea la jocuri de noroc.",
      required: true,
      minLength: 15,
      multiline: true,
    },
    {
      id: "parte",
      question: "Ce parte susții și care e linia ta în două propoziții?",
      hint: "Dacă nu încape în două propoziții, nu ai încă o linie.",
      placeholder:
        "Afirmator. Publicitatea la pariuri transformă un viciu într-un obicei normal, iar costul îl plătesc familiile, nu operatorii.",
      required: true,
      minLength: 25,
      multiline: true,
    },
    {
      id: "argument",
      question: "Argumentul tău cel mai puternic și mecanismul lui.",
      hint: "Nu doar ce susții — de ce se întâmplă asta, pas cu pas.",
      placeholder:
        "Expunerea repetată mută percepția de la „risc” la „divertisment”. Cine vede 30 de reclame pe zi nu mai evaluează riscul, îl recunoaște ca normal.",
      required: true,
      minLength: 40,
      multiline: true,
    },
    {
      id: "dovada",
      question: "O dovadă concretă: cifră, studiu, caz.",
      hint: "Un număr pe care îl poți rosti și apăra dacă ești întrebat.",
      placeholder:
        "În Italia, după interdicția din 2019, cheltuiala pe pariuri online a scăzut cu 7% în primul an.",
      required: true,
      minLength: 20,
      multiline: true,
    },
    {
      id: "contra",
      question: "Cel mai puternic contraargument al adversarului.",
      hint: "Îl spui tu primul, altfel îl spune el mai bine.",
      placeholder:
        "Interdicția mută piața în zona gri, unde nu există nicio protecție a consumatorului.",
      required: true,
      minLength: 25,
      multiline: true,
    },
    {
      id: "final",
      question: "Ce vrei să rămână în mintea juriului?",
      hint: "O propoziție. Ultima pe care o rostești.",
      placeholder: "Nu interzicem jocul. Interzicem vânătoarea de jucători.",
      required: true,
      minLength: 10,
      multiline: false,
    },
  ],
  sections: [
    {
      title: "Poziție",
      kind: "deschidere",
      weight: 1,
      brief: "Moțiunea, partea, și linia în două propoziții. Fără preambul.",
    },
    {
      title: "Argument principal",
      kind: "mesaj",
      weight: 2.5,
      brief:
        "Argumentul cu mecanismul explicat pas cu pas. De ce se întâmplă, nu doar că se întâmplă.",
    },
    {
      title: "Dovada",
      kind: "poveste",
      weight: 1.5,
      brief: "Cifra sau cazul concret din intake, cu sursa rostită natural.",
    },
    {
      title: "Răspuns la contraargument",
      kind: "mesaj",
      weight: 2,
      brief:
        "Enunță contraargumentul corect și cinstit, apoi arată de ce nu răstoarnă linia ta.",
    },
    {
      title: "Închidere",
      kind: "inchidere",
      weight: 1,
      brief: "Propoziția finală din intake, fără să rezumi tot ce ai spus.",
    },
  ],
};

const PREZENTARE: OccasionTemplate = {
  id: "prezentare",
  label: "Prezentare tehnică",
  blurb: "Licență, demo de produs sau prezentare de proiect.",
  defaultSeconds: 300,
  defaultProfile: "normal",
  durationOptions: [180, 300, 420, 600, 900],
  questions: [
    {
      id: "subiect",
      question: "Care e subiectul și cine e în sală?",
      hint: "Nivelul publicului decide ce poți sări peste.",
      placeholder:
        "Sistem de detecție a fraudei pentru plăți card. În sală: comisie de licență, doi profesori din afara domeniului.",
      required: true,
      minLength: 20,
      multiline: true,
    },
    {
      id: "problema",
      question: "Ce problemă concretă rezolvi și cine o simte?",
      hint: "Dacă nu doare pe nimeni, nu e o problemă.",
      placeholder:
        "Regulile fixe marchează 4% din tranzacții ca fraudă. 90% sunt false alarme, iar clientul rămâne cu cardul blocat în vacanță.",
      required: true,
      minLength: 30,
      multiline: true,
    },
    {
      id: "decizie",
      question: "Decizia tehnică cheie și de ce ai luat-o.",
      hint: "Comisia întreabă „de ce așa”. Răspunde înainte să întrebe.",
      placeholder:
        "Am ales gradient boosting în loc de rețea neuronală pentru că trebuia să pot explica fiecare decizie de blocare unui operator uman.",
      required: true,
      minLength: 30,
      multiline: true,
    },
    {
      id: "rezultat",
      question: "Un număr concret pe care îl poți apăra.",
      hint: "Un rezultat măsurat, cu ce a fost măsurat.",
      placeholder:
        "Am redus falsele alarme de la 90% la 31%, pe 200.000 de tranzacții reale din 2024.",
      required: true,
      minLength: 20,
      multiline: true,
    },
    {
      id: "greu",
      question: "Ce e cel mai greu de înțeles și cum explici simplu?",
      hint: "Analogia ta, în cuvintele tale.",
      placeholder:
        "Cum învață modelul fără etichete curate. Explic prin „învață ce e normal pentru fiecare client, apoi caută abaterea”.",
      required: true,
      minLength: 25,
      multiline: true,
    },
    {
      id: "final",
      question: "Ce vrei să facă publicul după prezentare?",
      hint: "O acțiune, nu o impresie.",
      placeholder: "Să aprobe trecerea în producție pe 10% din trafic.",
      required: true,
      minLength: 10,
      multiline: false,
    },
  ],
  sections: [
    {
      title: "Problema",
      kind: "deschidere",
      weight: 1,
      brief:
        "Problema concretă și cine o simte. Un exemplu uman înainte de orice termen tehnic.",
    },
    {
      title: "Soluția",
      kind: "mesaj",
      weight: 2,
      brief: "Ce ai construit, la nivelul de detaliu potrivit pentru sală.",
    },
    {
      title: "Decizia tehnică",
      kind: "poveste",
      weight: 2,
      brief:
        "Decizia cheie și alternativa respinsă. Aici se câștigă credibilitatea.",
    },
    {
      title: "Rezultate",
      kind: "mesaj",
      weight: 2,
      brief:
        "Numărul din intake, cu metoda de măsurare. Rostește cifrele în cuvinte.",
    },
    {
      title: "Ce urmează",
      kind: "inchidere",
      weight: 1,
      brief: "Cererea concretă din intake. Închide cu acțiunea, nu cu „mulțumesc”.",
    },
  ],
};

export const TEMPLATES: Record<Occasion, OccasionTemplate> = {
  nunta: NUNTA,
  dezbatere: DEZBATERE,
  prezentare: PREZENTARE,
};

export const OCCASION_LIST: OccasionTemplate[] = [NUNTA, DEZBATERE, PREZENTARE];

export function getTemplate(occasion: Occasion): OccasionTemplate {
  return TEMPLATES[occasion] ?? NUNTA;
}

export interface IntakeValidation {
  ok: boolean;
  missing: string[];
  tooShort: string[];
}

/**
 * Gate generation on a usable intake. Refusing to generate from three vague
 * words is the feature — it is the difference between a speech about this
 * couple and a speech about any couple.
 */
export function validateIntake(
  occasion: Occasion,
  answers: Record<string, string>,
): IntakeValidation {
  const template = getTemplate(occasion);
  const missing: string[] = [];
  const tooShort: string[] = [];

  for (const q of template.questions) {
    if (!q.required) continue;
    const value = (answers[q.id] ?? "").trim();
    if (value.length === 0) {
      missing.push(q.id);
    } else if (value.length < q.minLength) {
      tooShort.push(q.id);
    }
  }

  return { ok: missing.length === 0 && tooShort.length === 0, missing, tooShort };
}
