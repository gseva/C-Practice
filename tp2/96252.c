/*
  Autor: Gavrilov Vsevolod
  Fecha: 02.04.2014

  Programa que parsea un archivo en formato json y lo guarda en un TDA.
*/


#include "tdaTask.h"


void printOutput(int code) {
  switch (code) {
    case 1:
      printf("%s\n", "Hubo un problema 1");
      break;
    case 3:
      printf("%s\n", "Argumentos invalidos!");
      break;
    default:
      printf("%s\n", "Salio todo genial");
  }
}


int main (int argc, char* argv[]) {
  int out = 1;
  TDA_Task* task;

  if (argc == 2) {
    out = createTask(task, argv[1]);
  } else {
    out = 3;
  }

  printOutput(out);
}
