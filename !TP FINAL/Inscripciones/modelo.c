// ####################################################################################################################
// ####                                                  Modelo                                                    ####
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
