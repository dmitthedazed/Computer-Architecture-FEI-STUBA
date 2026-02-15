// BLOK 2 — Súhrnný súbor so všetkými úlohami bloku 2
// Ulohy: 2.1.1, 2.1.2, 2.1.3, 2.1.4, 2.2, 2.3.1, 2.3.2, 2.3.3, 2.4, 2.5.1, 2.5.2,
// 2.6 Počet bodov: 27 (max. 16)
//
// Pre kompiláciu: Visual Studio (x86), alebo cl BLOK2.c user32.lib winmm.lib
// Úlohy 2.1.4, 2.3.1, 2.3.3, 2.4, 2.5.2, 2.6 sú implementované v samostatných
// súboroch a v tomto indexovom súbore sú uvedené ako referencie.

#include <stdio.h>
#include <windows.h>

// Uloha 2.1.1 – procesor
// Vloženie assemblerového kódu na výpočet súčtu dvoch premenných.
void Uloha_2_1_1() {
  int iCislo1;
  int iCislo2;
  int iVysledok;

  printf("Zadajte prve cislo: ");
  scanf_s("%d", &iCislo1);

  printf("Zadajte druhe cislo: ");
  scanf_s("%d", &iCislo2);

  __asm {
        MOV EAX, iCislo1
        ADD EAX, iCislo2
        MOV iVysledok, EAX
  }

  printf("Sucet tychto dvoch cisel je: %d\n", iVysledok);
}

// Uloha 2.1.2 – procesor
// Použitie vloženého assembleru na násobenie dvomi bez použitia operátora
// súčinu.
void Uloha_2_1_2() {
  int iCislo;
  int iVysledok;

  printf("Zadajte cislo: ");
  scanf_s("%d", &iCislo);

  __asm {
        MOV EAX, iCislo
        SHL EAX, 1
        MOV iVysledok, EAX
  }

  printf("Toto cislo vynasobene dvoma sa rovna: %d\n", iVysledok);
}

// Úloha 2.1.3 – procesor
// Vloženie assemblerového kódu na prevod číslice na hexadecimálny ASCII znak.
void Uloha_2_1_3() {
  int cislo;
  char znak;

  printf("Zadajte cislo od 0 do 15:\n");
  scanf_s("%d", &cislo);
  if (cislo < 0 || cislo > 15) {
    printf("Nespravne cislo\n");
    return;
  }
  __asm {
        MOV EAX, cislo
        CMP EAX, 10
        JL menej_10
        ADD EAX, 55
        JMP koniec

        menej_10 :
        ADD EAX, '0'

            koniec :
            MOV znak, AL
  }
  printf("%2d -> %c\n", cislo, znak);
}

// Uloha 2.2 – ukazovatele
// Práca so smerníkmi: deklarácia, zmena adries a zápis na tieto adresy.
void Uloha_2_2() {

  printf("\nRetazec typu char:\n");
  char text[] = "architektura_pocitacov_je_super_predmet";
  char *pointer = text;

  printf("Povodna adresa: %p\n", pointer);
  pointer += 1;
  *pointer = 'F';

  printf("Zmeneny retazec: %s\n", text);
  pointer += 5;

  printf("Aktualna adresa: %p\n", pointer);

  puts("\nPole typu int:");
  int cisla[5] = {1, 2, 3, 4, 5};
  int *p_cisla = cisla;

  printf("Zaciatocna adresa: %p\n", p_cisla);
  p_cisla += 1;
  *p_cisla = 0;

  printf("Upravene pole: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", cisla[i]);
  }
  printf("\n");
}

// Uloha 2.3.2 – disky
// Vytvorenie a otvorenie súboru, zápis do neho a následné čítanie.
void Uloha_2_3_2() {
  FILE *file = NULL;
  errno_t err = fopen_s(&file, "koniec_poviedky.html", "rb");

  if (err != 0 || file == NULL) {
    printf("Nepodarilo sa otvorit subor.\n");
    return;
  }
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch ^ 27);
  }

  fclose(file);
}

// Uloha 2.5.1 grafika – farby
// Zmena farby textu v konzole na základe hodnoty premennej.
void Uloha_2_5_1() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  for (int i = 0; i <= 50; i++) {
    if (i <= 10) {
      SetConsoleTextAttribute(hConsole, 2); // green
    } else if (i <= 22) {
      SetConsoleTextAttribute(hConsole, 4); // red
    } else if (i <= 35) {
      SetConsoleTextAttribute(hConsole, 1); // blue
    } else {
      SetConsoleTextAttribute(hConsole, 7); // gray (default)
    }

    printf("%03d\n", i);
    Sleep(1000);
  }

  SetConsoleTextAttribute(hConsole, 7);
  printf("\nStlac a skoncime . . .");
  getchar();
  getchar(); // Wait for user input
}

// Uloha 2.1.4 — CPUID
// Implementacia v samostatnom subore: Uloha_2.1.4.c
void Uloha_2_1_4() {
  printf(
      "\nUloha 2.1.4 je implementovana v samostatnom subore Uloha_2.1.4.c\n");
  printf("Pouzite inline assembler instrukciu CPUID na zistenie vyrobcu "
         "procesora.\n");
}

// Uloha 2.3.1 — Konverzia kodovani ISO-8859-2 na CP-1250
// Implementacia v samostatnom subore: Uloha_2.3.1.c
void Uloha_2_3_1() {
  printf(
      "\nUloha 2.3.1 je implementovana v samostatnom subore Uloha_2.3.1.c\n");
  printf("Konvertuje subor z kodovani ISO-8859-2 do CP-1250.\n");
}

// Uloha 2.3.3 — Rekonstrukcia RAID pola
// Implementacia v samostatnom subore: Uloha_2.3.3.c
void Uloha_2_3_3() {
  printf(
      "\nUloha 2.3.3 je implementovana v samostatnom subore Uloha_2.3.3.c\n");
  printf("Rekonstruuje chybajuci blok RAID 5 pola pomocou XOR.\n");
}

// Uloha 2.4 — Multimediálny prehrávač
// Implementacia v samostatnom subore: Uloha_2.4.c
void Uloha_2_4() {
  printf("\nUloha 2.4 je implementovana v samostatnom subore Uloha_2.4.c\n");
  printf("Multimediálny prehravac pomocou MCI API (winmm.lib).\n");
}

// Uloha 2.5.2 — Semigrafická tabuľka
// Implementacia v samostatnom subore: Uloha_2.5.2.c
void Uloha_2_5_2() {
  printf(
      "\nUloha 2.5.2 je implementovana v samostatnom subore Uloha_2.5.2.c\n");
  printf("Dynamicka tabulka s ASCII ramikom na pozicii [x,y].\n");
}

// Uloha 2.6 — Meranie reakčného času
// Implementacia v samostatnom subore: Uloha_2.6.c
void Uloha_2_6() {
  printf("\nUloha 2.6 je implementovana v samostatnom subore Uloha_2.6.c\n");
  printf("Hra na meranie reakcneho casu s klavesami F1/F2/F10.\n");
}

// Hlavná funkcia — menu pre výber úlohy
int main() {
  int choice;

  do {
    printf("\n========================================\n");
    printf("  BLOK 2 — Vyber ulohu\n");
    printf("========================================\n");
    printf("  1 - Uloha 2.1.1  Sucet inline asm (1b)\n");
    printf("  2 - Uloha 2.1.2  SHL nasobenie (1b)\n");
    printf("  3 - Uloha 2.1.3  Hex ASCII prevod (3b)\n");
    printf("  4 - Uloha 2.1.4  CPUID vyrobca CPU (2b)\n");
    printf("  5 - Uloha 2.2    Smerniky (3b)\n");
    printf("  6 - Uloha 2.3.1  ISO->CP-1250 konverzia (2b)\n");
    printf("  7 - Uloha 2.3.2  XOR desifrovanie (1b)\n");
    printf("  8 - Uloha 2.3.3  RAID rekonstrukcia (3b)\n");
    printf("  9 - Uloha 2.4    Multimedia MCI (4b)\n");
    printf(" 10 - Uloha 2.5.1  Farby konzoly (1b)\n");
    printf(" 11 - Uloha 2.5.2  Semigrafika (3b)\n");
    printf(" 12 - Uloha 2.6    Reakcny cas (4b)\n");
    printf("  0 - Koniec\n");
    printf("Vas vyber: ");
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
      Uloha_2_1_1();
      break;
    case 2:
      Uloha_2_1_2();
      break;
    case 3:
      Uloha_2_1_3();
      break;
    case 4:
      Uloha_2_1_4();
      break;
    case 5:
      Uloha_2_2();
      break;
    case 6:
      Uloha_2_3_1();
      break;
    case 7:
      Uloha_2_3_2();
      break;
    case 8:
      Uloha_2_3_3();
      break;
    case 9:
      Uloha_2_4();
      break;
    case 10:
      Uloha_2_5_1();
      break;
    case 11:
      Uloha_2_5_2();
      break;
    case 12:
      Uloha_2_6();
      break;
    case 0:
      printf("Koniec programu.\n");
      break;
    default:
      printf("Nespravny vyber. Skuste znova.\n");
      break;
    }

  } while (choice != 0);

  return 0;
}

// Poznamka: Vsetky ulohy su spravene v jazyku C a su urcene pre Windows.
// Pre kompilaciu je potrebne pouzit Visual Studio (x86) alebo MSVC cl.