// ####################################################################################################################
// ####                                               Declaraciones                                                ####
// ####################################################################################################################

// helpers.c
char *getstring(char *buf, size_t size);
void cargarDesdeArchivo(usuario loggedUser, char *archivoTexto, tipoEntidad tEntidad);
void logger(usuario loggedUser, char *action);
void login();
void crearDb();
materia seleccionarMateria();
materia getMateriaById(int idMateria);
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
void materiaConsultarProfesor(usuario loggedUser, materia mat);
void materiaConsultarAlumnos(usuario loggedUser, materia mat);
void profesorConsultarAlumnosMateria(usuario loggedUser);

// abms.c
void usuarioAlta(usuario loggedUser, tipoUsuario tipoUsr);
void usuarioEditar(usuario loggedUser, tipoUsuario tipoUsr);
int usuarioEditarSelected(usuario *usr);
void alumnoAsignarMateria(usuario loggedUser);
void profesorAsignarMateria(usuario loggedUser);
// void usuarioDesasignarMateria(usuario loggedUser, int idUsuario, int idMateria);
void materiaAlta(usuario loggedUser);
void materiaEditar(usuario loggedUser);
int materiaEditarSelected(materia *mat);

