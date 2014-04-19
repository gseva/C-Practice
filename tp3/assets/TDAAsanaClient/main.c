#include <stdio.h>
#include <stdlib.h>
#include "TDA_AsanaClient.h"

#define PROJECT_ID "11183691543028"
#define TASK_ID "11183691543032"


int main(int argc, char* argv[]) {

    AsanaClient client;
    createAsanaClient(&client, "3fmVdZTk.dUwa5vc1oMyKSYOao7fOApx");

    char jsonFile[50];

    strcpy(jsonFile, "project.json");
    if(getProjectJsonFile(&client, PROJECT_ID, jsonFile) != 0) {
        printf("Fallo al obtener archivo de proyecto");
    } else {
        printf("Se obtuvo el archivo %s\n", jsonFile);
    }

    strcpy(jsonFile, "projectDetail.json");
    if(getProjectDetailJsonFile(&client, PROJECT_ID, jsonFile) != 0) {
        printf("Fallo al obtener archivo de proyecto");
    } else {
        printf("Se obtuvo el archivo %s\n", jsonFile);
    }

    strcpy(jsonFile, "task.json");
    if(getTaskJsonFile(&client, TASK_ID, jsonFile) != 0) {
        printf("Fallo al obtener archivo de proyecto");
    } else {
        printf("Se obtuvo el archivo %s\n", jsonFile);
    }

}
