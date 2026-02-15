// Úloha 1.5 (4b)
// Výpočet funkcie sin(x) pomocou rozvoja do Taylorovho radu.
//
// sin(x) = x - x³/3! + x⁵/5! - x⁷/7! + ...
//        = Σ (-1)^n · x^(2n+1) / (2n+1)!
//
// Každý ďalší člen radu sa vypočíta z predchádzajúceho:
//   term(n+1) = term(n) * (-x²) / ((2n+2)(2n+3))
//
// Pre ľubovoľné uhly sa využíva periodicita sin:
//   uhol sa normalizuje do intervalu [-π, π].

#include <stdio.h>

#define MY_PI 3.14159265358979323846f

// Normalizácia uhla do intervalu [-PI, PI]
static float normalize(float rad) {
  while (rad > MY_PI)
    rad -= 2.0f * MY_PI;
  while (rad < -MY_PI)
    rad += 2.0f * MY_PI;
  return rad;
}

// Prevod stupňov na radiány
static float deg2rad(float deg) { return deg * MY_PI / 180.0f; }

// Výpočet sin(x) Taylorovým radom
// radians - uhol v radiánoch
// epsilon - maximálny rozdiel medzi dvomi iteráciami na ukončenie
float sinus(float radians, float epsilon) {
  radians = normalize(radians);

  float term = radians; // prvý člen radu: x
  float sum = term;
  int n = 1;

  while (1) {
    // nasledujúci člen: term * (-x²) / ((2n)(2n+1))
    term *= -radians * radians / (float)((2 * n) * (2 * n + 1));
    sum += term;
    n++;

    // ak je absolútna hodnota členu menšia ako epsilon, končíme
    float abs_term = term < 0 ? -term : term;
    if (abs_term < epsilon)
      break;
  }

  return sum;
}

int main() {
  float epsilon = 0.000001f;
  float uhol;

  printf("Zadajte uhol v stupnoch: ");
  scanf("%f", &uhol);

  float rad = deg2rad(uhol);
  float vysledok = sinus(rad, epsilon);

  printf("sin(%.1f°) = %.6f\n", uhol, vysledok);

  // Kontrolné hodnoty
  printf("\nKontrolne hodnoty:\n");
  float test_angles[] = {0, 30, 45, 90, 180, 270, 360, -4500, 8649};
  int count = sizeof(test_angles) / sizeof(test_angles[0]);

  for (int i = 0; i < count; i++) {
    float r = deg2rad(test_angles[i]);
    printf("  sin(%8.1f°) = %10.6f\n", test_angles[i], sinus(r, epsilon));
  }

  return 0;
}
