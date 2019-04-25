#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
// #include <conio.h>
#include <string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase3.Ejercicio3.dat"

void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

int main() {
    FILE * fp;
    char * archivo = BIN_FILE_NAME;
    int n, i, pares[20], impares[20], paresIndex = 0, imparesIndex = 0;

    fp = fopen(archivo, "wb+");
    srand(time(NULL));

    for (i = 0; i < 20; i++) {
        n = rand() % 881 + 20;
        fwrite(&n, sizeof(int), 1, fp);
    };

    rewind(fp);

    while(fread(&n, sizeof(int), 1, fp)) {
        if (n%2 == 0) {
            pares[paresIndex] = n;
            paresIndex++;
        } else {
            impares[imparesIndex] = n;
            imparesIndex++;
        }
    }

    fclose(fp);

    p("Numeros pares: %d\n\n", paresIndex);
    for (i = 0; i < paresIndex; i++) {
        p("%d\t", pares[i]);
    }

    p("\n\n");

    p("\n\nNumeros impares: %d\n\n", imparesIndex);
    for (i = 0; i < imparesIndex; i++) {
        p("%d\t", impares[i]);
    }

    getch();
    return 0;
}
