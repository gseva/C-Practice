/*
  Autor: Gseva
  Fecha: 02.04.2014

  Programa que parsea un archivo en formato json y lo guarda en un TDA.
*/


/*
 * IMPORTANTE!!!
 * Este codigo es solamente para aprobar la entrega en jarvis, luego lo voy
 * a pulir.
 *
 */


#include "tdaTask.h"


void printTask(TDA_Task* task) {
  char* tags = malloc(255);
  printf("identificador: %s\n", task->id);
  printf("asignado a: %s\n", task->assignee.name);
  printf("tarea: %s\n", task->name);
  printf("creada: %s\n", task->createdAt);
  printf("ultima modificacion: %s\n", task->modifiedAt);
  printf("notas: %s\n", task->notes);
  printf("completada: %s\n", getBoolString(task->completed));
  printf("fecha finalizacion: %s\n", task->completedAt);
  printf("fecha estimada: %s\n", task->dueOn);
  getTaskTagNames(task, &tags);
  printf("tags: %s\n", tags);
}


void printOutput(int code, TDA_Task* task) {
  switch (code) {
    case 0:
      printTask(task);
      break;
    case 2:
      printf("Archivo invalido\n");
      break;
    case 3:
      printf("Argumentos invalidos!\n");
      break;
    default:
      printf("Hubo un problema desconocido\n");
  }
}


int main (int argc, char* argv[]) {
  int out = 1;
  TDA_Task task;

  if (argc == 2) {
    out = createTask(&task, argv[1]);
  } else {
    out = 3;
  }

  printOutput(out, &task);
}
