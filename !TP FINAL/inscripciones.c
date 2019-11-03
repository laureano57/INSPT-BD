// Librerias
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Libs y definiciones especificas de linux
#if defined(__linux__)
  #include "ncurses.h"
  #define CLEAR "clear"
#else
  #define CLEAR "cls"
#endif

// Archivos binarios
#define USUARIOS_DAT "usuarios.dat"
#define MATERIAS_DAT "materias.dat"
#define MATERIA_PROFESOR_DAT "materia_profesor.dat"
#define MATERIA_ESTUDIANTE_DAT "materia_estudiante.dat"

// ####################################################################################################################
// ####                                              Modelo de datos                                               ####
// ####################################################################################################################


// Tipos de usuario y entidad
typedef enum {
  ADMIN,
  PROFESOR,
  ALUMNO
} tipoUsuario;

typedef enum {
  MATERIA,
  USUARIO,
  MATERIA_PROFESOR,
  MATERIA_ESTUDIANTE
} tipoEntidad;

// Registros
typedef struct usuario {
  int id;
  char nombreCompleto[30];
  char username[30];
  char password[30];
  tipoUsuario tipo;
  int estado;
} usuario;

typedef struct materia {
  int id;
  char nombre[30];
  int estado;
} materia;

typedef struct materiaProfesor {
  int id;
  int idMateria;
  int idProfesor;
} materiaProfesor;

typedef struct materiaEstudiante {
  int id;
  int idMateria;
  int idEstudiante;
} materiaEstudiante;

// ####################################################################################################################
// ####                                               Declaraciones                                                ####
// ####################################################################################################################

void menuAdmMaterias();
void menuAdmProfesores();
void menuAdmAlumnos();
void menuAdmin();
void menuAlumno();
void menuProfesor();

// void materiasCargarDesdeArchivo();
// void materiaAlta();
// void materiaBaja(int idMateria);
// void materiaModificar(int idMateria);
void materiasListar();
// void materiaConsultarProfesor(int idMateria);
// void materiaConsultarAlumnos(int idMateria);

// void usuariosCargarDesdeArchivo(tipoUsuario tipo);
// void usuarioAlta();
// void usuarioBaja(int idUsuario);
// void usuarioModificar(int idUsuario);
void usuariosListar(tipoUsuario tipo);
// void usuarioConsultarMaterias(int idUsuario);
// void usuarioAsignarMateria(int idUsuario, int idMateria);
// void usuarioDesasignarMateria(int idUsuario, int idMateria);

// Listan las entidades y devuelven el ID de una de ellas
// int seleccionarMateria();
// int seleccionarUsuario(tipoUsuario tipo);


void cargarDesdeArchivo(char *archivoTexto, tipoEntidad tEntidad);

// ####################################################################################################################
// ####                                                  Helpers                                                   ####
// ####################################################################################################################

char *getstring(char *buf, size_t size) {
  if (buf != NULL && size > 0) {
    if (fgets(buf, size, stdin)) {
      buf[strcspn(buf, "\n")] = '\0';
      return buf;
    }
    *buf = '\0';  /* clear buffer at end of file */
  }
  return NULL;
}

void clearStdin(void) {
  int c;
  do
  c = getc(stdin);
  while (c != '\n' && c != EOF);
}

void cargarDesdeArchivo(char *archivoTexto, tipoEntidad tEntidad) {
  FILE *textoFp;
  FILE *dbFp;

  struct materia materiaReg;
  struct usuario usuarioReg;
  struct materiaProfesor materiaProfesorReg;
  struct materiaEstudiante materiaEstudianteReg;

  char *token;
  char line[80];
  char archivoDb[30];

  if (tEntidad == USUARIO) strcpy(archivoDb, USUARIOS_DAT);
  if (tEntidad == MATERIA) strcpy(archivoDb, MATERIAS_DAT);
  if (tEntidad == MATERIA_PROFESOR) strcpy(archivoDb, MATERIA_PROFESOR_DAT);
  if (tEntidad == MATERIA_ESTUDIANTE) strcpy(archivoDb, MATERIA_ESTUDIANTE_DAT);

  // Campos de los registros
  int id, idMateria, idProfesor, idEstudiante;
  int tipo, estado;
  char nombre[30];

  textoFp = fopen(archivoTexto, "r");
  dbFp = fopen(archivoDb, "wb+");

  if (textoFp == NULL) {
    printf("\nArchivo no encontrado!\n");
    getchar();
    return;
  }
  // Por cada linea
  while (fgets(line, 80, textoFp)) {
    // Parseo ID (comun a todas las entidades)
    token = strtok(line, ",");
    id = atoi(token);

    // Parseo la linea segun tipo de entidad
    if (tEntidad == USUARIO) {
        usuarioReg.id = id;

        token = strtok(NULL, ",");
        strcpy(usuarioReg.nombreCompleto, token);

        token = strtok(NULL, ",");
        strcpy(usuarioReg.username, token);

        token = strtok(NULL, ",");
        strcpy(usuarioReg.password, token);

        token = strtok(NULL, ",");
        tipo = atoi(token);
        if (tipo == 0) usuarioReg.tipo = ADMIN;
        if (tipo == 1) usuarioReg.tipo = PROFESOR;
        if (tipo == 2) usuarioReg.tipo = ALUMNO;

        token = strtok(NULL, ",");
        usuarioReg.estado = atoi(token);

        fwrite(&usuarioReg, sizeof(usuarioReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA) {
        materiaReg.id = id;

        token = strtok(NULL, ",");
        strcpy(materiaReg.nombre, token);

        token = strtok(NULL, ",");
        materiaReg.estado = atoi(token);

        fwrite(&materiaReg, sizeof(materiaReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA_PROFESOR) {
      materiaProfesorReg.id = id;

      token = strtok(NULL, ",");
      materiaProfesorReg.idMateria = atoi(token);

      token = strtok(NULL, ",");
      materiaProfesorReg.idProfesor = atoi(token);

      fwrite(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA_ESTUDIANTE) {
      materiaEstudianteReg.id = id;

      token = strtok(NULL, ",");
      materiaEstudianteReg.idMateria = atoi(token);

      token = strtok(NULL, ",");
      materiaEstudianteReg.idEstudiante = atoi(token);

      fwrite(&materiaEstudianteReg, sizeof(materiaEstudianteReg), 1, dbFp);
    }
  };

  fclose(dbFp);
  fclose(textoFp);

  system(CLEAR);
  printf("Archivo cargado exitosamente");
  clearStdin();
}

// ####################################################################################################################
// ####                                                 Listados                                                   ####
// ####################################################################################################################

void materiasListar() {
  materia materiaReg;
  FILE *fp;
  fp = fopen(MATERIAS_DAT, "rb");
  rewind(fp);
  system(CLEAR);

  printf("#############################################################################\n");
  printf("##                         Sistema de inscripciones                        ##\n");
  printf("##                             Materias cargadas                           ##\n");
  printf("#############################################################################\n");
  printf("\n%-10s%-30s%-12s\n", "Id", "Nombre", "Estado");

  fread(&materiaReg, sizeof(materiaReg), 1, fp);
  while (!feof(fp)) {
    if (materiaReg.estado == 1) {
      printf("\n%-10d%-30s%-12s", materiaReg.id, materiaReg.nombre,"Activa");
    } else {
      printf("\n%-10d%-30s%-12s", materiaReg.id, materiaReg.nombre,"Inactiva");
    }
    fread(&materiaReg, sizeof(materiaReg), 1, fp);
  }

  fclose(fp);
  getchar();
}

void usuariosListar(tipoUsuario tUsuario) {
  usuario usuarioReg;
  char tipoUsuario[30];
  FILE *fp;
  fp = fopen(USUARIOS_DAT, "rb");
  rewind(fp);
  system(CLEAR);

  if (tUsuario == ADMIN) strcpy(tipoUsuario, "Administrador");
  if (tUsuario == ALUMNO) strcpy(tipoUsuario, "Alumno");
  if (tUsuario == PROFESOR) strcpy(tipoUsuario, "Profesor");

  printf("#############################################################################\n");
  printf("##                         Sistema de inscripciones                        ##\n");
  printf("##                             Usuarios cargados                           ##\n");
  printf("#############################################################################\n");
  printf("\n%-10s%-20s%-20s%-12s%-12s\n", "Id", "Nombre", "Username", "Tipo", "Estado");

  fread(&usuarioReg, sizeof(usuarioReg), 1, fp);
  while (!feof(fp)) {
    if (usuarioReg.tipo == tUsuario) {
      if (usuarioReg.estado == 1) {
        printf("\n%-10d%-20s%-20s%-12s%-12s", usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username, tipoUsuario, "Activo");
      } else {
        printf("\n%-10d%-20s%-20s%-12s%-12s", usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username, tipoUsuario, "Inactivo");
      }
    }
    fread(&usuarioReg, sizeof(usuarioReg), 1, fp);
  }

  fclose(fp);
  getchar();
}

// ####################################################################################################################
// ####                                                  Menúes                                                    ####
// ####################################################################################################################

void login() {
  FILE *dbFp;
  usuario usr;
  int opt, existe;
  char username[32];
  char password[32];

  system(CLEAR);

  dbFp = fopen(USUARIOS_DAT, "rb");
  if (dbFp == NULL) {
    // Si devuelve null, inicializo el sistema
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                           Inicializar sistema                           ##\n");
    printf("#############################################################################\n");

    printf("Ingrese los datos del administrador del sistema");
    printf("\nNombre completo: ");
    getstring(usr.nombreCompleto, 32);
    printf("\nNombre de usuario: ");
    getstring(usr.username, 32);
    printf("\nPassword: ");
    getstring(usr.password, 32);

    usr.id = 1;
    usr.tipo = ADMIN;
    usr.estado = 1;

    dbFp = fopen(USUARIOS_DAT, "wb+");
    fwrite(&usr, sizeof(usr), 1, dbFp);

  } else {
    // Caso contrario, iniciar sesion
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                              Iniciar sesion                             ##\n");
    printf("#############################################################################\n");

    do {
      printf("\nUsuario: ");
      getstring(username, sizeof username);

      printf("\nPassword: ");
      getstring(password, sizeof password);

      fseek(dbFp, 0, SEEK_SET);
      existe = 0;
      while (fread(&usr, sizeof(usr), 1, dbFp)) {
        if (!strcmp(usr.username, username) && !strcmp(usr.password, password)) {
          existe = 1;
          break;
        };
      }

      if (existe == 0) {
        printf("Usuario o password incorrectos!\n");
        getchar();
        system(CLEAR);
      }
    } while (existe == 0);

  }

  fclose(dbFp);

  printf("\nBienvenido, %s", usr.nombreCompleto);
  getchar();
  if (usr.tipo == ADMIN) menuAdmin(usr.id);
  if (usr.tipo == ALUMNO) menuAlumno(usr.id);
  if (usr.tipo == PROFESOR) menuProfesor(usr.id);

  return;
}

void menuAdmin(int idUsuario) {
  int opt;
  char fileName[32];
  tipoEntidad tEntidad;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                            Menu Administrador                           ##\n");
    printf("#############################################################################\n");
    printf("[1] Administrar materias\n");
    printf("[2] Administrar profesores\n");
    printf("[3] Administrar alumnos\n");
    printf("[4] Cargar usuarios desde archivo\n");
    printf("[5] Cargar materias desde archivo\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      case 1:
        menuAdmMaterias();
        break;
      case 2:
        menuAdmProfesores();
        break;
      case 3:
        menuAdmAlumnos();
        break;
      case 4:
        system(CLEAR);
        printf("####  Cargar usuarios desde archivo  ####\n");
        printf("Ingrese el nombre del archivo: ");
        getstring(fileName, sizeof fileName);
        tEntidad = USUARIO;
        cargarDesdeArchivo(fileName, tEntidad);
        break;
      case 5:
        system(CLEAR);
        printf("####  Cargar materias desde archivo  ####\n");
        printf("Ingrese el nombre del archivo: ");
        getstring(fileName, sizeof fileName);
        tEntidad = MATERIA;
        cargarDesdeArchivo(fileName, tEntidad);
        break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

void menuAdmMaterias() {
  int opt;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                           Administrar materias                          ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar materias\n");
    printf("[2] Alta de materias\n");
    printf("[3] Baja de materias\n");
    printf("[4] Editar una materia\n");
    printf("[5] Consultar profesor asignado a una materia\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      case 1:
        materiasListar();
        break;
      // case 2:
      //   materiaAlta();
      //   break;
      // case 3:
      //   materiaBaja();
      //   break;
      // case 4:
      //   materiaModificar();
      //   break;
      // case 5:
      //   materiaConsultarProfesor();
      //   break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

void menuAdmProfesores() {
  int opt;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                          Administrar profesores                         ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar profesores\n");
    printf("[2] Alta de profesores\n");
    printf("[3] Baja de profesores\n");
    printf("[4] Editar un profesor\n");
    printf("[5] Listar materias asignadas a un profesor\n");
    printf("[6] Asignar una materia a un profesor\n");
    printf("[7] Des-asignar una materia a un profesor\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      case 1:
        usuariosListar(PROFESOR);
        break;
      // case 2:
      //   usuarioAlta();
      //   break;
      // case 3:
      //   usuarioBaja();
      //   break;
      // case 4:
      //   usuarioModificar();
      //   break;
      // case 5:
      //   usuarioConsultarMaterias();
      //   break;
      // case 6:
      //   usuarioAsignarMateria();
      //   break;
      // case 7:
      //   usuarioDesasignarMateria();
      //   break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

void menuAdmAlumnos() {
  int opt;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                            Administrar alumnos                          ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar alumnos\n");
    printf("[2] Alta de alumnos\n");
    printf("[3] Baja de alumnos\n");
    printf("[4] Editar un alumno\n");
    printf("[5] Listar materias inscriptas de un alumno\n");
    printf("[6] Inscribir alumno a una materia\n");
    printf("[7] Des-inscribir alumno de una materia\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      case 1:
        usuariosListar(ALUMNO);
        break;
      // case 2:
      //   usuarioAlta();
      //   break;
      // case 3:
      //   usuarioBaja();
      //   break;
      // case 4:
      //   usuarioModificar();
      //   break;
      // case 5:
      //   usuarioConsultarMaterias();
      //   break;
      // case 6:
      //   usuarioAsignarMateria();
      //   break;
      // case 7:
      //   usuarioDesasignarMateria();
      //   break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

void menuAlumno(int idUsuario) {
  int opt;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                              Menu de alumno                             ##\n");
    printf("#############################################################################\n");
    printf("[1] Ver materias inscriptas\n");
    printf("[2] Inscribirse a una materia\n");
    printf("[3] Desuscribirse de una materia\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      // case 1:
      //   usuarioConsultarMaterias(int idUsuario);
      //   break;
      // case 2:
      //   usuarioAsignarMateria(int idUsuario, int idMateria)();
      //   break;
      // case 3:
      //   usuarioDesasignarMateria();
      //   break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

void menuProfesor(int idUsuario) {
  int opt;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                             Menu de profesor                            ##\n");
    printf("#############################################################################\n");
    printf("[1] Ver materias asignadas\n");
    printf("[2] Ver alumnos por materia\n");
    printf("[0] Salir\n");
    scanf("%d", &opt);
    clearStdin();
    switch(opt) {
      case 0:
        break;
      // case 1:
      //   usuarioConsultarMaterias(int idUsuario);
      //   break;
      // case 2:
      //   materiaConsultarAlumnos(int idMateria);
      //   break;
      default:
        printf("Opcion incorrecta!\n");
        printf("Por favor, seleccione una opcion valida\n");
        break;
    }
  } while (opt != 0);
  return;
}

// ####################################################################################################################
// ####                                                    MAIN                                                    ####
// ####################################################################################################################

int main() {
  login();
  return 0;
}
