#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linux o windows
#include <ncurses.h>
// #include<conio.h>

// Linux o windows
#define CLEAR "clear"
// #define CLEAR "cls"

#define p printf
#define s scanf
#define BIN_FILE_NAME "Clase5.Ejercicio1.Choferes.dat"
#define TXT_FILE_NAME "Clase5.Ejercicio1.txt"

typedef struct chofer {
  int codigo;
  char nombre[30];
  int kilometros;
  int activo;
} chofer;

void clearStdin(void) {
  int c;
  do
    c = getchar();
  while (c != '\n' && c != EOF);
}

// Headers
void cargarArchivo(char archivoTexto[], char archivoDb[]);
void mostrar(char filename[]);
void bajarLegajo(int legajo, char fileName[]);
void activarLegajo(int legajo, char fileName[]);
void renombrarLegajo(int legajo, char fileName[]);
void editarLegajos(char fileName[]);
void menuPrincipal();

void cargarArchivo(char archivoTexto[], char archivoDb[]) {
  FILE *textoFp;
  FILE *dbFp;
  struct chofer chofReg;

  char line[80];
  char *token;
  char nombre[30];
  int codigo, kilometros, activo, existe;

  textoFp = fopen(TXT_FILE_NAME, "r");
  dbFp = fopen(BIN_FILE_NAME, "wb+");

  // Por cada linea
  while (fgets(line, 80, textoFp)) {
    // Parseo la linea
    token = strtok(line, ",");
    codigo = atoi(token);

    token = strtok(NULL, ",");
    strcpy(nombre, token);

    token = strtok(NULL, ",");
    kilometros = atoi(token);

    // Busco el registro en el archivo, si existe le agrego los kilometros
    fseek(dbFp, 0, SEEK_SET);
    existe = 0;
    while (fread(&chofReg, sizeof(chofReg), 1, dbFp)) {
      if (chofReg.codigo == codigo && chofReg.activo) {
        existe = 1;
        chofReg.kilometros += kilometros;
        fseek(dbFp, -sizeof(chofReg), SEEK_CUR);
        fwrite(&chofReg, sizeof(chofReg), 1, dbFp);
        break;
      };
    }

    if (!existe) {
      fseek(dbFp, 0, SEEK_END);

      chofReg.codigo = codigo;
      strcpy(chofReg.nombre, nombre);
      chofReg.kilometros = kilometros;
      chofReg.activo = 1;

      fwrite(&chofReg, sizeof(chofReg), 1, dbFp);
    }
  };

  fclose(dbFp);
  fclose(textoFp);

  system(CLEAR);
  p("Archivo cargado exitosamente");
  clearStdin();
  clearStdin();
  getchar();
  getchar();
}

void mostrar(char filename[]) {
  chofer chofReg;
  FILE *fp;
  fp = fopen(filename, "rb");
  rewind(fp);
  system(CLEAR);
  clearStdin();

  p("######################## Tabla de choferes ########################");
  p("\n\n%-10s%-30s%-20s%-10s\n", "Codigo", "Chofer", "Kilometros", "Activo");

  fread(&chofReg, sizeof(chofReg), 1, fp);
  while (!feof(fp)) {
    if (chofReg.activo) {
      p("\n%-10d%-30s%-20d%-10d", chofReg.codigo, chofReg.nombre,
        chofReg.kilometros, chofReg.activo);
    }
    fread(&chofReg, sizeof(chofReg), 1, fp);
  }

  fclose(fp);
  getchar();
}

void bajarLegajo(int legajo, char fileName[]) {
  FILE *dbFp;
  dbFp = fopen(fileName, "rb+");
  chofer chofReg;
  int existe = 0;

  while (fread(&chofReg, sizeof(chofReg), 1, dbFp)) {
    if (chofReg.codigo == legajo) {
      chofReg.activo = 0;
      existe = 1;
      fseek(dbFp, -sizeof(chofReg), SEEK_CUR);
      fwrite(&chofReg, sizeof(chofReg), 1, dbFp);
      break;
    }
  }

  if (!existe) {
    p("\nEl legajo ingresado no existe");
  } else {
    system(CLEAR);
    p("######################## Chofer eliminado ########################");
    p("\n\n%-10s%-30s%-20s\n", "Codigo", "Chofer", "Kilometros");
    p("\n%-10d%-30s%-20d", chofReg.codigo, chofReg.nombre, chofReg.kilometros);
  };
  getchar();
  fclose(dbFp);
}

void activarLegajo(int legajo, char fileName[]) {
  FILE *dbFp;
  dbFp = fopen(fileName, "rb+");
  chofer chofReg;
  int existe = 0;

  while (fread(&chofReg, sizeof(chofReg), 1, dbFp)) {
    if (chofReg.codigo == legajo) {
      chofReg.activo = 1;
      existe = 1;
      fseek(dbFp, -sizeof(chofReg), SEEK_CUR);
      fwrite(&chofReg, sizeof(chofReg), 1, dbFp);
      break;
    }
  }

  if (!existe)
    p("\nEl legajo ingresado no existe");

  fclose(dbFp);
}

void renombrarLegajo(int legajo, char fileName[]) {
  FILE *dbFp;
  dbFp = fopen(fileName, "rb+");
  chofer chofReg;
  int existe = 0;
  char nombre[30];

  system(CLEAR);
  clearStdin();
  p("Ingrese un nuevo nombre para el legajo: ");
  s("%[^\n]", nombre);

  while (fread(&chofReg, sizeof(chofReg), 1, dbFp)) {
    if (chofReg.codigo == legajo) {
      strcpy(chofReg.nombre, nombre);
      existe = 1;
      fseek(dbFp, -sizeof(chofReg), SEEK_CUR);
      fwrite(&chofReg, sizeof(chofReg), 1, dbFp);
      break;
    }
  }

  if (!existe)
    p("\nEl legajo ingresado no existe");

  fclose(dbFp);
}

void editarLegajos(char fileName[]) {
  FILE *dbFp;
  dbFp = fopen(fileName, "rb+");
  chofer chofReg;
  int existe = 0, legajo;
  int opt;

  system(CLEAR);
  p("################### Modificar Legajo ###################\n");
  p("\nIngrese un numero de legajo: ");
  s("%d", &legajo);
  system(CLEAR);

  p("################### Modificar Legajo ###################\n");
  p("\n1 - Desactivar legajo");
  p("\n2 - Reactivar legajo");
  p("\n3 - Renombrar legajo");
  p("\n4 - Volver");
  p("\nSeleccione una opcion: ");
  s("%d", &opt);

  switch (opt) {
  case 1:
    bajarLegajo(legajo, fileName);
    break;
  case 2:
    activarLegajo(legajo, fileName);
    break;
  case 3:
    renombrarLegajo(legajo, fileName);
    break;
  case 4:
    break;
  default:
    break;
  }

  menuPrincipal();
}

void menuPrincipal() {
  int opt = 1;

  while (opt != 0) {
    system(CLEAR);
    p("####################### CHOFERES #######################\n");
    p("\nMenu principal");
    p("\n1 - Cargar choferes desde archivo");
    p("\n2 - Mostrar legajos");
    p("\n3 - Editar legajos");
    p("\n4 - Salir");
    p("\nSeleccione una opcion: ");
    s("%d", &opt);

    switch (opt) {
    case 1:
      cargarArchivo(TXT_FILE_NAME, BIN_FILE_NAME);
      break;
    case 2:
      mostrar(BIN_FILE_NAME);
      break;
    case 3:
      editarLegajos(BIN_FILE_NAME);
      break;
    case 4:
      return;
      break;
    default:
      return;
    }
  }
}

int main() {
  menuPrincipal();

  getchar();
  return 0;
}
