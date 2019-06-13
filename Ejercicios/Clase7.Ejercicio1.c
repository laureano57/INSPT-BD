#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
// Reemplazo para conio.h en linux
// #include <ncurses.h>
#include <string.h>
#define p printf
#define s scanf
#define CLEAR "cls"
// #define CLEAR "clear"
#define BIN_FILE_NAME "Clase7.Ejercicio1.dat"

// Reemplazo para fflush(stdin);
void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

// Para los ejercics 1-3
// typedef struct elemento {
// 	int dato;
// 	struct elemento *sig;
// } nodo;

// Para la insercion de elementos unicos
typedef struct elemento {
	int dato;
	int cont;
	struct elemento *sig;
} nodo;

// struct lista {
// 	int dato;
// 	struct lista *sig;
// } lista;

// typedef struct lista nodo;

// typedef struct nodo {
// 	int dato;
// 	struct lista *sig;
// } nodo;

// 1) Ingresar datos en una lista simple por la cola de la misma
// 2) Ingresar datos en una lista simple por la cabeza de la misma
// 3) Ingresar datos en una lista simple en orden
// 4) Ingresar datos sin repeticiones
// 5) Borrar un elemento de la lista
// 6) Ingresar datos numericos en una lista y extraer de la lista original los nodos con datos impares e insertarlos en una nueva lista
// 7) Dada una lista con los primeros N numeros naturales, y utilizando el metodo de la "criba de eratostenes" generar los numeros primos que esten en la lista original
// 8) Ingresar datos en dos listas diferentes y generar la insercion en orden en una tercera lista

void insertar(nodo **, int);
void mostrar(nodo*);
void eliminar(nodo**);
nodo *buscar(nodo*, int);
void borrarNodo(nodo **, int);
void creapar(nodo **x,nodo **y);

nodo *nuevoNodo(int);

int main(){
	int cant, n, i;
	nodo *cabeza, *aux = NULL, *pares = NULL;

	cabeza = NULL;

	srand(time(NULL));
	p("\nIngrese cantidad de datos: ");
	s("%d", &cant);
	
	for (i = 0; i < cant; i++) {
		p("\nIngrese %d %c dato: ", i+1, 167);
		s("%d", &n);
		insertar(&cabeza, n);
	}
	
	p("\n\nLista cargada exitosamente\n\n");
	
	mostrar(cabeza);
	fflush(stdin);
	creapar(&cabeza, &pares);
	mostrar(pares);
	getchar();
	// p("\nIngrese dato a buscar: ");
	// s("%d", &n);
	// aux = buscar(cabeza, n);
	// if (aux) {
	// 	p("\nEl numero %d fue encontrado", n);
	// 	p("\nPresione una tecla para eliminar el valor %d", n);
	// 	getchar();
	// 	borrarNodo(&cabeza, n);
	// 	p("\nLista resultante:");
	// 	mostrar(cabeza);
	// } else p("\nEl valor %d no fue encontrado", n);

	p("\nPresione una tecla para eliminar los nodos\n\n");
	eliminar(&cabeza);
	free(cabeza);
	system(CLEAR);

	return 0;
}

nodo * nuevoNodo(int x) {
	nodo *a;
	a = (nodo*)malloc(sizeof(nodo));
	a->dato = x;
	a->cont = 1;
	a->sig = NULL;
	return a;
}

// Insercion al final
// void insertar(nodo **x, int y) {
// 	nodo * nuevo;
// 	if (*x == NULL) {
// 		nuevo = nuevoNodo(y);
// 		*x = nuevo;
// 	} else insertar(&(*x)->sig, y);
// }

// Insercion al inicio
// void insertar(nodo **x, int y) {
// 	nodo * nuevo;
	
// 	if (*x == NULL) {
// 		nuevo = nuevoNodo(y);
// 		*x = nuevo;
// 	} else {
// 		nuevo = nuevoNodo(y);
// 		nuevo->sig = *x;
// 		*x = nuevo;
// 	}
// }

// Insertar en orden
// void insertar(nodo **x, int y) {
// 	nodo * nuevo;
// 	if (*x == NULL) {
// 		nuevo = nuevoNodo(y);
// 		*x = nuevo;
// 	} else if (y < (*x)->dato) {
// 		nuevo = nuevoNodo(y);
// 		nuevo->sig = *x;
// 		*x = nuevo;
// 	} else {
// 		insertar(&(*x)->sig, y);
// 	}
// }

// Insercion unica con contador
void insertar(nodo **x, int y) {
	nodo * nuevo;
	if (*x == NULL) {
		nuevo = nuevoNodo(y);
		*x = nuevo;
	} else if (y < (*x)->dato) {
		nuevo = nuevoNodo(y);
		nuevo->sig = *x;
		*x = nuevo;
	} else if (y == (*x)->dato) {
		(*x)->cont++;
	} else {
		insertar(&(*x)->sig, y);
	}
}

void mostrar(nodo *x) {
	if (x) {
		// Para insercion normal
		// p("%3d", x->dato);
		// Para la insercion unica
		p("%3d(%d)", x->dato, x->cont);
		mostrar(x->sig);
	}
}

void eliminar(nodo **x) {
	nodo *aux;
	if (*x) {
		aux = *x;
		p("\nNodo a eliminar: %3d", (*x)->dato);
		getchar();
		*x = (*x)->sig;
		free(aux);
		eliminar(x);
	}
}

nodo *buscar(nodo *x, int y) {
	if (!x) return (NULL);
	else if (y == x->dato) return x;
	else (buscar(x->sig, y));
}

void borrarNodo(nodo **x, int y) {
	nodo *aux;
	if (*x) {
		aux = *x;
		if ((*x)->dato == y) {
			p("\nNodo a eliminar: %3d (%2d)", (*x)->dato, (*x)->cont);
			getchar();
			*x = aux->sig;
			free(aux);
		} else borrarNodo(&(*x)->sig, y);
	}
}

// Provista por lovallo
void creapar(nodo **x,nodo **y) {
    if (*x) {
       if ((*x)->dato % 2 == 0) {
            *y = *x;
            *x = (*x)->sig;
            (*y)->sig = NULL;
            p("\nNodo a extraer de la lista original:%3d (%d)\n",(*y)->dato,(*y)->cont);
			getch();
            creapar(&(*x) ,&(*y)->sig);
        } else creapar(&(*x)->sig, y);
    }
}
