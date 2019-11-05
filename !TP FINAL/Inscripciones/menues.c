// ####################################################################################################################
// ####                                                  Menues                                                    ####
// ####################################################################################################################

void menuAdmMaterias(usuario loggedUser) {
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
    switch (opt) {
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

void menuAdmProfesores(usuario loggedUser) {
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
    switch (opt) {
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

void menuAdmAlumnos(usuario loggedUser) {
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
    switch (opt) {
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
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
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
    scanf("%d", &opt);
    clearStdin();
    switch (opt) {
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
    printf("[0] Salir\n");
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
    default:
      printf("Opcion incorrecta!\n");
      printf("Por favor, seleccione una opcion valida\n");
      break;
    }
  } while (opt != 0);
  return;
}