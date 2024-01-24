#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct def_nodoA
{
  char letra;
  int prob;
  struct def_nodoA *izq;
  struct def_nodoA *der;
  struct def_nodoA *sig;  
}tiponodoA;

//Funciones Basicas
void Registrar(tiponodoA **Inicio);
void Mostrar(tiponodoA *Inicio, int contador);
void Eliminar(tiponodoA **Inicio);
void Modificar(tiponodoA **Inicio);
void Guardar(tiponodoA *Inicio);
void LeerA(tiponodoA **Inicio);
void Menu();
void Integrantes();
void Objetivo();
void Menu2();
void Salir(tiponodoA **lista);
void Salir2(tiponodoA *arbol);
void BorraA(tiponodoA *p);

//CrearArbol
void CrearArbol(tiponodoA **arbol,tiponodoA **listaOrd);
void CrearMicroArbol(tiponodoA *listaOrd, tiponodoA **raizArbol);
void AjustesLista(tiponodoA **listaOrd, tiponodoA *raizArbol);
void Borrar1Y2(tiponodoA **ListaOrd);
void InsertarOrden(tiponodoA **listaOrd,tiponodoA *nodo);
void LeerLista(tiponodoA **listaOrd);

//Codificar y Decodificar
void Codificar(tiponodoA *arbol);
void InfoArchivo(FILE **archivoL,FILE **archivoE);
void CerrarArchivos(FILE *archivoL,FILE *archivoE);
void BuscarLetra(tiponodoA *p,char c, char recorrido[],int i, char recorridoReal[]);
void Decodificar(tiponodoA *arbol);
char ArbolSimbolo(int *j,tiponodoA *arbol,char bits[],int i);
void LetraBits(tiponodoA *p, char recorrido[],int i);
//void MostrarLetraBits(tiponodoA *arbol);

int main(void)
{
  tiponodoA *lista;  
  int opc,opc2, contador=0;  
  tiponodoA *arbol,*listaOrd;
  char recorrido[30];
  lista=NULL;
  arbol=NULL;
  opc2=0;
  system("clear");
  Integrantes();
  Objetivo();
  do
    {
      Menu();
      __fpurge(stdin);
      scanf("%d", &opc);
      //system("clear");
      if(opc==1)
	Registrar(&lista);
      if(opc==2)
	Mostrar(lista, contador);
      if(opc==3)
	Eliminar(&lista);
      if(opc==4)
	Modificar(&lista);
      if(opc==5)
	Guardar(lista);
      if(opc==6)
	LeerA(&lista);
      if(opc==7)
	{
	  if(lista==NULL)
	    {
	      system("clear");
	      printf("Debe de cargar un diccionario primero");
	      opc=2;
	    }
	  else
	    {
	      CrearArbol(&arbol,&lista);
	    }
	  
	}
      //CrearArbol(&arbol,&lista);
      if(opc==8)
	{
	  Salir(&lista);
	}
    }
  while(opc >= 1 && opc <= 6);
  system("clear");
  while(opc==7 && opc2 != 4)
    {
      Menu2();
      __fpurge(stdin);
      scanf("%d",&opc2);
      system("clear");
      
      if(opc2==1)
	{
	  Codificar(arbol);
	}
      if(opc2==2)
	{
	  Decodificar(arbol);
	}
      if(opc2==3)
	{
	  LetraBits(arbol,recorrido,0);
	}
      if(opc==4)
	{
	  Salir2(arbol);
	}
    }
    
}

void Salir(tiponodoA **lista)
{
  tiponodoA *temp;
  
  while(*lista != NULL)
    {
      temp=*lista;
      *lista=temp->sig;
      free(temp);
    }
  printf("Gracias por usar el programa, adios.\n");
}

void Salir2(tiponodoA *arbol)
{
  if(arbol != NULL)
    {
      BorraA(arbol);
    }
}

void BorraA(tiponodoA *p)
{
  if(p!=NULL)
    {
      BorraA(p->izq);
      BorraA(p->der);
      free(p);
    }
}

void Menu2()
{
  printf("\n     ------Menu-----\n");
  printf("1. Codificar\n");
  printf("2. Decodificar\n");
  printf("3. Mostrar Letra-bits\n");
  printf("4. Salir\n");
}
//R
void Menu()
{
  printf("      ----- Menú ----\n");
  printf("1. Registrar símbolo y probabilidad.\n");
  printf("2. Mostrar diccionario.\n");
  printf("3. Eliminar símbolo.\n");
  printf("4. Modificar símbolo y/o probabilidad.\n");
  printf("5. Guardar diccionario.\n");
  printf("6. Cargar diccionario.\n");
  printf("7. Codificar o Decodificar.\n");
  printf("8. Salir.\n");
  printf("Elija una opción: ");
}


void Integrantes()
{
  printf("Colaboradores:\n");
  printf("Federico Pallach Loose\n");
  printf("Ricardo Antonio Avila Pineda\n");
  printf("Presione Enter para continuar....");
  getchar();
  system("clear");
}

void Objetivo()
{
  printf("El objetivo es crear un arbol mediante el codigo de Huffman, que dado simbolos y probabilidades, genera un ar\
    bol, acomodando los valores en los lugares correspondientes, asi como poder codificar o decodificar dicho arbol posteri\
    or a su ejecucion.\n");
  printf("Dado un menú, se realizará la actividad elegida por el usuario.\n");
  printf("Presione Enter para continuar....");
  getchar();
  system("clear");
}
/* Ingresa el simbolo y la probabilidad, simbolo y probabilidad a la vez*/
void Registrar(tiponodoA **Inicio)
{
  char letra;
  int prob;
  tiponodoA *temp;
  
  printf("Escribir simbolo y probabilidad(entero 1-100) a registrar. Formato: simbolo,probabilidad   Para finalizar, introduce algo que no este en ese formato \n");
  __fpurge(stdin);
  while(scanf("%c,%d\n",&letra,&prob)==2)
    {
      temp=(tiponodoA*)malloc(sizeof(tiponodoA));
      temp->letra = letra;
      temp->prob=prob;
      InsertarOrden(Inicio,temp);
    }
}

/*Muestra todos los simbolos junto a sus probabilidades*/
void Mostrar(tiponodoA *Inicio, int contador)
{
  tiponodoA *temp;
  temp=Inicio;
  
  printf("\nSimbolos con Probabilidad\n");
  while(temp != NULL)
    {
      printf("simb,prob: %c,%d% \n", temp->letra,temp->prob);
      contador=contador+ temp->prob;
      temp=temp->sig;
    }
  if(contador != 100)
    printf("No se podrá generar el arbol ya que las probabilidades no suman un total de 100\n\n\n\n\n");
  else
    printf("Ya es posible generar el arbol\n\n\n\n\n");
}

/*Elimina un simbolo y su probabilidad, se pregunta el simbolo que se quiere eliminar y lo elimina, lo puede comprobar usando la funcion Muestra*/
void Eliminar(tiponodoA **Inicio)
{
  tiponodoA *temp = *Inicio;
  tiponodoA *ant = NULL;
  char simbolo2;

  printf("Dime que simbolo quieres eliminar: ");
  __fpurge(stdin);
  scanf("%c", &simbolo2);
  while (temp != NULL)
    {
      if (temp->letra==simbolo2)
	{
	  if (ant == NULL)
	    {
	      *Inicio = temp->sig;
	    }
	  else
	    {
	      ant->sig = temp->sig;
	    }
	  free(temp);
	  printf("Símbolo eliminado correctamente.\n\n\n\n\n");
	  return;
	}
      ant = temp;
      temp = temp->sig;
    }
}

/*Modifica un simbolo, una probabilidad o ambas, se pregunta primero el simbolo, despues se pregunta si quiere modificar simbolo o probabilidad, cualquiera que elija, ingresa el nuevo simbolo o probabilidad, puede corroborar usando la funcion Muestra*/
void Modificar(tiponodoA **Inicio)
{
  char simbolo3, opc2, simbolomod;
  tiponodoA *temp;
  int prob2;

  temp = *Inicio;
  
  printf("Dame el simbolo a modificar: ");
  __fpurge(stdin);
  scanf("%c", &simbolo3);
  while (temp != NULL)
    {
      if (temp->letra==simbolo3)
	{
	  printf("Deseas modificar simbolo o probabilidad? (s/p): ");
	  __fpurge(stdin);
	  scanf("%c", &opc2);
	  if(opc2 == 's')
	    {
	      printf("Dame el nuevo simbolo: ");
	      __fpurge(stdin);
	      scanf("%c", &simbolomod);
	      temp->letra=simbolomod;
	    }
	  if(opc2 == 'p')
	    {
	      printf("Dame la nueva probabilidad: ");
	      __fpurge(stdin);
	      scanf("%d", &prob2);
	      temp->prob=prob2;
	    }
	}
      temp = temp->sig;
    }
  system("clear");
}

/*Guarda todos los simbolos y sus probabilidades (tambien llamado diccionario) en un archivo de texto, se pregunta el nombre del archivo y se guarda, lo puedes corroborar buscando con el nombre del archivo al final del programa*/
void Guardar(tiponodoA *Inicio)
{
  FILE *archivoNodo;
  char nombre_arch[100];
  tiponodoA *temp;

  printf("Nombre del archivo: ");
  __fpurge(stdin);
  gets(nombre_arch);
  
  archivoNodo = fopen(nombre_arch, "wt");
  if (archivoNodo == NULL)
    {
      printf("Error al abrir el archivo.\n\n\n\n\n");
      return;
    }
  
  temp = Inicio;
  while (temp != NULL)
    {
      fprintf(archivoNodo, "%s,%d\n", &temp->letra, temp->prob);
      temp = temp->sig;
    }
  
  fclose(archivoNodo);
  
  printf("Datos guardados correctamente en el archivo.\n\n\n\n\n");
}

/*Lee los datos que están en el archivo de texto que antes se guardó, carga el diccionario guardado, se puede corroborar usando la funcion Muestra*/
void LeerA(tiponodoA **Inicio)
{
  FILE *archivoNodo;
  char nombre_arch[100];
  tiponodoA *temp;
  char simbolo;
  int probabilidad;

  do
    {
      printf("Nombre del archivo: ");
      __fpurge(stdin);
      gets(nombre_arch);
      archivoNodo = fopen(nombre_arch, "rt");
      if(archivoNodo == NULL)
	{
	  printf("Error al abrir el archivo para leer.\n");
	  printf("Intenta de nuevo\n");
	  printf("Nombre del archivo: ");
	  __fpurge(stdin);
	  gets(nombre_arch);
	}
    }
  while(archivoNodo == NULL);
  
  while (fscanf(archivoNodo, "%c,%d\n", &simbolo, &probabilidad) == 2)
    {
      tiponodoA *temp = (tiponodoA*)malloc(sizeof(tiponodoA));
      if (temp == NULL)
	{
	  printf("Error: No se pudo asignar memoria para el nuevo nodo.\n\n\n\n\n");
	  exit(1);
	}
     
      temp->letra = simbolo;
      temp->prob = probabilidad;
      InsertarOrden(Inicio,temp);
    }
  fclose(archivoNodo);
  printf("Datos leídos y registrados correctamente desde el archivo.\n\n\n\n\n");
}

/*Crea el arbol con todos los simbolos y probabilidades*/
void CrearArbol(tiponodoA **arbol,tiponodoA **listaOrd)
{
  //nodos ya existentes borrar? falta desmalloc?
  while((*listaOrd)->sig !=NULL)    
    {
      tiponodoA *raizArbol; //raizArbol pequenio
      raizArbol = (tiponodoA*)malloc(sizeof(tiponodoA));
      CrearMicroArbol(*listaOrd,&raizArbol);
      AjustesLista(listaOrd,raizArbol);
    }
  *arbol = *listaOrd;
}


void CrearMicroArbol(tiponodoA *listaOrd, tiponodoA **raizArbol)
{
  (*raizArbol)->izq = listaOrd;
  (*raizArbol)->der = listaOrd->sig;
  (*raizArbol)->prob = (((*raizArbol)->izq)->prob) + (((*raizArbol)->der)->prob);
}

void AjustesLista(tiponodoA **listaOrd, tiponodoA *raizArbol)
{
  Borrar1Y2(listaOrd); 
  InsertarOrden(listaOrd,raizArbol);
}


void Borrar1Y2(tiponodoA **ListaOrd)
{
  *ListaOrd = ((*ListaOrd)->sig)->sig; 
}

/*Acomoda en orden los simbolos por medio de las probabilidades, de menor a mayor*/
void InsertarOrden(tiponodoA **Inicio, tiponodoA *nodo)
{
  tiponodoA *temp1,*temp2,*temp3;
  temp1 = nodo;
  if(*Inicio != NULL)
    {
      if(temp1->prob > (*Inicio)->prob)
	{
	  temp2 = *Inicio;
	  while((temp1->prob)>(temp2->prob))
	    {
	      temp3=temp2;
	      if(temp2->sig !=NULL)
		{
		  temp2=temp2->sig;
		}
	      else
		{
		  temp2=NULL;
		  break;
		}
	    }
	  temp3->sig=temp1;
	  temp1->sig = temp2;
	}
      else
	{
	  temp1->sig = *Inicio;
	  *Inicio = temp1;
	}
    }
  else
    {
      *Inicio = temp1;
    }
}

/*Ofrece información acerca de un archivo en especifico*/
void InfoArchivos(FILE **archivoL,FILE **archivoE)
{
  char c,nomArchL[20],nomArchE[20];
  
  printf("Introduce el nombre del archivo del que quieras leer\n");
  __fpurge(stdin);
  gets(nomArchL);
  *archivoL=fopen(nomArchL,"rt");
  
  printf("Introduce el nombre del archivo en el que quieras guardar el mensaje\n");
  __fpurge(stdin);
  gets(nomArchE);
  *archivoE=fopen(nomArchE,"wt");

}

void CerrarArchivos(FILE *archivoL,FILE *archivoE)
{
  fclose(archivoL);
  fclose(archivoE);
}
/*Codifica el codigo generado cuando se genero el arbol*/
void Codificar(tiponodoA *arbol)
{
  FILE *archivoL,*archivoE;
  char c;
  char letraC[30],recorridoF[30];
  
  
  InfoArchivos(&archivoL,&archivoE);  
  if(archivoL!=NULL && archivoE != NULL)
    {
      while(fscanf(archivoL,"%c",&c)==1)
	{
	  if(c != '\n')
	    {
	      int j;
	      j=0;
	      
	      BuscarLetra(arbol,c,recorridoF,j,letraC);
	      fprintf(archivoE,"%s",letraC);
	    }
	  else
	    fprintf(archivoE,"%c",c);
	}
    }
  CerrarArchivos(archivoL,archivoE);
}

void BuscarLetra(tiponodoA *p,char c, char recorrido[],int i, char recorridoReal[])
{
  if(p!=NULL)
    {
      if(p->letra==c)
	{
	  recorrido[i]='\0';
	  strcpy(recorridoReal,recorrido);
	}
      else
	{
	  recorrido[i]='0';
	  BuscarLetra(p->izq,c,recorrido,i+1,recorridoReal);
	  recorrido[i]='1';
	  BuscarLetra(p->der,c,recorrido,i+1,recorridoReal);
	}
    }
}

/*Decodifica el codigo generado al crear el arbol*/
void Decodificar(tiponodoA *arbol)
{
  FILE *archivoL,*archivoE;
  int i,*j,k,l;
  l=0;
  j=&l;
  
  InfoArchivos(&archivoL,&archivoE);
  
  while(!feof(archivoL))
    {
      char bits[1000],mensaje[400];
      i=0;
      k=0;
      *j=0;
      
      do
	{
	  fscanf(archivoL,"%c",&bits[i]);
	  i++;
	}
      while(bits[i-1]!='\n'&& !feof(archivoL));
      bits[i-1]='\0';
      i--; 
      while(*j<i)
	{
	  mensaje[k]=ArbolSimbolo(j,arbol,bits,i);
	  k++;
	}
      mensaje[k]='\0';
      fprintf(archivoE,"%s\n",mensaje);
    }
  CerrarArchivos(archivoL,archivoE);

}

char ArbolSimbolo(int *j,tiponodoA *nodo,char bits[],int i)
{ 
  while((*j)-1 < i)
    {
      if(nodo->izq == NULL && nodo->der == NULL)
	{
	  return nodo->letra;
	}
      if(bits[*j]=='0')
	{
	  nodo=nodo->izq;
	}
      if(bits[*j]=='1')
	{
	  nodo = nodo->der;
	}
      (*j)++;
    }
}

void LetraBits(tiponodoA *p, char recorrido[],int i)
{
  //int k=0;
  if(p!=NULL)
    {
      if(p->izq == NULL && p->der == NULL)
	{
	  recorrido[i]='\0';
	  printf("%c,%s\n",p->letra,recorrido);
	  /*
	  while(recorrido[k]!='\0');
	  {
	    recorridos[j][k]=recorrido;
	    k++;
	  }
	  recorridos[j][k]='\0';
	  (*j)++;
	  */
	}
      else
	{
	  recorrido[i]='0';
	  LetraBits(p->izq,recorrido,i+1);
	  recorrido[i]='1';
	  LetraBits(p->der,recorrido,i+1);
	}
    }
  
}

/*
MostrarLetraBits(tiponodo *arbol)
{
  char recorrido[600],letraBits[30][30];
  int i=0,k=0,j*;
  j=&k;
  LetraBits(arbol,recorrido,i,letraBits,*j);
    
}
*/
