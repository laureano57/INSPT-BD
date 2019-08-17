#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define p printf
#define s scanf

typedef struct elemento {
	int dato;
	struct elemento *adel;
	struct elemento *atra;
} nodo;

nodo *buscar(nodo*, int);
nodo *nuevonodo(int);

void busborrar(nodo**, int);
void insertar(nodo**, int);
void listar(nodo*);
void eliminar(nodo**);

int main() {
  int i, cant, num;
  nodo *cabeza, *aux;

  system("cls");
  cabeza = NULL;
  srand(time(NULL));
  
  p("\n INGRESE LA CANTIDAD DE DATOS:");
  s("%d",&cant);
  
  for (i = 0; i < cant; i++) {
    system("cls");
    p("\n INGRESE %d%c DATO:", i + 1, 167);
    s("%d", &num);
    insertar(&cabeza, num);
  }

  p("\n\n LISTA INGRESADA\n\n");
  listar(cabeza);

  // if (cabeza) {
  //   p("\n PRESIONE UNA TECLA PARA BORRAR LOS NODOS!!!!");
  //   getch();
  //   eliminar(&cabeza);
  // }

  p("\nIngrese un dato a buscar: ");
  s("%d", &num); // SEGUIR ACA
  // aux = buscar(cabeza, num);
  // if (aux == NULL) {
  //   p("\nNo se encontro el dato ingresado");
  // } else {
  //   p("\nSe encontro el dato: %d",  aux->dato);
  //   p("\nPosicion: %p",  *aux);
  // }

  busborrar(&cabeza, num);

  getch();
  system("cls");
  free(cabeza);

  return (0);
}

void insertar(nodo **x, int y) {
  nodo * nuevo;

  if ( *x == NULL || (*x)->dato > y) {
    nuevo = nuevonodo(y);
    nuevo->adel = *x;
    nuevo->atra = *x;
    *x = nuevo;
  } else insertar(&(*x)->adel, y);
}

nodo * nuevonodo(int x) {
  nodo *a;
  a = (nodo*)malloc(sizeof(nodo));
  a->dato = x;
  a->adel = a->atra = NULL;
  return a;
}

void listar(nodo *x) {
if (x) {
    p("%4d",x->dato);
    listar(x->adel);
  }
}

nodo * buscar(nodo *x, int y) {
	if (!x) return (NULL);
    else if (y == x->dato) return(x);
    else return (buscar(x->adel, y));
}

void eliminar(nodo **x) {
	nodo *aux;
	if (*x) {
		aux = *x;
		p("\nNODO A ELIMINAR:%3d", (*x)->dato);
		getch();
		*x = aux->adel;
		free(aux);
		eliminar(x);
	}
}

void busborrar(nodo** cabeza, int dato) {
  nodo *nAux;
  int iAux;

  p("Ingrese un dato a eliminar de la lista: ");
  s("%d", &iAux);
  nAux = buscar(*cabeza, iAux);

  if (nAux != NULL) {
    eliminar(&nAux);
    p("Se elimino el dato %d\n", dato);
  } else {
    p("No se encontro el dato %d\n", dato);
  }
}
