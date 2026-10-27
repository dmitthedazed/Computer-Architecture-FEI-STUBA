<div align="center">

# Computer Architecture

**Solutions for the Computer Architecture course at FEI STUBA: C, x86 inline assembly, Windows API and TCP**

Summer semester 2024/2025. Course site: [ap.urk.fei.stuba.sk](http://ap.urk.fei.stuba.sk/)

[![Build](https://github.com/dmitthedazed/Computer-Architecture-FEI-STUBA/actions/workflows/build.yml/badge.svg)](https://github.com/dmitthedazed/Computer-Architecture-FEI-STUBA/actions/workflows/build.yml)
![C](https://img.shields.io/badge/C-C99-A8B9CC?logo=c&logoColor=white)
![x86](https://img.shields.io/badge/x86-inline%20asm-lightgrey)
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey)](LICENSE)

<p align="center"><b>English</b> · <a href="README.sk.md">Slovenčina</a></p>

</div>

> [!WARNING]
> Block 2 uses MSVC inline assembly (`__asm {}`), which only builds in 32-bit MSVC. GCC and Clang do not support it.

Each block has its own README with a short English and Russian description.

## Intro

[`1_Uvod.c`](1_Uvod.c): loops and functions in C.

## Block 1: number systems and C basics

Combined file: [`BLOK1.C`](BLOK1/BLOK1.C). Details: [BLOK1/README.md](BLOK1/README.md).

| # | Topic | Pts | File |
|:-:|---|:-:|---|
| 1.1 | Number in binary, decimal and hexadecimal | 2 | [`Uloha_1.1.c`](BLOK1/Uloha_1.1.c) |
| 1.2 | Circular right bit rotation | 2 | [`Uloha_1.2.c`](BLOK1/Uloha_1.2.c) |
| 1.3 | Count set bits | 2 | [`Uloha_1.3.c`](BLOK1/Uloha_1.3.c) |
| 1.4 | Machine epsilon for `float` and `double` | 3 | [`Uloha_1.4.c`](BLOK1/Uloha_1.4.c) |
| 1.5 | `sin(x)` via Taylor series | 4 | [`Uloha_1.5.c`](BLOK1/Uloha_1.5.c) |
| 1.6 | IntelHex line checksum | 4 | [`Uloha_1.6.c`](BLOK1/Uloha_1.6.c) |

## Block 2: inline assembly and system programming

Combined file: [`BLOK2.c`](BLOK2/BLOK2.c). Details: [BLOK2/README.md](BLOK2/README.md).

| # | Topic | Pts | File |
|:-:|---|:-:|---|
| 2.1.1 | Sum of two numbers via inline asm | 1 | [`Uloha_2.1.1.c`](BLOK2/Uloha_2.1.1.c) |
| 2.1.2 | Multiply by 2 using SHL | 1 | [`Uloha_2.1.2.c`](BLOK2/Uloha_2.1.2.c) |
| 2.1.3 | Digit to hex ASCII character | 3 | [`Uloha_2.1.3.c`](BLOK2/Uloha_2.1.3.c) |
| 2.1.4 | CPU vendor string via CPUID | 2 | [`Uloha_2.1.4.c`](BLOK2/Uloha_2.1.4.c) |
| 2.2 | Pointers: addresses and dereferencing | 3 | [`Uloha_2.2.c`](BLOK2/Uloha_2.2.c) |
| 2.3.1 | ISO-8859-2 to CP-1250 conversion | 2 | [`Uloha_2.3.1.c`](BLOK2/Uloha_2.3.1.c) |
| 2.3.2 | File read and XOR decryption | 1 | [`Uloha_2.3.2.c`](BLOK2/Uloha_2.3.2.c) |
| 2.3.3 | RAID array reconstruction via XOR | 3 | [`Uloha_2.3.3.c`](BLOK2/Uloha_2.3.3.c) |
| 2.4 | Multimedia player (MCI API) | 4 | [`Uloha_2.4.c`](BLOK2/Uloha_2.4.c) |
| 2.5.1 | Console text colors | 1 | [`Uloha_2.5.1.c`](BLOK2/Uloha_2.5.1.c) |
| 2.5.2 | Framed semigraphic table at [x,y] | 3 | [`Uloha_2.5.2.c`](BLOK2/Uloha_2.5.2.c) |
| 2.6 | Reaction time measurement | 4 | [`Uloha_2.6.c`](BLOK2/Uloha_2.6.c) |

## Block 3: TCP client

A chat client for the course server `147.175.115.34:777`. It can send and receive messages, decrypt XOR blocks and extract the message hidden at prime positions. Details: [BLOK3/README.md](BLOK3/README.md).

| File | Platform | API |
|---|---|---|
| [`BLOK3_MSVC.c`](BLOK3/BLOK3_MSVC.c) | Windows | Winsock2 |
| [`BLOK3_Linux.c`](BLOK3/BLOK3_Linux.c) | Linux | POSIX sockets |

## Build

Block 1, the intro and the portable parts of block 2 (`Uloha_2.3.1.c`, `Uloha_2.3.3.c`) build with GCC:

```sh
gcc -Wall -Wextra -std=c99 BLOK1/Uloha_1.1.c -o uloha_1_1
gcc -Wall -Wextra -std=c99 BLOK1/Uloha_1.5.c -o uloha_1_5 -lm
```

The rest of block 2 needs Visual Studio (x86). Block 3:

```sh
gcc -Wall -Wextra -std=c99 BLOK3/BLOK3_Linux.c -o blok3_chat
```

```bat
cl BLOK3\BLOK3_MSVC.c ws2_32.lib
```

CI compiles everything on Linux (GCC) and Windows (MSVC, x86).

## Links

- [Course site](http://ap.urk.fei.stuba.sk/)
- [Block 1 tasks](http://ap.urk.fei.stuba.sk/student/blok-1)
- [Block 2 tasks](http://ap.urk.fei.stuba.sk/student/blok-2)
- [Block 3 tasks](http://ap.urk.fei.stuba.sk/student/blok-3)

> [!NOTE]
> The code is here for reference. At the defence you have to explain every line, so don't copy it without understanding it.

---

<div align="center">

Dmytrii Savin ([@dmitthedazed](https://github.com/dmitthedazed)). Licensed under the [MIT License](LICENSE).

</div>
