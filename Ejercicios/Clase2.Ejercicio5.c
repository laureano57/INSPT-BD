#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define p printf
#define s scanf

int main() {
    FILE * archivo;
    int count, i;
    char ch, cadena[80];
    char * nombre = "Text1.txt";
    archivo = fopen(nombre, "r");

    while (fgets(cadena, 81, archivo)) {
        i = 0;
        count = 0;
        p("%s", cadena);
        while(cadena[i]) {
            while(cadena[i] == ' ' && cadena[i]) i++;
            if (!cadena[i]) break;
            if (cadena[i]>64 && cadena[i]<130) {
                count++;
            }
            while (cadena[i] != ' ' && cadena[i]) i++;
        }
        p("Palabras en este renglon: %d", count);
        p("\n\n");
    }

    fclose(archivo);
    getch();
    return 0;
}


