#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
// Reemplazo para conio.h en linux
// #include <ncurses.h>
#include <string.h>
// #define p printf
// #define s scanf
#define CLEAR "cls"
// #define CLEAR "clear"
#define BIN_FILE_NAME "Clase8.Ejercicio1.dat"

// Reemplazo para fflush(stdin);
void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

// Para la insercion de elementos unicos
typedef struct nodo {
	int dato;
	struct nodo *sig;
} nodo;

nodo * ingresoDato (int x) {
	nodo *q;
	q = (nodo*) malloc(sizeof(nodo));
	q->dato = x;
	return q;
}

nodo *ingresarDato(void) {
  int nro;
  nodo *q;
  q = (nodo *)malloc(sizeof(nodo));
  printf("\n Ingrese dato:");
  scanf("%d", &nro);
  q->dato = nro;
  system("cls");
  q->sig = NULL;
  return q;
}

void apilar(nodo **p, nodo *q) {
	q->sig = *p;
	*p = q;
}

nodo* desapilar(nodo **p) {
	nodo *aux;
	aux = *p;
	*p = (*p)->sig;
	return aux;
}

nodo desapilar(nodo **p) {
  nodo dato, *aux;
  aux = *p;
  dato = **p;
  *p = (*p)->sig;
  free(aux);
  return dato;
}

void recorrerPila(nodo *p) {
	while(p) {
		printf("%d", p->dato);
		p = p->sig;
	}
}

void ordenarPila(nodo *pila) {
	// Pila auxiliar, pila de salida
	nodo *pAux2, *pOut;
	// Nodo auxiliar
	nodo *max, *aux;


	

	



}

void palindromizar(nodo **pila) {
	nodo *pilaAux, *nodoAux;
	pilaAux = *pila;

	while(*pila) {
		nodoAux = desapilar(*pila);
		apilar(pilaAux, nodoAux);
	}

	*pila = pilaAux;
}

int main(){
	return 0;
}

