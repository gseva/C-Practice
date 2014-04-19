#ifndef TDA_ASANACLIENT_H_INCLUDED
#define TDA_ASANACLIENT_H_INCLUDED

#define KEY_SIZE 50
#define PATH_SIZE 256
#define CALL_SIZE 512

#define SUCCESS 0
#define FAILED -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _AsanaClient {

    char key[KEY_SIZE];

} AsanaClient;

/**
Recibe un cliente y una clave de autenticacion para inicializar la estructura
Devuelve SUCCESS si el cliente fue creado exitosamente con la clave asociada
Devuelve FAILED si el cliente no pudo ser creado
*/
int createAsanaClient(AsanaClient* client, char key[KEY_SIZE]);


/**
Recibe un cliente creado, un identificador de proyecto y un nombre o path al archivo que se guardara
Devuelve un codigo de ejecucion y un archivo json ubicado en el path asignado en pathToFile
*/
int getProjectJsonFile(AsanaClient* client, char* projectId, char pathToFile[PATH_SIZE]);

/**
Recibe un cliente creado, un identificador de proyecto y un nombre o path al archivo que se guardara
Devuelve un codigo de ejecucion y un archivo json ubicado en el path asignado en pathToFile
*/
int getProjectDetailJsonFile(AsanaClient* client, char* projectId, char pathToFile[PATH_SIZE]);

/**
Recibe un cliente creado, un identificador de tarea y un nombre o path al archivo que se guardara
Devuelve un codigo de ejecucion y un archivo json ubicado en el path asignado en pathToFile
*/
int getTaskJsonFile(AsanaClient* client, char* taskId, char pathToFile[PATH_SIZE]);


#endif // TDA_ASANACLIENT_H_INCLUDED
