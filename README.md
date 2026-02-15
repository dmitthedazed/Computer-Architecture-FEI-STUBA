# 🖥️ Computer Architecture — FEI STU

> Riešenia úloh z predmetu **Architektúra počítačov**  
> Fakulta elektrotechniky a informatiky, Slovenská technická univerzita v Bratislave  
> Letný semester 2024/2025

## 📁 Štruktúra repozitára

### Úvod — [`1_Uvod.c`](1_Uvod.c)
Úvodné cvičenie — práca s cyklami a funkciami v jazyku C.

---

### BLOK 1 — Číselné sústavy a základy C  
📖 Podrobné README: [🇬🇧 English / 🇷🇺 Русский](BLOK1/README.md)

| Úloha | Téma | Body | Súbor |
|-------|------|------|-------|
| 1.1 | Zobrazenie čísla v dvojkovej, desiatkovej a šestnástkovej sústave | 2b | [`Uloha_1.1.c`](BLOK1/Uloha_1.1.c) |
| 1.2 | Rotačný posun bitov doprava (cyklický posun) | 2b | [`Uloha_1.2.c`](BLOK1/Uloha_1.2.c) |
| 1.3 | Počet jednotiek (nastavených bitov) v binárnej reprezentácii čísla | 2b | [`Uloha_1.3.c`](BLOK1/Uloha_1.3.c) |
| 1.4 | Výpočet strojového epsilon pre `float` a `double` | 3b | [`Uloha_1.4.c`](BLOK1/Uloha_1.4.c) |
| 1.5 | Výpočet `sin(x)` pomocou Taylorovho radu | 4b | [`Uloha_1.5.c`](BLOK1/Uloha_1.5.c) |
| 1.6 | Výpočet kontrolnej sumy (checksum) IntelHex riadka | 4b | [`Uloha_1.6.c`](BLOK1/Uloha_1.6.c) |

Súhrnný súbor so všetkými úlohami bloku: [`BLOK1.C`](BLOK1/BLOK1.C)

---

### BLOK 2 — Inline assembler a systémové programovanie  
📖 Podrobné README: [🇬🇧 English / 🇷🇺 Русский](BLOK2/README.md)

| Úloha | Téma | Body | Súbor |
|-------|------|------|-------|
| 2.1.1 | Súčet dvoch čísel pomocou inline assemblera | 1b | [`Uloha_2.1.1.c`](BLOK2/Uloha_2.1.1.c) |
| 2.1.2 | Násobenie dvomi pomocou bitového posunu (SHL) | 1b | [`Uloha_2.1.2.c`](BLOK2/Uloha_2.1.2.c) |
| 2.1.3 | Prevod číslice na hexadecimálny ASCII znak | 3b | [`Uloha_2.1.3.c`](BLOK2/Uloha_2.1.3.c) |
| 2.1.4 | Zistenie výrobcu procesora pomocou inštrukcie CPUID | 2b | [`Uloha_2.1.4.c`](BLOK2/Uloha_2.1.4.c) |
| 2.2 | Práca so smerníkmi — adresy, dereferencie | 3b | [`Uloha_2.2.c`](BLOK2/Uloha_2.2.c) |
| 2.3.1 | Konverzia kódovania ISO-8859-2 → CP-1250 | 2b | [`Uloha_2.3.1.c`](BLOK2/Uloha_2.3.1.c) |
| 2.3.2 | Čítanie súboru a XOR dešifrovanie | 1b | [`Uloha_2.3.2.c`](BLOK2/Uloha_2.3.2.c) |
| 2.3.3 | Rekonštrukcia RAID poľa pomocou XOR | 3b | [`Uloha_2.3.3.c`](BLOK2/Uloha_2.3.3.c) |
| 2.4 | Multimediálny prehrávač (MCI API) | 4b | [`Uloha_2.4.c`](BLOK2/Uloha_2.4.c) |
| 2.5.1 | Zmena farby textu v konzole | 1b | [`Uloha_2.5.1.c`](BLOK2/Uloha_2.5.1.c) |
| 2.5.2 | Semigrafická tabuľka na pozícii [x,y] | 3b | [`Uloha_2.5.2.c`](BLOK2/Uloha_2.5.2.c) |
| 2.6 | Meranie reakčného času (klávesnica) | 4b | [`Uloha_2.6.c`](BLOK2/Uloha_2.6.c) |

Súhrnný súbor so všetkými úlohami bloku: [`BLOK2.c`](BLOK2/BLOK2.c)

---

### BLOK 3 — Sieťové programovanie (TCP klient)  
📖 Podrobné README: [🇬🇧 English / 🇷🇺 Русский](BLOK3/README.md)

| Súbor | Popis |
|-------|-------|
| [`BLOK3_MSVC.c`](BLOK3/BLOK3_MSVC.c) | TCP chat klient — verzia pre Windows (Winsock2) |
| [`BLOK3_Linux.c`](BLOK3/BLOK3_Linux.c) | TCP chat klient — verzia pre Linux (POSIX sockets) |

Klient sa pripojí k serveru, umožňuje posielať a prijímať správy, s podporou XOR dešifrovania a extrakcie správ na prvočíselných pozíciách.

---

## 🔧 Kompilácia

### BLOK 1 (GCC / akýkoľvek C kompilátor)
```bash
gcc BLOK1/Uloha_1.1.c -o uloha_1_1
gcc BLOK1/Uloha_1.3.c -o uloha_1_3
gcc BLOK1/Uloha_1.6.c -o uloha_1_6
```

### BLOK 2 (vyžaduje MSVC — inline assembler `__asm`)
Otvoriť vo **Visual Studio** a skompilovať ako C projekt (x86).

> ⚠️ **Upozornenie:** BLOK 2 používa MSVC inline assembler (`__asm {}`), čo funguje **iba** v 32-bitovom režime MSVC.  GCC/Clang tento syntax nepodporujú.

### BLOK 3
```bash
# Linux
gcc BLOK3/BLOK3_Linux.c -o blok3_chat

# Windows (MSVC) — kompilovať vo Visual Studio, alebo:
cl BLOK3/BLOK3_MSVC.c ws2_32.lib
```

---

## ⚠️ Disclaimer

Tento repozitár slúži ako referencia a inšpirácia. **Nekopírujte riešenia bez pochopenia kódu** — na obhajobe musíte vedieť vysvetliť každý riadok.

## 📄 Licencia

[MIT](LICENSE)
