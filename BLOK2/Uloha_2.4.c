// Úloha 2.4 – multimédiá (4b)
// Jednoduchý prehrávač médií pomocou Windows MCI API.
//
// Program umožňuje: zadať meno súboru, spustiť, pozastaviť
// a ukončiť prehrávanie hudby alebo videa.
//
// Vyžaduje: #include <windows.h>, #include <mmsystem.h>
// Linkovanie: winmm.lib (alebo #pragma comment(lib, "winmm.lib"))
//
// Kompilujte: MSVC, architektúra x86 alebo x64
// Projekt nastaviť na MultiByte (nie Unicode).

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

void zobrazMenu() {
  system("cls");
  printf("\n");
  printf("  +============================================+\n");
  printf("  |                                            |\n");
  printf("  |       M E D I A   P L A Y E R   1.0       |\n");
  printf("  |                                            |\n");
  printf("  +============================================+\n");
  printf("  |                                            |\n");
  printf("  |   [1]  Zadat subor                         |\n");
  printf("  |   [2]  Spustit prehravanje                 |\n");
  printf("  |   [3]  Pozastavit                          |\n");
  printf("  |   [4]  Pokracovat                          |\n");
  printf("  |   [5]  Zastavit prehravanje                |\n");
  printf("  |   [0]  Ukoncit program                     |\n");
  printf("  |                                            |\n");
  printf("  +============================================+\n");
  printf("\n  Vasa volba: ");
}

int main() {
  char filename[256] = "";
  char cmd[512];
  int volba;
  int opened = 0;

  do {
    zobrazMenu();
    scanf("%d", &volba);

    switch (volba) {
    case 1:
      if (opened) {
        mciSendString("close myMedia", NULL, 0, NULL);
        opened = 0;
      }
      printf("  Zadajte cestu k suboru: ");
      scanf("%255s", filename);
      sprintf(cmd, "open \"%s\" alias myMedia", filename);
      if (mciSendString(cmd, NULL, 0, NULL) == 0) {
        printf("  Subor otvoreny: %s\n", filename);
        opened = 1;
      } else {
        printf("  Chyba pri otvarani suboru!\n");
      }
      Sleep(1500);
      break;

    case 2:
      if (opened) {
        mciSendString("play myMedia", NULL, 0, NULL);
        printf("  Prehravam...\n");
      } else {
        printf("  Najprv zadajte subor!\n");
      }
      Sleep(1000);
      break;

    case 3:
      if (opened) {
        mciSendString("pause myMedia", NULL, 0, NULL);
        printf("  Pozastavene.\n");
      }
      Sleep(1000);
      break;

    case 4:
      if (opened) {
        mciSendString("resume myMedia", NULL, 0, NULL);
        printf("  Pokracujem...\n");
      }
      Sleep(1000);
      break;

    case 5:
      if (opened) {
        mciSendString("stop myMedia", NULL, 0, NULL);
        mciSendString("close myMedia", NULL, 0, NULL);
        opened = 0;
        printf("  Prehravanje ukoncene.\n");
      }
      Sleep(1000);
      break;

    case 0:
      if (opened) {
        mciSendString("stop myMedia", NULL, 0, NULL);
        mciSendString("close myMedia", NULL, 0, NULL);
      }
      printf("  Dovidenia!\n");
      break;

    default:
      printf("  Neplatna volba!\n");
      Sleep(1000);
    }
  } while (volba != 0);

  return 0;
}
