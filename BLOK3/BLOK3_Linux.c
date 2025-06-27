#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h> 
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>

// ANSI color codes for terminal output
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_BRIGHT_BLUE "\x1b[94m"
#define ANSI_COLOR_BRIGHT_GREEN "\x1b[92m"
#define ANSI_COLOR_BRIGHT_RED "\x1b[91m"

// Structure to track cursor position
typedef struct {
    int X;
    int Y;
} COORD;

// Function to set console output to UTF-8 (no-op on Unix systems as they typically use UTF-8 by default)
void utf8_console() {
    // Unix systems typically use UTF-8 by default, so this is a no-op
    printf("\033[?25h"); // Ensure cursor is visible
}

// Function to calculate the remainder as per the requirements
int aisid_remainder(int student_id) {
    int d1 = student_id / 100000;       // First digit
    int d2 = (student_id / 10000) % 10; // Second digit
    int d3 = (student_id / 1000) % 10;  // Third digit
    int d4 = (student_id / 100) % 10;   // Fourth digit
    int d5 = (student_id / 10) % 10;    // Fifth digit

    int sum_first_five = d1 + d2 + d3 + d4 + d5;

    int fifth_digit = d5;

    if (fifth_digit == 0) {
        printf("Error: The fifth digit is zero, cannot divide by zero.\n");
        return -1;
    }

    int remainder = sum_first_five % fifth_digit;
    return remainder;
}

// Function to log messages to a file
void log_message(const char *source, const char *message) {
    FILE *logFile = fopen("chat_log.txt", "a");
    if (logFile == NULL) {
        fprintf(stderr, "Error opening log file: %s\n", strerror(errno));
        return;
    }
    fprintf(logFile, "%s: %s\n", source, message);
    fclose(logFile);
}

void print_with_position(const char* text, COORD* point_ptr, const char* color) {
    printf("\033[%d;%dH", point_ptr->Y + 1, point_ptr->X + 1); // Move cursor to position
    printf("%s", color);
    printf("%s", text);
    printf(ANSI_COLOR_RESET);
    
    // Update cursor position
    point_ptr->X += strlen(text);
}

void print_newline(COORD* point_ptr) {
    printf("\n");
    point_ptr->X = 0;
    point_ptr->Y += 1;
}

void sync_cursor_position(COORD* point_ptr) {
    // In a simple implementation, we just trust our tracking
    // For a more sophisticated version, we could query the terminal
}

void clear_screen() {
    printf("\033[2J\033[H"); // Clear screen and move cursor to home
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void usleep_ms(int milliseconds) {
    usleep(milliseconds * 1000);
}

int main(void) 
{
    utf8_console(); 
    
    // Add cursor positioning for two-sided chat display
    COORD point;
    point.X = 0;
    point.Y = 0;
    
    // Clear screen at start for clean display
    clear_screen();

    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *server;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error opening socket: %s\n", strerror(errno));
        return 1;
    }
    
    printf("Socket created successfully...\n");

    // Get server by name
    server = gethostbyname("147.175.115.34");
    if (server == NULL) {
        fprintf(stderr, "Error: no such host\n");
        close(sockfd);
        return 1;
    }
    
    printf("Host resolved successfully...\n");

    // Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(777);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Not connected to server...\n");
        close(sockfd);
        return 1;
    } else {
        printf("Connected to server!\n");
    }
    
    usleep_ms(250);

    #define DEFAULT_BUFLEN 4096
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];

    while (1) {
        // User message left side
        point.X = 0;
        point.Y += 2;
        move_cursor(point.X, point.Y);
        
        printf(ANSI_COLOR_BRIGHT_BLUE "Enter message: " ANSI_COLOR_RESET);
        if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
            printf("Error reading input.\n");
            break; 
        }

        sendbuf[strcspn(sendbuf, "\n")] = 0;

        if (strcmp(sendbuf, "quit") == 0) {
            printf(ANSI_COLOR_BRIGHT_BLUE "Exiting chat.\n" ANSI_COLOR_RESET);
            log_message("User", "quit"); 
            break;
        }
        
        point.Y += 1;
        move_cursor(point.X, point.Y);
        printf(ANSI_COLOR_BRIGHT_BLUE "You: " ANSI_COLOR_RESET);
        
        int counter = 0;
        for (int i = 0; i < strlen(sendbuf); i++) {
            if (sendbuf[i] == ' ') {
                int wordLen = 0;
                int j = i + 1;
                while (sendbuf[j] != '\0' && sendbuf[j] != ' ') {
                    wordLen++;
                    j++;
                }
                if ((wordLen + counter) >= 40) {
                    counter = 0;
                    point.X = 0;
                    point.Y += 1;
                    move_cursor(point.X, point.Y);
                }
            }
            
            if (counter == 40) {
                counter = 0;
                point.X = 0;
                point.Y += 1;
                move_cursor(point.X, point.Y);
            }
            
            printf("%c", sendbuf[i]);
            fflush(stdout);
            usleep_ms(1);
            counter++;
        }
        printf("\n");
        
        log_message("User", sendbuf); 

        ssize_t bytes_sent = send(sockfd, sendbuf, strlen(sendbuf), 0);
        if (bytes_sent < 0) {
            fprintf(stderr, "send failed: %s\n", strerror(errno));
            close(sockfd);
            return 1;
        }

        if (strcmp(sendbuf, "753332") == 0) {
            point.X = 0;
            point.Y += 1;
            move_cursor(point.X, point.Y);
            
            int remainder_result = aisid_remainder(135532);
        
            if (remainder_result != -1) {
                printf("Computed remainder for 135532: %d\n", remainder_result);
                point.Y += 1; 
            }
        }

        memset(recvbuf, 0, DEFAULT_BUFLEN);

        ssize_t bytes_received = recv(sockfd, recvbuf, DEFAULT_BUFLEN - 1, 0);

        if (bytes_received > 0) {
            point.X = 0;
            point.Y += 1;
            move_cursor(point.X, point.Y);
            
            printf("Bytes received: %ld\n", bytes_received);
            point.Y += 1; 

            if (bytes_received == 131) {
                printf("Decrypting 131 byte message...\n");
                point.Y += 1; // Update Y position
                for (int k = 0; k < bytes_received; k++) {
                    recvbuf[k] = recvbuf[k] ^ 55;
                }
            }
            
            char temp_recv_log_buf[DEFAULT_BUFLEN + 1];
            memcpy(temp_recv_log_buf, recvbuf, bytes_received);
            temp_recv_log_buf[bytes_received] = '\0';
            
            point.X = 50;
            move_cursor(point.X, point.Y);
            
            if (strcmp(sendbuf, "PRIMENUMBER") == 0) {
                char* prime_extracted_message = (char*)malloc(bytes_received + 1);
                if (prime_extracted_message == NULL) {
                    printf(ANSI_COLOR_BRIGHT_RED "Error: Memory allocation failed.\n" ANSI_COLOR_RESET);
                } else {
                    int n = 0;
                    for (int idx_to_check = 2; idx_to_check <= bytes_received; idx_to_check++) {
                        int is_prime = 1;
                        for (int j = 2; j * j <= idx_to_check; j++) {
                            if (idx_to_check % j == 0) {
                                is_prime = 0;
                                break;
                            }
                        }

                        if (is_prime) {
                            prime_extracted_message[n++] = recvbuf[idx_to_check - 1];
                        }
                    }
                    prime_extracted_message[n] = '\0';

                    printf(ANSI_COLOR_BRIGHT_GREEN "Server (PRIME): " ANSI_COLOR_RESET);
                    
                    int counter = 0;
                    for (int j = 0; j < n; j++) {
                        if (counter == 40) {
                            counter = 0;
                            point.X = 50;
                            point.Y += 1;
                            move_cursor(point.X, point.Y);
                        }
                        
                        printf("%c", prime_extracted_message[j]);
                        fflush(stdout);
                        usleep_ms(1);
                        counter++;
                    }
                    printf("\n");
                    log_message("Server (PRIMENUMBER)", prime_extracted_message);
                    free(prime_extracted_message);
                }
            } else {
                printf(ANSI_COLOR_BRIGHT_GREEN "Server: " ANSI_COLOR_RESET);
                
                int counter = 0;
                for (int j = 0; j < bytes_received; j++) {
                    if (recvbuf[j] == ' ') {
                        int wordLen = 0;
                        int k = j + 1;
                        while (k < bytes_received && recvbuf[k] != ' ' && recvbuf[k] != '\0') {
                            wordLen++;
                            k++;
                        }
                        if ((wordLen + counter) >= 40) {
                            counter = 0;
                            point.X = 50;
                            point.Y += 1;
                            move_cursor(point.X, point.Y);
                        }
                    }
                    
                    if (counter == 40) {
                        counter = 0;
                        point.X = 50;
                        point.Y += 1;
                        move_cursor(point.X, point.Y);
                    }
                    
                    printf("%c", recvbuf[j]);
                    fflush(stdout);
                    usleep_ms(1);
                    counter++;
                }
                printf("\n");
                log_message("Server", temp_recv_log_buf);
            }
            
            point.Y += 1;  
        }
        else if (bytes_received == 0) {
            printf("Connection closed by server.\n");
            break;
        }
        else {
            fprintf(stderr, "recv failed with error: %s\n", strerror(errno));
            break;
        }
    }

    close(sockfd);
    return 0;
}