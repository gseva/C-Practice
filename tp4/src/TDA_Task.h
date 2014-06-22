/*
  Autor: Gseva
  Fecha: 02.04.2014

  Tipo de dato abstracto Tarea con sus primitivas.
*/

#ifndef __TDA_TASK_H_DEFINED__

  #include <time.h>

  #include "parser.h"

  #define bool2str(a) (a ? "Si": "No")
  #define date2str(a) (a ? a: "null")

  /**
   * Private structure
   */
  typedef struct {
    char id[30];
    char name[100];
  } NamedObject;

  typedef struct {
    char id[30];
    char name[100];
    char notes[255];
    char parent[30];
    char assigneeStatus[30];

    bool completed;

    char completedAt[20];
    char createdAt[20];
    char dueOn[20];
    char modifiedAt[20];

    NamedObject assignee;
    NamedObject workspace;
    NamedObject followers[10];
    NamedObject projects[5];
    NamedObject tags[10];

    int _followersCount;
    int _projectsCount;
    int _tagsCount;

  } TDA_Task;


  /**
   * Fills task with data from file on path.
   *
   * PRE: Task has enough memory.
   * POST: Returns 0 if Task is successfully created, !0 otherwise.
   */
  int createTask(TDA_Task* task, char* path);

  int handleKey(TDA_Task* task, char** key, char** content);

  int initializeTask(TDA_Task* task);

  int setTaskId(TDA_Task* task, char* id);
  char* getTaskId(TDA_Task* task);

  int setTaskName(TDA_Task* task, char* name);
  char* getTaskName(TDA_Task* task);

  int setTaskNotes(TDA_Task* task, char* notes);
  char* getTaskNotes(TDA_Task* task);

  int setTaskParent(TDA_Task* task, char* parent);
  char* getTaskParent(TDA_Task* task);

  int setTaskAssigneeStatus(TDA_Task* task, char* assigneeStatus);
  char* getTaskAssigneeStatus(TDA_Task* task);

  int setTaskCreationDate(TDA_Task* task, char* date);
  char* getTaskCreationDate(TDA_Task* task);

  int setTaskModificationDate(TDA_Task* task, char* date);
  char* getTaskModificationDate(TDA_Task* task);

  int setTaskCompletionDate(TDA_Task* task, char* date);
  char* getTaskCompletionDate(TDA_Task* task);

  int setTaskDueDate(TDA_Task* task, char* date);
  char* getTaskDueDate(TDA_Task* task);

  int setTaskCompleted(TDA_Task* task, bool completed);
  bool getTaskCompleted(TDA_Task* task);

  int setTaskAssignee(TDA_Task* task, char* id, char* name);
  char* getTaskAssigneeId(TDA_Task* task);
  char* getTaskAssigneeName(TDA_Task* task);

  int setTaskWorkspace(TDA_Task* task, char* id, char* name);
  char* getTaskWorkspaceId(TDA_Task* task);
  char* getTaskWorkspaceName(TDA_Task* task);

  int addTaskTag(TDA_Task* task, char* id, char* name);
  char* getTaskTagId(TDA_Task* task, int index);
  char* getTaskTagName(TDA_Task* task, int index);
  int getTaskTagsCount(TDA_Task* task);

  int addTaskFollower(TDA_Task* task, char* id, char* name);
  char* getTaskFollowerId(TDA_Task* task, int index);
  char* getTaskFollowerName(TDA_Task* task, int index);
  int getTaskFollowersCount(TDA_Task* task);

  int addTaskProject(TDA_Task* task, char* id, char* name);
  char* getTaskProjectId(TDA_Task* task, int index);
  char* getTaskProjectName(TDA_Task* task, int index);
  int getTaskProjectsCount(TDA_Task* task);


  // Joins task tag names with ", "
  int getTaskTagNames(TDA_Task* task, char** value);

  void printTask(TDA_Task* task);


  int obtenerTipo(TDA_Task* task, char** tipo);

  int obtenerSprintInicio (TDA_Task* task, int* numeroSprint);

  int obtenerSprintFinalizacion (TDA_Task* task, int* numeroSprint);

  int obtenerDiasRetraso (TDA_Task* task, int* diasRetraso);

#endif
