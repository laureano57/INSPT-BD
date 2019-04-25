#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#include <ncurses.h>
#define p printf
#define s scanf
#define NOMBRE_ARCHIVO "Clase2.Ejercicio2.txt"

char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        return buffer;
    }
    return 0;
}

int main() {
    FILE * archivo;
    char ch, cadena[80];
    char * nombre = NOMBRE_ARCHIVO;
    archivo = fopen(nombre, "w+");

    p("\nEl archivo %s esta abierto para escritura", nombre);
    p("\nPara finalizar el ingreso de datos por renglon, presione enter\n");
    p("Para finalizar el ingreso de datos en el archivo presione Enter y ctrl-z\n");

    while(fgets_wrapper(cadena, 81, stdin) != NULL) {
        fputs(cadena, archivo);
        fputc('\n', archivo);
    }

    rewind(archivo);

    p("\nContenido del archivo %s:\n", nombre);
    while(fgets(cadena, 81, archivo))
        p("%s", cadena);

    fclose(archivo);
    getch();
    return 0;
}
