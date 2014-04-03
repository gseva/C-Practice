/*
  Autor: Gavrilov Vsevolod
  Fecha: 23.03.2014

  Programa que ordena alfabeticamente la entrada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int compare (const void * a, const void * b)
{
  return strcmp (*(const char **) a, *(const char **) b);
}


int main (int argc, char* argv[]) {
	int i;
  if (argc > 1) {
    qsort(&argv[1], argc-1, sizeof(char*), compare);
    i = 1;
    printf("%s", argv[i]);
    while(i < argc-1) {
      printf(" %s", argv[++i]);
    }
  }
  printf("\n");
}
