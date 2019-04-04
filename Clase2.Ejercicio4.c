#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define p printf
#define s scanf

int main() {
    FILE * archivo;
    int count = 0, i = 0;
    char ch, cadena[80];
    char * nombre = "Text1.txt";
    archivo = fopen(nombre, "r");

    while (fgets(cadena, 81, archivo)) {
        if (count%2 != 0) {
            i = 0;
            p("%s", cadena);
            while(cadena[i]) {
                ch = cadena[i];
                (ch<97 && ch>64) ? p("%c", ch) : 0;
                i++;
            }
            p("\n\n");
        }
        count++;
    }

    fclose(archivo);
    getch();
    return 0;
}

