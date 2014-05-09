/*
  Autor: Gseva
  Fecha: 02.04.2014
*/


#include "TDA_Task.h"



int setNamedObjectId(NamedObject* o, char* id) {
  strcpy(o->id, id);
  return 0;
}

char* getNamedObjectId(NamedObject* o) {
  return o->id;
}


int setNamedObjectName(NamedObject* o, char* name) {
  strcpy(o->name, name);
  return 0;
}

char* getNamedObjectName(NamedObject* o) {
  return o->name;
}


int copyNamedObject(NamedObject* to, NamedObject* from) {
  strcpy(to->id, from->id);
  strcpy(to->name, from->name);
  return 0;
}

int createNamedObject(NamedObject* o, char* id, char* name) {
  setNamedObjectId(o, id);
  setNamedObjectName(o, name);
  return 0;
}


int initializeTask(TDA_Task* task) {
  task->_followersCount = 0;
  task->_projectsCount = 0;
  task->_tagsCount = 0;
  return 0;
}


int setTaskId(TDA_Task* task, char* id) {
  strcpy(task->id, id);
  return 0;
}

char* getTaskId(TDA_Task* task) {
  return task->id;
}


int setTaskName(TDA_Task* task, char* name) {
  strcpy(task->name, name);
  return 0;
}

char* getTaskName(TDA_Task* task) {
  return task->name;
}


int setTaskNotes(TDA_Task* task, char* notes) {
  strcpy(task->notes, notes);
  return 0;
}

char* getTaskNotes(TDA_Task* task) {
  return task->notes;
}


int setTaskParent(TDA_Task* task, char* parent) {
  strcpy(task->parent, parent);
  return 0;
}

char* getTaskParent(TDA_Task* task) {
  return task->parent;
}

int setTaskAssigneeStatus(TDA_Task* task, char* assigneeStatus) {
  strcpy(task->assigneeStatus, assigneeStatus);
  return 0;
}

char* getTaskAssigneeStatus(TDA_Task* task) {
  return task->assigneeStatus;
}


int setTaskCreationDate(TDA_Task* task, char* date) {
  strcpy(task->createdAt, date);
  return 0;
}

char* getTaskCreationDate(TDA_Task* task) {
  return task->createdAt;
}


int setTaskModificationDate(TDA_Task* task, char* date) {
  strcpy(task->modifiedAt, date);
  return 0;
}

char* getTaskModificationDate(TDA_Task* task) {
  return task->modifiedAt;
}


int setTaskCompletionDate(TDA_Task* task, char* date) {
  strcpy(task->completedAt, date);
  return 0;
}

char* getTaskCompletionDate(TDA_Task* task) {
  return task->completedAt;
}


int setTaskDueDate(TDA_Task* task, char* date) {
  strcpy(task->dueOn, date);
  return 0;
}

char* getTaskDueDate(TDA_Task* task) {
  return task->dueOn;
}


int setTaskCompleted(TDA_Task* task, bool completed) {
  task->completed = completed;
  return 0;
}

bool getTaskCompleted(TDA_Task* task) {
  return task->completed;
}


int setTaskAssignee(TDA_Task* task, char* id, char* name) {
  NamedObject n; createNamedObject(&n, id, name); task->assignee = n;
  return 0;
}

char* getTaskAssigneeId(TDA_Task* task) {
  return getNamedObjectId(&(task->assignee));
}

char* getTaskAssigneeName(TDA_Task* task) {
  return getNamedObjectName(&(task->assignee));
}


int setTaskWorkspace(TDA_Task* task, char* id, char* name) {
  NamedObject n; createNamedObject(&n, id, name); task->workspace = n;
  return 0;
}

char* getTaskWorkspaceId(TDA_Task* task) {
  return getNamedObjectId(&(task->workspace));
}

char* getTaskWorkspaceName(TDA_Task* task) {
  return getNamedObjectName(&(task->workspace));
}


int addTaskTag(TDA_Task* task, char* id, char* name) {
  NamedObject n; createNamedObject(&n, id, name);
  copyNamedObject(&(task->tags)[task->_tagsCount++], &n);
  return 0;
}

char* getTaskTagId(TDA_Task* task, int index) {
  return getNamedObjectId(&(task->tags)[index]);
}

char* getTaskTagName(TDA_Task* task, int index) {
  return getNamedObjectName(&(task->tags)[index]);
}

int getTaskTagsCount(TDA_Task* task) {
  return task->_tagsCount;
}


int addTaskFollower(TDA_Task* task, char* id, char* name) {
  NamedObject n; createNamedObject(&n, id, name);
  copyNamedObject(&(task->followers)[task->_followersCount++], &n);
  return 0;
}
char* getTaskFollowerId(TDA_Task* task, int index) {
  return getNamedObjectId(&(task->followers)[index]);
}
char* getTaskFollowerName(TDA_Task* task, int index) {
  return getNamedObjectName(&(task->followers)[index]);
}
int getTaskFollowersCount(TDA_Task* task) {
  return task->_followersCount;
}


int addTaskProject(TDA_Task* task, char* id, char* name) {
  NamedObject n; createNamedObject(&n, id, name);
  copyNamedObject(&(task->projects)[task->_projectsCount++], &n);
  return 0;
}
char* getTaskProjectId(TDA_Task* task, int index) {
  return getNamedObjectId(&(task->projects)[index]);
}
char* getTaskProjectName(TDA_Task* task, int index) {
  return getNamedObjectName(&(task->projects)[index]);
}
int getTaskProjectsCount(TDA_Task* task) {
  return task->_projectsCount;
}


int getTaskTagNames(TDA_Task* task, char** value) {
  char out[255]; int i;
  if (task->_tagsCount > 0) {
    strcpy(out,  getTaskTagName(task, 0));
    for(i = 1; i < getTaskTagsCount(task); i++) {
      strcat(out, ", ");
      strcat(out, getTaskTagName(task, i));
    }
    strcpy(*value, out);
  } else {
    strcpy(*value, "No hay tags");
  }
  return 0;
}


int readNamedObject(char** content, char** key, NamedObject* obj) {
  int out; int count = 0;
  out = match(content, "{");
  incOpenBrackets();
  while(out > -1) {
    out = parse(content, key);
    if (out > -1) {
      if (strcmp(*key, "id") == 0) {
        count++;
        getInt(content, key);
        setNamedObjectId(obj, *key);
      } else if (strcmp(*key, "name") == 0) {
        count++;
        readString(content, key);
        setNamedObjectName(obj, *key);
      } else {
        break;
      }
      if (count == 2) { // 2 attributes set
        out = match(content, "}");
        if (out > -1) {
          incClosedBrackets();
          out = match(content, ",]");
          return out;
        }
      }
    }
  }
  return -1;
}


int handleKey(TDA_Task* task, char** key, char** content) {
  int out = -1;

  if (strcmp(*key, "data") == 0) {
    match(content, "{");
    incOpenBrackets();
    out = parse(content, key);
    while (out > -1) {
      out = handleKey(task, key, content);
      if (out <= 0) { // out == 0, Stop condition
        return out;
      } else {
        out = parse(content, key);
      }
    }


  } else if (strcmp(*key, "assignee") == 0) {
    NamedObject n;
    out = readNamedObject(content, key, &n);
    setTaskAssignee(task, n.id, n.name);

  } else if (strcmp(*key, "id") == 0) {
    out = getInt(content, key);
    setTaskId(task, *key);

  } else if (strcmp(*key, "name") == 0) {
    out = getString(content, key);
    setTaskName(task, *key);

  } else if (strcmp(*key, "notes") == 0) {
    out = getString(content, key);
    setTaskNotes(task, *key);

  } else if (strcmp(*key, "created_at") == 0) {
    out = getDate(content, key);
    setTaskCreationDate(task, *key);

  } else if (strcmp(*key, "modified_at") == 0) {
    out = getDate(content, key);
    setTaskModificationDate(task, *key);

  } else if (strcmp(*key, "completed_at") == 0) {
    out = getDate(content, key);
    setTaskCompletionDate(task, *key);

  } else if (strcmp(*key, "due_on") == 0) {
    out = getDate(content, key);
    setTaskDueDate(task, *key);

  } else if (strcmp(*key, "completed") == 0) {
    out = getBool(content, key);
    if (out > -1) setTaskCompleted(task, (bool) out);
    out = 2; // Can't return out, because it's 0 on false and 0 is parsing complete

  } else if (strcmp(*key, "tags") == 0) {
    out = match(content, "[");
    while(out > -1 && out != ']') {
      NamedObject n;
      out = readNamedObject(content, key, &n);
      addTaskTag(task, n.id, n.name);
    }
    out = match(content, ",");

  } else {
    out = skipField(content);
    if (out == 0) {
      return 0;
    }
  }

  return out;
}



int createTask(TDA_Task* task, char* path) {
  char* content; int out = 0;
  char* value = malloc(255 * sizeof(char));
  out = getFileContent(path, &content);

  if (out == -1) {
    return 2; // Bad file
  }

  initializeTask(task);

  initializeParser();

  do {
    out = parse(&content, &value);
    if (out > -1) out = handleKey(task, &value, &content);
  } while (out > 0);

  content = '\0'; // Si no hago eso me tira error, porque?

  free(content);
  free(value);

  return out;
}


void printTask(TDA_Task* task) {
  char* tags = malloc(255);
  printf("identificador: %s\n", getTaskId(task));
  printf("asignado a: %s\n", getTaskAssigneeName(task));
  printf("tarea: %s\n", getTaskName(task));
  printf("creada: %s\n", getTaskCreationDate(task));
  printf("ultima modificacion: %s\n", getTaskModificationDate(task));
  printf("notas: %s\n", getTaskNotes(task));
  printf("completada: %s\n", bool2str(getTaskCompleted(task)));
  printf("fecha finalizacion: %s\n", getTaskCompletionDate(task));
  printf("fecha estimada: %s\n", getTaskDueDate(task));
  getTaskTagNames(task, &tags);
  printf("tags: %s\n", tags);
  free(tags);
}
