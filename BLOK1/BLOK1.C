// BLOK 1 — Súhrnný súbor so všetkými úlohami
// Ulohy: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
//
// Pre kompiláciu:
//   gcc -Wall -std=c99 -o blok1 BLOK1.C -lm
//   alebo: cl BLOK1.C (MSVC)

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void uloha1_2() {
  unsigned int cislo;
  int posun;

  printf("\nZadajte cislo: ");
  scanf("%u", &cislo);

  printf("Zadajte pocet bitov na posun: ");
  scanf("%d", &posun);

  int bit_count = sizeof(unsigned int) * 8;
  posun = posun % bit_count;
  unsigned int vysledok = (cislo >> posun) | (cislo << (bit_count - posun));

  char binpred[65], binpo[65];
  tobinary(cislo, binpred);
  tobinary(vysledok, binpo);

  printf("Pred posunom:  %s (%u)\n", binpred, cislo);
  printf("Po posune o %d: %s (%u)\n", posun, binpo, vysledok);
}

void uloha1_3() {
  int n, pocet;
  printf("\nZadajte cislo: ");
  scanf("%d", &n);

  pocet = 0;

  while (n != 0) {
    if (n & 1) {
      pocet = pocet + 1;
    }
    n = n >> 1;
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

#define MY_PI 3.14159265358979323846f

static float normalize(float rad) {
  while (rad > MY_PI)
    rad -= 2.0f * MY_PI;
  while (rad < -MY_PI)
    rad += 2.0f * MY_PI;
  return rad;
}

static float deg2rad(float deg) { return deg * MY_PI / 180.0f; }

void uloha1_5() {
  float epsilon = 0.000001f;
  float uhol;

  printf("\nZadajte uhol v stupnoch: ");
  scanf("%f", &uhol);

  float rad = deg2rad(uhol);
  rad = normalize(rad);

  float term = rad;
  float sum = term;
  int n = 1;

  while (1) {
    term *= -rad * rad / (float)((2 * n) * (2 * n + 1));
    sum += term;
    n++;
    float abs_term = term < 0 ? -term : term;
    if (abs_term < epsilon)
      break;
  }

  printf("sin(%.1f°) = %.6f\n", uhol, sum);

  // Kontrolné hodnoty
  printf("\nKontrolne hodnoty:\n");
  float test_angles[] = {0, 30, 45, 90, 180, 270, 360};
  int count = sizeof(test_angles) / sizeof(test_angles[0]);
  for (int i = 0; i < count; i++) {
    float r = deg2rad(test_angles[i]);
    r = normalize(r);
    float t = r, s = t;
    int m = 1;
    while (1) {
      t *= -r * r / (float)((2 * m) * (2 * m + 1));
      s += t;
      m++;
      float at = t < 0 ? -t : t;
      if (at < epsilon)
        break;
    }
    printf("  sin(%6.1f°) = %10.6f\n", test_angles[i], s);
  }
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
  int choice;

  do {
    printf("\n========================================\n");
    printf("  BLOK 1 — Vyber ulohu\n");
    printf("========================================\n");
    printf("  1 - Uloha 1.1  Ciselne sustavy (1b)\n");
    printf("  2 - Uloha 1.2  Rotacny posun bitov (2b)\n");
    printf("  3 - Uloha 1.3  Pocet jednotiek (1b)\n");
    printf("  4 - Uloha 1.4  Strojove epsilon (3b)\n");
    printf("  5 - Uloha 1.5  Sinus – Taylor (4b)\n");
    printf("  6 - Uloha 1.6  IntelHex checksum (5b)\n");
    printf("  0 - Koniec\n");
    printf("Vas vyber: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      uloha1_1();
      break;
    case 2:
      uloha1_2();
      break;
    case 3:
      uloha1_3();
      break;
    case 4:
      uloha1_4();
      break;
    case 5:
      uloha1_5();
      break;
    case 6:
      uloha1_6();
      break;
    case 0:
      printf("Koniec programu.\n");
      break;
    default:
      printf("Nespravny vyber.\n");
      break;
    }
  } while (choice != 0);

  return 0;
}