#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
#include<ncurses.h>
#include<string.h>
#define p printf
#define s scanf
#define TXT_ORIG "Clase6.Ejercicio1_Orig.txt"
#define TXT_MOD "Clase6.Ejercicio1_Mod.txt"

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void leerRenglon(FILE * fp, char renglon[]) {
    char caracter = fgetc(fp);

    while(caracter != '\n') {
        append(renglon, caracter);
        caracter = fgetc(fp);
    }
}

void palabraMasLarga(char cad[]) {
    int count = 0, i = 0, j = 0, max = 0;
    char palabra[30], ret[30];

    while (cad[i] == ' ') i++; // Salteo espacios en blanco al principio

    // Leo hasta el final de la cadena
    while (cad[i]) {
        // Si la letra es un espacio o si la proxima letra es fin de linea,
        // verifico si es la palabra mas larga encontrada y la guardo
        if (cad[i] == ' ' || cad[i+1] == '\0') {
            palabra[j] = '\0';
            if (count > max) {
                strcpy(ret, palabra);
                max = count;
            }
            count = 0;
            j = 0;
        // Si la letra no es un espacio (es un caracter), almaceno la letra y voy contando
        } else if(cad[i] != ' ') {
            palabra[j] = cad[i];
            j++;
            count++;
        };
        i++;
    };

    p("Palabra mas larga: %s\n", ret);
}

// void capitalizarPalabrasMasLargas(char cad[], char txtMod[]) {
void capitalizarPalabrasMasLargas(char txtOrig[], char txtMod[]) {
    FILE *fpIn, *fpOut;

    int count, i, j, max;
    int startAux, endAux, startIndex, endIndex;

    char linea[100];
    char ret[100];

    // Abro archivo original
    fpIn = fopen(txtOrig, "r");

    // Creo archivo de texto y lo vacio, luego lo abro para agregar
    fpOut = fopen(txtMod, "w"); fclose(fpOut);
    fpOut = fopen(txtMod, "a");

    // Leemos cada linea
    while(fgets(linea, 100, fpIn)) {
        // Inicializo contadores
        i = j = count = max = startAux = endAux = startIndex = endIndex = 0;

        while (linea[i] == ' ') i++; // Salteo espacios en blanco al principio

        // Leo hasta el final de la linea
        while (linea[i]) {
            // Si es la primer letra de una palabra, capturo el indice
            if (i == 0 || linea[i-1] == ' ') {
                startAux = i;
            // Si la letra es un espacio o si la proxima letra es fin de linea,
            // llegue al final de una palabra, verifico si es la palabra mas larga encontrada
            } else if (linea[i] == ' ' || linea[i+1] == '\0') {
                // El fin de la palabra es el caracter anterior
                endAux = i - 1;
                if (count > max) {
                    // strcpy(ret, palabra);
                    max = count;
                    startIndex = startAux;
                    endIndex = endAux;
                }

                count = 0;
            // Si la letra no es un espacio (es un caracter), almaceno la letra y voy contando
            } else if(linea[i] != ' ') {
                count++;
            };
            i++;
        };

        // Copio toda la palabra y convierto la palabra mas larga a mayusculas
        strcpy(ret, linea);
        for (j = startIndex; j <= endIndex; j++) {
            ret[j] = ret[j] - 32;
        }

        // Guardo la palabra en el archivo de salida
        fputs(ret, fpOut);
    }

    fclose(fpIn);
    fclose(fpOut);
}

void capitalizarYContar(char linea[]) {
    FILE * fpOut;
    int count = 0, i = 0;
    char lineaCap[100] = "";

    // Lee hasta el final de la linea, caracter por caracter
    while (linea[i] != '\0') {
        // Si el caracter corriente es un espacio, lo saltea
        if (linea[i] == ' '){
            lineaCap[i] = linea[i];
            i++;
        } else {
            // Si es la primer letra de la oracion o si la letra anterior es
            // un espacio, es la primer letra de una palabra
            if ((i == 0) || (linea[i-1] && linea[i-1] == ' ')) {
                switch(linea[i]) {
                    // Vocales
                    case 97:
                    case 101:
                    case 105:
                    case 111:
                    case 117:
                        // Si es vocal minuscula, la capitaliza y cuenta
                        lineaCap[i] = linea[i] - 32;
                        count++; i++;
                        break;
                    default:
                        // Sino copia como esta
                        lineaCap[i] = linea[i];
                        i++;
                        break;
                }
            } else {
                // Si no es la primera letra de una palabra, copia como esta
                lineaCap[i] = linea[i];
                i++;
            }
        }
    }
    
    // Imprimo resultado
    p("%s\n", lineaCap);
    p("Cantidad de vocales en esta linea: %d\n\n", count);
    
    // Guardo
    fpOut = fopen(TXT_MOD, "a+");
    fputs(lineaCap, fpOut);
    fclose(fpOut);
}


int main(){
    capitalizarPalabrasMasLargas(TXT_ORIG, TXT_MOD);
    

    getch();
    return 0;
}
