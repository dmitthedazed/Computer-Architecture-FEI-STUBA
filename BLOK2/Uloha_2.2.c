// Uloha 2.2 – ukazovatele
// Práca so smerníkmi: deklarácia, zmena adries a zápis na tieto adresy.
#include <stdio.h>

int main() {

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