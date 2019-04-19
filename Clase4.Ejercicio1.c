#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase4.Ejercicio1.dat"

typedef struct registro {
    int cod_chof;
    char nom_chof[30];
    int cant_km;
    float sueldo;
} registro;

void init(FILE * fp) {
    registro reg;
    char * fn = BIN_FILE_NAME;
    fp = fopen(fn,"wb+");
    int i;
    char nom[][30] = {
        "Manuel Flores",
        "Ecumenico Lopez",
        "Francisco Real",
        "Alfinger Maldonado",
        "Elpidio Acosta",
        "Nicanor Paredes"
    };

    for (i = 0; i < 6; i++) {
        strcpy(reg.nom_chof, nom[i]);
        reg.cod_chof = i + 1;
        reg.cant_km = 0;
        reg.sueldo = 0.0;
        fseek(fp, 0, SEEK_END);
        fwrite(&reg, sizeof(reg), 1, fp);
    }

    fclose(fp);
}

void mostrar(FILE * fp) {
	registro reg;
	char * fn = BIN_FILE_NAME;
	fp = fopen(fn, "rb+");
	rewind(fp);

	p("\n \t\t\t Tabla de choferes \n\n");
	p("\n COD. \t    CHOFER  \t\t CANT. KM\t   SUELDO\n\n\n");

	fread(&reg,sizeof(reg),1,fp);
	while(!feof(fp)) {
		p("\n %-10d %-20s %d \t\t %6.2f \n\n",reg.cod_chof,reg.nom_chof,reg.cant_km,reg.sueldo);
		fread(&reg,sizeof(reg),1,fp);
    }

    fclose(fp);
}

void ingresarViaje(FILE * fp) {
    registro reg;
    char * fn = BIN_FILE_NAME;
    fp = fopen(fn, "wb+");

    system("cls");

    p("\nIngrese el codigo del chofer: ");
    s("%d", &reg.cod_chof);
    fflush(stdin);
    p("\nIngrese el nombre del chofer: ");
    s("%[^\n]", reg.nom_chof);
    p("\nIngrese la cantidad de kilometros: ");
    s("%d", &reg.cant_km);
    p("\nIngrese el sueldo del chofer: ");
    s("%f", &reg.sueldo);

    fseek(fp, 0, SEEK_END);
    fwrite(&reg, sizeof(struct registro), 1, fp);
    fclose(fp);
}

int main() {
    FILE * fp;

    init(fp);

    ingresarViaje(fp);

    mostrar(fp);



    getch();
    return 0;
}
