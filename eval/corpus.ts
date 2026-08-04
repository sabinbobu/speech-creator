/**
 * Calibration corpus.
 *
 * Five Romanian texts of increasing length, in the register the product
 * actually targets. You read these aloud with a stopwatch; `npm run calibrate`
 * fits `msPerSyllable` from your measured times.
 *
 * Read them the way you would deliver them — at a lectern, to a room — not the
 * way you would read a newspaper. The constant you fit is the constant the app
 * will use, so a rushed reading produces an app that runs everyone short.
 */

export interface CalibrationText {
  id: string;
  label: string;
  text: string;
}

export const CALIBRATION_CORPUS: CalibrationText[] = [
  {
    id: "scurt",
    label: "Foarte scurt — un toast",
    text: `Vă mulțumesc că sunteți aici. Pentru Ana și Mihai, pentru anii care vin, și pentru serile în care o să râdem exact ca acum. Să trăiți!`,
  },
  {
    id: "mediu",
    label: "Scurt — o amintire",
    text: `Acum șapte ani, într-o seară de octombrie, Ana m-a sunat din gară la Cluj.

Mi-a spus că a cunoscut pe cineva care râde la aceleași glume proaste ca ea. Atât. Nu mi-a spus cum îl cheamă, nu mi-a spus cu ce se ocupă. Mi-a spus doar partea aia, și mi-a ajuns.`,
  },
  {
    id: "lung",
    label: "Mediu — discurs de naș",
    text: `Dragii mei, nu o să vă țin mult.

Când Ana avea nouă ani, a decis că vrea să fie veterinar. A ținut-o așa până la optsprezece, când a intrat la Litere. Am întrebat-o ce s-a întâmplat cu animalele. Mi-a zis că a rămas la ideea de a avea grijă de cineva, doar că a schimbat specia.

Mihai, tu ai intrat în familia asta într-o zi de marți, cu o pungă de mere de la piață, pentru că nu știai ce se aduce la o primă întâlnire cu părinții. Mama încă vorbește despre merele alea.

Ce am văzut la voi doi în anii ăștia e greu de pus în cuvinte, dar ușor de recunoscut când îl vezi. Vă certați seara și vă împăcați tot seara. Nu v-am văzut niciodată plecând supărați la culcare.

Vă doresc să râdeți la fel de des și peste treizeci de ani.`,
  },
  {
    id: "tehnic",
    label: "Mediu — prezentare tehnică",
    text: `Problema cu care am plecat la drum era simplă de descris și greu de rezolvat.

Sistemul vechi marca patru la sută din tranzacții ca fiind fraudă. Din ele, nouăzeci la sută erau alarme false. Asta înseamnă că un om aflat în vacanță rămânea cu cardul blocat pentru că a cumpărat benzină în alt oraș decât de obicei.

Am ales gradient boosting în locul unei rețele neuronale, și nu pentru performanță. Am ales-o pentru că trebuia să pot explica unui operator uman, în două propoziții, de ce a fost blocată o tranzacție anume.

Rezultatul, măsurat pe două sute de mii de tranzacții reale din două mii douăzeci și patru: alarmele false au scăzut de la nouăzeci la sută la treizeci și unu la sută. Rata de fraudă prinsă a rămas neschimbată.`,
  },
  {
    id: "foarte-lung",
    label: "Lung — discurs complet",
    text: `Bună seara tuturor. Pentru cei care nu mă cunosc, sunt sora Anei. Am împărțit o cameră cu ea optsprezece ani, așa că tot ce urmează să spun am și dovezi.

Acum șapte ani, într-o seară de octombrie, m-a sunat din gară la Cluj. Era unsprezece noaptea și eu aveam examen a doua zi dimineață. Mi-a spus că a cunoscut pe cineva care râde la aceleași glume proaste ca ea. Nu mi-a spus cum îl cheamă. Nu mi-a spus cu ce se ocupă. Mi-a spus doar că a râs de trei ori în primele cinci minute, ceea ce, pentru cine o cunoaște pe Ana, este un record absolut.

Mihai, tu zici „doar cinci minute” de fiecare dată când pleci undeva. Nu au fost niciodată cinci minute. Ai întârziat la propria cerere în căsătorie cu douăzeci de minute, pentru că te-ai întors după inel. Ana te-a așteptat. Cred că asta spune tot ce trebuie spus despre amândoi.

Ce am învățat privindu-vă în anii ăștia e că răbdarea nu e o virtute pasivă. E o decizie pe care o iei în fiecare seară, de obicei obosit, de obicei când ai avea motive să nu o iei. Voi doi o luați constant. Nu v-am văzut niciodată plecând supărați la culcare, și am avut ocazia să vă văd în zile foarte proaste.

Așa că vă doresc un lucru simplu. Să vă certați în continuare seara și să vă împăcați tot seara. Să râdeți la fel de des și peste treizeci de ani. Și să întârziați împreună, la absolut tot ce urmează.

Să trăiți!`,
  },
];
