// ####################################################################################################################
// ####                                               Declaraciones                                                ####
// ####################################################################################################################

// helpers.c
char *getstring(char *buf, size_t size);
void cargarDesdeArchivo(usuario loggedUser, char *archivoTexto, tipoEntidad tEntidad);
void logger(usuario loggedUser, char *action);
void login();

// menues.c
void menuAdmin(usuario loggedUser);
void menuAdmMaterias(usuario loggedUser);
void menuAdmProfesores(usuario loggedUser);
void menuAdmAlumnos(usuario loggedUser);
void menuAlumno(usuario loggedUser);
void menuProfesor(usuario loggedUser);

// listados.c
void usuariosListar(tipoUsuario tipo, int mostrarTodos);
// void usuarioConsultarMaterias(int idUsuario);
void materiasListar();
// void materiaConsultarProfesor(int idMateria);
// void materiaConsultarAlumnos(int idMateria);

// abms.c
void usuarioAlta();
void usuarioActivarDesactivar(usuario loggedUser, tipoUsuario tipoUsr);
// void usuarioModificar(int idUsuario);
// void usuarioAsignarMateria(int idUsuario, int idMateria);
// void usuarioDesasignarMateria(int idUsuario, int idMateria);
// void materiaAlta();
// void materiaBaja(int idMateria);
// void materiaModificar(int idMateria);

// Listan las entidades y devuelven el ID de una de ellas
// int seleccionarMateria();
// int seleccionarUsuario(tipoUsuario tipo);
