#include "TDA_AsanaClient.h"


int createAsanaClient(AsanaClient* client, char key[KEY_SIZE]) {
    if (strlen(key) > KEY_SIZE) {
        return FAILED;
    }
    strcpy(client->key, key);

    return SUCCESS;
}


int getProjectJsonFile(AsanaClient* client, char* projectId, char pathToFile[PATH_SIZE]) {

    char curlCall[CALL_SIZE];
    sprintf(curlCall, "curl -u %s: https://app.asana.com/api/1.0/projects/%s > %s", client->key, projectId , pathToFile);
    int response = system(curlCall);
    return response;

}


int getProjectDetailJsonFile(AsanaClient* client, char* projectId, char pathToFile[PATH_SIZE]) {

    char curlCall[CALL_SIZE];
    sprintf(curlCall, "curl -u %s: https://app.asana.com/api/1.0/projects/%s/tasks > %s", client->key, projectId, pathToFile);
    int response = system(curlCall);
    return response;
}


int getTaskJsonFile(AsanaClient* client, char* taskId, char pathToFile[PATH_SIZE]) {

    char curlCall[CALL_SIZE];
    sprintf(curlCall, "curl -u %s: https://app.asana.com/api/1.0/tasks/%s > %s", client->key, taskId, pathToFile);
    int response = system(curlCall);
    return response;
}
