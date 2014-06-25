

#ifndef __TDA_PARSEAR_ENTRADA_H_DEFINED__

  #define __TDA_PARSEAR_ENTRADA_H_DEFINED__

  #include "stdio.h"
  #include "stdlib.h"
  #include "string.h"

  #define QUERY 1
  #define REPORT 2
  #define EXIT 3
  #define ERROR 4
  #define SINGLE_VALUE 1
  #define MULTIPLE_VALUE 2
  #define MULTIPLE_KEY 3
  #define MAX_LINE_SIZE 1000
  #define MAX_KEY_SIZE 255
  #define MAX_VALUES 10

  typedef struct _command{
  	int action;
    int format;

    int keyCount;
    char keys[255][MAX_VALUES];

    int valueCount;
  	char values[255][MAX_VALUES];

  	char* sortKey;
  	char sortOrder; //Orientacion del orden (a:Ascendente o d:Descendente)

  	char* file;
  } Command;

  int getAction(Command* command);
  int getFormat(Command* command);

  int getKeyCount(Command* command);
  char* getKeyByIndex(Command* command, int i);

  int getValueCount(Command* command);
  char* getValueByIndex(Command* command, int i);

  char* getSortKey(Command* command);
  char getSortOrder(Command* command);

  char* getFileName(Command* command);

  int pedirInstrucciones(Command *pCommand);


#endif



