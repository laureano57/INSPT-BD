#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define p printf
#define s scanf

int main() {
    FILE * archivo;
    int count, i, j;
    char ch, cadena[80];
    char palabra[30];
    char palabraLarga[30];
    char * nombre = "Text1.txt";
    archivo = fopen(nombre, "r");

    while (fgets(cadena, 81, archivo)) {
        i = 0;

        p("%s", cadena);
        while(cadena[i]) {
            while(cadena[i] == ' ' && cadena[i]) i++;
            j = 0;
            i--;
            while (cadena[i] != ' ' && cadena[i]) {
                palabra[j++] = cadena[i++];
            }
            palabra[j] = '\0';
            if (strlen(palabra) > strlen(palabraLarga)) {
                strcpy(palabra, palabraLarga);
            }
            i++;
        }
        p("Palabra mas larga: %s", palabraLarga);
        p("\n\n");
    }

    fclose(archivo);
    getch();
    return 0;
}


