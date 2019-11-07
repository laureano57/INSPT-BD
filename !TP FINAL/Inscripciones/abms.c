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
    printf("[1] Seguir\n");
    printf("[0] Salir\n\n");
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
  usuariosListar(tipoUsr, 1);

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
    printf("[1] Editar nombre\n");
    printf("[2] Editar username\n");
    printf("[3] Editar password\n");
    printf("[4] Cambiar estado\n");
    printf("[0] Salir\n");
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
        printf("[1] Activar usuario\n");
        printf("[0] Desactivar usuario\n");
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
