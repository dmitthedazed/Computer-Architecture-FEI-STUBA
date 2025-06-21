#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i <= 50; i++) {
        if (i <= 10) {
            SetConsoleTextAttribute(hConsole, 2); // green
        }
        else if (i <= 22) {
            SetConsoleTextAttribute(hConsole, 4); // red
        }
        else if (i <= 35) {
            SetConsoleTextAttribute(hConsole, 1); // blue
        }
        else {
            SetConsoleTextAttribute(hConsole, 7); // gray (default)
        }

        printf("%03d\n", i);
        Sleep(1000);
    }

    SetConsoleTextAttribute(hConsole, 7);
    printf("\nStlac a skoncime . . .");
    getchar();
    getchar(); // Wait for user input

    return 0;
}