/**
 *
 */

#include "TDA_ProjectReport.h"



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

int iterateTasks(ProjectReport* report, int key) {
  TDA_Task t; int output = 0, aux = 0; char* tipo = malloc(20);
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, (void*) &t);
    switch(key) {
      case 1: // Finalized tasks count
        if (getTaskCompleted(&t)) output++;
        break;
      case 2: // Overdue tasks count
        if (!obtenerDiasRetraso(&t, &aux) && aux) { output++; };
        break;
      case 3: // Bugs count
        if (!obtenerTipo(&t, &tipo) && (strcmp(tipo, "Bug") == 0)) { output++; }
        break;
      case 4: // Milestones count
        if (!obtenerTipo(&t, &tipo) && strcmp(tipo, "Milestone") == 0 && getTaskCompleted(&t)) { output++; }
        break;
      case 5: // Pending milestones count
        if (!obtenerTipo(&t, &tipo) && strcmp(tipo, "Milestone") == 0 && !getTaskCompleted(&t)) { output++; }
        break;
      case 6: // Overdue tasks count
        if (getTaskCompleted(&t) && !obtenerDiasRetraso(&t, &aux) && aux) { output++; };
        break;
      default:
        printTask(&t);
    }
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));
  return output;
}

int createReport(char* key, char* projectId) {
  AsanaClient client; char* docId = malloc(15); char* tasksFile = malloc(15);

  ProjectReport report;
  initializeReport(&report);

  createAsanaClient(&client, key);

  readProject(&client, projectId, &report);

  readProjectDetail(&client, projectId, &report);
  if (primer_sprint(report.projectDetail)) {
      do {
        if(primer_tarea_sprint_actual(report.projectDetail)) {
          do {
              docId = get_id_tarea_actual_sprint_actual(report.projectDetail);
              readTask(&client, docId, &report);
              //break; // Descomentar despues, es para hacer pruebas con 1 tarea
          } while(siguiente_tarea_sprint_actual(report.projectDetail));
        }
        //break; // Descomentar despues, es para hacer pruebas con 1 tarea
      } while(siguiente_sprint(report.projectDetail));
  }

  strcpy(tasksFile, "tasks.csv");

  makeTextOutput(&report, tasksFile);

  makeCsvOutput(&report, tasksFile);

  fillIndexes(&report);

  return destroyReport(&report);
}


int makeTextOutput(ProjectReport* report, char* csvFileName) {
  FILE *f = fopen("project.txt", "w"); int aux, aux2;
  if (f == NULL) {
      printf("Error opening file!\n");
      return 1;
  }

  fprintf(f, "Proyecto: %s\n", Get_name(report->project));
  fprintf(f, "Fecha inicio: %s\n", Get_created_at(report->project));
  fprintf(f, "Tareas (total): %d\n", getTasksCount(report));
  aux = getFinalizedTasksCount(report);
  aux2 = getOverdueFinalizedTasksCount(report);
  fprintf(f, "Tareas finalizadas: %d\n", aux);
  fprintf(f, "Tareas finalizadas con atrasos: %d\n", aux2);
  fprintf(f, "%% atrasadas / finalizadas: %.2f%%\n", percentage(aux, aux2));
  fprintf(f, "Promedio dias de atraso: %d\n", getAverageOverdue(report));
  fprintf(f, "Bugs reportados: %d\n", getBugsCount(report));
  aux = getMilestonesCount(report);
  aux2 = getPendingMilestonesCount(report);
  fprintf(f, "Hitos alcanzados: %d\n", aux);
  fprintf(f, "Hitos pendientes: %d\n", aux2);
  fprintf(f, "Progreso (hitos): %.2f%%\n", percentage(aux, aux2));
  fprintf(f, "Detalle de tareas: %s\n", csvFileName);

  return fclose(f);
}

int makeCsvOutput(ProjectReport* report, char* tasksFile) {
  char buffer[ROW_SIZE]; TDA_Task t; CsvFile csvFile; char* tags = malloc(255);
  int firstSprint, lastSprint, overdueDays;

  initializeCsvFile(&csvFile);
  addRow(&csvFile, "Sprint inicio,Tarea,Descripcion,Asignado,Fecha creacion,Fecha estimada,Fecha finalizada,Dias de atraso,Tipo,tags,Sprint finalizacion");

  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, &t);
    obtenerSprintInicio(&t, &firstSprint);
    obtenerSprintFinalizacion(&t, &lastSprint);
    getTaskTagNames(&t, &tags);
    obtenerDiasRetraso(&t, &overdueDays);
    sprintf(buffer, "%d,%s,%s,%s,%s,%s,%s,%d,%s,%d", firstSprint, getTaskName(&t),
            getTaskNotes(&t), getTaskAssigneeName(&t), getTaskCreationDate(&t),
            getTaskDueDate(&t), getTaskCompletionDate(&t), overdueDays, tags, lastSprint);
    addRow(&csvFile, buffer);
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));

  export(&csvFile, tasksFile);

  free(tags);
  return destroyCsvFile(&csvFile);
}


int readProject(AsanaClient* client, char* projectId, ProjectReport* report) {
  char jsonFile[50]; Project p;

  strcpy(jsonFile, "files/");
  strcat(jsonFile, "project.json");
  // Descomentar, es para hacer pruebas con tareas locales
  // if(getProjectJsonFile(client, projectId, jsonFile) != 0) {
  //     return -1;
  // }
  CargarProj(&p, jsonFile);
  memcpy(report->project, &p, sizeof(Project));
  return 0;
  // Descomentar, es para hacer pruebas con tareas locales
  // return remove(jsonFile);
}


int readProjectDetail(AsanaClient* client, char* pdId, ProjectReport* report) {
  char jsonFile[50]; TDA_ProjectDetail pd; char* data;


  strcpy(jsonFile, "files/");
  strcat(jsonFile, "projectdetail.json");
  // Descomentar, es para hacer pruebas con tareas locales
  // if(getProjectDetailJsonFile(client, pdId, jsonFile) != 0) {
  //     return -1;
  // }

  if (TDA_ProjectDetailLoadJson (jsonFile, &data))
    if (TDA_ProjectDetailCreate(&pd, data)) {
      memcpy(report->projectDetail, &pd, sizeof(TDA_ProjectDetail));
      return 0;
      // Descomentar, es para hacer pruebas con tareas locales
      // return remove(jsonFile); DEBUG
    }

  return -1;
}


int readTask(AsanaClient* client, char* taskId, ProjectReport* report) {
  char jsonFile[50]; TDA_Task t;

  strcpy(jsonFile, "files/");
  strcat(jsonFile, taskId);
  // Descomentar, es para hacer pruebas con tareas locales
  // if(getTaskJsonFile(client, taskId, jsonFile) != 0) {
  //     return -1;
  // }

  if (!createTask(&t, jsonFile)) {
    if (L_Vacia(report->tasks))
      L_Insertar_Cte(&(report->tasks), L_Primero, (void*) &t);
    else
      L_Insertar_Cte(&(report->tasks), L_Siguiente, (void*) &t);
  }

  return 0;
  // Descomentar, es para hacer pruebas con tareas locales
  // return remove(jsonFile); DEBUG
}


int getTasksCount(ProjectReport* report) {
  return cantidad_tareas_total(report->projectDetail);
}

int getSprintsCount(ProjectReport* report) {
  return cantidad_sprints(report->projectDetail);
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
int getOverdueFinalizedTasksCount(ProjectReport* report) {
  return iterateTasks(report, 6);
}

int getAverageOverdue(ProjectReport* report) {
  TDA_Task t; int count, total, aux;
  count = total = aux = 0;
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, &t);
    if (!obtenerDiasRetraso(&t, &aux) && aux) { total += aux; count++; }
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));
  return (count) ? total / count : 0;
}


int string_keycmp(const void* a, const void* b) {
  return strcmp ((char *) a, (char *) b);
}

int string_clone(void* destination, const void* source) {
  if (strcpy((char*) destination, (char*) source))
    return 0;
  return 1;
}

int string_destroy(void* item) {
  free(item);
  return 0;
}

int print_operate(void* value, void* shared_data) {
  printf("Opero valor %s\n", (char*) value);
  return 0;
}

int fillIndexes(ProjectReport* report) {
  TDA_Task t;
  char *taskId = malloc(30), *assignee = malloc(100);

  idx_create(&(report->assignee), 30, 100, string_keycmp, string_clone,
             string_clone, string_destroy, string_destroy);
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, &t);
    strcpy(taskId, getTaskId(&t));
    strcpy(assignee, getTaskAssigneeName(&t));
    idx_put(&(report->assignee), assignee, taskId);
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));

  idx_go_through(&(report->assignee), print_operate, NULL, 255);
  return 0;
}
