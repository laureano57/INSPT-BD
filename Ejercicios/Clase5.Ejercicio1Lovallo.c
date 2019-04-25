#include<stdio.h> // Carga de un archivo de Texto separado los campos por comas
#include<stdlib.h> // Convierte e inserta en un Archivo binario
#include<conio.h> // Probado con strtok
#include<string.h> // bien con registro completo , no campo a campo
#include<ctype.h>
#define p printf
#define s scanf
typedef struct
{
 int cod_chof;
 char nom_chof[30];
 int kms;
 int rec;
 int ver;
 } registro;
void cargar(FILE*,registro);
void tecla(char[]);
void sacar(char[],registro*);
void mostrar(FILE*,char[]);
void baja_logica(FILE*);
void baja_fisica(FILE*);
int cubalo(FILE*);
int main()
{

 FILE *archivo,*binario;
 char* nombre="Clase5.Ejercicio1.txt";// nombre físico del archivo
 char* nombin="Clase5.Ejercicio1.Choferes2.dat";

// char* nombaja="baja.dat";
 char cadena[80],op;
 registro reg;
 system("color 9f");
 binario=fopen(nombin,"w+");
 fclose(binario);
 if((archivo=fopen(nombre,"r+"))==NULL) p("\n\n***El archivo %s no pudo abrirse ***\n",nombre); // crea el archivo para escritura y lectura
   else
    {
        p("\n\t\t\t CONTENIDO DEL ARCHIVO DE TEXTO\n\n"); getch();
         while(fgets(cadena,81,archivo) )  //!=NULL)  hasta \n n-1 o salto de linea
           p("%s",cadena);
         rewind(archivo);
         tecla("VISUALIZAR LOS CAMPOS DE LOS REGISTROS EN MEMORIA");
         system("cls");
         p("\n\n \t\t\tCONTENIDO DE LOS CAMPOS EN MEMORIA");
         p("\n\n Codigo\t\tNombre\t\t\t   kms\n\n");
         while(fgets(cadena,81,archivo) ) // Recorro el Archivo de Texto
         {
           sacar(cadena,&reg); //getch(); // Saco del Archivo de Texto y lo cargo en el registro
           cargar(binario,reg); //Cargo el registro en el Archivo Binario
           p("\n\n");
         }
      binario=fopen(nombin,"rb+");
      mostrar(binario,"ARCHIVO BINARIO ORIGINAL");
      do{
          fflush(stdin);
          p("\n\n\n DESEA DAR DE BAJA L%cGICA DE ALG%cN REGISTRO!!![S-N]:",224,233);
          s("%c",&op);
					if(toupper(op)=='S')
					{
						baja_logica(binario);
					}
         fflush(stdin);
      } while(toupper(op)!='N');

      } // else de la apertura de Archivo
 system("cls");
 tecla("VISUALIZAR LOS REGISTROS DADOS DE BAJA");
 p("\n CANTIDAD DE REGISTROS DADOS DE BAJA:%d",cubalo(binario));
 getch();
  do{
          fflush(stdin);
          p("\n\n\n DESEA DAR DE BAJA F%cSICA DE TODOS LOS REGISTROS DE BAJA!!![S-N]:",214);
          s("%c",&op);
					if(toupper(op)=='S')
					{
						baja_fisica(binario);
						getch(); //system("cls");
						break;
					}
					   //getch();
      } while(toupper(op)!='N');

 mostrar(binario,"ARCHIVO DE REGISTROS ACTUALIZADO");
 tecla("PARA SALIR");
 system("cls");
 fclose(binario);
 fclose(archivo);
 tecla("PARA SALIR");
 //fclose(bajas);
 getch();
 system("cls");
 return(0);
}

void sacar(char x[],registro *y) // Modifico el Registro por Dirección
{
 char*pri,*seg,*ter;

   pri=strtok(x,",");
   y->cod_chof=atoi(pri);
   p("%3d",y->cod_chof); //getch();
   seg=strtok(NULL,",");
   strcpy(y->nom_chof,seg);
   p("\t\t%-20s ",seg);     // que será el nombre del chofente
   ter=strtok(NULL,",");
   y->kms=atoi(ter);
   p("\t%6d",y->kms);
   y->ver=1;
}

void tecla(char x[])
{
	p("\n\nPRESIONE CUALQUIER TECLA PARA %s!!!",x);
	getch();
}

void baja_logica(FILE*x)
{
 registro r;
 char nom[30],res;
 int op,c,enc=0,cocho;

    system("cls");
    mostrar(x,"ARCHIVO DE REGISTROS ACTIVOS");
 //   tecla();
    fflush(stdin);
    p("\n \n\n INGRESE CODIGO DEL CHOFER A ELIMINAR:");
    s("%d", &cocho);
    rewind(x);
    fread(&r,sizeof(r),1,x);
    c=0;
    while(!feof(x) && enc!=1)
      {
      if(r.cod_chof==cocho&& r.ver)
       {
         enc=1;  // ENCONTRADO
         break;
       }
       fread(&r,sizeof(r),1,x);
       }
      if(enc==0&& feof(x))
      {
       p("\n REGISTRO NO ENCONTRADO!!!!");
       tecla("CONTINUAR");
      } else   // se posiciona en el registro encontrado
			 {
				  p(" REGISTRO ENCONTRADO !!!!");
					p("C%cDIGO DE CHOFER : %d", 224,r.cod_chof);
					p(" NOMBRE Y APELLIDO: %s",r.nom_chof);
					fflush(stdin);
					 do
						{
							p("\n CONFIRMA LA BAJA [S-N]:");
							s("%c",&res);
						} while(!(tolower(res)=='s'||tolower(res)=='n'));
						if(res=='s') //break;
						 {
							 fseek (x,sizeof(r)*(-1L),SEEK_CUR);
							 r.ver=0;
							 fwrite(&r,sizeof(r),1,x);
						 }
				// mostrar(x);
		 }
  system("cls");
  mostrar(x,"ARCHIVO DE REGISTROS ACTIVOS");

 }
//}// Cierra la funcion
void cargar(FILE*x,registro y)
{
    registro r;
    char* nb="datos.dat";
    int pre=10;
    int ban=0;
   if((x=fopen(nb,"rb+"))==NULL)
     x=fopen(nb,"wb+");
    fread(&r,sizeof(r),1,x);
    while(!feof(x)&& ban==0)
    {
      if(strcmpi(r.nom_chof,y.nom_chof)==0)
        {
            ban=1;
            break;
        }  else  fread(&r,sizeof(r),1,x);
     }
     if(ban==1)
     {
       r.kms+=y.kms;
       r.rec+=y.kms*pre;
       r.ver=y.ver;
       fseek (x,sizeof(r)*(-1L),SEEK_CUR);
       fwrite(&r,sizeof(registro),1,x);
      } else
		 {
				y.rec=pre*y.kms;
				r.ver=y.ver;
				fseek(x,0L,SEEK_END);
				fwrite(&y,sizeof(y),1,x);
		 }

  fclose(x);
}
int cubalo(FILE*x)
{
    int b=0;
    registro r;
    rewind(x);
    fread(&r,sizeof(registro),1, x);
    while(!feof(x))
    {
        if(r.ver==0) b++;
        fread(&r,sizeof( registro),1, x);
    }
    return(b);
}

void mostrar(FILE*x,char y[])
{
   registro r;
    p("\n\n\n\t\t\t\t%s",y);
    p("\n\n C%cDIGO\t\tCHOFER\t\t\t   KMS\t\t\t    RECAUDACI%cN\n\n",224,224);
    rewind(x);
    fread(&r,sizeof(r),1,x);
    while(!feof(x))
	{
		if(r.ver)
		p("\n\n%3d\t\t%-20s\t%6d\t\t\t\t%6d",r.cod_chof,r.nom_chof,r.kms,r.rec);
		fread(&r,sizeof(r),1,x);
	}
}

void baja_fisica(FILE*x)
{
  FILE*auxi,*bafi;
  auxi=fopen("nuevo.dat","wb+");
  bafi=fopen("bajas.dat","wb+");
  registro r;

  int c=0, cbl=0;
  cbl=cubalo(x);
if(cbl==0)
{
 system("cls");
 p("\n\n\n NO EXISTEN REGISTROS PARA SU ELIMINACION !!! "); tecla("CONTINUAR");
 }
else
{
	p("\n EXISTEN %d REGISTROS PARA SU ELIMINACION DEFINITIVA",cbl);
	rewind(x);
	fread(&r,sizeof(r),1,x);
	while(!feof(x))
		{
			if(r.ver==0)
			{
				p("\n");
				p("C%cDIGO DE CHOFER : %d",224,r.cod_chof);
				p(" NOMBRE Y APELLIDO: %s",r.nom_chof);
				getch();
				r.ver=1;
				fwrite(&r,sizeof(r),1,bafi);
				c++;
			} else fwrite(&r,sizeof(r),1,auxi);
		  fread(&r,sizeof(r),1,x);
		}
	system("cls"); //getch();
	p("\n\nSE HAN DADO DE BAJA %d REGISTROS DEFINITIVAMENTE",c); getch();

	rewind(bafi);
	mostrar(bafi,"ARCHIVO DE REGISTROS DE BAJA FISICA");
	fclose(auxi);
	fclose(bafi);
	remove("datos.dat");
	rename("nuevo.dat","datos.dat" ); // datos es el reemplazo
	remove("nuevo.dat");


    }
}



