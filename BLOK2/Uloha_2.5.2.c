// Úloha 2.5.2 – semigrafika (3b)
// Program vypíše na pozíciu [x,y] tabuľku s informáciami o osobe.
// Rámik sa dynamicky prispôsobuje dĺžke textu (nie je „natvrdo").
//
// Používa Windows API: SetConsoleCursorPosition(), SetConsoleTextAttribute()
// Kompilujte v MSVC.

#include <stdio.h>
#include <string.h>
#include <windows.h>

// ─── Box-drawing characters (Code Page 437) ─────────────────────────────────
// Named constants for box-drawing characters — avoids magic numbers throughout.
//
// Double-line frame:
#define DBL_HOR 205 // ═
#define DBL_VER 186 // ║
#define DBL_UL 201  // ╔
#define DBL_UR 187  // ╗
#define DBL_BL 200  // ╚
#define DBL_BR 188  // ╝
#define DBL_ML 204  // ╠
#define DBL_MR 185  // ╣

// ─── Console colors ─────────────────────────────────────────────────────────
#define CLR_FRAME 11 // light cyan
#define CLR_TITLE 14 // yellow
#define CLR_DATA 15  // white
#define CLR_RESET 7  // default

// ═══════════════════════════════════════════════════════════════════════════
// Helper functions
// ═══════════════════════════════════════════════════════════════════════════

/** Move console cursor to (x, y). */
static void gotoxy(int x, int y) {
  COORD pos;
  pos.X = (SHORT)x;
  pos.Y = (SHORT)y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/** Set console text color. */
static void setColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

/** Draw a full-width horizontal line:  left ── mid ── mid ── right */
static void drawHLine(int x, int y, int width, int left, int fill, int right) {
  gotoxy(x, y);
  printf("%c", left);
  for (int i = 0; i < width; i++)
    printf("%c", fill);
  printf("%c", right);
}

/** Draw a data row:  ║ Label      : Value            ║ */
static void drawRow(int x, int y, int width, const char *label,
                    const char *value) {
  gotoxy(x, y);
  printf("%c %-10s: %-*s %c", (char)DBL_VER, label, width - 14, value,
         (char)DBL_VER);
}

// ═══════════════════════════════════════════════════════════════════════════
// Main
// ═══════════════════════════════════════════════════════════════════════════

int main(void) {
  int startX, startY;

  // Data — change these values and the frame resizes automatically.
  const char *meno = "Jan Novak";
  const char *fakulta = "FEI";
  const char *predmet = "Architektura pocitacov";
  const char *rok = "2024/2025";
  const char *os_id = "12345";

  printf("Zadajte suradnicu X: ");
  scanf("%d", &startX);
  printf("Zadajte suradnicu Y: ");
  scanf("%d", &startY);

  system("cls");

  // Compute frame width from the longest value.
  const char *vals[] = {meno, fakulta, predmet, rok, os_id};
  int maxLen = 0;
  for (int i = 0; i < 5; i++) {
    int len = (int)strlen(vals[i]);
    if (len > maxLen)
      maxLen = len;
  }
  int width = maxLen + 16; // label(10) + ": "(2) + padding(4)

  // ── Draw frame ──────────────────────────────────────────────
  setColor(CLR_FRAME);
  drawHLine(startX, startY, width, DBL_UL, DBL_HOR, DBL_UR);

  // Title row
  gotoxy(startX, startY + 1);
  setColor(CLR_TITLE);
  printf("%c%-*s%c", (char)DBL_VER, width, "  INFORMACIE O STUDENTOVI",
         (char)DBL_VER);

  setColor(CLR_FRAME);
  drawHLine(startX, startY + 2, width, DBL_ML, DBL_HOR, DBL_MR);

  // Data rows
  setColor(CLR_DATA);
  drawRow(startX, startY + 3, width, "Meno", meno);
  drawRow(startX, startY + 4, width, "Fakulta", fakulta);
  drawRow(startX, startY + 5, width, "Predmet", predmet);
  drawRow(startX, startY + 6, width, "Rok", rok);
  drawRow(startX, startY + 7, width, "Os. c.", os_id);

  // Bottom border
  setColor(CLR_FRAME);
  drawHLine(startX, startY + 8, width, DBL_BL, DBL_HOR, DBL_BR);

  // Reset and move cursor below the table
  setColor(CLR_RESET);
  gotoxy(0, startY + 10);

  return 0;
}
