#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h> 
#include <stdlib.h> 

#pragma comment(lib, "Ws2_32.lib")

// Function to set console output to UTF-8
void utf8_console() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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
    FILE *logFile = NULL;
    errno_t err;

    err = fopen_s(&logFile, "chat_log.txt", "a"); 
    if (err != 0 || logFile == NULL) { 
        char errmsg[256];
        strerror_s(errmsg, sizeof(errmsg), err); 
        fprintf(stderr, "Error opening log file: %s (code: %d)\n", errmsg, err);
        if (logFile == NULL && err == 0) { 
             perror("Error opening log file (perror)");
        }
        return;
    }
    fprintf(logFile, "%s: %s\n", source, message);
    fclose(logFile);
}

void print_with_position(HANDLE console, const char* text, COORD* point_ptr, WORD color) {
    SetConsoleCursorPosition(console, *point_ptr);
    SetConsoleTextAttribute(console, color);
    
    printf("%s", text);
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        *point_ptr = csbi.dwCursorPosition;
    }
}

void print_newline(HANDLE console, COORD* point_ptr) {
    printf("\n");
    point_ptr->X = 0;
    point_ptr->Y += 1;
    SetConsoleCursorPosition(console, *point_ptr);
}

void sync_cursor_position(HANDLE console, COORD* point_ptr) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(console, &csbi)) {
        *point_ptr = csbi.dwCursorPosition;
    }
}

int main(void) 
{
    utf8_console(); 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Add cursor positioning for two-sided chat display
    COORD point;
    point.X = 0;
    point.Y = 0;
    
    // Clear screen at start for clean display
    system("cls");

    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0)
    {
        WSACleanup();
        return 1;
    }
    else
        printf("getaddrinfo didn't fail...\n");

    SOCKET ConnectSocket = INVALID_SOCKET;

    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
        printf("Error at socket DIDN'T occur...\n");

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("Not connected to server...\n");
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Connected to server!\n");
    }
    
    Sleep(250);

    #define DEFAULT_BUFLEN 4096
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    while (1) {
        // User message left side
        point.X = 0;
        point.Y += 2;
        SetConsoleCursorPosition(hConsole, point);
        
        SetConsoleTextAttribute(hConsole, 9); 
        printf("Enter message: ");
        SetConsoleTextAttribute(hConsole, 15); 
        if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL) {
            printf("Error reading input.\n");
            break; 
        }

        sendbuf[strcspn(sendbuf, "\n")] = 0;

        if (strcmp(sendbuf, "quit") == 0) {
            SetConsoleTextAttribute(hConsole, 9); 
            printf("Exiting chat.\n");
            SetConsoleTextAttribute(hConsole, 15); 
            log_message("User", "quit"); 
            break;
        }
        point.Y += 1;
        SetConsoleCursorPosition(hConsole, point);
        SetConsoleTextAttribute(hConsole, 9);
        printf("You: ");
        
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
                    SetConsoleCursorPosition(hConsole, point);
                }
            }
            
            if (counter == 40) {
                counter = 0;
                point.X = 0;
                point.Y += 1;
                SetConsoleCursorPosition(hConsole, point);
            }
            
            printf("%c", sendbuf[i]);
            Sleep(1);
            counter++;
        }
        printf("\n");
        SetConsoleTextAttribute(hConsole, 15); 
        
        log_message("User", sendbuf); 

        iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        if (strcmp(sendbuf, "753332") == 0) {
            point.X = 0;
            point.Y += 1;
            SetConsoleCursorPosition(hConsole, point);
            
            int remainder_result = aisid_remainder(135532);
        
            if (remainder_result != -1) {
                printf("Computed remainder for 135532: %d\n", remainder_result);
                point.Y += 1; 
            }
        }

        ZeroMemory(recvbuf, DEFAULT_BUFLEN);

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0)
        {
            point.X = 0;
            point.Y += 1;
            SetConsoleCursorPosition(hConsole, point);
            
            printf("Bytes received: %d\n", iResult);
            point.Y += 1; 

            if (iResult == 131) {
                printf("Decrypting 131 byte message...\n");
                point.Y += 1; // Update Y position
                for (int k = 0; k < iResult; k++) {
                    recvbuf[k] = recvbuf[k] ^ 55;
                }
            }
            
            char temp_recv_log_buf[DEFAULT_BUFLEN + 1];
            memcpy(temp_recv_log_buf, recvbuf, iResult);
            temp_recv_log_buf[iResult] = '\0';
            
            point.X = 50;
            SetConsoleCursorPosition(hConsole, point);
            
            if (strcmp(sendbuf, "PRIMENUMBER") == 0) {
                char* prime_extracted_message = (char*)malloc(iResult + 1);
                if (prime_extracted_message == NULL) {
                    SetConsoleTextAttribute(hConsole, 12); // Bright Red for error
                    printf("Error: Memory allocation failed.\n");
                    SetConsoleTextAttribute(hConsole, 15); // Reset to White
                } else {
                    int n = 0;
                    for (int idx_to_check = 2; idx_to_check <= iResult; idx_to_check++) {
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

                    SetConsoleTextAttribute(hConsole, 10);
                    printf("Server (PRIME): ");
                    
                    int counter = 0;
                    for (int j = 0; j < n; j++) {
                        if (counter == 40) {
                            counter = 0;
                            point.X = 50;
                            point.Y += 1;
                            SetConsoleCursorPosition(hConsole, point);
                        }
                        
                        printf("%c", prime_extracted_message[j]);
                        Sleep(1);
                        counter++;
                    }
                    printf("\n");
                    SetConsoleTextAttribute(hConsole, 15); // Reset to White
                    log_message("Server (PRIMENUMBER)", prime_extracted_message);
                    free(prime_extracted_message);
                }
            } else {
                SetConsoleTextAttribute(hConsole, 10); // Green for server
                printf("Server: ");
                
                int counter = 0;
                for (int j = 0; j < iResult; j++) {
                    if (recvbuf[j] == ' ') {
                        int wordLen = 0;
                        int k = j + 1;
                        while (k < iResult && recvbuf[k] != ' ' && recvbuf[k] != '\0') {
                            wordLen++;
                            k++;
                        }
                        if ((wordLen + counter) >= 40) {
                            counter = 0;
                            point.X = 50;
                            point.Y += 1;
                            SetConsoleCursorPosition(hConsole, point);
                        }
                    }
                    
                    if (counter == 40) {
                        counter = 0;
                        point.X = 50;
                        point.Y += 1;
                        SetConsoleCursorPosition(hConsole, point);
                    }
                    
                    printf("%c", recvbuf[j]);
                    Sleep(1);
                    counter++;
                }
                printf("\n");
                SetConsoleTextAttribute(hConsole, 15); // Reset to White
                log_message("Server", temp_recv_log_buf);
            }
            
            point.Y += 1;  
        }
        else if (iResult == 0)
        {
            printf("Connection closed by server.\n");
            break;
        }
        else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            break;
        }
    }

    freeaddrinfo(result);
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}