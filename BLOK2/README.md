# BLOK 2 — Inline Assembly & System Programming / Ассемблер и системное программирование

## 🇬🇧 English

Block 2 covers MSVC inline assembly (`__asm`), pointers, file I/O with character encoding, multimedia APIs, and console semigraphics.

> ⚠️ **Note:** Tasks 2.1.x use MSVC inline assembler (`__asm {}`), which only works in **32-bit MSVC** mode. GCC/Clang do not support this syntax.

### Tasks

| # | Topic | Pts | File |
|---|-------|-----|------|
| 2.1.1 | Sum of two numbers via inline asm | 1 | [`Uloha_2.1.1.c`](Uloha_2.1.1.c) |
| 2.1.2 | Multiply by 2 using SHL | 1 | [`Uloha_2.1.2.c`](Uloha_2.1.2.c) |
| 2.1.3 | Digit → hex ASCII character | 3 | [`Uloha_2.1.3.c`](Uloha_2.1.3.c) |
| 2.1.4 | CPU vendor string via CPUID | 2 | [`Uloha_2.1.4.c`](Uloha_2.1.4.c) |
| 2.2 | Pointers — addresses & dereferencing | 3 | [`Uloha_2.2.c`](Uloha_2.2.c) |
| 2.3.1 | ISO-8859-2 → CP-1250 encoding conversion | 2 | [`Uloha_2.3.1.c`](Uloha_2.3.1.c) |
| 2.3.2 | File read + XOR decryption | 1 | [`Uloha_2.3.2.c`](Uloha_2.3.2.c) |
| 2.3.3 | RAID array reconstruction via XOR | 3 | [`Uloha_2.3.3.c`](Uloha_2.3.3.c) |
| 2.4 | Multimedia player (MCI API) | 4 | [`Uloha_2.4.c`](Uloha_2.4.c) |
| 2.5.1 | Console text color ranges | 1 | [`Uloha_2.5.1.c`](Uloha_2.5.1.c) |
| 2.5.2 | Semigraphic framed table at [x,y] | 3 | [`Uloha_2.5.2.c`](Uloha_2.5.2.c) |
| 2.6 | Reaction time measurement | 4 | [`Uloha_2.6.c`](Uloha_2.6.c) |

Combined file: [`BLOK2.c`](BLOK2.c)

### Build

Open in **Visual Studio** and compile as a C project (x86, 32-bit).

```cmd
cl /Fe:blok2.exe BLOK2.c winmm.lib
```

---

## 🇷🇺 Русский

Блок 2 охватывает встроенный ассемблер MSVC (`__asm`), указатели, файловый ввод-вывод с конвертацией кодировок, мультимедийные API и консольную семиграфику.

> ⚠️ **Примечание:** Задания 2.1.x используют синтаксис `__asm {}` от MSVC, который работает **только в 32-битном режиме MSVC**. GCC/Clang этот синтаксис не поддерживают.

### Задания

| # | Тема | Баллы | Файл |
|---|------|-------|------|
| 2.1.1 | Сумма двух чисел через inline asm | 1 | [`Uloha_2.1.1.c`](Uloha_2.1.1.c) |
| 2.1.2 | Умножение на 2 через SHL | 1 | [`Uloha_2.1.2.c`](Uloha_2.1.2.c) |
| 2.1.3 | Цифра → шестнадцатеричный ASCII символ | 3 | [`Uloha_2.1.3.c`](Uloha_2.1.3.c) |
| 2.1.4 | Строка производителя CPU через CPUID | 2 | [`Uloha_2.1.4.c`](Uloha_2.1.4.c) |
| 2.2 | Указатели — адреса и разыменование | 3 | [`Uloha_2.2.c`](Uloha_2.2.c) |
| 2.3.1 | Конвертация ISO-8859-2 → CP-1250 | 2 | [`Uloha_2.3.1.c`](Uloha_2.3.1.c) |
| 2.3.2 | Чтение файла + XOR-дешифрование | 1 | [`Uloha_2.3.2.c`](Uloha_2.3.2.c) |
| 2.3.3 | Восстановление RAID-массива через XOR | 3 | [`Uloha_2.3.3.c`](Uloha_2.3.3.c) |
| 2.4 | Мультимедийный проигрыватель (MCI API) | 4 | [`Uloha_2.4.c`](Uloha_2.4.c) |
| 2.5.1 | Цветовые диапазоны текста в консоли | 1 | [`Uloha_2.5.1.c`](Uloha_2.5.1.c) |
| 2.5.2 | Семиграфическая таблица в рамке на [x,y] | 3 | [`Uloha_2.5.2.c`](Uloha_2.5.2.c) |
| 2.6 | Измерение времени реакции | 4 | [`Uloha_2.6.c`](Uloha_2.6.c) |

Сводный файл: [`BLOK2.c`](BLOK2.c)

### Сборка

Открыть в **Visual Studio** и скомпилировать как C-проект (x86, 32-бит).

```cmd
cl /Fe:blok2.exe BLOK2.c winmm.lib
```
