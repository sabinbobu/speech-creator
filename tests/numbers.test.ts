import { describe, expect, it } from "vitest";
import { expandNumbers, numberToRomanian } from "@/lib/duration/numbers";

describe("numberToRomanian", () => {
  it("spells units and teens", () => {
    expect(numberToRomanian(0)).toBe("zero");
    expect(numberToRomanian(7)).toBe("șapte");
    expect(numberToRomanian(11)).toBe("unsprezece");
    expect(numberToRomanian(19)).toBe("nouăsprezece");
  });

  it("joins tens with 'și'", () => {
    expect(numberToRomanian(20)).toBe("douăzeci");
    expect(numberToRomanian(21)).toBe("douăzeci și unu");
    expect(numberToRomanian(65)).toBe("șaizeci și cinci");
  });

  it("uses feminine forms for hundreds and thousands", () => {
    expect(numberToRomanian(100)).toBe("o sută");
    expect(numberToRomanian(200)).toBe("două sute");
    expect(numberToRomanian(1000)).toBe("o mie");
    expect(numberToRomanian(2000)).toBe("două mii");
  });

  it("spells a year the way it is actually read aloud", () => {
    expect(numberToRomanian(2026)).toBe("două mii douăzeci și șase");
  });

  it("handles millions", () => {
    expect(numberToRomanian(1_000_000)).toBe("un milion");
    expect(numberToRomanian(3_500_000)).toBe("trei milioane cinci sute mii");
  });
});

describe("expandNumbers", () => {
  it("leaves plain words alone", () => {
    expect(expandNumbers("mulțumesc")).toBe("mulțumesc");
  });

  it("expands digits inside a token", () => {
    expect(expandNumbers("2026")).toBe("două mii douăzeci și șase");
  });

  it("reads a decimal separator as 'virgulă'", () => {
    expect(expandNumbers("3,5")).toBe("trei virgulă cinci");
  });
});
