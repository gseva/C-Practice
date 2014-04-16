/*
  Autor: Gseva
  Fecha: 02.04.2014
*/

#ifndef GLOBAL_GUARD
#define GLOBAL_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#endif

// Current string position
extern int ptr;

// Bracket counters for errors checking
extern int openBrackets;
extern int closedBrackets;


// Searches in str starting from pointer for any character from chrs.
char match(char** str, char* chrs);

/*
 * Reads from str starting from pointer into value until reaching any character
 * from chrs. Returns reached character or -1 in case of error.
 *
 * Preconditions: str is a valid json structure, position in str is appointed by ptr.
 * Postconditions: returns last read character otherwise or -1 if fails.
 */
char readUntil(char** str, char* chrs, char** value);

/*
 * Reads from str starting from pointer a json string into value. Can be null.
 *
 * Preconditions: str is a valid json structure, position in str is appointed by ptr
 *                at the start of a valid json string.
 * Postconditions: returns last read character otherwise or -1 if fails.
 */
int readString(char** str, char** value);

int getNull(char** str, char** value);
int getString(char** str, char** value);
int getInt(char** str, char** value);
int getBool(char** str, char** value);
int getDate(char** str, char** value);

// Skips a field until next key
int skipField(char** str);
int skipUntil(char** str, char* chrs);

int parse(char** str, char** key);

// Needs an open file
int getFileSize(FILE* file, size_t* size);
int getFileContent(char* path, char** content);
