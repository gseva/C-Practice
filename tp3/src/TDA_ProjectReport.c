/**
 *
 */

#include "TDA_ProjectReport.h"


int createReport(char* key, char* projectId) {
  char taskId[30], jsonFile[30]; AsanaClient client; TDA_Task task;
  createAsanaClient(&client, key);

  strcpy(taskId, "11183691543032");
  strcpy(jsonFile, "files/task.json");
  if(getTaskJsonFile(&client, taskId, jsonFile) != 0) {
      return -1;
  }

  createTask(&task, jsonFile);

  printTask(&task);

  return 0;
}
