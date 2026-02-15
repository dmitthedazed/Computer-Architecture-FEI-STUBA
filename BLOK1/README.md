# BLOK 1 — Number Systems & C Basics / Числовые системы и основы C

🌐 **Course website:** [ap.urk.fei.stuba.sk](http://ap.urk.fei.stuba.sk/) | [Block 1 tasks](http://ap.urk.fei.stuba.sk/student/blok-1)

## 🇬🇧 English

Block 1 covers number representations, bitwise operations, and numerical methods in C.

### Tasks

| # | Topic | Pts | File |
|---|-------|-----|------|
| 1.1 | Display a number in binary, decimal, and hexadecimal | 2 | [`Uloha_1.1.c`](Uloha_1.1.c) |
| 1.2 | Circular right bit-rotation | 2 | [`Uloha_1.2.c`](Uloha_1.2.c) |
| 1.3 | Count set bits (popcount) | 2 | [`Uloha_1.3.c`](Uloha_1.3.c) |
| 1.4 | Machine epsilon for `float` and `double` | 3 | [`Uloha_1.4.c`](Uloha_1.4.c) |
| 1.5 | `sin(x)` via Taylor series | 4 | [`Uloha_1.5.c`](Uloha_1.5.c) |
| 1.6 | IntelHex checksum computation | 4 | [`Uloha_1.6.c`](Uloha_1.6.c) |

Combined file: [`BLOK1.C`](BLOK1.C)

### Build

```bash
gcc Uloha_1.1.c -o uloha_1_1 -lm
gcc Uloha_1.5.c -o uloha_1_5 -lm
```

All tasks compile with any standard C compiler (GCC, Clang, MSVC).

---

## 🇷🇺 Русский

Блок 1 охватывает системы счисления, побитовые операции и численные методы на C.  
🌐 [Страница курса](http://ap.urk.fei.stuba.sk/) · [Задания Блока 1](http://ap.urk.fei.stuba.sk/student/blok-1)

### Задания

| # | Тема | Баллы | Файл |
|---|------|-------|------|
| 1.1 | Вывод числа в двоичной, десятичной и шестнадцатеричной системе | 2 | [`Uloha_1.1.c`](Uloha_1.1.c) |
| 1.2 | Циклический сдвиг битов вправо | 2 | [`Uloha_1.2.c`](Uloha_1.2.c) |
| 1.3 | Подсчет установленных битов (popcount) | 2 | [`Uloha_1.3.c`](Uloha_1.3.c) |
| 1.4 | Машинный эпсилон для `float` и `double` | 3 | [`Uloha_1.4.c`](Uloha_1.4.c) |
| 1.5 | `sin(x)` через ряд Тейлора | 4 | [`Uloha_1.5.c`](Uloha_1.5.c) |
| 1.6 | Вычисление контрольной суммы IntelHex | 4 | [`Uloha_1.6.c`](Uloha_1.6.c) |

Сводный файл: [`BLOK1.C`](BLOK1.C)

### Сборка

```bash
gcc Uloha_1.1.c -o uloha_1_1 -lm
gcc Uloha_1.5.c -o uloha_1_5 -lm
```

Все задания компилируются любым стандартным C-компилятором (GCC, Clang, MSVC).
