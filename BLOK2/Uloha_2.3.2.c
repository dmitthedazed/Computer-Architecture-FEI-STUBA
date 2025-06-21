// Uloha 2.3.2 – disky 
// Vytvorenie a otvorenie súboru, zápis do neho a následné čítanie.
#include <stdio.h>

int main() {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, "koniec_poviedky.html", "rb");

    if (err != 0 || file == NULL) {
        printf("Nepodarilo sa otvorit subor.\n");
        return 1;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch ^ 27);
    }

    fclose(file);
    return 0;
}