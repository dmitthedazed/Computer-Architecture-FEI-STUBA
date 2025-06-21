// Úloha 2.1.3 – procesor 
// Vloženie assemblerového kódu na prevod číslice na hexadecimálny ASCII znak.
#include <stdio.h>

int main() {
    int cislo;
    char znak;

    printf("Zadajte cislo od 0 do 15:\n");
    scanf_s("%d", &cislo);
    if (cislo < 0 || cislo > 15) {
        printf("Nespravne cislo\n");
        return 1;
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
    return 0;
}
