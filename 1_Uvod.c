// Úvod — cvičenie 1
// Základná práca s cyklami a funkciami v jazyku C.

#include <stdio.h>

void mojaFunkcia() {
  for (int i = 1; i <= 100; i++)
    printf("%d\n", i);
}

void nemojaFunkcia() {
  for (int a = 1; a <= 30; a++)
    if (a % 2 == 0) {
      printf("%d\n", a);
    }
}

int main() {
  printf("Nazdar!!!\n");
  mojaFunkcia();
  nemojaFunkcia();
  return 0;
}
