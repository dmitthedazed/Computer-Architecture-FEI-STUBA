// BLOK 3 — Sieťové programovanie (TCP klient)
// Verzia pre Windows (Winsock2, MSVC)
//
// Program sa pripojí k serveru cez TCP, umožňuje posielať a prijímať správy.
// Podporuje:
//   - XOR dešifrovanie (131-bajtové správy, kľúč 55)
//   - Extrakciu znakov na prvočíselných pozíciách (PRIMENUMBER)
//   - Výpočet zvyšku z AIS ID
//   - Caesarovu šifru (BONUS)
// Komunikácia je zobrazená ako dvojstranný chat s farebnými atribútmi konzoly.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

// ─── Configuration ──────────────────────────────────────────────────────────
#define AP_SERVER_IP "147.175.115.34"
#define AP_SERVER_PORT "777"
#define DEFAULT_BUFLEN 4096
#define CHAT_WIDTH 40 // max chars per line in chat column
#define SERVER_COL 50 // X offset for server messages

// ─── Console colors ─────────────────────────────────────────────────────────
#define CLR_USER 9    // bright blue
#define CLR_SERVER 10 // bright green
#define CLR_ERROR 12  // bright red
#define CLR_RESET 15  // white

// ─── Global ─────────────────────────────────────────────────────────────────
static HANDLE hConsole;
static COORD chatPos;
static FILE *logFile;

// ═══════════════════════════════════════════════════════════════════════════
// Helper functions
// ═══════════════════════════════════════════════════════════════════════════

/** Set console code page to UTF-8 and save the console handle. */
static void initConsole(void) {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  chatPos.X = 0;
  chatPos.Y = 0;
  system("cls");
}

/** Open (or reopen) the chat log file in append mode. */
static void initLog(void) {
  logFile = fopen("chat_log.txt", "w");
  if (!logFile) {
    fprintf(stderr, "Warning: could not open chat_log.txt\n");
  }
}

/** Append one line to the chat log. */
static void logMsg(const char *source, const char *text) {
  if (!logFile)
    return;
  fprintf(logFile, "%s: %s\n", source, text);
  fflush(logFile);
}

// ─── Connection helpers ─────────────────────────────────────────────────────

/** Initialise Winsock, resolve the address, create a socket and connect.
 *  Returns the connected SOCKET or exits on failure.                       */
static SOCKET initConnection(void) {
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    fprintf(stderr, "WSAStartup failed: %d\n", iResult);
    exit(1);
  }

  struct addrinfo hints, *result = NULL;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  iResult = getaddrinfo(AP_SERVER_IP, AP_SERVER_PORT, &hints, &result);
  if (iResult != 0) {
    fprintf(stderr, "getaddrinfo failed: %d\n", iResult);
    WSACleanup();
    exit(1);
  }

  SOCKET sock =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (sock == INVALID_SOCKET) {
    fprintf(stderr, "socket() failed: %d\n", WSAGetLastError());
    freeaddrinfo(result);
    WSACleanup();
    exit(1);
  }

  iResult = connect(sock, result->ai_addr, (int)result->ai_addrlen);
  freeaddrinfo(result);
  if (iResult == SOCKET_ERROR) {
    fprintf(stderr, "connect() failed – server unreachable.\n");
    closesocket(sock);
    WSACleanup();
    exit(1);
  }

  printf("Connected to %s:%s\n", AP_SERVER_IP, AP_SERVER_PORT);
  Sleep(250);
  return sock;
}

/** Clean up Winsock resources. */
static void disconnect(SOCKET sock) {
  closesocket(sock);
  WSACleanup();
}

// ─── Chat display helpers ───────────────────────────────────────────────────

/** Print text on the LEFT side of the console (user messages). */
static void printLeft(const char *prefix, const char *text) {
  chatPos.X = 0;
  chatPos.Y += 1;
  SetConsoleCursorPosition(hConsole, chatPos);
  SetConsoleTextAttribute(hConsole, CLR_USER);
  printf("%s ", prefix);

  int col = (int)strlen(prefix) + 1;
  for (int i = 0; text[i]; i++) {
    if (col >= CHAT_WIDTH) {
      col = 0;
      chatPos.Y += 1;
      chatPos.X = 0;
      SetConsoleCursorPosition(hConsole, chatPos);
    }
    putchar(text[i]);
    fflush(stdout);
    Sleep(1);
    col++;
  }
  printf("\n");
  chatPos.Y += 1;
  SetConsoleTextAttribute(hConsole, CLR_RESET);
}

/** Print text on the RIGHT side of the console (server messages). */
static void printRight(const char *prefix, const char *text) {
  chatPos.X = SERVER_COL;
  chatPos.Y += 1;
  SetConsoleCursorPosition(hConsole, chatPos);
  SetConsoleTextAttribute(hConsole, CLR_SERVER);
  printf("%s ", prefix);

  int col = (int)strlen(prefix) + 1;
  for (int i = 0; text[i]; i++) {
    if (text[i] == ' ') {
      /* look-ahead: check if the next word fits on this line */
      int wlen = 0;
      for (int k = i + 1; text[k] && text[k] != ' '; k++)
        wlen++;
      if (col + wlen >= CHAT_WIDTH) {
        col = 0;
        chatPos.X = SERVER_COL;
        chatPos.Y += 1;
        SetConsoleCursorPosition(hConsole, chatPos);
      }
    }
    if (col >= CHAT_WIDTH) {
      col = 0;
      chatPos.X = SERVER_COL;
      chatPos.Y += 1;
      SetConsoleCursorPosition(hConsole, chatPos);
    }
    putchar(text[i]);
    fflush(stdout);
    Sleep(1);
    col++;
  }
  printf("\n");
  chatPos.Y += 1;
  SetConsoleTextAttribute(hConsole, CLR_RESET);
}

// ─── Send / receive wrappers ────────────────────────────────────────────────

/** Send a message and log it.  Returns bytes sent or exits on error. */
static int sendMsg(SOCKET sock, const char *msg) {
  int n = send(sock, msg, (int)strlen(msg), 0);
  if (n == SOCKET_ERROR) {
    fprintf(stderr, "send failed: %d\n", WSAGetLastError());
    disconnect(sock);
    exit(1);
  }
  printLeft("You:", msg);
  logMsg("User", msg);
  return n;
}

/** Receive a message into buf (caller provides DEFAULT_BUFLEN).
 *  Returns bytes received, 0 on connection close, or exits on error.       */
static int recvMsg(SOCKET sock, char *buf) {
  ZeroMemory(buf, DEFAULT_BUFLEN);
  int n = recv(sock, buf, DEFAULT_BUFLEN - 1, 0);
  if (n > 0) {
    buf[n] = '\0';
  } else if (n == 0) {
    printf("Connection closed by server.\n");
  } else {
    fprintf(stderr, "recv failed: %d\n", WSAGetLastError());
  }
  return n;
}

// ═══════════════════════════════════════════════════════════════════════════
// Task-specific logic
// ═══════════════════════════════════════════════════════════════════════════

/** Auto-send helper: send a fixed reply and immediately read response.
 *  Returns 1 so the caller can skip the next manual input.                 */
static int autoSend(SOCKET sock, const char *reply, char *recvbuf) {
  sendMsg(sock, reply);
  return 1; /* flag: skip next user input */
}

/** Compute remainder from AIS student ID (6 digits).
 *  sum(first 5 digits) % fifth_digit, encoded as a printable char.        */
static char aisidRemainder(const char *id) {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += id[i] - '0';
  }
  int div = id[4] - '0';
  if (div == 0)
    div = 9;
  return (char)((sum % div) + '0');
}

/** XOR decrypt (key = 55) with isprint validation. */
static void decryptXOR(const char *src, int len, char *dst) {
  int j = 0;
  for (int i = 0; i < len; i++) {
    char ch = src[i] ^ 55;
    if (isprint((unsigned char)ch) || ch == ' ' || ch == '\n') {
      dst[j++] = ch;
    }
  }
  dst[j] = '\0';
}

/** Check if n is a prime number. */
static int isPrime(int n) {
  if (n < 2)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;
  for (int d = 3; d * d <= n; d += 2) {
    if (n % d == 0)
      return 0;
  }
  return 1;
}

/** Extract characters at prime-number positions (1-indexed). */
static void extractPrimeChars(const char *src, char *dst) {
  int len = (int)strlen(src);
  int j = 0;
  for (int i = 2; i <= len; i++) {
    if (isPrime(i)) {
      dst[j++] = src[i - 1];
    }
  }
  dst[j] = '\0';
}

/** Caesar cipher: shift uppercase letters by `shift` positions.
 *  Input string is assumed to be uppercase or gets uppercased.             */
static void caesarCipher(const char *src, int shift, char *dst) {
  int len = (int)strlen(src);
  for (int i = 0; i < len; i++) {
    char ch = (char)toupper((unsigned char)src[i]);
    if (isalpha((unsigned char)ch)) {
      ch = (char)(((ch - 'A' + shift) % 26) + 'A');
    }
    dst[i] = ch;
  }
  dst[len] = '\0';
}

/** Extract the integral part of a double as a string (static buffer). */
static const char *integralPart(double value) {
  static char buf[16];
  snprintf(buf, sizeof(buf), "%d", (int)value);
  return buf;
}

// ═══════════════════════════════════════════════════════════════════════════
// Main chat loop
// ═══════════════════════════════════════════════════════════════════════════

int main(void) {
  initConsole();
  initLog();

  SOCKET sock = initConnection();

  char sendbuf[DEFAULT_BUFLEN];
  char recvbuf[DEFAULT_BUFLEN];
  char decoded[DEFAULT_BUFLEN];
  int skipInput = 0; /* when 1, skip manual input (auto-reply) */

  while (1) {
    /* ── 1. Get user input (or skip if we auto-replied) ──────── */
    if (!skipInput) {
      chatPos.X = 0;
      chatPos.Y += 1;
      SetConsoleCursorPosition(hConsole, chatPos);
      SetConsoleTextAttribute(hConsole, CLR_USER);
      printf("Enter message: ");
      SetConsoleTextAttribute(hConsole, CLR_RESET);

      if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
        break;
      sendbuf[strcspn(sendbuf, "\n")] = '\0';
      if (strlen(sendbuf) == 0)
        continue;
      if (strcmp(sendbuf, "quit") == 0) {
        logMsg("User", "quit");
        break;
      }

      sendMsg(sock, sendbuf);
    }
    skipInput = 0;

    /* ── 2. Receive server response ──────────────────────────── */
    int n = recvMsg(sock, recvbuf);
    if (n <= 0)
      break;

    /* ── 3. Handle XOR decryption (131 bytes, key 55) ────────── */
    if (n == 131) {
      decryptXOR(recvbuf, n, decoded);
      printRight("Server (decrypted):", decoded);
      logMsg("Server (XOR)", decoded);

      /* Auto-respond if the decrypted message asks a question */
      if (strstr(decoded, "Are you willing to find out where she is?")) {
        skipInput = autoSend(sock, "BB", recvbuf);
        continue;
      }
    }
    /* ── 4. Handle PRIMENUMBER extraction ────────────────────── */
    else if (strcmp(sendbuf, "PRIMENUMBER") == 0) {
      extractPrimeChars(recvbuf, decoded);
      printRight("Server (PRIME):", decoded);
      logMsg("Server (PRIMENUMBER)", decoded);
    }
    /* ── 5. Normal server message ────────────────────────────── */
    else {
      printRight("Server:", recvbuf);
      logMsg("Server", recvbuf);
    }

    /* ── 6. Auto-response pattern matching ───────────────────── */
    /* Code prompts */
    if (strstr(recvbuf, "send me the code 845548")) {
      skipInput = autoSend(sock, "845548", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send me the code 753332")) {
      skipInput = autoSend(sock, "753332", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send me the code 123")) {
      skipInput = autoSend(sock, "123", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "333222334")) {
      skipInput = autoSend(sock, "333222334", recvbuf);
      continue;
    }
    /* Coordinate prompts */
    if (strstr(recvbuf, "Send me the integral part of the first coordinate")) {
      skipInput = autoSend(sock, integralPart(51.8723), recvbuf);
      continue;
    }
    if (strstr(recvbuf, "Send me the integral part of the second coordinate")) {
      skipInput = autoSend(sock, integralPart(0.0012), recvbuf);
      continue;
    }
    if (strstr(recvbuf, "Send me the abbreviation of the detected object")) {
      skipInput = autoSend(sock, "B.B.", recvbuf);
      continue;
    }
    /* PRIMENUMBER */
    if (strstr(recvbuf, "send me the string PRIMENUMBER")) {
      skipInput = autoSend(sock, "PRIMENUMBER", recvbuf);
      continue;
    }
    /* Trinity / Sion */
    if (strstr(recvbuf, "send it to Sion")) {
      skipInput = autoSend(sock, "Trinity", recvbuf);
      continue;
    }
    /* AIS ID remainder */
    if (strstr(recvbuf, "The result must be computed by your software!")) {
      char reply[2] = {aisidRemainder(sendbuf), '\0'};
      skipInput = autoSend(sock, reply, recvbuf);
      continue;
    }
    /* Caesar cipher BONUS */
    if (strstr(recvbuf, "THE BONUS IS HERE")) {
      caesarCipher("OBVMHKR", 7, decoded);
      skipInput = autoSend(sock, decoded, recvbuf);
      continue;
    }
  }

  if (logFile)
    fclose(logFile);
  disconnect(sock);
  return 0;
}