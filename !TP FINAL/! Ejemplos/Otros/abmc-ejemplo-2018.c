/*
ABML
1. ejecutar el archivo fuente.
2. comprobar sus funciones
3. analizar y comentar el c�digo
*/
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<string.h>
#include<ctype.h>

struct producto {
    int articulo;
    char marca[30];
    int stock;
    float precio;
    char valido;
};

void clearStdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

void crearbin(FILE *archivo) {
    if ( ( archivo = fopen( "stock.dat", "w+b" ) ) == NULL )
        printf( "No pudo abrirse el archivo.\n" );
    else {
        printf("Archivo creado exitosamente.\n");
        fclose( archivo );
    }
    getchar();
}

int Menu() {
    char opcion;
    printf("Elige una opci%cn:\n", 162);
    printf("C - Crear el archivo\n");
    printf("G - Guardar producto\n");
    printf("E - Listar productos\n");
    printf("B - Buscar producto\n");
    printf("P - Modificar precio\n");
    printf("O - Dar de baja logica de un producto\n");
    printf("X - Actualizar archivo eliminando bajas de productos\n");
    printf("S - Salir\n");
    scanf("%c", &opcion);
    clearStdin();
    return toupper(opcion);
}

void guardarDatos(FILE *archivo) {
    struct producto prod;
    archivo = fopen("stock.dat", "a+b");
    fseek(archivo, 0, SEEK_END);
    clearStdin();
    printf("Ingrese c%cdigo num%crico del art%cculo: \n", 162, 130, 161);
    scanf("%d", &prod.articulo);
    clearStdin();
    printf("Ingrese marca del producto: \n");
    fgets(prod.marca, 60, stdin);
    getchar();
    clearStdin();
    printf("Ingrese stock: \n");
    scanf("%d", &prod.stock);
    clearStdin();
    while(prod.stock < 0) {
        printf("El stock de un producto no puede ser con valor negativo,\npor favor ingrese un valor correcto\n");
        printf("Ingrese stock: \n");
        scanf("%d", &prod.stock);
    }
    printf("Ingrese el precio: \n");
    scanf("%f", &prod.precio);
    while(prod.precio <= 0) {
        printf("El precio de un producto debe ser mayor a cero, introduzca un valor correcto\n");
        printf("Ingrese precio: \n");
        scanf("%f", &prod.precio);
    }
    prod.valido = 'S';
    fwrite(&prod, sizeof(struct producto), 1, archivo);
    fclose(archivo);
    getchar();
}

void emitirDatos(FILE *archivo, int *cantprod) {
    struct producto prod;
    int i = 0;
    archivo = fopen("stock.dat", "rb");
    fread(&prod, sizeof(struct producto), 1, archivo);
    fseek(archivo, 0, SEEK_END);
    *cantprod = ftell(archivo) / sizeof(struct producto);
    printf("*** Cantidad de art%cculos almacenados: %d ***\n", 161, *cantprod);
    printf( "Art%cculo\tMarca\t\tStock\t\tPrecio\tActivo\n", 161 );
    while(i < (*cantprod)) {
        fseek(archivo, i * sizeof(struct producto), SEEK_SET);
        fread(&prod, sizeof(struct producto), 1, archivo);
        printf( "%-14d%-10s%13d%15.2lf %8c\n", prod.articulo, prod.marca, prod.stock, prod.precio, prod.valido);
        i++;
    }
    fclose(archivo);
    getchar();
}

int leerArt() {
    int art;
    printf("Ingrese c%cdigo num%crico del art%cculo: \n", 162, 130, 161);
    scanf("%d", &art);
    return art;
}

void buscarProducto(FILE *archivo) {
    struct producto prod;
    int art;

    art = leerArt();
    archivo = fopen("stock.dat", "r+b");
    while(!feof(archivo)) {
        if (fread(&prod, sizeof(struct producto), 1, archivo) == 1) {
            if(art == prod.articulo) {
                printf("Marca: %s\nArt%cculo: %d\nStock: %d\nPrecio: %.2f\n", prod.marca, 161, prod.articulo, prod.stock, prod.precio);
            }
        }
    }
    fclose(archivo);
    getchar();
}

void modificarPrecio(FILE *archivo) {
    int art;
    float nuevoPrecio, temporal;
    struct producto prod;
    FILE *temp;
    art = leerArt();
    printf("Ingrese nuevo precio\n");
    scanf("%f", &nuevoPrecio);
    while(nuevoPrecio <= 0) {
        printf("El precio debe ser mayor a 0, ingrese nuevamente\n");
        printf("Ingrese nuevo precio\n");
        scanf("%f", &nuevoPrecio);
    }
    archivo = fopen("stock.dat", "r+b");
    temp = fopen("stock.temp", "wb");
    fseek(archivo, 0, SEEK_SET);
    while(fread(&prod, sizeof(struct producto ), 1, archivo)) {
        if(prod.articulo == art) {
            prod.precio = nuevoPrecio;
        }
        fwrite(&prod, sizeof(struct producto), 1, temp);
    }
    fclose(archivo);
    fclose(temp);
    remove("stock.dat");
    rename("stock.temp", "stock.dat");
    remove("stock.temp");
    printf("\n***--Precio modificado correctamente\n--***");
    system("pause");
}

void bajaLogica(FILE *archivo) {
    int art;
    struct producto prod;
    art = leerArt();
    printf("\narticulo le%cdo es: %d", 161, art); //control
    archivo = fopen("stock.dat", "r+b");
    while(!feof(archivo)) {
        if(fread(&prod, sizeof(struct producto), 1, archivo) == 1) {
            if(art == prod.articulo) {
                prod.valido = 'N';
                fseek(archivo, -sizeof(struct producto), SEEK_CUR);
                fwrite(&prod, sizeof(struct producto), 1, archivo);
                fflush(archivo);
            }
        }
    }
    fclose(archivo);
    printf("\n***--El producto %d se dio de baja correctamente--***\n", art);
    getchar();
}

void bajaFisica(FILE *archivo) {
    FILE *temp;
    struct  producto prod;
    archivo = fopen("stock.dat", "rb");
    temp = fopen("stock.temp", "w+b");
    rewind(archivo);
    while(fread(&prod, sizeof(struct producto), 1, archivo)) {
        if(prod.valido == 'S') {
            fwrite(&prod, sizeof(struct producto ), 1, temp);
        }
    }
    fclose(temp);
    fclose(archivo);
    remove("stock.dat");
    rename("stock.temp", "stock.dat");
    remove("stock.temp");
    printf("\n***--Archivo actualizado--***\n");
}

int main() {
    char opcion;
    int i, cantprod;
    FILE *archivo;
    do {
        opcion = Menu();
        switch(opcion) {
        case 'C':
            crearbin(archivo);
            break;
        case 'G':
            guardarDatos(archivo);
            break;
        case 'E':
            emitirDatos(archivo, &cantprod);
            break;
        case 'B':
            buscarProducto(archivo);
            break;
        case 'P':
            modificarPrecio(archivo);
            break;
        case 'O':
            bajaLogica(archivo);
            break;
        case 'X':
            bajaFisica(archivo);
            break;
        }
    } while(opcion != 'S');
    return 0;
}
