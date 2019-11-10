// ####################################################################################################################
// ####                                               Declaraciones                                                ####
// ####################################################################################################################

// helpers.c
char *getstring(char *buf, size_t size);
void cargarDesdeArchivo(usuario loggedUser, char *archivoTexto, tipoEntidad tEntidad);
void logger(usuario loggedUser, char *action);
void login();
// Listan las entidades y devuelven una de ellas
// materia seleccionarMateria();
// materia getMateriaById(int idMateria);
usuario seleccionarUsuario(tipoUsuario tipo);
usuario getUsuarioById(int idUsr, tipoUsuario tipo);

// menues.c
void menuAdmin(usuario loggedUser);
void menuAdmMaterias(usuario loggedUser);
void menuAdmProfesores(usuario loggedUser);
void menuAdmAlumnos(usuario loggedUser);
void menuAlumno(usuario loggedUser);
void menuProfesor(usuario loggedUser);

// listados.c
void usuariosListar(tipoUsuario tipo, int mostrarTodos);
void usuarioConsultarMaterias(usuario loggedUser, usuario usr);
void materiasListar(int mostrarTodas);
// void materiaConsultarProfesor(int idMateria);
// void materiaConsultarAlumnos(int idMateria);

// abms.c
void usuarioAlta();
void usuarioEditar(usuario loggedUser, tipoUsuario tipoUsr);
int usuarioEditarSelected(usuario *usr);
// void usuarioAsignarMateria(int idUsuario, int idMateria);
// void usuarioDesasignarMateria(int idUsuario, int idMateria);
// void materiaAlta();
// void materiaBaja(int idMateria);
void materiaEditar(usuario loggedUser);
int materiaEditarSelected(materia *mat);

