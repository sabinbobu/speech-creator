import { describe, expect, it } from "vitest";
import { PAUSE_TABLE, pauseForPunctuation } from "@/lib/duration/pauses";

describe("pauseForPunctuation", () => {
  it("returns nothing when a word runs into the next", () => {
    expect(pauseForPunctuation("")).toBeNull();
  });

  it("maps the basic marks", () => {
    expect(pauseForPunctuation(",")).toEqual({
      kind: "comma",
      ms: PAUSE_TABLE.comma,
    });
    expect(pauseForPunctuation(".")).toEqual({
      kind: "period",
      ms: PAUSE_TABLE.period,
    });
  });

  it("reads an ellipsis as one long beat, not three periods", () => {
    expect(pauseForPunctuation("...")?.kind).toBe("ellipsis");
    expect(pauseForPunctuation("…")?.kind).toBe("ellipsis");
  });

  it("lets the stronger mark win in a cluster", () => {
    expect(pauseForPunctuation("?!")?.kind).toBe("exclamation");
    expect(pauseForPunctuation('."')?.kind).toBe("period");
  });

  it("gives a dash a shorter beat than a period", () => {
    expect(pauseForPunctuation("—")!.ms).toBeLessThan(PAUSE_TABLE.period);
  });

  it("orders the table the way speech actually behaves", () => {
    expect(PAUSE_TABLE.comma).toBeLessThan(PAUSE_TABLE.period);
    expect(PAUSE_TABLE.period).toBeLessThan(PAUSE_TABLE.paragraph);
  });
});
