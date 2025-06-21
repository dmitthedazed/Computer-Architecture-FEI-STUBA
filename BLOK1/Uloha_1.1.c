// Úloha 1.1 (2b)
// Napíšte program, ktorý zobrazí nasledovné dva vstupy: 
//
//     číslo 33777
//     ASCII kód znaku ‘X’ 
//
// v dvojkovej, desiatkovej a šestnástkovej sústave. 
// Program musí fungovať tak, aby bolo vstupy možné meniť (stačí v zdrojovom súbore).
//
// Tip: Použite čo najmenší počet premenných; využite možnosti, 
// ktoré poskytuje funkcia printf, prevod do dvojkovej sústavy však budete musieť naprogramovať.

#include <stdio.h>
#include <string.h>

void tobinary(unsigned int value, char *binarystr) { 
    int k = 0;
    if (value == 0) {
        strcpy(binarystr, "0");
        return;
    }
    while (value != 0) {
        if (value % 2 == 0) {
            binarystr[k] = '0';
        } else {
            binarystr[k] = '1';
        }
        k = k + 1;
        value = value / 2;
    }
    binarystr[k] = '\0';
    
    int len = strlen(binarystr);
    int i = 0;
    int j = len - 1;
    while (i < j) {
        char temp = binarystr[i];
        binarystr[i] = binarystr[j];
        binarystr[j] = temp;
        i++;
        j--;
    }
}

int main() {
    int cislo = 11037;
    int znak = '&';
    char binarystr[64];

    tobinary(cislo, binarystr);
    printf("Cislo %d:\n", cislo);
    printf("Dvojkova: %s\n", binarystr);
    printf("Desiatkova: %d\n", cislo);
    printf("Sestnastkova: %x\n", cislo);

    tobinary((unsigned int)znak, binarystr);
    printf("\nASCII znak '&':\n");
    printf("Dvojkova: %s\n", binarystr);
    printf("Desiatkova: %d\n", znak);
    printf("Sestnastkova: %x\n", znak);
    
    return 0;
}