// Uloha 2.5.1 – grafika – farby (1b)
// Zmena farby textu v konzole na základe hodnoty premennej.
// Program vypisuje čísla 0–50 s farebným odlíšením rozsahov:
//   0–10: zelená, 11–22: červená, 23–35: modrá, 36–50: žltá.
//
// Использует printColoredNumbersRange() + #define для именованных цветов.

#include <stdio.h>
#include <windows.h>

// ─── Console colors (Windows) ───────────────────────────────────────────────
#define CLR_GREEN 2
#define CLR_RED 4
#define CLR_BLUE 1
#define CLR_YELLOW 6
#define CLR_DEFAULT 7

// ─── Helper ─────────────────────────────────────────────────────────────────

/** Print numbers [from..to] in the given console color. */
static void printRange(HANDLE h, int from, int to, int color) {
  SetConsoleTextAttribute(h, (WORD)color);
  for (int i = from; i <= to; i++) {
    printf("%03d\n", i);
    Sleep(100);
  }
}

// ─── Main ───────────────────────────────────────────────────────────────────

int main(void) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  printRange(hConsole, 0, 10, CLR_GREEN);
  printRange(hConsole, 11, 22, CLR_RED);
  printRange(hConsole, 23, 35, CLR_BLUE);
  printRange(hConsole, 36, 50, CLR_YELLOW);

  SetConsoleTextAttribute(hConsole, CLR_DEFAULT);
  printf("\nStlac a skoncime . . .");
  getchar();
  getchar();

  return 0;
}