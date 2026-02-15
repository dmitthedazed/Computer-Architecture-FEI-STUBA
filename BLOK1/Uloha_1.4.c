// Úloha 1.4 (3b)
// Napíšte program, ktorý zistí a vypíše strojové epsilon
// pre dátové typy float a double.
//
// Strojové epsilon je najmenšie číslo ε také, že 1 + ε > 1.
// Hľadáme ho delením dvomi (pracujeme v dvojkovej sústave):
//   epsilon = 1.0
//   kým (1.0 + epsilon/2 > 1.0): epsilon = epsilon / 2
//
// Porovnajte výsledok s konštantami FLT_EPSILON a DBL_EPSILON
// zadefinovanými vo float.h.

#include <float.h>
#include <stdio.h>

int main() {
  float epsilon_float = 1.0f;
  double epsilon_double = 1.0;

  while (1.0f + epsilon_float / 2.0f > 1.0f) {
    epsilon_float = epsilon_float / 2.0f;
  }

  while (1.0 + epsilon_double / 2.0 > 1.0) {
    epsilon_double = epsilon_double / 2.0;
  }

  printf("Strojove epsilon pre float:  %g\n", epsilon_float);
  printf("FLT_EPSILON (float.h):       %g\n\n", FLT_EPSILON);

  printf("Strojove epsilon pre double: %g\n", epsilon_double);
  printf("DBL_EPSILON (float.h):       %g\n", DBL_EPSILON);

  return 0;
}
