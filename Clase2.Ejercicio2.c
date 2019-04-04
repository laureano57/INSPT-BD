#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define p printf
#define s scanf

int main() {
    FILE * archivo;
    char ch, cadena[80];
    char * nombre = "Text2.txt";
    archivo = fopen(nombre, "w+");

    p("\nEl archivo %s esta abierto para escritura", nombre);
    p("\nPara finalizar el ingreso de datos por renglon, presione enter\n");
    p("\nPara finalizar el ingreso de datos en el archivo presione Enter y ctrl-z\n");

    while(gets(cadena) != NULL) {
        fputs(cadena, archivo);
        fputc('\n', archivo);
        fputs
    }

    rewind(archivo);

    p("\nContenido del archivo %s:\n", nombre);
    while(fgets(cadena, 81, archivo))
        p("%s", cadena);

    fclose(archivo);
    getch();
    return 0;
}
