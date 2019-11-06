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

void usuarioActivarDesactivar(usuario loggedUser, tipoUsuario tipoUsr) {
  FILE *dbFp;
  dbFp = fopen(USUARIOS_DAT, "rb+");
  usuario usuarioReg;
  int idUsr, opt, existe = 0;
  char logMessage[100];
  char strNum[5];

  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                       Activar o desactivar usuarios                     ##\n");
    // Lista usuarios activos e inactivos
    usuariosListar(tipoUsr, 1);

    printf("\n");
    if (opt < 0 || opt > 2) printf("\nOpcion invalida!");
    printf("\nSeleccione una operacion: \n");
    printf("[1] Activar\n");
    printf("[2] Desactivar\n");
    printf("[0] Salir\n");
    printf("Opcion: ");
    scanf("%d", &opt);
    clearStdin();
    if (opt == 0) return;
  } while (opt < 0 || opt > 2);

  printf("Ingrese el ID de usuario: ");
  scanf("%d", &idUsr);
  clearStdin();

  while (fread(&usuarioReg, sizeof(usuarioReg), 1, dbFp)) {
    if (usuarioReg.id == idUsr && usuarioReg.tipo == tipoUsr) {
      usuarioReg.estado = (opt == 1) ? 1 : 0;
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
      usuarioReg.id, usuarioReg.nombreCompleto,
      usuarioReg.username, tipoUsrString[usuarioReg.tipo],
      (opt == 1) ? "Activo" : "Inactivo"
    );

    // Logs
    strcpy(logMessage, "Cambio el estado del usuario '");
    strcat(logMessage, usuarioReg.username);
    strcat(logMessage, "' (Id: ");
    sprintf(strNum,"%d", usuarioReg.id);
    strcat(logMessage, strNum);
    strcat(logMessage, " | Tipo: ");
    strcat(logMessage, tipoUsrString[usuarioReg.tipo]);
    strcat(logMessage, ") a ");
    if (usuarioReg.estado == 0) strcat(logMessage, "IN");
    strcat(logMessage, "ACTIVO");
    logger(loggedUser, logMessage);
  };

  getchar();
  fclose(dbFp);
}
