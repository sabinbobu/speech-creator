# Cadență

**Un antrenor de livrare pentru discursuri în română, cu un editor atașat — nu un generator de discursuri cu teleprompter atașat.**

Orice model de limbă scrie un discurs de cinci minute dintr-un prompt. Generarea
de text e o marfă. Partea grea — și singura care contează pentru cineva care are
o nuntă peste trei zile — e ca discursul să dureze *exact* cinci minute când îl
rostește el, cu vocea lui, în sala aia.

---

## Cele trei diferențiatoare

Exact trei. Nimic altceva.

1. **Precizie de durată.** „5:00 ± 5 secunde", garantat și verificabil. Motorul
   numără silabe și pauze de punctuație, nu cuvinte pe minut.
2. **Română nativă.** Silabificare cu diftongi, triftongi, hiat morfologic și
   regula lui *-i* final neaccentuat. Numeralele se citesc, nu se numără ca cifre.
3. **Teleprompter care te urmărește pe tine.** Fiecare cuvânt are durata lui.
   Un derulaj cu WPM fix se desincronizează în treizeci de secunde, pentru că
   „azi" și „binecuvântare" nu sunt aceeași cantitate de vorbire.

---

## Stare: V0

Ce există:

- Motor de durată determinist (zero LLM), testat cu 86 de teste
- Teleprompter karaoke cu timing per cuvânt, ritm reglabil live, pauze marcate
- Intake de 6 întrebări obligatorii + 3 șabloane (nuntă, dezbatere, prezentare)
- Generare cu constrângere de durată: buclă generează → estimează → rescrie
  chirurgical doar secțiunile deblocate
- Editor pe secțiuni, cu durată și țintă per secțiune, cu blocare
- Persistență în localStorage. **Fără cont, fără plăți, fără backend.**
- Harness de evaluare (100 de cazuri) + unealtă de calibrare cu cronometru

Ce **nu** există, deliberat (V1/V2 din plan): microfon și ASR, aliniere la
script, raport post-livrare, versionare, export cue cards, share link, plăți.
Planul e explicit: un V0 cu conturi și plăți nu se lansează niciodată.

---

## Pornire

```bash
npm install
npm run dev            # http://localhost:3000
```

Teleprompterul funcționează **fără nicio cheie API** — lipești textul și pornești.
Ăsta e demo-ul, și nu depinde de niciun model.

Pentru generarea de discursuri:

```bash
export OPENAI_API_KEY=sk-...
export OPENAI_MODEL=gpt-4o      # opțional; implicit gpt-4o
```

Fără cheie, `/api/generate` întoarce 503 cu un mesaj care trimite utilizatorul
către teleprompter. Aplicația nu se strică.

| Comandă | Ce face |
| --- | --- |
| `npm run dev` | Server de dezvoltare |
| `npm test` | 86 de teste (motor, silabe, numerale, pauze, buclă, intake) |
| `npm run typecheck` | `tsc --noEmit` |
| `npm run eval` | Harness de evaluare pe 100 de cazuri |
| `npm run calibrate` | **Calibrare cu cronometru — citește secțiunea de mai jos** |

---

## Motorul de durată

Nucleul tehnic. TypeScript pur, determinist, fără nicio dependență, fără LLM.

```
durată(cuvânt) = silabe × msPerSilabă + overhead
+ pauză(punctuația care urmează)
```

**De ce silabe și nu cuvinte.** Lungimea cuvintelor variază enorm în română.
Un estimator pe cuvinte se înșală sistematic pe orice text care nu are
distribuția lui de antrenament. Silabele sunt unitatea reală a timpului de
vorbire.

**De ce contează pauzele.** Într-un discurs de cinci minute, pauzele de
punctuație ocupă ~15–20% din timpul de ceas. Un estimator care le ignoră
greșește cu un minut întreg.

**Silabificarea** rezolvă grupurile vocalice prin potrivire greedy împotriva
inventarului de triftongi și diftongi, apoi aplică:

- diftongi doar-finali: `ii` și `eu` fuzionează la final de cuvânt, dar se
  deschid în hiat la mijloc (`co-pii` vs `vi-i-tor`, `me-reu` vs `îm-pre-u-nă`)
- `-ie` / `-ia` final după consoană = hiat (`fa-mi-li-e`, `Ro-mâ-ni-a`)
- *-i* final neaccentuat e nesilabic (`lupi` = 1, `oameni` = 2)
- hiat morfologic la cusătura prefixelor și a neologismelor latinești
  (`re-a-li-ta-te`, `cre-a-ție`, `te-a-tru`)

**Numeralele** se extind înainte de numărare: `2026` sunt opt silabe
(„do-uă mii do-uă-zeci și șa-se"), nu patru caractere.

---

## ⚠️ Stare de calibrare — citește asta înainte să crezi vreun număr

**Constanta `msPerSyllable` din `src/lib/duration/calibration.ts` NU a fost
potrivită pe înregistrări umane.** Valorile livrate (245 / 210 / 182 ms/silabă)
sunt puncte de plecare derivate din literatură pentru oratorie românească —
un *prior*, nu un rezultat măsurat.

Asta înseamnă că promisiunea „±5 secunde" nu e încă demonstrată împotriva unui
cronometru. Bucla de ajustare nimerește ținta pe care i-o dă motorul; dacă
motorul e decalat, toate discursurile ies decalate cu aceeași proporție.

**Pasul care rezolvă asta durează cincisprezece minute:**

```bash
npm run calibrate
```

Citești cu voce tare cinci texte de lungimi diferite, unealta te
cronometrează, potrivește constanta prin cele mai mici pătrate ponderate pe
silabe și raportează eroarea reziduală per text. Dacă nu ajungi sub ±5%, afli
asta în cincisprezece minute, nu în două luni.

---

## Raport de acuratețe

### Numărătoarea de silabe

Măsurată împotriva unor liste etichetate manual, cu convenția că *-i* final
după consoană e nesilabic.

| Set | n | Potrivire exactă | MAE | Bias |
| --- | --- | --- | --- | --- |
| `SYLLABLE_CORPUS` (vocabular de eveniment) | 100 | 100% | 0.000 | 0.000 |
| `SYLLABLE_HELDOUT` (civic, academic, neologisme) | 64 | 100% | 0.000 | 0.000 |

**Cât de mult să crezi cifrele astea.** Nu foarte mult, și iată de ce.

Prima măsurătoare pe un set complet nevăzut a dat **75,6% potrivire exactă, cu
bias −0,200 silabe/cuvânt** — o subestimare *sistematică*, exact tipul de eroare
care nu se anulează pe un discurs întreg și care ar face fiecare discurs să
depășească timpul. Ratările erau toate hiat latinesc (`cre-a-ție`,
`re-a-li-ta-te`, `te-a-tru`). Am adăugat regulile de hiat morfologic, apoi am
măsurat pe un al doilea set proaspăt: **98% (49/50), bias −0,020**. Singura
ratare, `Ro-mâ-ni-a`, a produs regula `-ia` final.

După acea corecție am mutat cazurile grele în `SYLLABLE_HELDOUT`. **Asta le-a
transformat în date de antrenament.** Cele două tabele de 100% de mai sus
măsoară potrivire, nu generalizare. Ultima măsurătoare curată a fost **98%**.

Dacă extinzi regulile: construiește un set nou, etichetează-l fără să te uiți la
implementare, măsoară o dată. Bias-ul contează mai mult decât potrivirea exactă —
erorile de ±1 se anulează pe 700 de cuvinte, o înclinare sistematică nu.

### Bucla de ajustare a duratei

`npm run eval` — 100 de cazuri: ocazie × durată țintă × eroare a primei
variante × bias al scriitorului × zgomot. Scriitorul e sintetic și determinist,
ca evaluarea să ruleze offline; ratează lungimea cerută cu un bias direcțional
constant plus zgomot, exact ca un model real.

| Metrică | Valoare |
| --- | --- |
| În ±5s | **74%** |
| În ±2% | 60% |
| Eroare medie absolută | **3,85s** |
| p50 / p90 / max | 3,49s / 5,87s / 15,11s |
| Pași folosiți în medie | 1,80 din 3 |
| **Fără buclă (referință)** | **125,85s** eroare medie |

Bucla reduce eroarea medie de la 126s la 3,9s — de ~33 de ori.

**De ce exact 3 pași.** Planul spune „maximum 3". Măsurat:

| Pași | În ±5s | Eroare medie | p90 |
| --- | --- | --- | --- |
| 1 | 46% | 7,98s | 18,26s |
| 2 | 67% | 4,95s | 9,30s |
| **3** | **74%** | **3,85s** | **5,87s** |
| 4 | 77% | 3,69s | 5,74s |
| 5 | 78% | 3,61s | 5,56s |

Al patrulea pas aduce 3 puncte procentuale, al cincilea unul singur, fiecare
costând un tur complet de apeluri la model. Trei e locul potrivit.

**Ce NU măsoară asta:** dacă motorul de durată e de acord cu un cronometru.
Un scor perfect aici cu un motor necalibrat înseamnă că fiecare discurs
aterizează la exact lungimea greșită. Vezi secțiunea de calibrare.

---

## Bucla de ajustare

Nucleul roadmap-ului, în `src/lib/script/fit.ts`:

```
generează → estimează → contractă/expandează DOAR secțiunile marcate → repetă (max 3)
```

Trei lucruri o fac să funcționeze:

**Nu regenerează niciodată tot discursul.** Regenerarea aruncă detaliul personal
care face discursul să merite rostit și face lungimea să rătăcească
imprevizibil. Editarea e chirurgicală, pe secțiune.

**Secțiunile blocate sunt intangibile.** Gluma pe care a scris-o utilizatorul
supraviețuiește fiecărei treceri.

**Corecție de bias cu reacție inversă.** Modelele ratează o instrucțiune de
lungime într-o direcție constantă — ceri 40 de secunde, primești fiabil 32. Să
ceri iar același număr reproduce aceeași ratare, iar bucla se blochează scurt la
infinit. Așa că bucla măsoară ce a întors modelul față de ce i-a cerut și
compensează la următoarea cerere. Estimarea se actualizează după *fiecare*
secțiune, nu la finalul pasului, ca secțiunile rămase din același pas să
beneficieze deja.

**Refuză o rescriere care înrăutățește lucrurile.** Dacă textul nou aterizează
mai departe de țintă decât cel pe care l-ar înlocui, e aruncat — dar bias-ul pe
care tocmai l-a dezvăluit e păstrat. Fără garanția asta, un scriitor cu bias
0,65 căruia i se cere să *extindă* o secțiune întoarce text mai scurt și bucla
merge înapoi. Adăugarea ei a redus eroarea maximă de la 49,6s la 15,1s.

---

## Intake-ul e produsul

Discursurile generate sună generic pentru că input-ul e generic. „Scrie un
discurs pentru sora mea" nu-i dă unui model nimic ce nu se află deja în alte o
mie de discursuri de nuntă.

Așa că aplicația refuză să genereze până nu are lucrurile pe care doar
vorbitorul le știe: un moment concret, o glumă internă, un lucru observabil pe
care îl admiră. Sunt șase întrebări, toate obligatorii, cu prag minim de
lungime — pentru că „sunt oameni buni" trece de o verificare de câmp obligatoriu
și produce un discurs despre nimeni.

Asta e moat-ul, nu prompt-ul.

---

## Arhitectură

```
src/lib/duration/     motor determinist — silabe, pauze, timeline, calibrare
src/lib/script/       model de script, estimare pe secțiuni, bucla de ajustare
src/lib/templates.ts  3 șabloane + cele 6 întrebări de intake
src/lib/llm.ts        SINGURUL loc cu apeluri la model (OpenAI)
src/components/       teleprompterul
src/app/api/          generate (o variantă) + fit (un pas)
eval/                 corpusuri, harness, calibrare
tests/                86 de teste
```

Bucla de ajustare rulează **un pas per cerere HTTP**, nu trei, ca o funcție
serverless să nu stea într-un singur apel prin trei tururi de model. Clientul
conduce bucla și duce corecția de bias mai departe între cereri.

LLM-ul e injectat ca dependență în buclă, așa că bucla se testează integral
fără niciun model în cameră.

---

## Note

**Numele.** Planul spune că „Speech Creator" e generic, mort pentru SEO și
imposibil de marcat. L-am schimbat în **Cadență** înainte de a cumpăra vreun
domeniu — cuvânt românesc, scurt, și înseamnă exact lucrul pe care produsul îl
vinde.

**Deploy pe Vercel.** Rutele API au `maxDuration = 300`. Pe planul Hobby limita
e 60s, așa că generarea poate expira; bucla e deja împărțită pe cereri, ceea ce
ajută, dar pentru trafic real trebuie Pro.

**Modelul.** OpenAI, prin `chat.completions`, cu structured outputs în mod
`strict` pentru generare. Id-ul modelului se configurează prin `OPENAI_MODEL`
(implicit `gpt-4o`), ca să poți trece pe un model mai bun fără modificări de cod.
Refuzurile vin pe câmpul `refusal`, nu ca eroare HTTP, și sunt tratate explicit.

---

## Ce urmează (din plan)

Pașii 6 și 8–10 din roadmap, în ordine:

1. **Zece utilizatori reali** — grupuri de nuntă, cluburi de dezbateri.
   Privește-i folosind aplicația. Asta înainte de orice feature nou.
2. **Calibrare pe voci reale**, nu doar pe a ta. Constanta ar putea avea nevoie
   să fie per-utilizator, învățată din prima repetiție.
3. **Microfon: ASR + aliniere la script** (V1). Testează întâi acuratețea în
   română — planul avertizează corect că e mai slabă decât în engleză.
4. **Raport post-livrare**: WPM real vs țintă pe secțiuni, umpluturi RO, pauze > 2s.
5. **Plată: Event pack cu Stripe.** Prima încasare contează mai mult decât orice
   feature nou.
