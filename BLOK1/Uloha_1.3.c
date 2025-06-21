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