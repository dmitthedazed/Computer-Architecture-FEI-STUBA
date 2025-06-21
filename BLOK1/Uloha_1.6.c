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