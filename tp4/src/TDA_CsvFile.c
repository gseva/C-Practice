/**
 *
 */


#include "TDA_CsvFile.h"

int initializeCsvFile(CsvFile* csvFile) {
  L_Crear(&(csvFile->rows), ROW_SIZE);
  return 0;
}

int destroyCsvFile(CsvFile* csvFile) {
  L_Vaciar(&(csvFile->rows));
  return 0;
}

int addRow(CsvFile* csvFile, char* row) {
  char aux[ROW_SIZE];
  strcpy(aux, row);

  if (L_Vacia(csvFile->rows)) {
    L_Insertar_Cte(&(csvFile->rows), L_Primero, &aux);
  } else {
    L_Insertar_Cte(&(csvFile->rows), L_Siguiente, &aux);
  }

  return 0;
}

int export(CsvFile* csvFile, char* path) {
  FILE *f = fopen(path, "w"); char aux[ROW_SIZE];
  if (f == NULL) {
      printf("Error opening file!\n");
      return 1;
  }

  L_Mover_Cte(&(csvFile->rows), L_Primero);
  do {
    L_Elem_Cte(csvFile->rows, &aux);
    fprintf(f, "%s\n", aux);
  } while(L_Mover_Cte(&(csvFile->rows), L_Siguiente));

  return fclose(f);
}
