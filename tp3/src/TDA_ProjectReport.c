/**
 *
 */

#include "TDA_ProjectReport.h"


// Ejemplo de uso de lista
void prueba(AsanaClient* client, ProjectReport* report) {
  TDA_Task t; char* taskIds[5];

  taskIds[0] = "11183691543044";
  taskIds[1] = "11183691543041";
  taskIds[2] = "11183691543037";
  taskIds[3] = "11183691543032";
  taskIds[4] = "11183691543063";

  for (int i = 0; i < 5; i++) {
    readTask(client, taskIds[i], report);
  }

  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, (void*) &t);
    printf("\n------------------------------------------------\n");
    printTask(&t);
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));
}


int createReport(char* key, char* projectId) {
  char docId[30]; AsanaClient client;
  TDA_Task t;

  ProjectReport report;
  initializeReport(&report);

  createAsanaClient(&client, key);

  prueba(&client, &report);

  destroyReport(&report);
  return 0;
}


int countTasks(&project)


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
  return remove(jsonFile);
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
//   return remove(jsonFile);
// }


int readTask(AsanaClient* client, char* taskId, ProjectReport* report) {
  char jsonFile[10]; TDA_Task t;

  strcpy(jsonFile, "task.json");
  if(getTaskJsonFile(client, taskId, jsonFile) != 0) {
      return -1;
  }

  if (!createTask(&t, jsonFile)) {
    if (L_Vacia(report->tasks))
      L_Insertar_Cte(&(report->tasks), L_Primero, (void*) &t);
    else
      L_Insertar_Cte(&(report->tasks), L_Siguiente, (void*) &t);
  }

  return remove(jsonFile);
}
