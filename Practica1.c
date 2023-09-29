#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void menu(int *opcion);
void seleccionarImagenYObtColReng(int *col,int *ren);
void crearMatriz(int **tabla,int col,int ren);

int main(void)
{
  int opcion,col,ren;
  int **tabla;
  printf("\nBienvenido al programa para modificar imagenes!\n");
  printf("-------------------------Practica 1--------------------------------------------\nProgramadores: \nBosco Attolini -227013-A\nFederico Pallach -208036-1\n");
  seleccionarImagenYObtColReng(&col,&reng);
  crearMatriz(tabla,col,ren);
  
  do
    {
      menu(&opcion);
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
          break;
	default:
          printf("La opcion es invalida\n");
          break;
        }
    }while(opcion!=5);

  
}

void menu(int *opcion)
{
  printf("Ingrese lo que desea hacer con una imagen\n");
  printf("1.Negativo\n2.Ecualizacion\n3.Ampliar Imagen\n4.Reducir Imagen\n5.Salir");
  scanf("%d",opcion);
}

//void carga(tipoalumno grupo[], int *insertados);
void crearMatriz(int **tabla)
{
}

void seleccionarImagenYObtColReng(int *col,int *ren)
{
  FILE *archivo;
  char nombrearch[50];
  char Encabezado[15];
  int valP;
  //int numCol,numRen;
  
  //int numCol,numReng, valP;

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

void crearMatriz(unsigned char **tabla,int col,int ren)
{
  int i;
  tabla = (unsigned char**)malloc(sizeof(unsigned char*)*ren);
  for(i=0; i<ren;i++)
    tabla[i]=(unsigned char*)malloc(sizeof(unsigned char)*col);
  //Liberar
  for(i=0;i<ren;i++)
    {
      free(tabla[i]);
    }
  free(tabla);
}
/*
//Extra para entender
      fseek(archivo,sizeof(char)*5L,SEEK_CUR);
      //fseek(archivo,0L,SEEK_SET);
      //fread(&valP,1,1,archivo);
      fread(&valP,1,1,archivo);
      printf("Primer pixel es %d\n",valP);
*/
