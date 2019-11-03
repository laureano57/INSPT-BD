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

struct materia {
    int idMateria;
    char nombreMateria[30];
    //int stock;
    //float precio;
    char valida;
};

// Linux o windows
#define CLEAR "clear"
// #define CLEAR "cls"

void crearbin(FILE *archivo) {
    if ( ( archivo = fopen( "stock.dat", "w+b" ) ) == NULL )
        printf( "No pudo abrirse el archivo.\n" );
    else {
        printf("Archivo creado exitosamente.\n");
        fclose( archivo );
    }
    getchar();
}

char *getstring(char *buf, size_t size) {
    if (buf != NULL && size > 0) {
        if (fgets(buf, size, stdin)) {
            buf[strcspn(buf, "\n")] = '\0';
            return buf;
        }
        *buf = '\0';  /* clear buffer at end of file */
    }
    return NULL;
}

void clearStdin(void) {
    int c;
    do
        c = getchar();
    while (c != '\n' && c != EOF);
}

int menu() {
    char opcion;
    printf("Elige una opcion:\n");
    printf("C - Crear el archivo\n");
    printf("G - Guardar Materia\n");
    printf("E - Listar Materias\n");
    printf("B - Buscar Materias\n");
    //printf("P - Modificar precio\n");
    printf("O - Dar de baja logica de una materia\n");
    printf("X - Actualizar archivo eliminando bajas de materias\n");
    printf("S - Salir\n");
    scanf("%c", &opcion);
    clearStdin();
    return toupper(opcion);
}

void menuAdmin() {
    char opt;
    do {
        system(CLEAR);
        printf("#######################################\n");
        printf("##         Menu Administrador        ##\n");
        printf("#######################################\n");
        printf("[1] Administrar materias\n");
        printf("[2] Administrar profesores\n");
        printf("[3] Administrar alumnos\n");
        printf("[0] Salir\n");
        scanf("%c", &opt);
        clearStdin();
        switch(opt) {
        case 0:
            return;
            break;
        case 1:
            menuAdmMaterias();
            break;
        case 2:
            menuAdmProfesores();
            break;
        case 3:
            menuAdmAlumnos();
            break;
        default:
            printf("Opcion incorrecta!\n");
            printf("Por favor, seleccione una opcion valida\n");
            break;
        }
    } while (opt < 0 || opt > 3);
}

void guardarDatos(FILE *archivo) {
    struct materia mat;
    archivo = fopen("stock.dat", "a+b");
    fseek(archivo, 0, SEEK_END);
    clearStdin();
    printf("Ingrese el codigo numerico de la materia: \n");
    scanf("%d", &mat.idMateria);
    clearStdin();
    printf("Ingrese nombre de la materia: \n");
    getstring(mat.nombreMateria, 30);
    clearStdin();
    //printf("Ingrese stock: \n");
    //scanf("%d",&prod.stock);
    clearStdin();
    /*while(prod.stock<0){
        printf("El stock de un producto no puede ser con valor negativo,\npor favor ingrese un valor correcto\n");
        printf("Ingrese stock: \n");
        scanf("%d",&prod.stock);
    }*/
    /*printf("Ingrese el precio: \n");
    scanf("%f",&prod.precio);
    while(prod.precio<=0){
        printf("El precio de un producto debe ser mayor a cero, introduzca un valor correcto\n");
        printf("Ingrese precio: \n");
        scanf("%f",&prod.precio);
    }*/
    mat.valida = 'S';
    fwrite(&mat, sizeof(struct materia), 1, archivo);
    fclose(archivo);
    getchar();
}

void emitirDatos(FILE *archivo, int *cantprod) {
    struct materia mat;
    int i = 0;
    archivo = fopen("stock.dat", "rb");
    fread(&mat, sizeof(struct materia), 1, archivo);
    fseek(archivo, 0, SEEK_END);
    *cantprod = ftell(archivo) / sizeof(struct materia);
    printf("*** Cantidad de Materias almacenados: %d ***\n", *cantprod);
    printf("Id Materia\tNombre\tActivo\n");
    while(i < (*cantprod)) {
        fseek(archivo, i * sizeof(struct materia), SEEK_SET);
        fread(&mat, sizeof(struct materia), 1, archivo);
        printf( "%-14d%-10s %8c\n", mat.idMateria, mat.nombreMateria, mat.valida);
        i++;
    }
    fclose(archivo);
    getchar();
}

int leerMatr() {
    int matr;
    printf("Ingrese codigo numerico de la materia: \n");
    scanf("%d", &matr);
    return matr;
}

void buscarMateria(FILE *archivo) {
    struct materia mat;
    int matr;

    matr = leerMatr();
    archivo = fopen("stock.dat", "r+b");
    while(!feof(archivo)) {
        if (fread(&mat, sizeof(struct materia), 1, archivo) == 1) {
            if(matr == mat.idMateria) {
                printf("Nombre: %s\nID: %d\n\n", mat.nombreMateria, mat.idMateria);
            }
        }
    }
    fclose(archivo);
    getchar();
}

/*void modificarPrecio(FILE *archivo){
    int art;
    float nuevoPrecio,temporal;
    struct producto prod;
    FILE * temp;
art=leerArt();
printf("Ingrese nuevo precio\n");
scanf("%f",&nuevoPrecio);
    while(nuevoPrecio<=0){
        printf("El precio debe ser mayor a 0, ingrese nuevamente\n");
        printf("Ingrese nuevo precio\n");
        scanf("%f",&nuevoPrecio);
    }
    archivo=fopen("stock.dat","r+b");
    temp=fopen("stock.temp","wb");
    fseek(archivo,0,SEEK_SET);
    while(fread(&prod,sizeof(struct producto ),1,archivo)){
        if(prod.articulo==art){
            prod.precio=nuevoPrecio;
        }
        fwrite(&prod,sizeof(struct producto),1,temp);
    }
    fclose(archivo);
    fclose(temp);
    remove("stock.dat");
    rename("stock.temp","stock.dat");
    remove("stock.temp");
    printf("\n***--Precio modificado correctamente\n--***");
    system("pause");
}*/

void bajaLogica(FILE *archivo) {
    int matr;
    struct materia mat;
    matr = leerMatr();
    printf("\nID le%cdo es: %d", 161, matr); //control
    archivo = fopen("stock.dat", "r+b");
    while(!feof(archivo)) {
        if(fread(&mat, sizeof(struct materia), 1, archivo) == 1) {
            if(matr == mat.idMateria) {
                mat.valida = 'N';
                fseek(archivo, -sizeof(struct materia), SEEK_CUR);
                fwrite(&mat, sizeof(struct materia), 1, archivo);
                fflush(archivo);
            }
        }
    }
    fclose(archivo);
    printf("\n***--La materia %d se dio de baja correctamente--***\n", matr);
    getchar();
}

void bajaFisica(FILE *archivo) {
    FILE *temp;
    struct  materia mat;
    archivo = fopen("stock.dat", "rb");
    temp = fopen("stock.temp", "w+b");
    rewind(archivo);
    while(fread(&mat, sizeof(struct materia), 1, archivo)) {
        if(mat.valida == 'S') {
            fwrite(&mat, sizeof(struct materia ), 1, temp);
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
        opcion = menu();
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
            buscarMateria(archivo);
            break;
        /*case 'P':
            modificarPrecio(archivo);
            break;*/
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
