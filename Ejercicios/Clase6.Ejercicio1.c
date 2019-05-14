#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
#include<ncurses.h>
#include<string.h>

#define p printf
#define s scanf
#define TXT_ORIG "Clase6.Ejercicio1_Orig.txt"
#define TXT_MOD "Clase6.Ejercicio1_Mod.txt"


int * posicionPalabraMasLarga(char cad[]) {
    int i = 0, count = 0, max = 0;
    int startAux = 0, endAux = 0;
    int posicionRet[2];
    int *ret = posicionRet;

    // Leo hasta el final de la cadena
    while (cad[i]) {

        // Si es un espacio, sigo
        if (cad[i] == ' ') {
            i++;
            continue;

        } else {
            
            // Si no es espacio es una letra, voy contando
            count++;

            // Si la letra anterior es un espacio o es el primer caracter de la 
            // linea, es la primer letra de una palabra, guardo la posicion
            if (cad[i-1] == ' ' || i == 0) {
                startAux = i;

            // Si la proxima letra es un espacio o fin/salto de linea,
            // verifico si es la palabra mas larga encontrada y guardo los indices
            } else if (cad[i+1] == ' ' || cad[i+1] == '\n' || cad[i+1] == '\0') {
                endAux = i;
                if (count > max) {
                    max = count;
                    posicionRet[0] = startAux;
                    posicionRet[1] = endAux;
                }
                count = 0;
            }
        }

        // Proximo caracter de la linea
        i++;
    };

    return ret;
}

void palabraLineaMayuscula(char txtOrig[], char txtMod[], int numLinea, int numPalabra) {
    FILE *fpIn, *fpOut;

    // int lineaActual = 0, i, j, max;
    // int startAux, endAux, startIndex, endIndex;
    int countPalabras = 0, lineaActual = 0, i;

    char linea[100];
    char lineaAux[100];

    // Abro archivo original
    fpIn = fopen(txtOrig, "r");

    // Creo archivo de texto y lo vacio, luego lo abro para agregar
    fpOut = fopen(txtMod, "w"); fclose(fpOut);
    fpOut = fopen(txtMod, "a");

    // Recorre todas las lineas del archivo
    while(fgets(linea, 100, fpIn)) {

        // Arranca en cero, salta a la siguiente linea
        lineaActual++;

        // Si la linea actual no es la ingresada por el usuario,
        // agrega la linea tal cual esta y sigue con la proxima
        if (lineaActual != numLinea) {
            fputs(linea, fpOut);

        // Si es la linea seleccionada, busca la palabra y la pasa
        // a mayuscula
        } else {
            strcpy(lineaAux, linea);
            countPalabras = 0;
            i = 0;
            // Salteo espacios al inicio si los hay
            while(linea[i] == ' ') i++;
            
            // Si llegue ya al final de la linea, devuelve error y sale
            if (linea[i] == '\n' || linea[i] == '\0') {
                p("Error: no se hallaron palabras en la linea %d", numLinea);
                return;
            } else {
                // Encontre una palabra
                countPalabras++;

                // Me muevo hasta el principio de la palabra buscada
                while (countPalabras != numPalabra && (linea[i] != '\n' || linea[i] != '\0')) {
                    // Proximo caracter
                    i++;
                    // Si el caracter anterior es un espacio, cuento otra palabra
                    if (linea[i-1] == ' ') countPalabras++;
                    // Si llego hasta el final y no encontro el numero de palabra buscado,
                    // sale y devuelve error
                    if (linea[i] == '\n' || linea[i] == '\0') {
                        p("Error: la linea %d no tiene %d palabra/s", numLinea, numPalabra);
                        return;
                    }
                }
                // Mientras sea una letra, la capitalizo
                while (linea[i] >= 65 && linea[i] <= 172) {
                    // Solo si la letra es minuscula
                    if (linea[i] >= 97 && linea[i] <= 172){
                        lineaAux[i] = lineaAux[i] - 32;
                    }
                    i++;
                }
            }
            // Agrego la linea modificada
            fputs(lineaAux, fpOut);
        }
    }

    if (numLinea > lineaActual) {
        p("Error: el archivo ingresado tiene %d lineas, no %d", lineaActual, numLinea);
    } else {
        p("Archivo procesado exitosamente");
    }

    fclose(fpIn);
    fclose(fpOut);
}

void palabrasMasLargasMayusculas(char txtOrig[], char txtMod[]) {
    FILE *fpIn, *fpOut;

    int i;
    char linea[100];
    char ret[100];

    // Abro archivo original
    fpIn = fopen(txtOrig, "r");

    // Creo archivo de texto vacio y lo cierro, luego lo abro para agregar
    fpOut = fopen(txtMod, "w"); fclose(fpOut);
    fpOut = fopen(txtMod, "a");

    // Leemos cada linea
    while(fgets(linea, 100, fpIn)) {

        // Obtengo posicion de inicio y fin de la palabra mas larga
        int *posPointer = posicionPalabraMasLarga(linea);
        int posiciones[2] = {posPointer[0], posPointer[1]};

        // Copio toda la linea y convierto la palabra mas larga a mayusculas
        strcpy(ret, linea);
        for (i = posiciones[0]; i <= posiciones[1]; i++) {
            ret[i] = ret[i] - 32;
        }

        p("%s\n", ret);

        // Guardo la palabra en el archivo de salida
        fputs(ret, fpOut);
    }

    fclose(fpIn);
    fclose(fpOut);
}

void capitalizarYContar(char txtOrig[], char txtMod[]) {
    FILE *fpIn, *fpOut;

    int count, i;

    char linea[100];

    // Abro archivo original
    fpIn = fopen(txtOrig, "r");

    // Creo archivo de texto y lo vacio, luego lo abro para agregar
    fpOut = fopen(txtMod, "w"); fclose(fpOut);
    fpOut = fopen(txtMod, "a");

    // Leemos cada linea
    while(fgets(linea, 100, fpIn)) {

        // Inicializamos variables
        count = 0, i = 0;

        // Lee hasta el final de la linea, caracter por caracter
        while (linea[i] != '\0') {

            // Si el caracter corriente es un espacio, lo saltea
            if (linea[i] == ' '){
                fputc(linea[i], fpOut);
                p("%c", linea[i]);

            } else {

                // Si es la primer letra de la oracion o si la letra anterior es
                // un espacio, es la primer letra de una palabra
                if ((i == 0) || (linea[i-1] && linea[i-1] == ' ')) {
                    switch(linea[i]) {
                        // Vocales minusculas
                        case 97:
                        case 101:
                        case 105:
                        case 111:
                        case 117:
                            // Si es vocal minuscula, la capitaliza y cuenta
                            fputc(linea[i]-32, fpOut);
                            p("%c", linea[i]-32);
                            count++;
                            break;
                        // Vocales mayusculas
                        case 65:
                        case 69:
                        case 73:
                        case 79:
                        case 85:
                            // Si es vocal mayuscula, la cuenta
                            fputc(linea[i], fpOut);
                            p("%c", linea[i]);
                            count++;
                            break;
                        
                        default:
                            // Sino copia como esta
                            fputc(linea[i], fpOut);
                            p("%c", linea[i]);
                            break;
                    }

                } else {

                    // Si no es la primera letra de una palabra, copia como esta
                    fputc(linea[i], fpOut);
                    p("%c", linea[i]);
                }
            }
            i++;
        }
        p("Cantidad de vocales en esta linea: %d\n\n", count);
        
    }

    fclose(fpIn);
    fclose(fpOut);
}


int main(){
    // palabrasMasLargasMayusculas(TXT_ORIG, TXT_MOD);
    // capitalizarYContar(TXT_ORIG, TXT_MOD);
    // palabraLineaMayuscula(TXT_ORIG, TXT_MOD, 4, 1);

    char poronga[] = "esto es una poronga";
    char *ptr = poronga;
    char *token;


    while ((token = strtok(ptr, " ")) != NULL) {
        ptr = NULL;
        p("|%s|", token);
    }

    getch();
    return 0;
}
