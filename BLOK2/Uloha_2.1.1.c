// Uloha 2.1.1 – procesor
// Vloženie assemblerového kódu na výpočet súčtu dvoch premenných.
#include <stdio.h>

int main() {
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
    return 0;
}