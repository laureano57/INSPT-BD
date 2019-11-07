// ####################################################################################################################
// ####                                                  Header                                                    ####
// ####################################################################################################################

// Librerias
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Libs y definiciones especificas de linux
#if defined(__linux__)
  #include "ncurses.h"
  #define CLEAR "clear"
#else
  #define CLEAR "cls"
#endif

// Archivo de logs
#define LOG_FILE "data/logs.txt"
// Archivos binarios
#define USUARIOS_DAT "data/usuarios.dat"
#define MATERIAS_DAT "data/materias.dat"
#define MATERIA_PROFESOR_DAT "data/materia_profesor.dat"
#define MATERIA_ALUMNO_DAT "data/materia_alumno.dat"