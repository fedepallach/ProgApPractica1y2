#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void seleccionarImagen();
void menu(int *opcion);

int main(void)
{
  int opcion;
  printf("\nBienvenido al programa para modificar imagenes!\n");
  seleccionarImagen();
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
void seleccionarImagen()
{
  FILE *archivo;
  char nombrearch[50];
  
  printf("Por favor introduce el nombre del archivo de la imagen: ");
      __fpurge(stdin);
      gets(nombrearch);
      archivo=fopen(nombrearch,"rt");
      if(archivo!=NULL)
        {
          //*insertados=0;
          //while(!feof(archivo)&&(*insertados<30))
          //  {
              //fgets(grupo[*insertados].nombre,28,archivo);
              //grupo[*insertados].nombre[strlen(grupo[*insertados].nombre)-1]='\0';
              //fscanf(archivo,"%f,%f,%f\n",&grupo[*insertados].c1,&grupo[*insertados].c2,&grupo[*insertados].c3);
              //fscanf(archivo,"%f\n",&grupo[*insertados].prom);
              //(*insertados)++;
	  // }
          fclose(archivo);
	}
      else
	printf("El archivo no existe en la direccion de trabajo");
}
