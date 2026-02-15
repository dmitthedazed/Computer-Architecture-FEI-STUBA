// Úloha 2.6 – klávesnica a myš (4b)
// Meranie reakčného času: program vygeneruje náhodný znak,
// zobrazí ho a meria čas do stlačenia rovnakej klávesy.
//
// F1  – zobrazí návod
// F2  – spustí meranie
// F10 / ESC – ukončí program
//
// Vyžaduje: windows.h, conio.h, time.h
// Kompilujte v MSVC.

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void zobrazNavod() {
  system("cls");
  printf("\n");
  printf("  +============================================+\n");
  printf("  |                                            |\n");
  printf("  |     M E R A N I E   R E A K C I E          |\n");
  printf("  |                                            |\n");
  printf("  +============================================+\n");
  printf("  |                                            |\n");
  printf("  |  Program vygeneruje nahodny znak.          |\n");
  printf("  |  Stlacte rovnaku klavesu co najrychlejsie. |\n");
  printf("  |  Iny znak sa ignoruje.                     |\n");
  printf("  |                                            |\n");
  printf("  |  [F1]  - tento navod                       |\n");
  printf("  |  [F2]  - spustit meranie                   |\n");
  printf("  |  [F10] - ukoncit program                   |\n");
  printf("  |  [ESC] - ukoncit program                   |\n");
  printf("  |                                            |\n");
  printf("  +============================================+\n");
  printf("\n  Stlacte lubovolnu klavesu...\n");
  _getch();
}

void spustiMeranie() {
  srand((unsigned int)time(NULL));
  int pokracovat = 1;

  while (pokracovat) {
    // Generuj náhodné písmeno A–Z
    char ciel = 'A' + (rand() % 26);
    printf("\n  Stlac: %c  ... ", ciel);

    // Začni meranie času
    clock_t start = clock();

    // Čakaj na správnu klávesu
    while (1) {
      int ch = _getch();

      // ESC alebo F10 – koniec
      if (ch == 27) { // ESC
        printf("  [ESC] Ukoncene.\n");
        return;
      }
      if (ch == 0 || ch == 224) { // funkčná klávesa
        int fkey = _getch();
        if (fkey == 68) { // F10
          printf("  [F10] Ukoncene.\n");
          return;
        }
        continue; // ignoruj ostatné funkčné klávesy
      }

      // Porovnaj (case-insensitive)
      char upper = (ch >= 'a' && ch <= 'z') ? (char)(ch - 32) : (char)ch;
      if (upper == ciel) {
        clock_t end = clock();
        double cas = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%.2f s  (stlacene %c)\n", cas, upper);
        break;
      }
      // Ak nie je správna klávesa, ignoruj
    }

    // Kontrola – F10 alebo ESC pre ďalšie kolo?
    printf("  [F2] = dalsia runda, [F10/ESC] = koniec: ");
    int ch = _getch();
    if (ch == 27) {
      pokracovat = 0;
    } else if (ch == 0 || ch == 224) {
      int fkey = _getch();
      if (fkey == 68) { // F10
        pokracovat = 0;
      }
      // F2 (60) = pokračuj
    }
  }
}

int main() {
  system("cls");
  printf("\n  === Meranie reakcneho casu ===\n");
  printf("  [F1] Navod | [F2] Meranie | [F10/ESC] Koniec\n");

  while (1) {
    if (_kbhit()) {
      int ch = _getch();

      if (ch == 27) { // ESC
        break;
      }

      if (ch == 0 || ch == 224) { // funkčná klávesa
        int fkey = _getch();

        switch (fkey) {
        case 59: // F1
          zobrazNavod();
          system("cls");
          printf("\n  === Meranie reakcneho casu ===\n");
          printf("  [F1] Navod | [F2] Meranie | [F10/ESC] Koniec\n");
          break;
        case 60: // F2
          spustiMeranie();
          system("cls");
          printf("\n  === Meranie reakcneho casu ===\n");
          printf("  [F1] Navod | [F2] Meranie | [F10/ESC] Koniec\n");
          break;
        case 68: // F10
          printf("\n  Dovidenia!\n");
          return 0;
        }
      }
    }
    Sleep(50); // netreba CPU žrať na 100%
  }

  printf("\n  Dovidenia!\n");
  return 0;
}
