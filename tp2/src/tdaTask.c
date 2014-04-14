/*
  Autor: Gavrilov Vsevolod
  Fecha: 02.04.2014
*/


#include "tdaTask.h"


int setNamedObjectId(NamedObject* o, char* id) {
  strcpy(o->id, id);
  return 0;
}


int setNamedObjectName(NamedObject* o, char* name) {
  // o->name = malloc(strlen(name));
  strcpy(o->name, name);
  return 0;
}


int setTaskAssignee(TDA_Task* task, NamedObject* assignee) {
  task->assignee = *assignee;
  return 0;
}


int initializeTask(TDA_Task* task) {
  task->tagsCount = 0;
  return 0;
}


int setTaskId(TDA_Task* task, char* id) {
  strcpy(task->id, id);
  return 0;
}


int setTaskName(TDA_Task* task, char* name) {
  strcpy(task->name, name);
  return 0;
}


int setTaskNotes(TDA_Task* task, char* notes) {
  strcpy(task->notes, notes);
  return 0;
}


int setTaskCreationDate(TDA_Task* task, char* date) {
  strcpy(task->createdAt, date);
  return 0;
}


int setTaskModificationDate(TDA_Task* task, char* date) {
  strcpy(task->modifiedAt, date);
  return 0;
}


int setTaskCompletionDate(TDA_Task* task, char* date) {
  strcpy(task->completedAt, date);
  return 0;
}


int setTaskDueDate(TDA_Task* task, char* date) {
  strcpy(task->dueOn, date);
  return 0;
}


int setTaskCompleted(TDA_Task* task, bool completed) {
  task->completed = completed;
  return 0;
}


int addTaskTag(TDA_Task* task, NamedObject* tag) {
  task->tags[task->tagsCount++] = *tag;
  return 0;
}


char* getBoolString(bool b) {
  return b ? "Si" : "No";
}


int getTaskTagNames(TDA_Task* task, char** value) {
  char out[255]; int i;
  if (task->tagsCount > 0) {
    strcpy(out, task->tags[0].name);
    for(i = 1; i < task->tagsCount; i++) {
      strcat(out, ", ");
      strcat(out, task->tags[i].name);
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
  openBrackets++;
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
          closedBrackets++;
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
    openBrackets++;
    out = parse(content, key);
    while (out > -1) {
      out = handleKey(task, key, content);
      if (!out) { // out == 0, Stop condition
        return out;
      } else if (out < 0) {
        return out;
      } else {
        out = parse(content, key);
      }
    }


  } else if (strcmp(*key, "assignee") == 0) {
    NamedObject n;
    out = readNamedObject(content, key, &n);
    setTaskAssignee(task, &n);

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
      addTaskTag(task, &n);
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

  do {
    out = parse(&content, &value);
    if (out > -1) out = handleKey(task, &value, &content);
  } while (out > 0);

  content = '\0'; // Si no hago eso me tira error, porque?

  free(content);
  free(value);

  return out;
}
