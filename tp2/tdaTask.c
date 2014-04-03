/*
  Autor: Gavrilov Vsevolod
  Fecha: 02.04.2014
*/


#include "tdaTask.h"


int createTask(TDA_Task* task, char* path) {
  char* content;
  int out = readJsonFile(path, &content);
  fputs(content, stdout);
  free(content);
  return out;
}


int getFileSize(FILE* file, size_t* size) {
  fseek(file, 0, SEEK_END);
  *size = ftell(file);
  if(*size != -1L) {
    fseek(file, 0, SEEK_SET);
    return 0;
  } else {
    return -1;
  }
}


int readJsonFile(char* path, char** content) {
  size_t size;
  FILE* file = fopen(path, "rb");

  if (file == NULL)
    return 1;
  else {
    // Check for errors
    getFileSize(file, &size);

    // Check for errors
    *content = malloc(size);

    // Check for errors
    fread(*content, size, 1, file);

  }

  fclose (file);
  return 0;
}
