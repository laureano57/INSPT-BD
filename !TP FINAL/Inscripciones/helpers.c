// ####################################################################################################################
// ####                                                  Helpers                                                   ####
// ####################################################################################################################

char *getstring(char *buf, size_t size) {
  if (buf != NULL && size > 0) {
    if (fgets(buf, size, stdin)) {
      buf[strcspn(buf, "\n")] = '\0';
      return buf;
    }
    *buf = '\0'; /* clear buffer at end of file */
  }
  return NULL;
}

void clearStdin(void) {
  int c;
  do
    c = getc(stdin);
  while (c != '\n' && c != EOF);
}

void logger(usuario loggedUser, char *action) {
  FILE *fp;
  char message[160];
  time_t t;
  struct tm *timeStruct;
  char fechaHora[50];

  fp = fopen(LOG_FILE, "a");

  time(&t);
  timeStruct = localtime(&t);
  strftime(fechaHora, sizeof(fechaHora), "%d/%m/%Y - %H:%Mhs | ", timeStruct);

  strcpy(message, fechaHora);
  strcat(message, "Operador: ");
  strcat(message, loggedUser.username);
  if (loggedUser.tipo == ADMIN)
    strcat(message, " (ADMIN) | ");
  if (loggedUser.tipo == PROFESOR)
    strcat(message, " (PROFESOR) | ");
  if (loggedUser.tipo == ALUMNO)
    strcat(message, " (ALUMNO) | ");
  strcat(message, action);

  fputs(message, fp);
  fputs("\n", fp);

  fclose(fp);
}

void cargarDesdeArchivo(usuario loggedUser, char *archivoTexto, tipoEntidad tEntidad) {
  FILE *textoFp;
  FILE *dbFp;

  struct materia materiaReg;
  struct usuario usuarioReg;
  struct materiaProfesor materiaProfesorReg;
  struct materiaAlumno materiaAlumnoReg;

  char *token;
  char line[80];
  char archivoDb[30];

  if (tEntidad == USUARIO)
    strcpy(archivoDb, USUARIOS_DAT);
  if (tEntidad == MATERIA)
    strcpy(archivoDb, MATERIAS_DAT);
  if (tEntidad == MATERIA_PROFESOR)
    strcpy(archivoDb, MATERIA_PROFESOR_DAT);
  if (tEntidad == MATERIA_ALUMNO)
    strcpy(archivoDb, MATERIA_ALUMNO_DAT);

  // Campos de los registros
  int id, idMateria, idProfesor, idAlumno;
  int tipo, estado;
  char nombre[30];

  // Variables para el log
  char nombreTabla[30];
  char logMessage[100];

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
      if (tipo == 0)
        usuarioReg.tipo = ADMIN;
      if (tipo == 1)
        usuarioReg.tipo = PROFESOR;
      if (tipo == 2)
        usuarioReg.tipo = ALUMNO;

      token = strtok(NULL, ",");
      usuarioReg.estado = atoi(token);

      strcpy(nombreTabla, "usuario");
      fwrite(&usuarioReg, sizeof(usuarioReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA) {
      materiaReg.id = id;

      token = strtok(NULL, ",");
      strcpy(materiaReg.nombre, token);

      token = strtok(NULL, ",");
      materiaReg.estado = atoi(token);

      strcpy(nombreTabla, "materia");
      fwrite(&materiaReg, sizeof(materiaReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA_PROFESOR) {
      materiaProfesorReg.id = id;

      token = strtok(NULL, ",");
      materiaProfesorReg.idMateria = atoi(token);

      token = strtok(NULL, ",");
      materiaProfesorReg.idProfesor = atoi(token);

      strcpy(nombreTabla, "materia_profesor");
      fwrite(&materiaProfesorReg, sizeof(materiaProfesorReg), 1, dbFp);
    }
    // Parseo la linea segun tipo de entidad
    if (tEntidad == MATERIA_ALUMNO) {
      materiaAlumnoReg.id = id;

      token = strtok(NULL, ",");
      materiaAlumnoReg.idMateria = atoi(token);

      token = strtok(NULL, ",");
      materiaAlumnoReg.idAlumno = atoi(token);

      strcpy(nombreTabla, "materia_alumno");
      fwrite(&materiaAlumnoReg, sizeof(materiaAlumnoReg), 1, dbFp);
    }
  };

  // Armo el mensaje para el log
  strcpy(logMessage, "Se cargo la tabla '");
  strcat(logMessage, nombreTabla);
  strcat(logMessage, "' con el archivo '");
  strcat(logMessage, archivoTexto);
  strcat(logMessage, "'");

  // Logueo mensaje
  logger(loggedUser, logMessage);

  fclose(dbFp);
  fclose(textoFp);

  system(CLEAR);
  printf("Archivo cargado exitosamente");
  clearStdin();
}

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
    do {
      printf("#############################################################################\n");
      printf("##                         Sistema de inscripciones                        ##\n");
      printf("##                              Iniciar sesion                             ##\n");
      printf("#############################################################################\n");

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
  if (usr.tipo == ADMIN)
    menuAdmin(usr);
  if (usr.tipo == ALUMNO)
    menuAlumno(usr);
  if (usr.tipo == PROFESOR)
    menuProfesor(usr);

  return;
}

usuario seleccionarUsuario(tipoUsuario tipo) {
  int idUsr;
  usuario usr;
  // Lista solo usuarios activos
  usuariosListar(tipo, 0);
  do {
    printf("\n\nIngrese el ID de un usuario: ");
    scanf("%d", &idUsr);
    clearStdin();
    usr = getUsuarioById(idUsr, tipo);
    if (usr.id == -1) {
      printf("Opcion invalida!");
      getchar();
    }
  } while (usr.id == -1);

  return usr;
}

usuario getUsuarioById(int idUsr, tipoUsuario tipo) {
  FILE *fp;
  usuario usr;

  fp = fopen(USUARIOS_DAT, "rb");
  fread(&usr, sizeof(usr), 1, fp);
  while(!feof(fp)) {
    if (usr.id == idUsr && usr.tipo == tipo) {
      fclose(fp);
      return usr;
    }
    fread(&usr, sizeof(usr), 1, fp);
  }
  fclose(fp);
  usr.id = -1;
  return usr;
}

materia seleccionarMateria() {
  materia mat;
  int idMateria;

  materiasListar(0);

  do {
    printf("\n\nIngrese el ID de una materia: ");
    scanf("%d", &idMateria);
    clearStdin();
    mat = getMateriaById(idMateria);
    if (mat.id == -1) {
      printf("Opcion invalida!");
      getchar();
    }
  } while (mat.id == -1);

  return mat;
}

materia getMateriaById(int idMateria) {
  FILE *fp;
  materia mat;

  fp = fopen(MATERIAS_DAT, "rb");

  fread(&mat, sizeof(mat), 1, fp);
  while(!feof(fp)) {
    if (mat.id == idMateria) {
      fclose(fp);
      return mat;
    }
    fread(&mat, sizeof(mat), 1, fp);
  }
  fclose(fp);
  mat.id = -1;
  return mat;
}
