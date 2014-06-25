/**
 *
 */

#include "TDA_ProjectReport.h"

typedef struct _sd {
  TListaSimple initial, *sorted;
} _sharedData;

int initializeReport(ProjectReport* report) {
  report->project = malloc(sizeof(Project));
  report->projectDetail = malloc(sizeof(TDA_ProjectDetail));
  L_Crear(&(report->tasks), sizeof(TDA_Task));
  return 0;
}

int destroyReport(ProjectReport* report) {
  free(report->project);
  free_ProjectDetail(report->projectDetail);
  L_Vaciar(&(report->tasks));
  idx_destroy(&(report->assigneeIndex));
  idx_destroy(&(report->tagsIndex));
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

  makeOutput(report.tasks, tasksFile);

  fillIndexes(&report);

  getInput(&report);

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

int makeOutput(TListaSimple tasks, char* tasksFile) {
  char buffer[ROW_SIZE]; TDA_Task t; CsvFile csvFile; char* tags = malloc(255);
  int firstSprint, lastSprint, overdueDays;

  if (tasksFile) {
    initializeCsvFile(&csvFile);
    addRow(&csvFile, "Sprint inicio,Tarea,Descripcion,Asignado,Fecha creacion,Fecha estimada,Fecha finalizada,Dias de atraso,Tipo,tags,Sprint finalizacion");
  }

  L_Mover_Cte(&tasks, L_Primero);
  do {
    L_Elem_Cte(tasks, &t);
    obtenerSprintInicio(&t, &firstSprint);
    obtenerSprintFinalizacion(&t, &lastSprint);
    getTaskTagNames(&t, &tags);
    obtenerDiasRetraso(&t, &overdueDays);
    sprintf(buffer, "%d,%s,%s,%s,%s,%s,%s,%d,%s,%d", firstSprint, getTaskName(&t),
            getTaskNotes(&t), getTaskAssigneeName(&t), getTaskCreationDate(&t),
            getTaskDueDate(&t), getTaskCompletionDate(&t), overdueDays, tags, lastSprint);
    if (tasksFile) addRow(&csvFile, buffer);
    else printf("%s\n", buffer);
  } while(L_Mover_Cte(&tasks, L_Siguiente));

  if (tasksFile) export(&csvFile, tasksFile);

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

int strcicmp(char const *a, char const *b) {
    for (;; a++, b++) {
      int d = tolower(*a) - tolower(*b);
      if (d != 0 || !*a)
        return d;
    }
}

int string_keycmp(const void* a, const void* b) {
  return strcicmp ((const char *) a, (const char *) b);
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
  return 0;
}

int show_due_date(void* value, void* shared_data) {
  TDA_Task t;
  getTaskById((ProjectReport*) shared_data, value, &t);
  printf("Obtengo tarea con due date %s\n", getTaskDueDate(&t));
  return 0;
}

int _searchAndInsert(char* value, _sharedData* shared_data, int mov) {
  TDA_Task t;
  if (L_Vacia(shared_data->initial)) return -1;
  L_Mover_Cte(&(shared_data->initial), L_Primero);
  do {
    L_Elem_Cte(shared_data->initial, &t);
    if (strcmp(getTaskId(&t), value) == 0) {
      if (L_Vacia(*(shared_data->sorted))) {
        L_Insertar_Cte(shared_data->sorted, L_Primero, &t);
      } else {
        L_Insertar_Cte(shared_data->sorted, mov, &t);
      }
    }
  } while(L_Mover_Cte(&(shared_data->initial), L_Siguiente));
  return 0;
}

int sortAscending(void* value, void* shared_data) {
  return _searchAndInsert(value, shared_data, L_Siguiente);
}

int sortDescending(void* value, void* shared_data) {
  return _searchAndInsert(value, shared_data, L_Anterior);
}

int fillIndexes(ProjectReport* report) {
  TDA_Task t; int i;
  char *taskId = malloc(30), *assigneeName = malloc(100), *tag = malloc(100), *dueDate = malloc(20);

  idx_create(&(report->assigneeIndex), 100, 30, string_keycmp, string_clone,
             string_clone, string_destroy, string_destroy);
  idx_create(&(report->tagsIndex), 100, 30, string_keycmp, string_clone,
             string_clone, string_destroy, string_destroy);
  idx_create(&(report->dueDateIndex), 20, 30, string_keycmp, string_clone,
             string_clone, string_destroy, string_destroy);

  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, &t);
    strcpy(taskId, getTaskId(&t));
    strcpy(assigneeName, getTaskAssigneeName(&t));
    strcpy(dueDate, getTaskDueDate(&t));
    idx_put(&(report->assigneeIndex), assigneeName, taskId);
    idx_put(&(report->dueDateIndex), dueDate, taskId);
    for(i = 0; i < getTaskTagsCount(&t); i++) {
      strcpy(tag, getTaskTagName(&t, i));
      idx_put(&(report->tagsIndex), tag, taskId);
    }
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente));

  free(taskId); free(assigneeName); free(dueDate);
  return 0;
}

int getTaskById(ProjectReport* report, char* taskId, TDA_Task *t) {
  int output = -1;
  L_Mover_Cte(&(report->tasks), L_Primero);
  do {
    L_Elem_Cte(report->tasks, t);
    output = strcmp(taskId, getTaskId(t));
  } while(L_Mover_Cte(&(report->tasks), L_Siguiente) && output);
  return output;
}

T_Index* getIndexByKey(ProjectReport* report, char* key) {
  T_Index* index = NULL;
  if (strcmp(key, "tags") == 0) {
    index = &(report->tagsIndex);
  } else if (strcmp(key, "dueDate") == 0) {
    index = &(report->dueDateIndex);
  } else if (strcmp(key, "assignee") == 0) {
    index = &(report->assigneeIndex);
  }
  return index;
}

void getInput(ProjectReport* report) {
  Command command;
  pedirInstrucciones(&command);
  while (getAction(&command) != EXIT) {
    if (getAction(&command) == ERROR) printf("Incorrect input\n");
    else executeCommand(report, &command);
    pedirInstrucciones(&command);
  }
  printf("Bye\n");
}


int executeCommand(ProjectReport* report, Command* command) {
  int keyCount, valueCount, i, j; char sortOrder; FILE* file; _sharedData sharedData;
  TDA_Task task; TListaSimple taskIds, tasks, sortedTasks; T_Index* index;
  char *key = malloc(255), *value = malloc(255), *taskId = malloc(30),
       *fileName = NULL, *sortKey = NULL;

  L_Crear(&taskIds, 30); L_Crear(&tasks, sizeof(TDA_Task));
  keyCount = getKeyCount(command);
  valueCount = getValueCount(command);
  sortOrder = getSortOrder(command);

  if (getAction(command) == REPORT) {
    fileName = malloc(255);
    strcpy(fileName, getFileName(command));
    file = fopen(fileName, "w");
    if (!file) {
      printf("No se pudo abrir el archivo\n");
      return -1;
    }
    fclose(file);
  } // prepare file

  if (sortOrder) {
    sortKey = malloc(255);
    strcpy(sortKey, getSortKey(command));
  }


  for (i = 0; i < keyCount; i++) {
    strcpy(key, getKeyByIndex(command, i));
    index = getIndexByKey(report, key);
    if (!index) {
      printf("Clave %s incorrecta\n", key);
      return -1;
    }
    switch (getFormat(command)) {
      case SINGLE_VALUE:
        strcpy(value, getValueByIndex(command, 0));
        idx_get(index, value, &taskIds);
        break;
      case MULTIPLE_VALUE:
        for (j = 0; j < valueCount; j++) {
          strcpy(value, getValueByIndex(command, j));
          idx_get(index, value, &taskIds);
        }
        break;
      case MULTIPLE_KEY:
        strcpy(value, getValueByIndex(command, i));
        idx_get(index, value, &taskIds);
        break;
      default:
        return -1;
    } // switch

    if(!L_Vacia(taskIds)) {
      L_Mover_Cte(&taskIds, L_Primero);
      do {
        L_Elem_Cte(taskIds, taskId);
        getTaskById(report, taskId, &task);
        if (!L_Vacia(tasks)) {
          L_Insertar_Cte(&tasks, L_Primero, &task);
        } else {
          L_Insertar_Cte(&tasks, L_Siguiente, &task);
        }
      } while(L_Mover_Cte(&taskIds, L_Siguiente)); // Fill tasks list

      if (sortOrder) {
        index = getIndexByKey(report, sortKey);
        if (!index) {
          printf("No se puede ordenar por %s\n", sortKey);
          return -1;
        }
        printf("Ordeno por %s\n", sortKey);
        L_Crear(&sortedTasks, sizeof(TDA_Task));
        sharedData.initial = tasks;
        sharedData.sorted = &sortedTasks;
        if (sortOrder == 'a')
          idx_go_through(&(report->assigneeIndex), sortAscending, &sharedData, 255);
        else
          idx_go_through(&(report->assigneeIndex), sortDescending, &sharedData, 255);
        makeOutput(sortedTasks, fileName);
        L_Vaciar(&sortedTasks);
      } else {
        makeOutput(tasks, fileName);
      } // Sort and output

    } else {
      printf("No se encontraron tareas \n");
      return -1;
    }

    L_Vaciar(&tasks); L_Vaciar(&taskIds);
  }

  // printf("Clave de sort %s\n", getSortKey(command));
  // printf("Orden de sort %c\n", getSortOrder(command));

  free(value); free(key); free(fileName); free(taskId); free(sortKey);
  return 0;

}
