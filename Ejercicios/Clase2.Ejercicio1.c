#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
// #include<conio.h>
#define p printf
#define s scanf

int main() {
    FILE * archivo;
    char ch, cadena[80];
    char * nombre = "Text1.txt";
    archivo = fopen(nombre, "r");

    p("\nEl contenido del archivo %s caracter a caracter es:\n", nombre);
    while((ch = getc(archivo)) != EOF) {
        p("%c", ch);
    };
    rewind(archivo);

    p("\n\nEl contenido del archivo %s renglon a renglon es:\n", nombre);
    while(fgets(cadena, 81, archivo)) {
        p("%s", cadena);
    }

    fclose(archivo);
    getch();
    return 0;
}
