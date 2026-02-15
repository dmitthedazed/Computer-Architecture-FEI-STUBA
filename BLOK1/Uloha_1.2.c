// Úloha 1.2 (2b)
// Napíšte program, ktorý vykoná rotačný posun bitov doprava
// pre celé kladné číslo.
//
// Príklad:
// Číslo 9 (binárne 1001) pri rotačnom posune doprava o 1 bit → 1100...0100
// (posledný bit sa presunie na najvyššiu pozíciu)
//
// Rotačný posun (cyklický posun) — bity, ktoré "vypadnú" na jednom konci,
// sa vrátia na opačný koniec.
//
// Tip: Použite dátový typ unsigned int.
//      int bit_count = sizeof(unsigned int) * 8;

#include <stdio.h>
#include <string.h>

void tobinary(unsigned int value, char *binarystr) {
  int bit_count = sizeof(unsigned int) * 8;
  for (int i = bit_count - 1; i >= 0; i--) {
    binarystr[bit_count - 1 - i] = (value >> i) & 1 ? '1' : '0';
  }
  binarystr[bit_count] = '\0';
}

unsigned int rotate_right(unsigned int value, int shift) {
  int bit_count = sizeof(unsigned int) * 8;
  shift = shift % bit_count;
  return (value >> shift) | (value << (bit_count - shift));
}

int main() {
  unsigned int cislo;
  int posun;

  printf("Zadajte cislo: ");
  scanf("%u", &cislo);

  printf("Zadajte pocet bitov na posun: ");
  scanf("%d", &posun);

  char binpred[65], binpo[65];
  tobinary(cislo, binpred);

  unsigned int vysledok = rotate_right(cislo, posun);
  tobinary(vysledok, binpo);

  printf("\nPred posunom:  %s (%u)\n", binpred, cislo);
  printf("Po posune o %d: %s (%u)\n", posun, binpo, vysledok);

  return 0;
}
