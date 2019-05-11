#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linux o windows
#include <ncurses.h>
// #include <conio.h>

// Linux o windows
#define CLEAR "clear"
// #define CLEAR "cls"

#define p printf
#define s scanf

#define ART_FILE_NAME "Clase4.Ejercicio2.Articulos.dat"
#define CLI_FILE_NAME "Clase4.Ejercicio2.Clientes.dat"
#define FACT_FILE_NAME "Clase4.Ejercicio2.Facturas.dat"

// Headers
void cargarArticulos(char fileName[]);
void cargarClientes(char fileName[]);
void mostrarArticulos(char fileName[]);
void mostrarClientes(char fileName[]);
void mostrarFacturas(char fileName[]);
void facturar(char articulosFile[], char clientesFile[], char facturasFile[]);
float facturarProducto(int codArt, int cant, char articulosFile[]);
void menuAltas();
void menuListados();
void menuPrincipal();

// reemplazo de fflush(stdin)
void clearStdin() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int fileExist(FILE * fp, char fileName[]) {
    if (fp == NULL) {
        p("Error: El archivo %s no existe", fileName);
        return 0;
    }
    return 1;
}

// Structs
typedef struct regart {
    int cod_art;
    char nom_art[20];
    float pre_art;
    int sto_art;
    float fact_art;
} regart;

typedef struct regcli {
    int cod_cli;
    char nom_cli[20];
    float cuenta;
} regcli;

typedef struct regfact {
    int cod;
    int cod_cli;
    char nom_cli[20];
    float total;
} regfact;


// Funciones
void cargarArticulos(char fileName[]) {
    FILE * fp;
    regart reg;
    int seguir, articuloExiste, codArt;

    // Si no existe el archivo lo crea, sino lo abre para r/w
    if ((fp = fopen(fileName, "rb+")) == NULL) {
        fp = fopen(fileName, "wb+");
    } else {
        fp = fopen(fileName, "rb+");
    }

    fseek(fp, 0, SEEK_END);

    system(CLEAR);

    do {
        p("##### Cargar articulo #####\n");

        clearStdin();
        p("Ingrese el codigo del articulo: ");
        s("%d", &codArt);

        // Verifica si el cliente ya fue ingresado
        articuloExiste = 0;
        fseek(fp, 0, SEEK_SET);
        while(fread(&reg, sizeof(reg), 1, fp)) {
            if (reg.cod_art == codArt) {
                articuloExiste = 1;
            }
        }

        // Si el articulo no fue ingresado, lo carga
        if (articuloExiste == 0) {

            reg.cod_art = codArt;

            clearStdin();
            p("\nIngrese el nombre del articulo: ");
            s("%[^\n]", reg.nom_art);

            reg.sto_art = rand()%81 + 20;
            reg.pre_art = (8*(1.*rand())/RAND_MAX + 4);
            reg.fact_art = 0.0;

            fwrite(&reg, sizeof(reg), 1, fp);

            clearStdin();
            system(CLEAR);
        } else {
            p("El articulo %d ya se encuentra cargado\n\n", codArt);
        }

        p("Para terminar ingrese 0, para continuar ingrese 1\n");
        s("%d", &seguir);
        system(CLEAR);
    } while (seguir != 0);

    fclose(fp);

    system(CLEAR);

    menuPrincipal();
}

void cargarClientes(char fileName[]) {
    FILE * fp;
    regcli reg;
    int seguir, codCli, clienteExiste;

    // Si no existe el archivo lo crea, sino lo abre para r/w
    if ((fp = fopen(fileName, "rb+")) == NULL) {
        fp = fopen(fileName, "wb+");
    } else {
        fp = fopen(fileName, "rb+");
    }

    system(CLEAR);

    do {
        p("##### Cargar cliente #####\n");
        clearStdin();

        p("Ingrese el codigo del cliente: ");
        s("%d", &codCli);

        // Verifica si el cliente ya fue ingresado
        clienteExiste = 0;
        fseek(fp, 0, SEEK_SET);
        while(fread(&reg, sizeof(reg), 1, fp)) {
            if (reg.cod_cli == codCli) {
                clienteExiste = 1;
            }
        }

        fseek(fp, 0, SEEK_END);

        if (clienteExiste == 0) {
            reg.cod_cli = codCli;

            clearStdin();
            p("\nIngrese el nombre del cliente: ");
            s("%[^\n]", reg.nom_cli);

            clearStdin();
            p("\nIngrese el numero de cuenta del cliente: ");
            s("%f", &reg.cuenta);

            fwrite(&reg, sizeof(reg), 1, fp);

            clearStdin();
            system(CLEAR);
        } else {
            p("El cliente No. %d ya fue ingresado\n", codCli);
        }

        p("Para terminar ingrese 0, para continuar ingrese 1\n");
        s("%d", &seguir);
        system(CLEAR);
    } while (seguir != 0);

    fclose(fp);

    system(CLEAR);

    menuPrincipal();
}

void mostrarArticulos(char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "rb+");
    regart reg;

    system(CLEAR);

    // Header
    p("#################### Listado de articulos ####################\n\n");
    p("%-4s %-20s %-8s %-10s %-10s\n", "Cod.", "Articulo", "Stock", "Precio", "Facturacion");

    while (fread(&reg, sizeof(reg), 1, fp)) {
        p("%-4d %-20s %-8.2d %-10.2f %-10.2f\n", reg.cod_art, reg.nom_art, reg.sto_art, reg.pre_art, reg.fact_art);
    }

    fclose(fp);

    clearStdin();
    clearStdin();
    getch();

    menuPrincipal();
}

void mostrarClientes(char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "rb+");
    regcli reg;

    system(CLEAR);

    // Header
    p("#################### Listado de clientes ####################\n\n");
    p("%-4s %-20s %-8s\n", "Cod.", "Nombre", "Cuenta");

    while (fread(&reg, sizeof(reg), 1, fp)) {
        p("%-4d %-20s %-8.2f\n", reg.cod_cli, reg.nom_cli, reg.cuenta);
    }

    fclose(fp);

    clearStdin();
    clearStdin();
    getch();

    menuPrincipal();
}

void mostrarFacturas(char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "rb");
    regfact reg;

    system(CLEAR);

    if (!fileExist(fp, fileName)) return;

    // Header
    p("#################### Listado de facturas ####################\n\n");
    p("%-15s %-15s %-20s %-10s\n", "Factura No.", "Cod. Cliente", "Nombre Cliente", "Total");

    while (fread(&reg, sizeof(reg), 1, fp)) {
        p("%-15d %-15d %-20s %-10.2f\n", reg.cod, reg.cod_cli, reg.nom_cli, reg.total);
    }

    fclose(fp);

    clearStdin();
    clearStdin();
    getch();

    menuPrincipal();
}

void facturar(char articulosFile[], char clientesFile[], char facturasFile[]) {
    FILE *artFp, *cliFp, *factFp;
    regfact rFact;
    regcli rCli;
    // regart rArt;
    int numFact, codCli, codArt, cantArt, facExiste, cliExiste;
    float subtotalFacturado;

    // Si no existe el archivo lo crea, sino lo abre para r/w
    if ((factFp = fopen(facturasFile, "rb+")) == NULL) {
        factFp = fopen(facturasFile, "wb+");
    } else {
        factFp = fopen(facturasFile, "rb+");
    }

    cliFp = fopen(clientesFile, "rb");
    // artFp = fopen(articulosFile, "rb");


    do {
        system(CLEAR);
        p("################### Cargar Factura #####################");
        p("\nIngrese el numero de factura o 0 para salir: ");
        s("%d", &numFact);

        if (numFact != 0) {
            facExiste = 0;
            while(fread(&rFact, sizeof(rFact), 1, factFp)) {
                if (rFact.cod == numFact) {
                    facExiste = 1;
                    break;
                }
            }
            rewind(factFp);

            if (facExiste) {
                p("El numero de factura ya se encuentra ingresado\n\n");
                clearStdin();
                clearStdin();
                getch();
                getch();
                system(CLEAR);
                continue;
            } else {
                rFact.cod = numFact;
            }

            p("\nIngrese el codigo de cliente: ");
            s("%d", &codCli);

            cliExiste = 0;
            while(fread(&rCli, sizeof(rCli), 1, cliFp)) {
                // Si encuentro el cliente, inicializo la factura con sus datos
                if(rCli.cod_cli == codCli) {
                    cliExiste = 1;
                    rFact.cod_cli = codCli;
                    strcpy(rFact.nom_cli, rCli.nom_cli);
                    rFact.total = 0.0;
                    break;
                }
            }
            rewind(cliFp);

            if (!cliExiste) {
                p("El codigo de cliente ingresado no existe\n\n");
                clearStdin();
                clearStdin();
                getch();
                getch();
                system(CLEAR);
                continue;
            }
            do {
                // Facturar multiples articulos
                system(CLEAR);
                p("#################### Agregar productos ####################");
                p("\nFactura No. %d - Cliente: %s\n\n", rFact.cod, rFact.nom_cli);

                p("\nIngrese el codigo del articulo o 0 para terminar: ");
                s("%d", &codArt);
                if (codArt != 0) {
                    p("\nIngrese la cantidad a facturar: ");
                    s("%d", &cantArt);

                    subtotalFacturado = facturarProducto(codArt, cantArt, articulosFile);

                    if(subtotalFacturado != -1) {
                        rFact.total += subtotalFacturado;
                    } else {
                        continue;
                    }
                }

            } while (codArt != 0);

            fseek(factFp, 0, SEEK_END);
            fwrite(&rFact, sizeof(rFact), 1, factFp);
            p("\nFactura ingresada exitosamente");

            clearStdin();
            clearStdin();
            getch();
            getch();
        }
    } while (numFact != 0);

    fclose(cliFp);
    fclose(factFp);

    menuPrincipal();
}

float facturarProducto(int codArt, int cant, char articulosFile[]) {
    FILE * artFp;
    regart rArt;
    float totalFacturado = 0;
    artFp = fopen(articulosFile, "rb+");

    while(fread(&rArt, sizeof(rArt), 1, artFp)) {
        // Si coincide el codigo
        if (rArt.cod_art == codArt) {
            // y el stock es mayor o igual a la cantidad
            if (rArt.sto_art >= cant) {
                // calculamos el subtotal,
                totalFacturado = rArt.pre_art * cant;
                // restamos la cantidad del articulo,
                rArt.sto_art = rArt.sto_art - cant;
                // cargamos el total facturado en el articulo,
                rArt.fact_art += totalFacturado;
                // nos movemos un struct hacia atras en el archivo
                fseek(artFp, -sizeof(rArt), SEEK_CUR);
                // y guardamos el articulo con la nueva cantidad
                fwrite(&rArt, sizeof(rArt), 1, artFp);
                fclose(artFp);
                return totalFacturado;
            } else {
                fclose(artFp);
                p("\nLa cantidad ingresada supera el stock del producto");
                clearStdin();
                clearStdin();
                getch();
                getch();
                return -1;
            }
        }
    }
    fclose(artFp);
    p("\nEl codigo de articulo ingresado no existe");
    clearStdin();
    clearStdin();
    getch();
    return -1;
}

void menuListados() {
    int opt;


    do {
        system(CLEAR);
        p("#################### LISTADOS ####################\n\n");
        p("1- LISTADO DE ARTICULOS\n");
        p("2- LISTADO DE CLIENTES\n");
        p("3- LISTADO DE FACTURAS\n");
        p("4- VOLVER AL MENU PRINCIPAL\n");
        p("Ingrese opcion: ");
        s("%d", &opt);
    } while ((opt < 1) || (opt > 4));

    switch(opt) {
        case 1:
            mostrarArticulos(ART_FILE_NAME);
            break;

        case 2:
            mostrarClientes(CLI_FILE_NAME);
            break;

        case 3:
            mostrarFacturas(FACT_FILE_NAME);
            break;

        case 4:
            menuPrincipal();
            break;
    }
}

void menuAltas() {
    int opt;

    system(CLEAR);

    do {
        p("#################### ALTAS ####################\n\n");
        p("1- ALTA DE ARTICULOS\n");
        p("2- ALTA DE CLIENTES\n");
        p("3- VOLVER AL MENU PRINCIPAL\n");
        p("Ingrese opcion: ");
        s("%d", &opt);
    } while ((opt < 1) || (opt > 3));

    switch(opt) {
        case 1:
            cargarArticulos(ART_FILE_NAME);
            break;

        case 2:
            cargarClientes(CLI_FILE_NAME);
            break;

        default:
            menuPrincipal();
            break;
    }
}

void menuPrincipal() {
    int opt;

    system(CLEAR);

    do {
        p("#################### MENU PRINCIPAL ####################\n\n");
        p("1- ALTAS\n");
        p("2- FACTURACION\n");
        p("3- LISTADOS\n");
        p("4- SALIR\n");
        p("Ingrese opcion: ");
        s("%d", &opt);
    } while ((opt < 1) || (opt > 4));

    switch(opt) {
        case 1:
            menuAltas();
            break;

        case 2:
            facturar(ART_FILE_NAME, CLI_FILE_NAME, FACT_FILE_NAME);
            break;

        case 3:
            menuListados();
            break;

        case 4:
            return;
            break;

        default:
            break;
    };
}

int main() {
    menuPrincipal();
    getch();
    return 0;
}
