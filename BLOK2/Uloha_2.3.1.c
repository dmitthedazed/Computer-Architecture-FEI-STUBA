// Úloha 2.3.1 – disky (2b)
// Konverzia textu z kódovania ISO-8859-2 do Windows CP-1250.
//
// Tieto dve kódovania sa líšia len v 8 znakoch.
// Program načíta vstupný súbor (napr. poviedka.html) a zapíše
// výstupný súbor s prevedenými znakmi.
//
// Tabuľka rozdielov (ISO-8859-2 → CP-1250):
//   0xA1 (161) → 0xA5 (165)   Ą
//   0xA2 (162) → 0x98 (152)   ˘ (breve)
//   0xA3 (163) → 0xA3 (163)   Ł (rovnaké)
//   0xA5 (165) → 0xBC (188)   Ľ
//   0xA6 (166) → 0x8C (140)   Ś
//   0xAA (170) → 0x8A (138)   Ş → Š
//   0xAB (171) → 0x8D (141)   Ť
//   0xAC (172) → 0x8F (143)   Ź
//   0xAE (174) → 0x8E (142)   Ž
//   0xAF (175) → 0xAF (175)   Ż (rovnaké)
//   0xB1 (177) → 0xB9 (185)   ą
//   0xB2 (178) → 0x9B (155)   ˛ (ogonek) → ›
//   0xB5 (181) → 0xBE (190)   ľ
//   0xB6 (182) → 0x9C (156)   ś
//   0xBA (186) → 0x9A (154)   š
//   0xBB (187) → 0x9D (157)   ť
//   0xBC (188) → 0x9F (159)   ź
//   0xBE (190) → 0x9E (158)   ž

#include <stdio.h>

int main() {
  char vstup[256], vystup[256];

  printf("Zadajte nazov vstupneho suboru (ISO-8859-2): ");
  scanf("%255s", vstup);

  printf("Zadajte nazov vystupneho suboru (CP-1250): ");
  scanf("%255s", vystup);

  FILE *fin = fopen(vstup, "rb");
  if (!fin) {
    printf("Nepodarilo sa otvorit vstupny subor!\n");
    return 1;
  }

  FILE *fout = fopen(vystup, "wb");
  if (!fout) {
    printf("Nepodarilo sa otvorit vystupny subor!\n");
    fclose(fin);
    return 1;
  }

  int c;
  while ((c = fgetc(fin)) != EOF) {
    unsigned char ch = (unsigned char)c;

    switch (ch) {
    case 0xA1:
      ch = 0xA5;
      break; // Ą
    case 0xA2:
      ch = 0x98;
      break; // breve
    case 0xA5:
      ch = 0xBC;
      break; // Ľ
    case 0xA6:
      ch = 0x8C;
      break; // Ś
    case 0xAA:
      ch = 0x8A;
      break; // Š
    case 0xAB:
      ch = 0x8D;
      break; // Ť
    case 0xAC:
      ch = 0x8F;
      break; // Ź
    case 0xAE:
      ch = 0x8E;
      break; // Ž
    case 0xB1:
      ch = 0xB9;
      break; // ą
    case 0xB2:
      ch = 0x9B;
      break; // ogonek
    case 0xB5:
      ch = 0xBE;
      break; // ľ
    case 0xB6:
      ch = 0x9C;
      break; // ś
    case 0xBA:
      ch = 0x9A;
      break; // š
    case 0xBB:
      ch = 0x9D;
      break; // ť
    case 0xBC:
      ch = 0x9F;
      break; // ź
    case 0xBE:
      ch = 0x9E;
      break; // ž
    }

    fputc(ch, fout);
  }

  fclose(fin);
  fclose(fout);

  printf("Konverzia dokoncena: %s -> %s\n", vstup, vystup);
  return 0;
}
