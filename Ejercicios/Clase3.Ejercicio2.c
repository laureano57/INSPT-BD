#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
// #include <conio.h>
#include <string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase3.Ejercicio2.dat"

void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

int esPrimo(int num) {
    int k;
    for (k = 2; k < num; k++) {
        if (num%k == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE * fp;
    char * archivo = BIN_FILE_NAME;
    int primosBuscados = 20, esteNum = 1, primosHallados = 0;

    fp = fopen(archivo, "wb+");

    p("Ingrese la cantidad de numeros primos a imprimir: ");
    s("%d", &primosBuscados);

    system("clear");

    do {
        if (esPrimo(esteNum)) {
            fwrite(&esteNum, sizeof(int), 1, fp);
            primosHallados++;
        }
        esteNum++;
    } while (primosHallados < primosBuscados);

    rewind(fp);

    while(fread(&primosBuscados, sizeof(int), 1, fp)) {
        p("%d\n", primosBuscados);
    }

    fclose(fp);

    getch();
    return 0;
}
