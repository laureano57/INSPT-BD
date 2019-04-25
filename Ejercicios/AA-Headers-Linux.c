#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
// Reemplazo para conio.h en linux
#include <ncurses.h>
#include <string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "binario.dat"

// Reemplazo para fflush(stdin);
void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

// Reemplazo para system("cls");
system("clear");