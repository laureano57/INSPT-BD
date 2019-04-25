#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
// #include <conio.h>
#include <string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase3.Ejercicio4.dat"

void clearStdin() {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

typedef struct registro {
    int cod_chof;
    char nom_chof[30];
    int kms;
    int rec; //red = kmsx10
} registro;

void cargarFilas(char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "wb+");
    registro reg;
    int seguir;
    
    fseek(fp, 0, SEEK_END);
    
    system("clear");
    
    p("##### Cargar registros #####");
    clearStdin();
    getch();

    do {
        system("clear");

        p("Ingrese el codigo del chofer: ");
        s("%d", &reg.cod_chof);
        
        clearStdin();
        p("\nIngrese el nombre del chofer: ");
        s("%[^\n]", reg.nom_chof);
        
        clearStdin();
        p("\nIngrese los kilometros recorridos por el chofer: ");
        s("%d", &reg.kms);
        
        reg.rec = reg.kms * 10;

        fwrite(&reg, sizeof(reg), 1, fp);

        clearStdin();
        system("clear");
        p("Para terminar ingrese 0, para continuar ingrese 1\n");
        s("%d", &seguir);
    } while (seguir != 0);

    fclose(fp);

    system("clear");
}

void importarLegajos(char fileName[], char legajosCsv[]) {
    FILE *fp, *csv;
    registro reg;
    char linea[80];
    char *campo;

    fp = fopen(fileName, "wb+");
    csv = fopen(legajosCsv, "r");

    while (fgets(linea, 80, csv) != NULL) {
        campo = strtok(linea, ",");
        reg.cod_chof = atoi(campo);

        campo = strtok(NULL, ",");
        strcpy(reg.nom_chof, campo);

        campo = strtok(NULL, ",");
        reg.kms = atoi(campo);

        reg.rec = reg.kms * 10;

        fwrite(&reg, sizeof(reg), 1, fp);
    }
        
    fclose(fp);
    fclose(csv);
}



void mostrarLegajos(char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "rb+");
    registro reg;
    
    // fseek(fp, 0, SEEK_SET);
    
    system("clear");
    p("#################### Legajos cargados ####################\n\n");
    p("%-4s %-24s %-8s %-8s\n", "Cod.", "Nombre", "Kms.", "Recomp.");

    while (fread(&reg, sizeof(reg), 1, fp)) {
        p("%-4d %-24s %-8d %-8d\n", reg.cod_chof, reg.nom_chof, reg.kms, reg.rec);
    }

    fclose(fp);
}

int main() {
    FILE * fp;

    // cargarFilas(BIN_FILE_NAME);
    importarLegajos(BIN_FILE_NAME, "Clase3.Ejercicio4.csv");
    mostrarLegajos(BIN_FILE_NAME);

    getch();
    return 0;
}
