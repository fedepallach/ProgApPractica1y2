#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void menu(int *opcion);
void seleccionarImagenYObtColReng(int *col,int *reng);

void crearMatriz(int **tabla);

int main(void)
{
  int opcion,col,reng;
  int **tabla;
  printf("\nBienvenido al programa para modificar imagenes!\n");
  seleccionarImagenYObtColReng(&col,&reng);
  printf("%d,%d",col,reng);
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

//int *datosTemps
//datosTemps=(int*)malloc(sizeof(int)*cantidad);

//void carga(tipoalumno grupo[], int *insertados);
void seleccionarImagenYObtColReng(int *col,int *reng)
{
  FILE *archivo;
  char nombrearch[50];
  char numCol[4],numRen[4];
  unsigned char valP;
  
  printf("Por favor introduce el nombre del archivo de la imagen:");
  __fpurge(stdin);
  gets(nombrearch);
  archivo=fopen(nombrearch,"rb");//este es el que
  //__fpurge(stdin);
  
  if(archivo!=NULL)
    { 
      fseek(archivo,sizeof(char)*3L,SEEK_SET); //habia puesto 4
      fread(numCol,sizeof(char)*3,1,archivo);
      *(numCol[3])="\0";
      //fread(&numCol,sizeof(int),1,archivo);

      printf("Columnas: %s\n",numCol);
      //*col = numCol;
      fseek(archivo,sizeof(char)*1L,SEEK_CUR);
      fread(numRen,sizeof(char)*3,1,archivo);
      *(numRen[3])="\0";
      //fread(&numReng,sizeof(int),1,archivo);
      printf("Renglones %s el ant\n",numReng);
      *reng = (int)numReng;

      //Extra para entender
      fseek(archivo,sizeof(char)*5L,SEEK_CUR);
      //fseek(archivo,0L,SEEK_SET);
      //fread(&valP,1,1,archivo);
      fread(&valP,1,1,archivo);
      printf("Primer pixel es %d\n",valP);
      
    }
  else
    printf("El archivo no existe en la direccion de trabajo");
  fclose(archivo);
}

void crearMatriz(int **tabla)
{
}
