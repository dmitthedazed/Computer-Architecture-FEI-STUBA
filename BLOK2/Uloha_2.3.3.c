// Úloha 2.3.3 – RAID (3b)
// Rekonštrukcia chýbajúceho bloku z RAIDového poľa.
//
// RAID 5 používa XOR paritu na rekonštrukciu dát.
// Ak máme bloky A, B, C, P (parita), pričom P = A ^ B ^ C,
// tak chýbajúci blok X = XOR všetkých ostatných blokov.
//
// Program načíta 4 súbory (bloky), identifikuje poškodený
// a rekonštruuje ho pomocou XOR ostatných blokov.
//
// POZOR: funguje len pod Windows, súbory čítajte v textovom režime.

#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 4096
#define NUM_BLOCKS 4

int main() {
  char filenames[NUM_BLOCKS][256];
  FILE *files[NUM_BLOCKS];
  int damaged_block = -1;

  printf("=== RAID Rekonstrukcia ===\n\n");

  for (int i = 0; i < NUM_BLOCKS; i++) {
    printf("Zadajte nazov bloku %d: ", i + 1);
    scanf("%255s", filenames[i]);
  }

  printf("Ktory blok je poskodeny? (1-%d): ", NUM_BLOCKS);
  scanf("%d", &damaged_block);
  damaged_block--; // 0-indexed

  if (damaged_block < 0 || damaged_block >= NUM_BLOCKS) {
    printf("Nespravne cislo bloku!\n");
    return 1;
  }

  // Otvor všetky súbory okrem poškodeného
  for (int i = 0; i < NUM_BLOCKS; i++) {
    if (i == damaged_block)
      continue;
    files[i] = fopen(filenames[i], "r");
    if (!files[i]) {
      printf("Nepodarilo sa otvorit subor: %s\n", filenames[i]);
      return 1;
    }
  }

  // Otvor výstupný súbor pre rekonštrukciu
  char output[256];
  printf("Nazov vystupneho (rekonstruovaneho) suboru: ");
  scanf("%255s", output);

  FILE *fout = fopen(output, "w");
  if (!fout) {
    printf("Nepodarilo sa vytvorit vystupny subor!\n");
    return 1;
  }

  // Rekonštrukcia pomocou XOR
  int done = 0;
  while (!done) {
    int result = 0;
    int got_char = 0;

    for (int i = 0; i < NUM_BLOCKS; i++) {
      if (i == damaged_block)
        continue;

      int c = fgetc(files[i]);
      if (c == EOF) {
        done = 1;
        break;
      }
      result ^= c;
      got_char = 1;
    }

    if (got_char && !done) {
      fputc(result, fout);
    }
  }

  // Zatvor súbory
  for (int i = 0; i < NUM_BLOCKS; i++) {
    if (i == damaged_block)
      continue;
    fclose(files[i]);
  }
  fclose(fout);

  printf("Rekonstrukcia dokoncena! Vysledok: %s\n", output);
  return 0;
}
