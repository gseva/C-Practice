/**
 *
 */

#include "TDA_ProjectReport.h"


int createReport(char* key, char* projectId) {
  AsanaClient client; char* docId = malloc(15);

  ProjectReport report;
  initializeReport(&report);

  createAsanaClient(&client, key);

  readProjectDetail(&client, projectId, &report);

  do {
    if(primer_tarea_sprint_actual(report.projectDetail)) {
      do {
          docId = get_id_tarea_actual_sprint_actual(report.projectDetail);
          readTask(&client, docId, &report);
          break; // Descomentar despues, es para hacer pruebas con 1 tarea
      } while(siguiente_tarea_sprint_actual(report.projectDetail));
    }
    break; // Descomentar despues, es para hacer pruebas con 1 tarea
  } while(siguiente_sprint(report.projectDetail));

  printf("tareas %d\n", getTasksCount(&report));
  iterateTasks(&report, 20);

  destroyReport(&report);
  return 0;
}


// int countTasks(&project){}


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


int readProjectDetail(AsanaClient* client, char* pdId, ProjectReport* report) {
  char jsonFile[20]; TDA_ProjectDetail pd; char* data;

  strcpy(jsonFile, "projectdetail.json");
  if(getProjectDetailJsonFile(client, pdId, jsonFile) != 0) {
      return -1;
  }

  if (TDA_ProjectDetailLoadJson (jsonFile, &data))
    if (TDA_ProjectDetailCreate(&pd, data)) {
      memcpy(report->projectDetail, &pd, sizeof(TDA_ProjectDetail));
      return remove(jsonFile);
    }

  return -1;
}

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


int getTasksCount(ProjectReport* report) {
  return cantidad_tareas_total(report->projectDetail);
}

int getSprintsCount(ProjectReport* report) {
  return cantidad_sprints(report->projectDetail);
}

int iterateTasks(ProjectReport* report, char key) {
  TDA_Task t; int output = 0;
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, (void*) &t);
    switch(key) {
      case 1: // Finalized tasks count
        if (getTaskCompleted(&t)) output++;
        break;
      case 2: // Overdue tasks count
        // if (obtenerDiasRetraso(&t, &aux) && aux) { output++ };
        break;
      case 3: // Bugs count
        // if (obtenerTipo(&t, &tipo) && (strcmp(tipo, "Bug") == 0) { output++ }
        break;
      case 4: // Milestones count
        // if (obtenerTipo(&t, &tipo) && strcmp(tipo, "Milestone") == 0 && getTaskCompleted(&t)) { output++ }
        break;
      case 5: // Pending milestones count
        // if (obtenerTipo(&t, &tipo) && strcmp(tipo, "Milestone") == 0 && !getTaskCompleted(&t)) { output++ }
        break;
      default:
        printTask(&t);
    }
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));
  return output;
}

int getFinalizedTasksCount(ProjectReport* report) {
  return iterateTasks(report, 1);
}
int getOverdueTasksCount(ProjectReport* report) {
  return iterateTasks(report, 2);
}
int getBugsCount(ProjectReport* report) {
  return iterateTasks(report, 3);
}
int getMilestonesCount(ProjectReport* report) {
  return iterateTasks(report, 4);
}
int getPendingMilestonesCount(ProjectReport* report) {
  return iterateTasks(report, 5);
}

int getAverageOverdue(ProjectReport* report) {
  TDA_Task t; int count, total, aux;
  count = total = aux = 0;
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, (void*) &t);
    // if (obtenerDiasRetraso(&t, &aux) && aux) {
    //   total += aux; count++;
    // }
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));
  return total/count;
}
