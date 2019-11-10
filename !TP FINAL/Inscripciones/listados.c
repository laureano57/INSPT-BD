// ####################################################################################################################
// ####                                                  Listados                                                  ####
// ####################################################################################################################

void materiasListar(int mostrarTodas) {
  materia materiaReg;
  FILE *fp;
  fp = fopen(MATERIAS_DAT, "rb");
  rewind(fp);
  system(CLEAR);

  printf("#############################################################################\n");
  printf("##                         Sistema de inscripciones                        ##\n");
  printf("##                             Materias cargadas                           ##\n");
  printf("#############################################################################\n");
  if (mostrarTodas) {
    printf("\n%-10s%-30s%-12s\n", "Id", "Nombre", "Estado");
  } else {
    printf("\n%-10s%-30s\n", "Id", "Nombre");
  }

  fread(&materiaReg, sizeof(materiaReg), 1, fp);
  while (!feof(fp)) {
    if (materiaReg.estado == 1) {
      if (mostrarTodas) {
        printf("\n%-10d%-30s%-12s", materiaReg.id, materiaReg.nombre,"Activa");
      } else {
        printf("\n%-10d%-30s", materiaReg.id, materiaReg.nombre);
      }
    } else {
      if (mostrarTodas) {
        printf("\n%-10d%-30s%-12s", materiaReg.id, materiaReg.nombre,"Inactiva");
      }
    }
    fread(&materiaReg, sizeof(materiaReg), 1, fp);
  }

  fclose(fp);
}

void usuariosListar(tipoUsuario tUsuario, int mostrarTodos) {
  usuario usuarioReg;
  FILE *fp;
  fp = fopen(USUARIOS_DAT, "rb");
  rewind(fp);

  printf("#############################################################################\n");
  printf("##                             Usuarios cargados                           ##\n");
  printf("#############################################################################\n");
  if (mostrarTodos) {
    printf("\n%-10s%-30s%-20s%-12s%-12s\n", "Id", "Nombre", "Username", "Tipo", "Estado");
  } else {
    printf("\n%-10s%-30s%-20s%-12s\n", "Id", "Nombre", "Username", "Tipo");
  }

  fread(&usuarioReg, sizeof(usuarioReg), 1, fp);
  while (!feof(fp)) {
    if (usuarioReg.tipo == tUsuario) {
      if (usuarioReg.estado == 1) {
        if (mostrarTodos) {
          printf("\n%-10d%-30s%-20s%-12s%-12s", usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username, tipoUsrString[tUsuario], "Activo");
        } else {
          printf("\n%-10d%-30s%-20s%-12s", usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username, tipoUsrString[tUsuario]);
        }
      } else {
        if (mostrarTodos) {
          printf("\n%-10d%-30s%-20s%-12s%-12s", usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username, tipoUsrString[tUsuario], "Inactivo");
        }
      }
    }
    fread(&usuarioReg, sizeof(usuarioReg), 1, fp);
  }

  fclose(fp);
}

void usuarioConsultarMaterias(usuario loggedUser, usuario usr) {
  FILE *materiaUsuarioFp, *materiaFp;
  materia materiaReg;
  materiaProfesor materiaProfesorReg;
  materiaAlumno materiaAlumnoReg;
  int tieneMaterias = 0;
  char logMessage[100];

  materiaFp = fopen(MATERIAS_DAT, "rb");

  if (usr.tipo == PROFESOR) {
    materiaUsuarioFp = fopen(MATERIA_PROFESOR_DAT,"rb");
  } else if (usr.tipo == ALUMNO) {
    materiaUsuarioFp = fopen(MATERIA_ALUMNO_DAT,"rb");
  }

  rewind(materiaUsuarioFp);

  printf("#############################################################################\n");
  printf("##                            Materias asignadas                           ##\n");
  printf("#############################################################################\n");
  printf("\n%s:", tipoUsrString[usr.tipo]);
  printf("\n%-10s%-30s%-20s\n", "Id", "Nombre", "Username");
  printf("%-10d%-30s%-20s\n\n", usr.id, usr.nombreCompleto, usr.username);

  fread(&materiaReg, sizeof(materiaReg), 1, materiaFp);
  // Por cada materia...
  while (!feof(materiaFp)) {
    // ...que este activa
    if (materiaReg.estado == 1) {
      // Si es un profesor
      if (usr.tipo == PROFESOR) {
        fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, materiaUsuarioFp);
        // Recorro todas las relaciones materiaProfesor
        while (!feof(materiaUsuarioFp)) {
          // Si coinciden el id de materia con el id de materia de la relacion y el id del usuario con el de la relacion
          if (materiaReg.id == materiaProfesorReg.idMateria && usr.id == materiaProfesorReg.idProfesor) {
            if (!tieneMaterias) printf("Materias:\n");
            // Encontro una materia al menos
            tieneMaterias = 1;
            // Imprimo la materia
            printf("%d | %s\n", materiaReg.id, materiaReg.nombre);
          }
        fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, materiaUsuarioFp);
        }
        rewind(materiaUsuarioFp);
      }
      // Si es un alumno
      if (usr.tipo == ALUMNO) {
        fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, materiaUsuarioFp);
        // Recorro todas las relaciones materiaProfesor
        while (!feof(materiaUsuarioFp)) {
          // Si coinciden el id de materia con el id de materia de la relacion y el id del usuario con el de la relacion
          if (materiaReg.id == materiaAlumnoReg.idMateria && usr.id == materiaAlumnoReg.idAlumno) {
            if (!tieneMaterias) printf("Materias:\n");
            // Encontro una materia al menos
            tieneMaterias = 1;
            // Imprimo la materia
            printf("%d | %s\n", materiaReg.id, materiaReg.nombre);
          }
        fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, materiaUsuarioFp);
        }
        rewind(materiaUsuarioFp);
      }
    }
    fread(&materiaReg, sizeof(materiaReg), 1, materiaFp);
  }

  if (!tieneMaterias) printf("No se encontraron materias asignadas!");

  // Logger
  if (loggedUser.id == usr.id) {
    strcpy(logMessage, "El usuario consulto sus materias asignadas");
  } else {
    strcpy(logMessage, "Se listaron las materias asignadas al usuario '");
    strcat(logMessage, usr.username);
    if (usr.tipo == PROFESOR) strcat(logMessage, "' (Profesor)");
    if (usr.tipo == ALUMNO) strcat(logMessage, "' (Alumno)");
  }
  logger(loggedUser, logMessage);

  getchar();

  fclose(materiaUsuarioFp);
  fclose(materiaFp);
}
