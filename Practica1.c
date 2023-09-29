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
void guardarImagen(unsigned char **tabla,int col,int ren,char encab2[]);
void generarEncabezado(char encab2[],int col,int ren);
void negativoImagen(unsigned char **tabla,int col,int ren);
void ecualizarImagen(unsigned char **tabla, int col, int ren);
void ampliarImagenYGuardar(unsigned char **tabla,int col,int ren);
void reducirImagenYGuardar(unsigned char **tabla,int col,int ren);

int main(void)
{
  int opcion,col,ren,i;
  unsigned char **tabla;
  char nombrearch[50],encab2[20];
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
  //printf("\n%d",tabla[0][3]);   SI PODEMOS LEER BIEN LA TABLA
  do
    {
      Menu(&opcion);
      switch (opcion)
        {
        case 1:
          negativoImagen(tabla,col,ren);	  
          break;
        case 2:
	  ecualizarImagen(tabla,col,ren);
          break;
        case 3:
          //ampliarImagen();
          break;
        case 4:
          //ReducirImagen();
          break;
	case 5:
	  generarEncabezado(encab2,col,ren); //col2 ren2 realmente
	  guardarImagen(tabla,col,ren,encab2);
        case 6:
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
    }while(opcion!=6);

  
}

void Menu(int *opcion)
{
  printf("Ingrese lo que desea hacer con una imagen\n");
  printf("1.Negativo\n2.Ecualizacion\n3.Ampliar Imagen\n4.Reducir Imagen\n5.Guardar la anterior que realizaste(solo para negativo y ecualizar, las otras directo\n6.Salir\n");
  scanf("%d",opcion);
}


void seleccionarImagenYObtColReng(int *col,int *ren,char nombrearch[50])
{
  FILE *archivo;
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
    }
  else
    printf("El archivo no existe en la direccion de trabajo");
  fclose(archivo);
  
}
/*    ESTA LA PROGRAMAMOS DIRECTO EN EL MAIN
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
      for(i=0;i<ren;i++)//486
	{
	  for(j=0;j<col;j++)//479
	    {
	      fread(&tabla[i][j],1,1,archivo);	
	      //printf("\nPixel %d %d es %d\n",i,j,tabla[i][j]);
	    }
	}

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

void negativoImagen(unsigned char **tabla,int col,int ren)
{
  int i,j;
  for(i=0;i<ren;i++)
    {
      for(j=0;j<col;j++)
	{
	  tabla[i][j]=255-(tabla[i][j]);
	}
    }
}

void ecualizarImagen(unsigned char **tabla, int col, int ren)
{
  unsigned char max=tabla[0][0];
  unsigned char min=tabla[0][0];
  //unsigned char pixEQ[col][ren];
  int i,j,m,b;

  //ENCONTRAR MAXIMO
  for(i=0; i<ren; i++)
    {
      for(j=0; j<col; j++)
        {
          if(tabla[i][j]>max)
            {
              max=tabla[i][j];
            }
          if(tabla[i][j]<min)
            {
              min=tabla[i][j];
            }
        }
    }
  //FIN DE ENCONTRAR MAXIMO

  m = 255/(max-min);
  b= -(255/(m*max));
  
  for(i=0; i<ren; i++)
    {
      for(j=0; j<col; j++)
	{
	  tabla[i][j] = m*tabla[i][j]+b;
	}
    }
}






void generarEncabezado(char encab2[],int col,int ren)
{
  char colS[4],renS[4];
  sprintf(colS, "%d", col);
  sprintf(renS, "%d", ren);
  strcpy(encab2,"P5 ");
  strcat(encab2,colS);
  strcat(encab2," ");
  strcat(encab2,renS);
  strcat(encab2," 255 ");
  __fpurge(stdin);
  puts(encab2);
}

void guardarImagen(unsigned char **tabla,int col,int ren,char encab2[])
{
  FILE *archivo;
  char nombrearch[50];
  int i,j;
  printf("dame el nombre del archivo a generar: ");
  __fpurge(stdin);
  gets(nombrearch);
  archivo=fopen(nombrearch,"wb");
  if(archivo!=NULL)
    {
      fwrite(encab2,sizeof(char),15,archivo);
      for(i=0;i<ren;i++)
	{
	  for(j=0;j<col;j++)
	    {
	      fwrite(tabla[i][j],1,1,archivo); //marca errores por los tipos... y genera seg fault
	    }
	}
      fclose(archivo);
    }
}

//CERRAR LA PROGRAMAMOS DIRECTO EN EL MAIN
void Cerrar(unsigned char **tabla,int ren)
{
  int i;
    for(i=0;i<ren;i++)
    {
      free(tabla[i]);
    }
  free(tabla);
}

