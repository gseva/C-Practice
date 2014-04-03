/*
  Autor: Gavrilov Vsevolod
  Fecha: 02.04.2014

  Tipo de dato abstracto Tarea con sus primitivas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
  char* id;
  char* name;
} NamedObject;


typedef struct {
  char* id;
  char* name;
  char* notes;
  char* parent;
  char* assignee;
  char* assignee_status;

  bool completed;

  char* completed_at;
  char* created_at;
  char* due_on;
  char* modified_at;

  NamedObject workspace;
  NamedObject followers[10];
  NamedObject projects[5];
  NamedObject tags[10];

} TDA_Task;


int createTask(TDA_Task* task, char* path);

int readJsonFile(char* path, char** content);


// Needs an open file
int getFileSize(FILE* file, size_t* size);
