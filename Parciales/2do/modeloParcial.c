// Un estudio de arquitectura ingresa datos de inspecciones de obra de
// profesionales de proyectos

// Datos de ingreso:
// Numero de inspeccion
// Numero de profesional
// Cantidad de horas
// Nombre del profesional

// En caso de existir el profesional debera omitir el ingreso de datos el nombre
// del mismo

// Se pide:
// Las inspecciones se cargan de a una por vez, pudiendo un mismo profesional
// realizar varias inspecciones
// El honorario (sueldo) de cada profesional se calcula con el valor de hora de
// $250

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
#define BIN_FILE_NAME "modeloParcial.dat"
#define TXT_FILE_NAME "modeloParcial.txt"

typedef struct {
  int cod_prof;
  char nom_prof[30];
  int cant_insp;
  int horas;
  int sueldo;
} registro;

void clearStdin() {
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF && c != '\0');
}

registro buscarProfesional(int codProf, FILE **fp) {
  registro auxReg;
  fseek(*fp, 0, SEEK_SET);
  while (fread(&auxReg, sizeof(registro), 1, *fp)) {
    if (auxReg.cod_prof == codProf) {
      fseek(*fp, -sizeof(registro), SEEK_CUR);
      return auxReg;
    }
  }
  fseek(*fp, 0, SEEK_END);
  return;
}

void cargarInspecciones(char fileName[]) {
  registro newReg;
  int numInspeccion, codProf, auxHoras;
  char nombreAux[30];
  FILE *fp;
  fp = fopen(fileName, "rb+");
  if (fp == NULL) {
    fp = fopen(fileName, "wb");
  }

  p("##### Nueva inspeccion #####\n");
  p("### Para salir ingrese 0 ###\n");
  p("- Numero de inspeccion: ");
  s("%d", &numInspeccion);
  clearStdin();
  while (numInspeccion != 0) {
    p("\n- Codigo de profesional: ");
    s("%d", &codProf);
    clearStdin();
    // Primero busco el profesional, si existe tomo los datos y quedo parado en
    // el la posicion de memoria donde
    // empieza el struct del profesional buscado y devuelvo el struct de dicho
    // prof.
    newReg = buscarProfesional(codProf, &fp);
    // Si no existe, lo carga de cero
    // if (newReg.cod_prof != codProf) {
    if (newReg.cod_prof != codProf) {
      newReg.cod_prof = codProf;
      p("\n- Nombre del profesional: ");
      s("%[^\n]", nombreAux);
      clearStdin();
      strcpy(newReg.nom_prof, nombreAux);
      p("\n- Cantidad de horas: ");
      s("%d", &newReg.horas);
      clearStdin();
      newReg.cant_insp = 1;
      newReg.sueldo = newReg.horas * 250;
      // Si existe, sumo horas, sumo cantidad de inspecciones, recalculo sueldo
    } else {
      p("\n- Cantidad de horas: ");
      s("%d", &auxHoras);
      clearStdin();
      newReg.horas += auxHoras;
      newReg.cant_insp += 1;
      newReg.sueldo = newReg.horas * 250;
    }

    fwrite(&newReg, sizeof(registro), 1, fp);
    system(CLEAR);
    p("##### Nueva inspeccion #####\n");
    p("### Para salir ingrese 0 ###\n");
    p("- Numero de inspeccion: ");
    s("%d", &numInspeccion);
    clearStdin();
  };

  fclose(fp);
}

void mostrarRegistros(char fileName[]) {
  registro auxReg;
  FILE *fp;
  fp = fopen(fileName, "rb");
  if (fp == NULL) {
    p("Archivo vacio!\n");
    getchar();
    return;
  }
  system(CLEAR);
  p("######################### LISTADO DE PROFESIONALES "
    "#########################\n\n");
  p("%-10s %-30s %-15s %-10s %-10s\n", "Cod.", "Nombre", "Inspecciones",
    "Horas", "Sueldo");
  while (fread(&auxReg, sizeof(registro), 1, fp)) {
    p("%-10d %-30s %-15d %-10d %-10d\n", auxReg.cod_prof, auxReg.nom_prof,
      auxReg.cant_insp, auxReg.horas, auxReg.sueldo);
  }

  fclose(fp);
  clearStdin();
  getchar();
}

void menu() {
  int opt;

  while (opt != 3) {
    system(CLEAR);

    p("##### MENU PRINCIPAL #####\n");
    p("1- Cargar inspecciones\n");
    p("2- Mostrar profesionales\n");
    p("3- Salir\n");
    p("Opcion: ");
    s("%d", &opt);
    clearStdin();

    switch (opt) {
    case 1:
      system(CLEAR);
      cargarInspecciones(BIN_FILE_NAME);
      break;
    case 2:
      system(CLEAR);
      mostrarRegistros(BIN_FILE_NAME);
      break;
    }
  }
}

int main() {
  menu();
  return 0;
}
