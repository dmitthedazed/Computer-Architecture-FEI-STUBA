#define _DEFAULT_SOURCE /* usleep(), h_addr */

// BLOK 3 — Sieťové programovanie (TCP klient)
// Verzia pre Linux (POSIX sockets)
//
// Program sa pripojí k serveru cez TCP, umožňuje posielať a prijímať správy.
// Podporuje:
//   - XOR dešifrovanie (131-bajtové správy, kľúč 55)
//   - Extrakciu znakov na prvočíselných pozíciách (PRIMENUMBER)
//   - Výpočet zvyšku z AIS ID
//   - Caesarovu šifru (BONUS)
// Komunikácia je zobrazená ako dvojstranný chat s farebnými ANSI kódmi.

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// ─── Configuration ──────────────────────────────────────────────────────────
#define AP_SERVER_IP "147.175.115.34"
#define AP_SERVER_PORT 777
#define DEFAULT_BUFLEN 4096
#define CHAT_WIDTH 40 // max chars per line in chat column
#define SERVER_COL 50 // X offset for server messages

// ─── ANSI color codes ───────────────────────────────────────────────────────
#define CLR_RESET "\x1b[0m"
#define CLR_USER "\x1b[94m"   // bright blue
#define CLR_SERVER "\x1b[92m" // bright green
#define CLR_ERROR "\x1b[91m"  // bright red

// ─── Global ─────────────────────────────────────────────────────────────────
static FILE *logFile;

// ═══════════════════════════════════════════════════════════════════════════
// Terminal helpers (ANSI cursor positioning)
// ═══════════════════════════════════════════════════════════════════════════

/** Move cursor to (x, y) — both 0-indexed. */
static void moveTo(int x, int y) { printf("\033[%d;%dH", y + 1, x + 1); }

static void clearScreen(void) { printf("\033[2J\033[H"); }

static void sleepMs(int ms) { usleep(ms * 1000); }

// ═══════════════════════════════════════════════════════════════════════════
// Logging
// ═══════════════════════════════════════════════════════════════════════════

static void initLog(void) {
  logFile = fopen("chat_log.txt", "w");
  if (!logFile) {
    fprintf(stderr, "Warning: could not open chat_log.txt\n");
  }
}

static void logMsg(const char *source, const char *text) {
  if (!logFile)
    return;
  fprintf(logFile, "%s: %s\n", source, text);
  fflush(logFile);
}

// ═══════════════════════════════════════════════════════════════════════════
// Connection helpers
// ═══════════════════════════════════════════════════════════════════════════

/** Create, configure and connect a TCP socket.
 *  Returns the file descriptor or exits on failure.                        */
static int initConnection(void) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr, "socket() failed: %s\n", strerror(errno));
    exit(1);
  }

  struct hostent *host = gethostbyname(AP_SERVER_IP);
  if (!host) {
    fprintf(stderr, "gethostbyname failed\n");
    close(sockfd);
    exit(1);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(AP_SERVER_PORT);
  memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);

  if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "connect() failed: %s\n", strerror(errno));
    close(sockfd);
    exit(1);
  }

  printf("Connected to %s:%d\n", AP_SERVER_IP, AP_SERVER_PORT);
  sleepMs(250);
  return sockfd;
}

// ═══════════════════════════════════════════════════════════════════════════
// Chat display helpers
// ═══════════════════════════════════════════════════════════════════════════

static int chatY; // tracks current chat row

/** Print text on the LEFT side (user messages). */
static void printLeft(const char *prefix, const char *text) {
  chatY++;
  moveTo(0, chatY);
  printf(CLR_USER "%s " CLR_RESET, prefix);

  int col = (int)strlen(prefix) + 1;
  for (int i = 0; text[i]; i++) {
    if (col >= CHAT_WIDTH) {
      col = 0;
      chatY++;
      moveTo(0, chatY);
    }
    putchar(text[i]);
    fflush(stdout);
    sleepMs(1);
    col++;
  }
  printf("\n");
  chatY++;
}

/** Print text on the RIGHT side (server messages). */
static void printRight(const char *prefix, const char *text) {
  chatY++;
  moveTo(SERVER_COL, chatY);
  printf(CLR_SERVER "%s " CLR_RESET, prefix);

  int col = (int)strlen(prefix) + 1;
  for (int i = 0; text[i]; i++) {
    if (text[i] == ' ') {
      int wlen = 0;
      for (int k = i + 1; text[k] && text[k] != ' '; k++)
        wlen++;
      if (col + wlen >= CHAT_WIDTH) {
        col = 0;
        chatY++;
        moveTo(SERVER_COL, chatY);
      }
    }
    if (col >= CHAT_WIDTH) {
      col = 0;
      chatY++;
      moveTo(SERVER_COL, chatY);
    }
    putchar(text[i]);
    fflush(stdout);
    sleepMs(1);
    col++;
  }
  printf("\n");
  chatY++;
}

// ═══════════════════════════════════════════════════════════════════════════
// Send / receive wrappers
// ═══════════════════════════════════════════════════════════════════════════

/** Send a message, display on left column, and log it. */
static int sendMsg(int sockfd, const char *msg) {
  ssize_t n = send(sockfd, msg, strlen(msg), 0);
  if (n < 0) {
    fprintf(stderr, "send failed: %s\n", strerror(errno));
    close(sockfd);
    exit(1);
  }
  printLeft("You:", msg);
  logMsg("User", msg);
  return (int)n;
}

/** Receive into buf.  Returns bytes received, 0 on close, -1 on error. */
static int recvMsg(int sockfd, char *buf) {
  memset(buf, 0, DEFAULT_BUFLEN);
  ssize_t n = recv(sockfd, buf, DEFAULT_BUFLEN - 1, 0);
  if (n > 0) {
    buf[n] = '\0';
  } else if (n == 0) {
    printf("Connection closed by server.\n");
  } else {
    fprintf(stderr, "recv failed: %s\n", strerror(errno));
  }
  return (int)n;
}

// ═══════════════════════════════════════════════════════════════════════════
// Task-specific logic
// ═══════════════════════════════════════════════════════════════════════════

/** Auto-send helper: send a fixed reply.
 *  Returns 1 so the caller can skip the next manual input.                 */
static int autoSend(int sockfd, const char *reply, char *recvbuf) {
  (void)recvbuf; /* unused, kept for symmetry */
  sendMsg(sockfd, reply);
  return 1;
}

/** Compute remainder from AIS student ID (6 digits).
 *  sum(first 5 digits) % fifth_digit, returned as a printable char.       */
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

/** Caesar cipher: shift uppercase letters by `shift` positions. */
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
  printf("\033[?25h"); /* ensure cursor is visible */
  clearScreen();
  initLog();

  int sockfd = initConnection();

  char sendbuf[DEFAULT_BUFLEN];
  char recvbuf[DEFAULT_BUFLEN];
  char decoded[DEFAULT_BUFLEN];
  int skipInput = 0;

  chatY = 2;

  while (1) {
    /* ── 1. Get user input (or skip if we auto-replied) ──────── */
    if (!skipInput) {
      chatY++;
      moveTo(0, chatY);
      printf(CLR_USER "Enter message: " CLR_RESET);

      if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
        break;
      sendbuf[strcspn(sendbuf, "\n")] = '\0';
      if (strlen(sendbuf) == 0)
        continue;
      if (strcmp(sendbuf, "quit") == 0) {
        logMsg("User", "quit");
        break;
      }

      sendMsg(sockfd, sendbuf);
    }
    skipInput = 0;

    /* ── 2. Receive server response ──────────────────────────── */
    int n = recvMsg(sockfd, recvbuf);
    if (n <= 0)
      break;

    /* ── 3. Handle XOR decryption (131 bytes, key 55) ────────── */
    if (n == 131) {
      decryptXOR(recvbuf, n, decoded);
      printRight("Server (decrypted):", decoded);
      logMsg("Server (XOR)", decoded);

      if (strstr(decoded, "Are you willing to find out where she is?")) {
        skipInput = autoSend(sockfd, "BB", recvbuf);
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
    if (strstr(recvbuf, "send me the code 845548")) {
      skipInput = autoSend(sockfd, "845548", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send me the code 753332")) {
      skipInput = autoSend(sockfd, "753332", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send me the code 123")) {
      skipInput = autoSend(sockfd, "123", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "333222334")) {
      skipInput = autoSend(sockfd, "333222334", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "Send me the integral part of the first coordinate")) {
      skipInput = autoSend(sockfd, integralPart(51.8723), recvbuf);
      continue;
    }
    if (strstr(recvbuf, "Send me the integral part of the second coordinate")) {
      skipInput = autoSend(sockfd, integralPart(0.0012), recvbuf);
      continue;
    }
    if (strstr(recvbuf, "Send me the abbreviation of the detected object")) {
      skipInput = autoSend(sockfd, "B.B.", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send me the string PRIMENUMBER")) {
      skipInput = autoSend(sockfd, "PRIMENUMBER", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "send it to Sion")) {
      skipInput = autoSend(sockfd, "Trinity", recvbuf);
      continue;
    }
    if (strstr(recvbuf, "The result must be computed by your software!")) {
      char reply[2] = {aisidRemainder(sendbuf), '\0'};
      skipInput = autoSend(sockfd, reply, recvbuf);
      continue;
    }
    /* Caesar cipher BONUS */
    if (strstr(recvbuf, "THE BONUS IS HERE")) {
      caesarCipher("OBVMHKR", 7, decoded);
      skipInput = autoSend(sockfd, decoded, recvbuf);
      continue;
    }
  }

  if (logFile)
    fclose(logFile);
  close(sockfd);
  return 0;
}