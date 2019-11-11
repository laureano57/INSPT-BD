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

  while (fread(&materiaReg, sizeof(materiaReg), 1, fp)) {
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

  while (fread(&usuarioReg, sizeof(usuarioReg), 1, fp)) {
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

  // Por cada materia...
  while (fread(&materiaReg, sizeof(materiaReg), 1, materiaFp)) {
    // ...que este activa
    if (materiaReg.estado == 1) {
      // Si es un profesor
      if (usr.tipo == PROFESOR) {
        // Recorro todas las relaciones materiaProfesor
        while (fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, materiaUsuarioFp)) {
          // Si coinciden el id de materia con el id de materia de la relacion y el id del usuario con el de la relacion
          if (materiaReg.id == materiaProfesorReg.idMateria && usr.id == materiaProfesorReg.idProfesor) {
            if (!tieneMaterias) printf("Materias:\n");
            // Encontro una materia al menos
            tieneMaterias = 1;
            // Imprimo la materia
            printf("%d | %s\n", materiaReg.id, materiaReg.nombre);
          }
        }
        rewind(materiaUsuarioFp);
      }
      // Si es un alumno
      if (usr.tipo == ALUMNO) {
        // Recorro todas las relaciones materiaProfesor
        while (fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, materiaUsuarioFp)) {
          // Si coinciden el id de materia con el id de materia de la relacion y el id del usuario con el de la relacion
          if (materiaReg.id == materiaAlumnoReg.idMateria && usr.id == materiaAlumnoReg.idAlumno) {
            if (!tieneMaterias) printf("Materias:\n");
            // Encontro una materia al menos
            tieneMaterias = 1;
            // Imprimo la materia
            printf("%d | %s\n", materiaReg.id, materiaReg.nombre);
          }
        }
        rewind(materiaUsuarioFp);
      }
    }
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

void materiaConsultarProfesor(usuario loggedUser, materia mat) {
  FILE *materiaProfesorFp, *profesorFp;
  materiaProfesor materiaProfesorReg;
  usuario profesor;
  int tieneProfesor = 0;
  char numStr[5];
  char logMessage[120];

  materiaProfesorFp = fopen(MATERIA_PROFESOR_DAT,"rb");
  profesorFp = fopen(USUARIOS_DAT, "rb");

  rewind(profesorFp);

  printf("#############################################################################\n");
  printf("##                            Profesor asignado                            ##\n");
  printf("#############################################################################\n");
  printf("\nMateria: %d - %s", mat.id, mat.nombre);

  // Por cada materia/profesor
  while (fread(&materiaProfesorReg, sizeof(materiaProfesor), 1, materiaProfesorFp)) {
    if (mat.id == materiaProfesorReg.idMateria) {
      if (!tieneProfesor) printf("\n\n%-10s%-30s%-20s\n", "Id", "Nombre", "Username");
      tieneProfesor = 1;
      profesor = getUsuarioById(materiaProfesorReg.idProfesor, PROFESOR);
      printf("%-10d%-30s%-20s\n", profesor.id, profesor.nombreCompleto, profesor.username);
      break;
    }
  }

  if (!tieneProfesor) printf("\n\nLa materia seleccionada no tiene un profesor designado");

  // Logger
  strcpy(logMessage, "Se consulto el profesor designado de la materia '");
  strcat(logMessage, mat.nombre);
  strcat(logMessage, "' (ID: ");
  sprintf(numStr, "%d", mat.id);
  strcat(logMessage, numStr);
  strcat(logMessage, ")");
  logger(loggedUser, logMessage);

  fclose(materiaProfesorFp);
  fclose(profesorFp);

  getchar();
}

void materiaConsultarAlumnos(usuario loggedUser, materia mat) {
  FILE *materiaAlumnoFp, *alumnoFp;
  materiaAlumno materiaAlumnoReg;
  usuario alumno;
  int tieneMaterias = 0;
  char numStr[5];
  char logMessage[120];

  materiaAlumnoFp = fopen(MATERIA_ALUMNO_DAT,"rb");
  alumnoFp = fopen(USUARIOS_DAT, "rb");

  rewind(alumnoFp);

  printf("#############################################################################\n");
  printf("##                            Alumnos inscriptos                           ##\n");
  printf("#############################################################################\n");
  printf("\nMateria: %d - %s", mat.id, mat.nombre);

  // Por cada materia/alumno
  while (fread(&materiaAlumnoReg, sizeof(materiaAlumno), 1, materiaAlumnoFp)) {
    if (mat.id == materiaAlumnoReg.idMateria) {
      if (tieneMaterias == 0) printf("\n\n%-10s%-30s%-20s\n", "Id", "Nombre", "Username");
      tieneMaterias = 1;
      alumno = getUsuarioById(materiaAlumnoReg.idAlumno, ALUMNO);
      printf("%-10d%-30s%-20s\n", alumno.id, alumno.nombreCompleto, alumno.username);
    }
  }

  if (!tieneMaterias) printf("\n\nLa materia seleccionada no posee alumnos inscriptos");

  // Logger
  strcpy(logMessage, "Se listaron los alumnos inscriptos en la materia '");
  strcat(logMessage, mat.nombre);
  strcat(logMessage, "' (ID: ");
  sprintf(numStr, "%d", mat.id);
  strcat(logMessage, numStr);
  strcat(logMessage, ")");
  logger(loggedUser, logMessage);

  fclose(materiaAlumnoFp);
  fclose(alumnoFp);

  getchar();
}
