/**
 *
 */

#include "TDA_ProjectReport.h"


int createReport(char* key, char* projectId) {
  char taskId[30], jsonFile[30]; AsanaClient client;
  TDA_Task t;

  ProjectReport report;
  initializeReport(&report);

  createAsanaClient(&client, key);

  strcpy(taskId, "11183691543032");
  strcpy(jsonFile, "files/task.json");

  readTask(&client, taskId, &report);

  L_Elem_Cte(report.tasks, (void*) &t);
  printTask(&t);

  destroyReport(&report);
  return 0;
}


int initializeReport(ProjectReport* report) {
  report->project = malloc(sizeof(Project));
  report->projectDetail = malloc(sizeof(TDA_ProjectDetail));
  L_Crear(&(report->tasks), sizeof(TDA_Task));
  return 0;
}

int destroyReport(ProjectReport* report) {
  free(report->project);
  free(report->projectDetail);
  L_Vaciar(&(report->tasks));
  return 0;
}


int readProject(AsanaClient* client, char* projectId, ProjectReport* report) {
  char jsonFile[15]; Project p;

  strcpy(jsonFile, "project.json");
  if(getProjectJsonFile(client, projectId, jsonFile) != 0) {
      return -1;
  }

  InicProj(&p);
  CargarProj(&p, jsonFile);
  report->project = &p;
  return 0;
}

// Descomentar cuando este el TDA_ProjectDetail.c
// int readProjectDetail(AsanaClient* client, char* pdId, ProjectReport* report) {
//   char jsonFile[20]; TDA_ProjectDetail pd;

//   strcpy(jsonFile, "projectdetail.json");
//   if(getProjectDetailJsonFile(client, pdId, jsonFile) != 0) {
//       return -1;
//   }

//   // Capturar error aqui
//   TDA_ProjectDetailCreate(&pd, jsonFile);
//   report->projectDetail = &pd;
//   return 0;
// }


int readTask(AsanaClient* client, char* taskId, ProjectReport* report) {
  char jsonFile[10]; TDA_Task t;

  strcpy(jsonFile, "task.json");
  if(getTaskJsonFile(client, taskId, jsonFile) != 0) {
      return -1;
  }

  if (!createTask(&t, jsonFile)) {
    if (L_Vacia(report->tasks))
      return L_Insertar_Cte(&(report->tasks), L_Primero, (void*) &t);
    else
      return L_Insertar_Cte(&(report->tasks), L_Siguiente, (void*) &t);
  }
  return -1;
}
