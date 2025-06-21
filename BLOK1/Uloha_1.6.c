// Úloha 1.6 (4b)
// Napíšte program na výpočet kontrolnej sumy (checksum) 
// pre zadaný riadok tzv. IntelHex súboru.
//
// Na získanie plného počtu bodov musíte cvičiacemu vedieť vysvetliť:
// - jednotlivé časti IntelHex riadka (viď. dolu),
// - akúkoľvek časť Vášho kódu.
//
// IntelHex riadok má štruktúru:
// :LLAAAATT[DD...]CC
// kde:
//   ':'        – začiatok riadku
//   LL         – počet dátových bajtov (length)
//   AAAA       – adresa (address)
//   TT         – typ záznamu (record type), napr. 00 = data, 01 = EOF
//   DD         – dátové bajty (data)
//   CC         – kontrolná suma (checksum)
//
// Kontrolná suma sa počíta takto:
//   1. Spočítajú sa všetky bajty od LL po posledný DD.
//   2. Výsledok sa neguje (bitwise NOT) a pripočíta sa 1 (two's complement).
//   3. Výsledok (8-bitový) je hodnota kontrolnej sumy (CC).

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
 char inputstr[100];
    printf("Zadajte retazec iHEX: ");
    fgets(inputstr, 100, stdin);

    int i = 1;
    int checksum = 0;
    
    while (inputstr[i] != 'x' && inputstr[i] != 'X') {
        char hex[3];
        hex[0] = inputstr[i];
        hex[1] = inputstr[i + 1];
        hex[2] = '\0';

        int num = strtol(hex, NULL, 16);
        checksum = checksum + num;
        i = i + 2;
    }

    checksum = 255 - (checksum % 256) + 1;
    int len = strlen(inputstr);
    inputstr[len - 3] = '\0';
    printf("\nChecksum: %s%X\n", inputstr, checksum);
    
    return 0;
}