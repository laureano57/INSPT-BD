#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct datosCliente {
int cli;
char ape[30];
char local[20];
char cat;
float sueldoxhora;
int horastrab;
float total;
int valido;


};


int Menu(){

    char opcion;
    printf("Elige una opcion\n");

    printf("L - Listar archivo\n");
    printf("A - Agregar empleado\n");
    printf("Q - Actualizar sueldo\n");
    printf("T - Calcular sueldo total\n");
    printf("E - Eliminar pasivos\n");
    printf("S - Salir\n");
    scanf("%c",&opcion);
    fflush(stdin);
    return toupper(opcion);

}
    void listar(FILE * archivo,int * cantProd){
    struct datosCliente prod;
    int i=0,c;
    archivo=fopen("empleados.dat","rb");
    //fread(&prod,sizeof(struct datosCliente),1,archivo); //INNECESARIO
    fseek(archivo,0,SEEK_END);
    *cantProd=ftell(archivo)/sizeof(struct datosCliente);
    fseek(archivo,0,SEEK_SET);

    printf( "Legajo\tNombre\tLocalidad\tCateg\tSueldo hora\tHoras Trab.\tTotal\tActivo\n" );
    while(fread(&prod,sizeof(struct datosCliente),1,archivo)){
        //fseek(archivo,i*sizeof(struct datosCliente),SEEK_SET);  INNECESARIO
       //c = fread(&prod,sizeof(struct datosCliente),1,archivo);
        printf( " %-5d %-12s %-15s %-12c %-10.2lf %-12d %-10.2lf %-6d\n", prod.cli, prod.ape, prod.local, prod.cat, prod.sueldoxhora,prod.horastrab,prod.total,prod.valido);
       /*if (prod.valido==1){
            printf( " %-5d %-12s %-15s %-12c %-10.2lf %-12d %-10.2lf %-6d\n", prod.cli, prod.ape, prod.local, prod.cat, prod.sueldoxhora,prod.horastrab,prod.total,prod.valido);}
       else {
            (*cantProd)=*cantProd-1;
            }*/
        i++;
    }
    printf("*** Cantidad de Empleados: %d ***\n",*cantProd);
    fclose(archivo);
    getchar();
    }

    void agregarEmpleado (FILE *archivo){
    struct datosCliente prod;

    archivo=fopen("empleados.dat","a+b");
    fseek(archivo,0,SEEK_END);
    fflush(stdin);
    printf("Indique el numero de empleado\n");
    scanf("%d",&prod.cli);
    fflush(stdin);
    printf("Indique el apellido del empleado\n");
    gets(prod.ape);
    fflush(stdin);
    printf("Indique la localidad del empleado\n");
    gets(prod.local);
    fflush(stdin);
    printf("Indique la categoria del empleado\n");
    scanf("%c",&prod.cat);
    fflush(stdin);
    printf("Indique el sueldo por hora del empleado\n");
    scanf("%f",&prod.sueldoxhora);
    fflush(stdin);
    printf("Indique la cantidad horas trabajadas\n");
    scanf("%d",&prod.horastrab);
    fflush(stdin);
    prod.valido=1;

    fwrite(&prod,sizeof(struct datosCliente),1,archivo);

    fclose(archivo);
    getchar();
    }

    void actualizarSueldo(FILE *archivo){
    struct datosCliente prod;
    int i;
    FILE * temp;
    archivo=fopen("empleados.dat","r+b");
    temp=fopen("empleados.temp","wb");
    fseek(archivo,0,SEEK_SET);
    while(fread(&prod,sizeof(struct datosCliente),1,archivo)){
        if(prod.cat=='B'){
            prod.sueldoxhora=prod.sueldoxhora*1.10;
        }
         fwrite(&prod,sizeof(struct datosCliente),1,temp);
    }

    fclose(archivo);
    fclose(temp);
    remove("empleados.dat");
    rename("empleados.temp","empleados.dat");
    remove("empleados.temp");
    printf("\n***--El sueldo por hora fue modificado correctamente\n--***");
    getchar();
    }

    void calcularSueldoTotal (archivo){
    struct datosCliente prod;

    FILE * temp;
    archivo=fopen("empleados.dat","r+b");
    temp=fopen("empleados.temp","wb");
    fseek(archivo,0,SEEK_SET);
    while(fread(&prod,sizeof(struct datosCliente),1,archivo)){
        prod.total=prod.sueldoxhora*prod.horastrab;
         fwrite(&prod,sizeof(struct datosCliente),1,temp);
    }

    fclose(archivo);
    fclose(temp);
    remove("empleados.dat");
    rename("empleados.temp","empleados.dat");
    remove("empleados.temp");
    printf("\n***--El sueldo total fue calculado correctamente\n--***");
    getchar();

    }

    void eliminarPasivos (FILE * archivo){
    struct datosCliente prod;
    FILE *temp;
    archivo=fopen("empleados.dat","r+b");
    temp=fopen("empleados.temp","wb");
    rewind(archivo);
    while (fread(&prod,sizeof(struct datosCliente),1,archivo)){
        if (prod.valido==1){
            fwrite(&prod,sizeof(struct datosCliente),1,temp);
        }

    }
    fclose(archivo);
    fclose(temp);
    remove("empleados.dat");
    rename("empleados.temp","empleados.dat");
    remove("empleados.temp");
    printf("Los pasivos fueron eliminados exitosamente\n");
    getchar();

    }

int main(){
    char opcion;
    int i,cantProd;
    FILE *archivo;

    do  {
        opcion=Menu();
        switch(opcion){

        case 'L': listar(archivo,&cantProd);
        break;
        case 'A':agregarEmpleado(archivo);
        break;
        case 'Q':actualizarSueldo(archivo);
        break;
        case 'T':calcularSueldoTotal(archivo);
        break;
        case 'E':eliminarPasivos(archivo);
        break;
        }


    }while(opcion!='S');
    return 0;


}
