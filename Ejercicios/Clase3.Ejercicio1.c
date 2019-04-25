#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
// #include <conio.h>
#include <string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase3.Ejercicio1.dat"

void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

int main() {
    FILE * fp;
    char * archivo = BIN_FILE_NAME;
    int n, i, pares[20], impares[20];

    fp = fopen(archivo, "wb+");
    srand(time(NULL));

    for (i = 0; i < 20; i++) {
        n = rand() % 881 + 20;
        fwrite(&n, sizeof(int), 1, fp);
    };

    rewind(fp);

    while(fread(&n, sizeof(int), 1, fp)) {
        p("%d\n", n);
    }

    fclose(fp);

    getch();
    return 0;
}
