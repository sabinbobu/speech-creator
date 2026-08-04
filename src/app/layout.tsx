import type { Metadata } from "next";
import Link from "next/link";
import "./globals.css";

export const metadata: Metadata = {
  title: "Cadență — discursuri care se încadrează în timp",
  description:
    "Antrenor de livrare pentru discursuri în română: durată exactă, prozodie nativă și un teleprompter care te urmărește pe tine.",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="ro">
      <body className="min-h-screen">
        <header className="border-b border-line">
          <div className="mx-auto flex max-w-5xl items-center justify-between px-5 py-4">
            <Link href="/" className="group flex items-baseline gap-2">
              <span className="display text-xl tracking-tight text-cream">
                Cadență
              </span>
              <span className="hidden text-xs text-faint sm:inline">
                discursuri la secundă
              </span>
            </Link>
            <nav className="flex items-center gap-5 text-sm">
              <Link
                href="/prompter"
                className="text-muted transition-colors hover:text-cream"
              >
                Teleprompter
              </Link>
              <Link
                href="/compose"
                className="rounded-md bg-brass px-3 py-1.5 font-medium text-ink transition-opacity hover:opacity-90"
              >
                Discurs nou
              </Link>
            </nav>
          </div>
        </header>
        <main className="mx-auto max-w-5xl px-5 py-8">{children}</main>
        <footer className="mx-auto max-w-5xl px-5 py-10 text-xs text-faint">
          Fără cont, fără plăți. Discursurile tale rămân în browserul tău.
        </footer>
      </body>
    </html>
  );
}
