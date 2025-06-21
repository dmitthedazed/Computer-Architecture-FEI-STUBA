// Úloha 1.3 (2b)
// Napíšte program, ktorý spočíta počet jednotiek (nastavených bitov) 
// v binárnej reprezentácii zadaného čísla.
//
// Príklad:
// Vstup: 13 (binárne 1101)
// Výstup: 3 jednotky
//
// Tip 1: Využite bitový AND a bitový posun. 
// Ako použiť bitové operácie v jazyku C sa dozviete tu. 
// Zaujímavé video na túto tému je tu.

#include <stdio.h>

int main() {
    int n, pocet;
    printf("Zadajte cislo: ");
    scanf("%d", &n);
    
    int orign = n;
    pocet = 0;

    while (n != 0) {
        if (n % 2 == 1) {
            pocet = pocet + 1;
        }
        n = n / 2;
    }
    printf("%d jednotiek\n", pocet);
    
    return 0;
}