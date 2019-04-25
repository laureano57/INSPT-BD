#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define p printf
#define s scanf

void copiar(FILE * origen, FILE * destino) {
    char cadena[80];
    int count = 0;
    while(fgets(cadena, 81, origen) != NULL) {
        (count%2 == 0) ? fputs(cadena, destino) : 0;
        count++;
    }
}

void mostrar(FILE * archivo) {
    char cadena[80];

    while(fgets(cadena, 80, archivo)) {
        p("\n%s", cadena);
    }
}

int main() {
    FILE * archivoOrigen;
    FILE * archivoDestino;
    int count = 0;
    char ch, cadena[80];
    char * nombreOrigen = "Text1.txt";
    char * nombreDestino = "TextOutput.txt";
    archivoOrigen = fopen(nombreOrigen, "r");
    archivoDestino = fopen(nombreDestino, "w+");

    //p("\nEl archivo %s esta abierto para lectura", nombreOrigen);
    //p("\nEl archivo %s esta abierto para escritura", nombreDestino);
    //p("\nSe copiaran los renglones pares\n");

    //while(fgets(cadena, 81, archivoOrigen) != NULL) {
    //    (count%2 == 0) ? fputs(cadena, archivoDestino) : 0;
    //    count++;
    //}

    copiar(archivoOrigen, archivoDestino);

    fclose(archivoOrigen);
    fclose(archivoDestino);

    archivoDestino = fopen(nombreDestino, "r");
    p("\nEl archivo resultante:\n");

    //while(fgets(cadena, 81, archivoDestino) != NULL) {
    //    p("%s", cadena);
    //}

    mostrar(archivoDestino);
    fclose(archivoDestino);
    getch();
    return 0;
}

