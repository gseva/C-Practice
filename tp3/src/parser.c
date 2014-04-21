/*
  Autor: Gseva
  Fecha: 02.04.2014
*/

#include "parser.h"


// Current string position
int ptr = 0;

// Counters for errors checking
int openBrackets = 0;
int closedBrackets = 0;


char match(char** str, char* chrs) {
  char c = -1;
  while(c) {
    c = *(*str + ++ptr - 1);
    if (!isspace(c)) break;
  }
  return strchr(chrs, c) ? c : -1;
}


char readUntil(char** str, char* chrs, char** value) {
  int i = 0; char c = -1; char aux[255];
  while(c) {
    c = *(*str + ptr + i);
    if (strchr(chrs, c)) {
      aux[i] = '\0';
      *value = realloc(*value, strlen(aux)+1);
      strcpy(*value, aux);
      ptr = ptr + ++i; // Pointer is set to a current position
      break;
    } else {
      aux[i] = c;
    }
    i++;
  }
  return c;
}


int readString(char** str, char** value) {
  char c;

  c = match(str, "\"");
  if (c == -1) return -1;
  c = readUntil(str, "\"", value);

  return c;
}


int readField(char** str, char** value) {
  char c = readUntil(str, " ,", value);
  if (c == ' ') {
    c = match(str, ",");
  }
  return c;
}


int getNull(char** str, char** value) {
  char c = *(*str + ptr-- - 1);
  if (c == 'n') c = readField(str, value);
  if (strcmp(*value, "null") == 0) {
    return c;
  }
  return -1;
}


int getBool(char** str, char** value) {
  char c;
  c = match(str, "tf");
  if (c > -1) {
    ptr--;
    c = readField(str, value);
  }
  if (c > -1) {
    if (strcmp(*value, "true") == 0) {
      return 1;
    } else if (strcmp(*value, "false") == 0) {
      return 0;
    } else {
      return -1;
    }
  }
  return c;
}


int getInt(char** str, char** value) {
  char c;
  c = match(str, "1234567890");
  if (c == -1) return -1;
  ptr--;
  c = readField(str, value);
  return c;
}


int getDate(char** str, char** value) {
  int out = getString(str, value);
  if (out < 0) return out;
  if (strcmp(*value, "null") == 0) return out;
  *(*value + 10) = '\0';
  return out;
}


int getString(char** str, char** value) {
  int out = -1;
  out = readString(str, value);
  if (out == -1) return getNull(str, value);
  out = match(str, ",");
  return out;
}


int skipUntil(char** str, char* chrs) {
  char c;
  do {
    c = *(*str + ++ptr);
    if (strchr(chrs, c)) break;
  } while(c);
  return c;
}


int skipField(char** str) {
  char chrs[10]; char c; int i = 0;
  chrs[0] = ',';
  c = *(*str + ptr);
  while(c && (i > -1)) {
    if (c == chrs[i]) {
      if (c != ',') closedBrackets++;
      i--;

    } else if (c == '{') {
      openBrackets++;
      chrs[++i] = '}';

    } else if (c == '[') {
      openBrackets++;
      chrs[++i] = ']';

    } else if (c == '}' || c == ']') {
      closedBrackets++;

    } else if (c == '"') {
      if (skipUntil(str, "\"") < 0) return -1;
    }

    c = *(*str + ++ptr);
    if (closedBrackets == openBrackets) return 0;
  }
  return c ? c : -1;
}


int parse(char** str, char** key) {
  char c; int out;
  if (ptr == 0) {
    openBrackets++;
    c = match(str, "{[");
    if (c == -1)
      return -1;
  }
  out = readString(str, key);
  c = match(str, ":");
  if (c == -1)
    return -1;
  return out;
}



int getFileSize(FILE* file, size_t* size) {
  fseek(file, 0, SEEK_END);
  *size = ftell(file);
  if(*size != -1L) {
    fseek(file, 0, SEEK_SET);
    return 0;
  } else {
    return -1;
  }
}


int getFileContent(char* path, char** content) {
  size_t size;
  FILE* file = fopen(path, "rb");

  if (file == NULL)
    return -1;
  else {
    // Check for errors
    getFileSize(file, &size);

    // Check for errors
    *content = malloc(size);

    // Check for errors
    fread(*content, size, 1, file);

  }

  fclose (file);
  return 0;
}
