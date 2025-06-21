// Uloha 2.1.2 – procesor
// Použitie vloženého assembleru na násobenie dvomi bez použitia operátora súčinu.
#include <stdio.h>

int main() {
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
    return 0;
}