# BLOK 3 — Network Programming (TCP Client) / Сетевое программирование (TCP-клиент)

## 🇬🇧 English

Block 3 implements a TCP chat client that connects to a course server. Two platform-specific versions are provided.

### Files

| File | Platform | Socket API |
|------|----------|------------|
| [`BLOK3_MSVC.c`](BLOK3_MSVC.c) | Windows | Winsock2 |
| [`BLOK3_Linux.c`](BLOK3_Linux.c) | Linux | POSIX sockets |

### Features

- **Modular architecture** — connection, send/receive, and crypto logic are split into small helper functions
- **Named constants** — server IP, port, colors, chat layout width
- **Auto-response** — automatic pattern matching for server prompts (codes, coordinates, PRIMENUMBER, Trinity, AIS ID remainder)
- **XOR decryption** — 131-byte block with key 55, validated with `isprint()`
- **Prime char extraction** — characters at prime indices form a hidden message
- **Caesar cipher** — bonus task for shifted-alphabet decryption
- **Session logging** — all messages logged to `chat_log.txt`

### Build

```bash
# Linux
gcc -Wall -Wextra -std=c99 BLOK3_Linux.c -o blok3_chat

# Windows (MSVC)
cl BLOK3_MSVC.c ws2_32.lib
```

### Usage

```bash
./blok3_chat
# Type messages, press Enter to send
# Type "end" to disconnect
```

---

## 🇷🇺 Русский

Блок 3 реализует TCP чат-клиент для подключения к серверу курса. Представлены две платформенные версии.

### Файлы

| Файл | Платформа | Сокет API |
|------|-----------|-----------|
| [`BLOK3_MSVC.c`](BLOK3_MSVC.c) | Windows | Winsock2 |
| [`BLOK3_Linux.c`](BLOK3_Linux.c) | Linux | POSIX sockets |

### Возможности

- **Модульная архитектура** — логика подключения, отправки/приёма и шифрования разделена на вспомогательные функции
- **Именованные константы** — IP сервера, порт, цвета, ширина чата
- **Автоответы** — автоматическое сопоставление с промптами сервера (коды, координаты, PRIMENUMBER, Trinity, остаток AIS ID)
- **XOR-дешифрование** — 131 байт с ключом 55, валидация через `isprint()`
- **Извлечение простых символов** — символы на позициях простых чисел формируют скрытое сообщение
- **Шифр Цезаря** — бонусное задание для дешифровки со сдвигом алфавита
- **Логирование сессии** — все сообщения записываются в `chat_log.txt`

### Сборка

```bash
# Linux
gcc -Wall -Wextra -std=c99 BLOK3_Linux.c -o blok3_chat

# Windows (MSVC)
cl BLOK3_MSVC.c ws2_32.lib
```

### Использование

```bash
./blok3_chat
# Вводите сообщения, Enter для отправки
# "end" для отключения
```
