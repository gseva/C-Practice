/**
 *
 */

#ifndef TDA_CSVFILE_H_INCLUDED
  #define TDA_CSVFILE_H_INCLUDED

  #include <stdio.h>
  #include <stdio.h>
  #include <string.h>

  #include "Lista.h"

  #define ROW_SIZE 1024

  typedef struct _CsvFile {

    TListaSimple rows;

  } CsvFile;

  int initializeCsvFile(CsvFile* csvFile);
  int destroyCsvFile(CsvFile* csvFile);

  int addRow(CsvFile* csvFile, char* row);

  int export(CsvFile* csvFile, char* path);

#endif // TDA_CSVFILE_H_INCLUDED
