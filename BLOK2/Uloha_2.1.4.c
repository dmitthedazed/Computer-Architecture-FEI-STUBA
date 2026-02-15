// Úloha 2.1.4 – procesor (2b)
// Program pomocou inline assemblerovej inštrukcie CPUID zistí
// výrobcu procesora (napr. GenuineIntel, AuthenticAMD, CyrixInstead).
//
// Inštrukcia CPUID s funkciou 0 (EAX = 0) vráti:
//   EBX, EDX, ECX – 12-bajtový reťazec identifikátora výrobcu.
// Dávame 0, lebo funkcia 0 = "Get Vendor ID String".

#include <stdio.h>

int main() {
  char vendor[13] = {0};

  __asm {
        MOV EAX, 0 // funkcia 0: Get Vendor ID
        CPUID
        MOV DWORD PTR [vendor],     EBX // prvé 4 znaky
        MOV DWORD PTR [vendor + 4], EDX // druhé 4 znaky
        MOV DWORD PTR [vendor + 8], ECX // tretie 4 znaky
  }

  printf("Vyrobca procesora: %s\n", vendor);
  return 0;
}
