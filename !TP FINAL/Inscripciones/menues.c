// ####################################################################################################################
// ####                                                  Menues                                                    ####
// ####################################################################################################################

void menuAlumno(usuario loggedUser) {
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
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      system(CLEAR);
      usuarioConsultarMaterias(loggedUser, loggedUser);
      break;
    case 2:
      system(CLEAR);
      alumnoAsignarMateria(loggedUser);
      break;
    // case 3:
    //   usuarioDesasignarMateria();
    //   break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  system(CLEAR);
  printf("Saliendo...");
  return;
}

void menuProfesor(usuario loggedUser) {
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
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      system(CLEAR);
      usuarioConsultarMaterias(loggedUser, loggedUser);
      break;
    case 2:
      system(CLEAR);
      profesorConsultarAlumnosMateria(loggedUser);
      break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  system(CLEAR);
  printf("Saliendo...");
  return;
}

void menuAdmin(usuario loggedUser) {
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
    printf("[6] Cargar materia_alumno desde archivo\n");
    printf("[7] Cargar materia_profesor desde archivo\n");
    printf("[0] Salir\n");
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      menuAdmMaterias(loggedUser);
      break;
    case 2:
      menuAdmProfesores(loggedUser);
      break;
    case 3:
      menuAdmAlumnos(loggedUser);
      break;
    case 4:
      system(CLEAR);
      printf("####  Cargar usuarios desde archivo  ####\n");
      printf("Ingrese el nombre del archivo: ");
      getstring(fileName, sizeof fileName);
      tEntidad = USUARIO;
      cargarDesdeArchivo(loggedUser, fileName, tEntidad);
      break;
    case 5:
      system(CLEAR);
      printf("####  Cargar materias desde archivo  ####\n");
      printf("Ingrese el nombre del archivo: ");
      getstring(fileName, sizeof fileName);
      tEntidad = MATERIA;
      cargarDesdeArchivo(loggedUser, fileName, tEntidad);
      break;
    case 6:
      system(CLEAR);
      printf("####  Cargar materia_alumno desde archivo  ####\n");
      printf("Ingrese el nombre del archivo: ");
      getstring(fileName, sizeof fileName);
      tEntidad = MATERIA_ALUMNO;
      cargarDesdeArchivo(loggedUser, fileName, tEntidad);
      break;
    case 7:
      system(CLEAR);
      printf("####  Cargar materia_profesor desde archivo  ####\n");
      printf("Ingrese el nombre del archivo: ");
      getstring(fileName, sizeof fileName);
      tEntidad = MATERIA_PROFESOR;
      cargarDesdeArchivo(loggedUser, fileName, tEntidad);
      break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  system(CLEAR);
  printf("Saliendo...");
  return;
}

void menuAdmMaterias(usuario loggedUser) {
  int opt;
  materia mat;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                           Administrar materias                          ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar materias\n");
    printf("[2] Alta de materias\n");
    printf("[3] Editar una materia\n");
    printf("[4] Consultar profesor asignado a una materia\n");
    printf("[5] Consultar alumnos inscriptos a una materia\n");
    printf("[0] Volver\n");
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      materiasListar(0);
      getchar();
      break;
    case 2:
      materiaAlta(loggedUser);
      break;
    case 3:
      materiaEditar(loggedUser);
      break;
    case 4:
      mat = seleccionarMateria();
      if (mat.id == -1) break;
      system(CLEAR);
      materiaConsultarProfesor(loggedUser, mat);
      break;
    case 5:
      mat = seleccionarMateria();
      if (mat.id == -1) break;
      system(CLEAR);
      materiaConsultarAlumnos(loggedUser, mat);
      break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  return;
}

void menuAdmProfesores(usuario loggedUser) {
  int opt;
  usuario profesorUsr;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                          Administrar profesores                         ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar profesores\n");
    printf("[2] Alta de profesores\n");
    printf("[3] Editar un profesor\n");
    printf("[4] Listar materias asignadas a un profesor\n");
    printf("[5] Asignar una materia a un profesor\n");
    printf("[6] Des-asignar una materia a un profesor\n");
    printf("[0] Volver\n");
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      system(CLEAR);
      // Lista solo usuarios activos
      usuariosListar(PROFESOR, 0);
      getchar();
      break;
    case 2:
      usuarioAlta(loggedUser, PROFESOR);
      break;
    case 3:
      usuarioEditar(loggedUser, PROFESOR);
      break;
    case 4:
      system(CLEAR);
      profesorUsr = seleccionarUsuario(PROFESOR);
      if (profesorUsr.id == -1) break;
      system(CLEAR);
      usuarioConsultarMaterias(loggedUser, profesorUsr);
      break;
    case 5:
      system(CLEAR);
      profesorAsignarMateria(loggedUser);
      break;
    // case 6:
    //   usuarioDesasignarMateria();
    //   break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  return;
}

void menuAdmAlumnos(usuario loggedUser) {
  int opt;
  usuario alumnoUsr;
  do {
    system(CLEAR);
    printf("#############################################################################\n");
    printf("##                         Sistema de inscripciones                        ##\n");
    printf("##                            Administrar alumnos                          ##\n");
    printf("#############################################################################\n");
    printf("[1] Listar alumnos\n");
    printf("[2] Alta de alumnos\n");
    printf("[3] Editar un alumno\n");
    printf("[4] Listar materias inscriptas de un alumno\n");
    printf("[5] Inscribir alumno a una materia\n");
    printf("[6] Des-inscribir alumno de una materia\n");
    printf("[0] Volver\n");
    printf("\nOpcion: ");
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
    case 0:
      break;
    case 1:
      system(CLEAR);
      // Lista solo usuarios activos
      usuariosListar(ALUMNO, 0);
      getchar();
      break;
    case 2:
      usuarioAlta(loggedUser, ALUMNO);
      break;
    case 3:
      usuarioEditar(loggedUser, ALUMNO);
      break;
    case 4:
      system(CLEAR);
      alumnoUsr = seleccionarUsuario(ALUMNO);
      if (alumnoUsr.id == -1) break;
      system(CLEAR);
      usuarioConsultarMaterias(loggedUser, alumnoUsr);
      break;
    case 5:
      system(CLEAR);
      alumnoAsignarMateria(loggedUser);
      break;
    // case 6:
    //   usuarioDesasignarMateria();
    //   break;
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      getchar();
      break;
    }
  } while (opt != 0);
  return;
}
