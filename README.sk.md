<div align="center">

# Computer Architecture

**Riešenia úloh z predmetu Architektúra počítačov na FEI STUBA: C, x86 inline assembler, Windows API a TCP**

Letný semester 2024/2025. Stránka predmetu: [ap.urk.fei.stuba.sk](http://ap.urk.fei.stuba.sk/)

[![Build](https://github.com/dmitthedazed/Computer-Architecture-FEI-STUBA/actions/workflows/build.yml/badge.svg)](https://github.com/dmitthedazed/Computer-Architecture-FEI-STUBA/actions/workflows/build.yml)
![C](https://img.shields.io/badge/C-C99-A8B9CC?logo=c&logoColor=white)
![x86](https://img.shields.io/badge/x86-inline%20asm-lightgrey)
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey)](LICENSE)

<p align="center"><a href="README.md">English</a> · <b>Slovenčina</b></p>

</div>

> [!WARNING]
> Blok 2 používa MSVC inline assembler (`__asm {}`), ktorý funguje iba v 32-bitovom režime MSVC. GCC a Clang ho nepodporujú.

Každý blok má vlastný README s krátkym popisom v angličtine a ruštine.

## Úvod

[`1_Uvod.c`](1_Uvod.c): cykly a funkcie v jazyku C.

## Blok 1: číselné sústavy a základy C

Súhrnný súbor: [`BLOK1.C`](BLOK1/BLOK1.C). Podrobnosti: [BLOK1/README.md](BLOK1/README.md).

| Úloha | Téma | Body | Súbor |
|:-:|---|:-:|---|
| 1.1 | Zobrazenie čísla v dvojkovej, desiatkovej a šestnástkovej sústave | 2 | [`Uloha_1.1.c`](BLOK1/Uloha_1.1.c) |
| 1.2 | Rotačný posun bitov doprava (cyklický posun) | 2 | [`Uloha_1.2.c`](BLOK1/Uloha_1.2.c) |
| 1.3 | Počet jednotiek (nastavených bitov) v binárnej reprezentácii čísla | 2 | [`Uloha_1.3.c`](BLOK1/Uloha_1.3.c) |
| 1.4 | Strojové epsilon pre `float` a `double` | 3 | [`Uloha_1.4.c`](BLOK1/Uloha_1.4.c) |
| 1.5 | `sin(x)` pomocou Taylorovho radu | 4 | [`Uloha_1.5.c`](BLOK1/Uloha_1.5.c) |
| 1.6 | Kontrolná suma riadka IntelHex | 4 | [`Uloha_1.6.c`](BLOK1/Uloha_1.6.c) |

## Blok 2: inline assembler a systémové programovanie

Súhrnný súbor: [`BLOK2.c`](BLOK2/BLOK2.c). Podrobnosti: [BLOK2/README.md](BLOK2/README.md).

| Úloha | Téma | Body | Súbor |
|:-:|---|:-:|---|
| 2.1.1 | Súčet dvoch čísel pomocou inline assemblera | 1 | [`Uloha_2.1.1.c`](BLOK2/Uloha_2.1.1.c) |
| 2.1.2 | Násobenie dvomi pomocou bitového posunu (SHL) | 1 | [`Uloha_2.1.2.c`](BLOK2/Uloha_2.1.2.c) |
| 2.1.3 | Prevod číslice na hexadecimálny ASCII znak | 3 | [`Uloha_2.1.3.c`](BLOK2/Uloha_2.1.3.c) |
| 2.1.4 | Výrobca procesora cez inštrukciu CPUID | 2 | [`Uloha_2.1.4.c`](BLOK2/Uloha_2.1.4.c) |
| 2.2 | Smerníky: adresy a dereferencia | 3 | [`Uloha_2.2.c`](BLOK2/Uloha_2.2.c) |
| 2.3.1 | Konverzia kódovania ISO-8859-2 → CP-1250 | 2 | [`Uloha_2.3.1.c`](BLOK2/Uloha_2.3.1.c) |
| 2.3.2 | Čítanie súboru a XOR dešifrovanie | 1 | [`Uloha_2.3.2.c`](BLOK2/Uloha_2.3.2.c) |
| 2.3.3 | Rekonštrukcia RAID poľa pomocou XOR | 3 | [`Uloha_2.3.3.c`](BLOK2/Uloha_2.3.3.c) |
| 2.4 | Multimediálny prehrávač (MCI API) | 4 | [`Uloha_2.4.c`](BLOK2/Uloha_2.4.c) |
| 2.5.1 | Zmena farby textu v konzole | 1 | [`Uloha_2.5.1.c`](BLOK2/Uloha_2.5.1.c) |
| 2.5.2 | Semigrafická tabuľka na pozícii [x,y] | 3 | [`Uloha_2.5.2.c`](BLOK2/Uloha_2.5.2.c) |
| 2.6 | Meranie reakčného času | 4 | [`Uloha_2.6.c`](BLOK2/Uloha_2.6.c) |

## Blok 3: TCP klient

Chat klient pre server predmetu `147.175.115.34:777`. Posiela a prijíma správy, dešifruje XOR bloky a extrahuje správu na prvočíselných pozíciách. Podrobnosti: [BLOK3/README.md](BLOK3/README.md).

| Súbor | Platforma | API |
|---|---|---|
| [`BLOK3_MSVC.c`](BLOK3/BLOK3_MSVC.c) | Windows | Winsock2 |
| [`BLOK3_Linux.c`](BLOK3/BLOK3_Linux.c) | Linux | POSIX sockets |

## Kompilácia

Blok 1, úvod a prenosné časti bloku 2 (`Uloha_2.3.1.c`, `Uloha_2.3.3.c`) sa preložia v GCC:

```sh
gcc -Wall -Wextra -std=c99 BLOK1/Uloha_1.1.c -o uloha_1_1
gcc -Wall -Wextra -std=c99 BLOK1/Uloha_1.5.c -o uloha_1_5 -lm
```

Zvyšok bloku 2 vyžaduje Visual Studio (x86). Blok 3:

```sh
gcc -Wall -Wextra -std=c99 BLOK3/BLOK3_Linux.c -o blok3_chat
```

```bat
cl BLOK3\BLOK3_MSVC.c ws2_32.lib
```

CI prekladá všetko na Linuxe (GCC) aj Windowse (MSVC, x86).

## Odkazy

- [Stránka predmetu](http://ap.urk.fei.stuba.sk/)
- [Zadania bloku 1](http://ap.urk.fei.stuba.sk/student/blok-1)
- [Zadania bloku 2](http://ap.urk.fei.stuba.sk/student/blok-2)
- [Zadania bloku 3](http://ap.urk.fei.stuba.sk/student/blok-3)

> [!NOTE]
> Kód slúži ako referencia. Na obhajobe musíte vysvetliť každý riadok, preto ho nekopírujte bez pochopenia.

---

<div align="center">

Dmytrii Savin ([@dmitthedazed](https://github.com/dmitthedazed)). Licencia [MIT](LICENSE).

</div>
