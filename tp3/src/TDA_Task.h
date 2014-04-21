/*
  Autor: Gseva
  Fecha: 02.04.2014

  Tipo de dato abstracto Tarea con sus primitivas.
*/

#include "parser.h"


typedef struct {
  char id[255];
  char name[255];
} NamedObject;


typedef struct {
  char id[255];
  char name[255];
  char notes[255];
  char parent[255];
  char assigneeStatus[255];

  bool completed;

  char completedAt[255];
  char createdAt[255];
  char dueOn[255];
  char modifiedAt[255];

  NamedObject assignee;
  NamedObject workspace;
  NamedObject followers[10];
  NamedObject projects[5];
  NamedObject tags[10];

  int _followersCount;
  int _projectsCount;
  int _tagsCount;

} TDA_Task;


int createTask(TDA_Task* task, char* path);

int handleKey(TDA_Task* task, char** key, char** content);


int readNamedObject(char** content, char** key, NamedObject* obj);

int setNamedObjectId(NamedObject* o, char* name);
char* getNamedObjectId(NamedObject* o);

int setNamedObjectName(NamedObject* o, char* id);
char* getNamedObjectName(NamedObject* o);

int copyNamedObject(NamedObject* a, NamedObject* b);


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

int setTaskAssignee(TDA_Task* task, NamedObject* asignee);
int getTaskAssignee(TDA_Task* task, NamedObject* asignee);

int setTaskWorkspace(TDA_Task* task, NamedObject* workspace);
int getTaskWorkspace(TDA_Task* task, NamedObject* workspace);

int addTaskTag(TDA_Task* task, NamedObject* tag);
int getTaskTag(TDA_Task* task, NamedObject* tag, int index);
int getTaskTagsCount(TDA_Task* task);

int addTaskFollower(TDA_Task* task, NamedObject* follower);
int getTaskFollower(TDA_Task* task, NamedObject* follower, int index);
int getTaskFollowersCount(TDA_Task* task);

int addTaskProject(TDA_Task* task, NamedObject* project);
int getTaskProject(TDA_Task* task, NamedObject* project, int index);
int getTaskProjectsCount(TDA_Task* task);


// Returns "Si" or "No" depending on bool value
char* getBoolString(bool b);

// Joins task names with ", "
int getTaskTagNames(TDA_Task* task, char** value);
