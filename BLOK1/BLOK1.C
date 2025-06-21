#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

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

void uloha1_1() {
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
}

void uloha1_3() {
    int n, pocet;
    printf("\nZadajte cislo: ");
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
}

void uloha1_4() {
    float epsilon_float = 1.0f;
    double epsilon_double = 1.0;

    while (1.0f + epsilon_float / 2.0f > 1.0f) { 
        epsilon_float = epsilon_float / 2.0f;
    }

    while (1.0 + epsilon_double / 2.0 > 1.0) { 
        epsilon_double = epsilon_double / 2.0;
    }

    printf("\nStrojove epsilon pre float: %g\n", epsilon_float);
    printf("FLT_EPSILON: %g\n\n", FLT_EPSILON);
    printf("Strojove epsilon pre double: %g\n", epsilon_double);
    printf("DBL_EPSILON: %g\n", DBL_EPSILON);
}

void uloha1_6() {
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
}

int main() {
    printf("Uloha 1.1\n");
    uloha1_1();
    
    printf("\nUloha 1.3\n");
    uloha1_3();
    
    printf("\nUloha 1.4\n");
    uloha1_4();

    printf("\nUloha 1.6\n");
    uloha1_6();
    
    return 0;
}