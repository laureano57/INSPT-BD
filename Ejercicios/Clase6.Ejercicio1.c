#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define p printf
#define s scanf
#define TXT_FILE_NAME "Clase6.Ejercicio1.txt"

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void leerRenglon(FILE * fp, char nombre[], char renglon[]) {
    char caracter;

    fp = fopen(nombre, "r");
    caracter = fgetc(fp);

    while(caracter != '\n') {
        append(renglon, caracter);
        caracter = fgetc(fp);
    }

    fclose(fp);
}

void palabraMasLarga(char cad[]) {
    int count = 0, i = 0, j = 0, max = 0;
    char palabra[30], ret[30];

    while(cad[i]) {
        if(cad[i] != ' ' && cad[i]) {
            palabra[j] = cad[i];
            j++;
            i++;
            count++;
        } else if (cad[i] == ' ') {
            palabra[j] = '\0';
            if (count > max) {
                strcpy(ret, palabra);
                max = count;
            }
            count = 0;
            j = 0;
            i++;
        };
    }

    p("\nPalabra mas larga: %s\n", ret);
}

char* capitalizarVocales(char linea[], char lineaCap[]) {
    int count = 0, i = 0, j = 0;

    while (linea[i]) {
        // Si hay espacios al principio los saltea
        if (linea[i] == ' '){
            lineaCap[i] = linea[i];
            i++;
        } else {
            // Si no es la primera letra de la oracion y la letra anterior es un espacio,
            // o si es la primera letra de la oracion (y no es un espacio), es la primer letra de una palabra
            if ((i == 0) || (linea[i-1] && linea[i-1] == ' ')) {
                switch(linea[i]) {
                    case 97:
                    case 101:
                    case 105:
                    case 111:
                    case 117:
                        // Si es vocal minuscula, la capitaliza
                        lineaCap[i] = linea[i] - 32;
                        i++;
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
}

int main(){
    FILE * fp;
    char linea[100] = "";
    char lineaCap[100] = "";

    leerRenglon(fp, TXT_FILE_NAME, linea);
    capitalizarVocales(linea, lineaCap);
    p("%s", lineaCap);

    getch();
    return 0;
}
