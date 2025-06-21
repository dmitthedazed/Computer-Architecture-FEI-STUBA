// Datum: 14.04.2025
// BLOK2 – Uloha 2.1.1, 2.1.2, 2.1.3, 2.2, 2.3.2, 2.5.1
// Pocet bodov: 10

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
// Použitie vloženého assembleru na násobenie dvomi bez použitia operátora súčinu.
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
    char* pointer = text;

    printf("Povodna adresa: %p\n", pointer);
    pointer += 1;
    *pointer = 'F';

    printf("Zmeneny retazec: %s\n", text);
    pointer += 5;

    printf("Aktualna adresa: %p\n", pointer);

    puts("\nPole typu int:");
    int cisla[5] = { 1, 2, 3, 4, 5 };
    int* p_cisla = cisla;

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
    FILE* file = NULL;
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
        }
        else if (i <= 22) {
            SetConsoleTextAttribute(hConsole, 4); // red
        }
        else if (i <= 35) {
            SetConsoleTextAttribute(hConsole, 1); // blue
        }
        else {
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

// Hlavná funkcia
// Vytvorenie menu pre výber úlohy.
int main() {
    int choice;

    do {
        printf("\nVyberte ulohu, ktoru chcete spustit:\n");
        printf("1 - Uloha 2.1.1 - procesor (1b) \n");
        printf("2 - Uloha 2.1.2 - procesor (1b)\n");
        printf("3 - Uloha 2.1.3 - procesor (3b)\n");
        printf("4 - Uloha 2.2 - pamat (3b)\n");
        printf("5 - Uloha 2.3.2 - disky (1b)\n");
        printf("6 - Uloha 2.5.1 grafika - farby (1b)\n");
        printf("0 - Exit\n");
        printf("Vas vyber:  ");
        scanf_s("%d", &choice);


        switch (choice) {
        case 1: Uloha_2_1_1(); break;
        case 2: Uloha_2_1_2(); break;
        case 3: Uloha_2_1_3(); break;
        case 4: Uloha_2_2(); break;
        case 5: Uloha_2_3_2(); break;
        case 6: Uloha_2_5_1(); break;
        case 0: printf("Koniec programu.\n"); break;
        default: printf("Nespravny vyber. Skuste znova.\n"); break;
        }

    } while (choice != 0);

    return 0;
}

// Koniec
// Poznamka: Vsetky ulohy su spravene v jazyku C a su urcene pre Windows.
// Pre kompilaciu je potrebne pouzit Visual Studio alebo iny C kompilator, ktory podporuje inline assembler.