// ####################################################################################################################
// ####                                                  Listados                                                  ####
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