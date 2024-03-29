void usuarioAlta(usuario loggedUser, tipoUsuario tipoUsr) {
  FILE *dbFp;
  usuario nuevoUsr;
  int opt, maxId;
  char nombreCompleto[40];
  char username[30];
  char password[30];
  char logMessage[100];

  // Si no existe el archivo lo crea, sino lo abre para r/w
  if ((dbFp = fopen(USUARIOS_DAT, "rb+")) == NULL) {
    dbFp = fopen(USUARIOS_DAT, "wb+");
  } else {
    dbFp = fopen(USUARIOS_DAT, "rb+");
  }

  // Obtiene el mayor id de la tabla
  maxId = 0;
  fseek(dbFp, 0, SEEK_SET);
  while (fread(&nuevoUsr, sizeof(nuevoUsr), 1, dbFp)) {
    if (nuevoUsr.id > maxId) {
      maxId = nuevoUsr.id;
    }
  }
  fseek(dbFp, 0, SEEK_END);

  system(CLEAR);

  do {
    printf("#############################################################################\n");
    if (tipoUsr == PROFESOR)
      printf("##                            Alta de profesores                           ##\n");
    if (tipoUsr == ALUMNO)
      printf("##                             Alta de alumnos                             ##\n");
    printf("#############################################################################\n");

    // Incrementa el ID
    maxId += 1;

    // Setea ID
    nuevoUsr.id = maxId;

    // Setea tipo
    nuevoUsr.tipo = tipoUsr;

    // Setea nombre completo
    printf("\nIngrese el nombre completo: ");
    getstring(nombreCompleto, sizeof nombreCompleto);
    strcpy(nuevoUsr.nombreCompleto, nombreCompleto);

    // Setea nombre de usuario
    printf("\nIngrese el nombre de usuario: ");
    getstring(username, sizeof username);
    strcpy(nuevoUsr.username, username);

    // Setea password
    printf("\nIngrese el password: ");
    getstring(password, sizeof password);
    strcpy(nuevoUsr.password, password);

    // Setea estado activo
    nuevoUsr.estado = 1;

    fwrite(&nuevoUsr, sizeof(nuevoUsr), 1, dbFp);

    // Logs
    strcpy(logMessage, "Se agrego el usuario '");
    strcat(logMessage, nuevoUsr.username);
    if (tipoUsr == PROFESOR) strcat(logMessage, "' (Profesor)");
    if (tipoUsr == ALUMNO) strcat(logMessage, "' (Alumno)");
    logger(loggedUser, logMessage);

    printf("Desea seguir cargando usuarios?\n");
    printf("  [1] Seguir\n");
    printf("  [0] Salir\n\n");
    printf("Opcion: ");
    scanf("%d", &opt);
    clearStdin();

    system(CLEAR);
  } while (opt != 0);

  fclose(dbFp);
}

void usuarioEditar(usuario loggedUser, tipoUsuario tipoUsr) {
  FILE *dbFp;
  dbFp = fopen(USUARIOS_DAT, "rb+");
  usuario usuarioReg;
  int idUsr, opt, operacion, existe = 0;
  char logMessage[100];
  char strNum[5];

  system(CLEAR);
  printf("#############################################################################\n");
  printf("##                              Editar usuarios                            ##\n");

  // Lista usuarios activos e inactivos
  usuariosListar(loggedUser, tipoUsr, 1);

  printf("\n\nIngrese el ID de un usuario: ");
  scanf("%d", &idUsr);
  clearStdin();

  while (fread(&usuarioReg, sizeof(usuarioReg), 1, dbFp)) {
    if (usuarioReg.id == idUsr && usuarioReg.tipo == tipoUsr) {
      operacion = usuarioEditarSelected(&usuarioReg);

      if (operacion == 0) return;

      existe = 1;
      fseek(dbFp, -sizeof(usuarioReg), SEEK_CUR);
      fwrite(&usuarioReg, sizeof(usuarioReg), 1, dbFp);
      break;
    }
  }

  if (!existe) {
    printf("\nEl id ingresado no existe o no es de tipo '%s'", tipoUsrString[tipoUsr]);
  } else {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                             Usuario modificado                          ##\n");
    printf("#############################################################################\n");
    printf("\n\n%-5s%-30s%-20s%-15s%-15s\n", "Id", "Nombre completo", "Username", "Tipo", "Estado");
    printf("\n%-5d%-30s%-20s%-15s%-15s",
      usuarioReg.id, usuarioReg.nombreCompleto, usuarioReg.username,
      tipoUsrString[usuarioReg.tipo], usuarioReg.estado ? "Activo" : "Inactivo"
    );

    // Logs
    strcpy(logMessage, "Id usuario: ");
    sprintf(strNum,"%d", usuarioReg.id);
    strcat(logMessage, strNum);
    strcat(logMessage, " => Cambia el campo '");

    switch (operacion) {
      // Editar nombre
      case 1:
        strcat(logMessage, "Nombre completo' a '");
        strcat(logMessage, usuarioReg.nombreCompleto);
        strcat(logMessage, "'");
        break;
      // Editar username
      case 2:
        strcat(logMessage, "Username' a '");
        strcat(logMessage, usuarioReg.username);
        strcat(logMessage, "'");
        break;
      // Editar password
      case 3:
        strcat(logMessage, "Password' a '");
        strcat(logMessage, usuarioReg.password);
        strcat(logMessage, "'");
        break;
      // Editar estado
      case 4:
        strcat(logMessage, "Estado' a '");
        strcat(logMessage, usuarioReg.estado ? "Activo" : "Inactivo");
        strcat(logMessage, "'");
        break;
    }
    logger(loggedUser, logMessage);
  };

  getchar();
  fclose(dbFp);
}

int usuarioEditarSelected(usuario *usr) {
  int estado, operacion;
  char aux[30];

  do {
    printf("\nSeleccione una operacion: \n");
    printf("  [1] Editar nombre\n");
    printf("  [2] Editar username\n");
    printf("  [3] Editar password\n");
    printf("  [4] Cambiar estado\n");
    printf("  [0] Salir\n");
    printf("Opcion: ");
    scanf("%d", &operacion);
    clearStdin();
    if (operacion == 0) return operacion;
  } while (operacion < 0 || operacion > 4);

  switch (operacion) {
    case 1:
      printf("\nIngrese el nuevo nombre completo: ");
      getstring(aux, sizeof aux);
      strcpy(usr->nombreCompleto, aux);
      return operacion;
      break;
    case 2:
      printf("\nIngrese el nuevo nombre de usuario: ");
      getstring(aux, sizeof aux);
      strcpy(usr->username, aux);
      return operacion;
      break;
    case 3:
      printf("\nIngrese el nuevo password: ");
      getstring(aux, sizeof aux);
      strcpy(usr->password, aux);
      return operacion;
      break;
    case 4:
      do {
        printf("\nSeleccione una opcion: \n");
        printf("  [1] Activar usuario\n");
        printf("  [0] Desactivar usuario\n");
        scanf("%d", &estado);
        clearStdin();
      } while (estado < 0 || estado > 1);
      usr->estado = estado;
      return operacion;
      break;
    default:
      return 0;
  }
}

void materiaAlta(usuario loggedUser) {
  FILE *dbFp;
  materia nuevaMat;
  int opt, maxId;
  char nombre[40];
  char logMessage[100];

  // Si no existe el archivo lo crea, sino lo abre para r/w
  if ((dbFp = fopen(MATERIAS_DAT, "rb+")) == NULL) {
    dbFp = fopen(MATERIAS_DAT, "wb+");
  } else {
    dbFp = fopen(MATERIAS_DAT, "rb+");
  }

  // Obtiene el mayor id de la tabla
  maxId = 0;
  fseek(dbFp, 0, SEEK_SET);
  while (fread(&nuevaMat, sizeof(nuevaMat), 1, dbFp)) {
    if (nuevaMat.id > maxId) {
      maxId = nuevaMat.id;
    }
  }
  fseek(dbFp, 0, SEEK_END);

  system(CLEAR);

  do {
    printf("#############################################################################\n");
    printf("##                            Alta de materias                             ##\n");
    printf("#############################################################################\n");

    // Incrementa el ID
    maxId += 1;

    // Setea ID
    nuevaMat.id = maxId;

    // Setea nombre
    printf("\nIngrese el nombre de la materia: ");
    getstring(nombre, sizeof nombre);
    strcpy(nuevaMat.nombre, nombre);

    // Setea estado activo
    nuevaMat.estado = 1;

    fwrite(&nuevaMat, sizeof(nuevaMat), 1, dbFp);

    // Logs
    strcpy(logMessage, "Se creo la materia '");
    strcat(logMessage, nuevaMat.nombre);
    strcat(logMessage, "'");
    logger(loggedUser, logMessage);

    printf("Desea seguir cargando materias?\n");
    printf("  [1] Seguir\n");
    printf("  [0] Salir\n\n");
    printf("Opcion: ");
    scanf("%d", &opt);
    clearStdin();

    system(CLEAR);
  } while (opt != 0);

  fclose(dbFp);
}

void materiaEditar(usuario loggedUser) {
  FILE *dbFp;
  dbFp = fopen(MATERIAS_DAT, "rb+");
  materia materiaReg;
  int idMateria, operacion, existe = 0;
  char logMessage[100];
  char strNum[5];

  system(CLEAR);
  printf("#############################################################################\n");
  printf("##                              Editar materias                            ##\n");

  // Lista todas las materias
  materiasListar(loggedUser, 1);

  printf("\n\nIngrese el ID de una materia: ");
  scanf("%d", &idMateria);
  clearStdin();

  while (fread(&materiaReg, sizeof(materiaReg), 1, dbFp)) {
    if (materiaReg.id == idMateria) {
      operacion = materiaEditarSelected(&materiaReg);

      if (operacion == 0) return;

      existe = 1;
      fseek(dbFp, -sizeof(materiaReg), SEEK_CUR);
      fwrite(&materiaReg, sizeof(materiaReg), 1, dbFp);
      break;
    }
  }

  if (!existe) {
    printf("\nEl id de materia ingresada no existe!");
  } else {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                             Materia modificada                          ##\n");
    printf("#############################################################################\n");
    printf("\n\n%-5s%-30s%-15s\n", "Id", "Nombre", "Estado");
    printf("\n%-5d%-30s%-15s", materiaReg.id, materiaReg.nombre, materiaReg.estado ? "Activo" : "Inactivo");

    // Logs
    strcpy(logMessage, "Id materia: ");
    sprintf(strNum,"%d", materiaReg.id);
    strcat(logMessage, strNum);
    strcat(logMessage, " => Cambia el campo '");

    switch (operacion) {
      // Editar nombre
      case 1:
        strcat(logMessage, "Nombre' a '");
        strcat(logMessage, materiaReg.nombre);
        strcat(logMessage, "'");
        break;
      // Editar estado
      case 2:
        strcat(logMessage, "Estado' a '");
        strcat(logMessage, materiaReg.estado ? "Activo" : "Inactivo");
        strcat(logMessage, "'");
        break;
    }
    logger(loggedUser, logMessage);
  };

  getchar();
  fclose(dbFp);
}

int materiaEditarSelected(materia *mat) {
  int estado, operacion;
  char aux[30];

  do {
    printf("\nSeleccione una operacion: \n");
    printf("  [1] Editar nombre\n");
    printf("  [2] Cambiar estado\n");
    printf("  [0] Salir\n");
    printf("Opcion: ");
    scanf("%d", &operacion);
    clearStdin();
    if (operacion == 0) return operacion;
  } while (operacion < 0 || operacion > 2);

  switch (operacion) {
    case 1:
      printf("\nIngrese el nuevo nombre de la materia: ");
      getstring(aux, sizeof aux);
      strcpy(mat->nombre, aux);
      return operacion;
      break;
    case 2:
      do {
        printf("\nSeleccione una opcion: \n");
        printf("  [1] Activar materia\n");
        printf("  [0] Desactivar materia\n");
        printf("Opcion: ");
        scanf("%d", &estado);
        clearStdin();
      } while (estado < 0 || estado > 1);
      mat->estado = estado;
      return operacion;
      break;
    default:
      return 0;
  }
}

// Menu Admin Alumnos / Menu Profesor
void alumnoAsignarMateria(usuario loggedUser) {
  FILE *fp;
  int esAdmin, existe = 0, maxId;
  char logMessage[100];
  char numStr[5];
  materiaAlumno materiaAlumnoReg;
  materia mat;
  usuario usr;
  fp = fopen(MATERIA_ALUMNO_DAT, "rb+");

  esAdmin = (loggedUser.tipo == ADMIN);

  // Si es para menu admin
  if (esAdmin) {
    // Lista usuarios para seleccionar uno sobre el cual operar
    usr = seleccionarUsuario(loggedUser, ALUMNO);
    if (usr.id == -1) return;
  }

  // Lista las materias para seleccionar una
  mat = seleccionarMateria(loggedUser);

  while (fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, fp)) {
    if (materiaAlumnoReg.idAlumno == (esAdmin ? usr.id : loggedUser.id)
        && materiaAlumnoReg.idMateria == mat.id
        && materiaAlumnoReg.estado) {
      existe = 1;
    }
  }

  if (!existe) {

    // Obtiene el mayor id de la tabla
    maxId = 0;
    fseek(fp, 0, SEEK_SET);
    while (fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, fp)) {
      if (materiaAlumnoReg.id > maxId) {
        maxId = materiaAlumnoReg.id;
      }
    }
    fseek(fp, 0, SEEK_END);

    materiaAlumnoReg.id = maxId + 1;
    materiaAlumnoReg.idAlumno = esAdmin ? usr.id : loggedUser.id;
    materiaAlumnoReg.idMateria = mat.id;
    materiaAlumnoReg.estado = 1;
    fwrite(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, fp);
    fclose(fp);
    printf("\nMateria asignada exitosamente");
    getchar();
  } else {
    printf("La materia ya se encuentra asignada\n");
    getchar();
    fclose(fp);
    return;
  }

  // Logs
  if (esAdmin) {
    strcpy(logMessage, "Se asigno la materia '");
    strcat(logMessage, mat.nombre);
    strcat(logMessage, "' al alumno '");
    strcat(logMessage, usr.nombreCompleto);
    strcat(logMessage, "' (ID: ");
    sprintf(numStr, "%d", usr.id);
    strcat(logMessage, numStr);
    strcat(logMessage, ")");
  } else {
    strcpy(logMessage, "Se inscribio en la materia '");
    strcat(logMessage, mat.nombre);
    strcat(logMessage, "' (ID: ");
    sprintf(numStr, "%d", mat.id);
    strcat(logMessage, numStr);
    strcat(logMessage, ")");
  }
  logger(loggedUser, logMessage);
}

// Menu Admin Profesores
void profesorAsignarMateria(usuario loggedUser) {
  FILE *fp;
  materiaProfesor materiaProfesorReg;
  materia mat;
  usuario usr;
  int estaAsignada = 0, maxId;
  char logMessage[100];
  char numStr[5];

  fp = fopen(MATERIA_PROFESOR_DAT, "rb+");

  // Lista los usuarios para seleccionar un profesor
  usr = seleccionarUsuario(loggedUser, PROFESOR);
  if (usr.id == -1) return;

  // Lista las materias para seleccionar una
  mat = seleccionarMateria(loggedUser);
  if (mat.id == -1) return;

  // Busco saber si la materia seleccionada ya está asignada a un profesor
  while (fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, fp)) {
    if (materiaProfesorReg.idMateria == mat.id && materiaProfesorReg.estado) {
      estaAsignada = 1;
    }
  }

  // Si no esta asignada
  if (!estaAsignada) {

    // Obtiene el mayor id de la tabla
    maxId = 0;
    fseek(fp, 0, SEEK_SET);
    while (fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, fp)) {
      if (materiaProfesorReg.id > maxId) {
        maxId = materiaProfesorReg.id;
      }
    }
    fseek(fp, 0, SEEK_END);

    // Cargo la nueva relacion
    materiaProfesorReg.id = maxId + 1;
    materiaProfesorReg.idProfesor = usr.id;
    materiaProfesorReg.idMateria = mat.id;
    materiaProfesorReg.estado = 1;
    fwrite(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, fp);
    fclose(fp);
    printf("\nMateria asignada exitosamente");
    getchar();
  } else {
    printf("La materia ya se encuentra asignada\n");
    getchar();
    fclose(fp);
    return;
  }

  // Logs
  strcpy(logMessage, "Se asigno la materia '");
  strcat(logMessage, mat.nombre);
  strcat(logMessage, "' al profesor '");
  strcat(logMessage, usr.nombreCompleto);
  strcat(logMessage, "' (ID: ");
  sprintf(numStr, "%d", usr.id);
  strcat(logMessage, numStr);
  strcat(logMessage, ")");
  logger(loggedUser, logMessage);
}

void usuarioDesasignarMateria(usuario loggedUser, usuario usr) {
  FILE *materiaUsuarioFp, *materiaFp;
  materia materiaReg;
  materiaProfesor materiaProfesorReg;
  materiaAlumno materiaAlumnoReg;
  int tieneMaterias = 0, idMateria;
  int materiaEncontrada = 0;
  char logMessage[100];
  char strNum[5];

  materiaFp = fopen(MATERIAS_DAT, "rb");

  if (usr.tipo == PROFESOR) {
    materiaUsuarioFp = fopen(MATERIA_PROFESOR_DAT,"rb+");
  } else if (usr.tipo == ALUMNO) {
    materiaUsuarioFp = fopen(MATERIA_ALUMNO_DAT,"rb+");
  }

  tieneMaterias = usuarioConsultarMaterias(loggedUser, usr);

  if (!tieneMaterias) return;

  do {
    printf("\nSeleccione una materia o ingrese 0 para salir: ");
    scanf("%d", &idMateria);
    clearStdin();

    if (idMateria == 0) return;

    rewind(materiaUsuarioFp);

    if (usr.tipo == PROFESOR) {
      // Recorro todas las relaciones materiaProfesor
      while (fread(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, materiaUsuarioFp)) {
        // Si esta activa la relacion
        if (materiaProfesorReg.estado) {
          // Si coinciden el idMateria seleccionado con el id de materia de la relacion y el id del usuario con el de la relacion
          if (idMateria == materiaProfesorReg.idMateria && usr.id == materiaProfesorReg.idProfesor) {
            materiaProfesorReg.estado = 0;
            fseek(materiaUsuarioFp, -sizeof(materiaProfesorReg), SEEK_CUR);
            fwrite(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, materiaUsuarioFp);
            materiaEncontrada = 1;
            break;
          }
        }
      }
      rewind(materiaUsuarioFp);
    }
    // Si es un alumno
    if (usr.tipo == ALUMNO) {
      // Recorro todas las relaciones materiaProfesor
      while (fread(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, materiaUsuarioFp)) {
        // Si esta activa la relacion
        if (materiaAlumnoReg.estado) {
          // Si coinciden el id de materia con el id de materia de la relacion y el id del usuario con el de la relacion
          if (idMateria == materiaAlumnoReg.idMateria && usr.id == materiaAlumnoReg.idAlumno) {
            materiaAlumnoReg.estado = 0;
            fseek(materiaUsuarioFp, -sizeof(materiaAlumnoReg), SEEK_CUR);
            fwrite(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, materiaUsuarioFp);
            materiaEncontrada = 1;
            break;
          }
        }
      }
      rewind(materiaUsuarioFp);
    }
    if (!materiaEncontrada) printf("\nOpcion invalida!");
  } while (!materiaEncontrada);

  printf("\nMateria desasignada exitosamente");
  getchar();

  // Logger
  materiaReg = getMateriaById(idMateria);
  if (loggedUser.id == usr.id) {
    strcpy(logMessage, "Se des-asigno la materia '");
    strcat(logMessage, materiaReg.nombre);
    strcat(logMessage, "' (ID: ");
    sprintf(strNum, "%d", materiaReg.id);
    strcat(logMessage, strNum);
    strcat(logMessage, ")");
  } else {
    strcpy(logMessage, "Se des-asigno la materia '");
    strcat(logMessage, materiaReg.nombre);
    strcat(logMessage, "' (ID: ");
    sprintf(strNum, "%d", materiaReg.id);
    strcat(logMessage, strNum);
    strcat(logMessage, ") del usuario '");
    strcat(logMessage, usr.username);
    if (usr.tipo == PROFESOR) strcat(logMessage, "' (Profesor)");
    if (usr.tipo == ALUMNO) strcat(logMessage, "' (Alumno)");
  }
  logger(loggedUser, logMessage);

  fclose(materiaUsuarioFp);
  fclose(materiaFp);
}
