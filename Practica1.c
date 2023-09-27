#include <stdio.h>
void menu(int *opcion);
int main(void)
{
  int opcion;
  menu(&opcion);
  printf("%d",opcion);
}

void menu(int *opcion)
{
  printf("Bienvenido al programa para modificar imagenes!\nIngrese lo que desea hacer con una imagen\n");
  printf("1.Negativo\n2.Ecualizacion\n3.Ampliar Imagen\n4. Reducir Imagen\n");
  scanf("%d",opcion);
}
