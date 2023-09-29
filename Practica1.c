#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void Menu(int *opcion);
//void seleccionarImagen(FILE *archivo);
void seleccionarImagenYObtColReng(int *col,int *ren,char nombrearch[50]);
void crearMatriz(unsigned char ***tabla,int col,int ren);
void Introduccion();
void Enter();
void llenarMatriz(unsigned char **tabla,int col,int ren,char nombrearch[50]);
void Cerrar(unsigned char **tabla,int ren);

int main(void)
{
  int opcion,col,ren,i;
  unsigned char **tabla;
  char nombrearch[50];
  //FILE *archivo;
  Introduccion();
  //seleccionarImagen(archivo);
  seleccionarImagenYObtColReng(&col,&ren,nombrearch);
  printf("\n%s",nombrearch);

  //crearMatriz(&tabla,col,ren); //CODIGO EN MAIN
  tabla = (unsigned char**)malloc(sizeof(unsigned char*)*ren);
  for(i=0; i<ren;i++)
    {
      tabla[i]=(unsigned char*)malloc(sizeof(unsigned char)*col);
    }
  //FIN DE CODIGO EN MAIN

  
  llenarMatriz(tabla,col,ren,nombrearch);
  do
    {
      Menu(&opcion);
      switch (opcion)
        {
        case 1:
          //Negativo();	  
          break;
        case 2:
          //Ecualizacion();
          break;
        case 3:
          //AmpliarImage();
          break;
        case 4:
          //ReducirImagen();
          break;
        case 5:
          printf("Buen dia\n");
	  
	  //Cerrar(tabla,ren);   //INICIA CODIGO EN MAIN
	  for(i=0;i<ren;i++)
	    {
	      free(tabla[i]);
	    }
	  free(tabla);
	  //FIN DE CODIGO EN MAIN
	  
          break;
	default:
	  printf("La opcion es invalida\n");
          break;
        }
    }while(opcion!=5);

  
}

void Menu(int *opcion)
{
  printf("Ingrese lo que desea hacer con una imagen\n");
  printf("1.Negativo\n2.Ecualizacion\n3.Ampliar Imagen\n4.Reducir Imagen\n5.Salir");
  scanf("%d",opcion);
}

/*
void seleccionarImagen(FILE *archivo)
{
  char nombrearch[50];
  printf("Por favor introduce el nombre del archivo de la imagen:");
  __fpurge(stdin);
  gets(nombrearch);
  archivo=fopen(nombrearch,"rb");//este es el que
  __fpurge(stdin);

  if(archivo!=NULL)
    {
      printf("Si existe el archivo");
    }
  else
    printf("El archivo no existe en la direccion de trabajo");
  //fclose(archivo);
}
*/

void seleccionarImagenYObtColReng(int *col,int *ren,char nombrearch[50])
{
  FILE *archivo;
  //char nombrearch[50];
  char Encabezado[15];
  unsigned char valP;
  printf("Por favor introduce el nombre del archivo de la imagen:");
  __fpurge(stdin);
  gets(nombrearch);
  archivo=fopen(nombrearch,"rb");//este es el que
  __fpurge(stdin);

  if(archivo!=NULL)
    {
      fread(Encabezado,sizeof(unsigned char),15,archivo);
      sscanf(Encabezado,"P5 %d %d 255 ", col, ren);

      //Extra para entender
      //fseek(archivo,sizeof(char)*5L,SEEK_CUR);
      //fseek(archivo,0L,SEEK_SET);
      //fread(&valP,1,1,archivo);
      
      //fread(&valP,1,1,archivo);
      //printf("\nPrimer pixel es %d\n",valP);
    }
  else
    printf("El archivo no existe en la direccion de trabajo");
  fclose(archivo);
  
}
/*
void crearMatriz(unsigned char ***tabla,int col,int ren)
{
  int i;
  *tabla = (unsigned char**)malloc(sizeof(unsigned char*)*ren);
  for(i=0; i<ren;i++)
    {
      *tabla[i]=(unsigned char*)malloc(sizeof(unsigned char)*col);
    }
    //Liberar en Cerrar()
}
*/
void llenarMatriz(unsigned char **tabla,int col,int ren,char nombrearch[50])
{
  
  //unsigned char tab[486][479];
  FILE *archivo;
  int i,j; //encab=15
  
  archivo=fopen(nombrearch,"rb");
  __fpurge(stdin);
  

  if(archivo!=NULL)
    {
      fseek(archivo,sizeof(unsigned char)*15L,SEEK_SET);
      for(i=0;i<486;i++)//486
	{
	  for(j=0;j<479;j++)//479
	    {
	      fread(&tabla[i][j],1,1,archivo);	
	      printf("\nPixel %d %d es %d\n",i,j,tabla[i][j]);
	    }
	}

      //Extra para entender
      //fseek(archivo,sizeof(char)*5L,SEEK_CUR);
      //fseek(archivo,0L,SEEK_SET);
      //fread(&valP,1,1,archivo);
      
      //fread(&valP,1,1,archivo);
      //printf("\nPrimer pixel es %d\n",valP);
    }
  else
    printf("El archivo no existe en la direccion de trabajo");
  fclose(archivo);
  

  //fread(&valP,1,1,archivo);
  //printf("\nPrimer pixel es %d\n",valP);
}

void Enter()
 {
   char Basura;

   __fpurge(stdin);
   printf("Presiona <Enter> para continuar...");
   Basura = getchar();
 }

void Introduccion()
{
  system("clear");
  printf("\t-PRÁCTICA 1-\n");
  printf("Bosco Attolini Gay 22013-A\n");
  printf("Federico Pallach Loose 208036-1\n\n");

  Enter();
  printf("Bienvenido, este programa utilizara una imagen con el formato PGM y la modificara digitalmente de las siguientes 4 maneras \n\n");
  printf("-Creara el negativo de la imagen\n     En donde los valores de luminiscencia en la escala de grises de cada pixel se invertirá con respecto al maximo y al mínimo valor posible.");
  printf("-Creara una ecualización lineal de la imagen\n           En donde se normalizaran los valores de luminiscencia de la imagen para que se ocupe todo el rango posible.");
  printf("-Creara una reducción de la imagen\n   En donde la imagen original se verá reducida a un cuarto de su tamaño inicial.");
  printf("-Creara una ampliación de la imagen\n  En donde la imagen original tendrá 4 veces el tamaño de la imagen original.");
  printf("Todos estos cambios se guardaran en un nuevo archivo con nombre dado por el usuario, dejando la imagen original intacta.");

  Enter();
}

void Cerrar(unsigned char **tabla,int ren)
{
  int i;
    for(i=0;i<ren;i++)
    {
      free(tabla[i]);
    }
  free(tabla);
}

