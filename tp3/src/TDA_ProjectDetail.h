#ifndef TDA_ProjectDetail_h
#define TDA_ProjectDetail_h
#include <stdio.h>
#include <stdlib.h>
#include "parserDetail.h"
#include "Lista.h"


typedef struct
        {

            TListaSimple sprints;

        } TDA_ProjectDetail;

void new_sprint (TDA_ProjectDetail *ProjectDetail, char* name, char* id);

void inicializar_ProjectDetail (TDA_ProjectDetail *ProjecDetail);

int TDA_ProjectDetailCreate (TDA_ProjectDetail* ProjectDetail, char* JsonFile);

int siguiente_sprint (TDA_ProjectDetail *ProjectDetail);

int primer_tarea_sprint_actual (TDA_ProjectDetail *ProjectDetail);

int siguiente_tarea_sprint_actual (TDA_ProjectDetail *ProjectDetail);

int primer_sprint (TDA_ProjectDetail *ProjectDetail);

int cantidad_tareas_sprint_actual (TDA_ProjectDetail *ProjectDetail);

int cantidad_tareas_total (TDA_ProjectDetail *ProjectDetail);

int cantidad_sprints(TDA_ProjectDetail *ProjectDetail);

char* get_name_tarea_actual_sprint_actual (TDA_ProjectDetail *ProjectDetail);

char* get_id_tarea_actual_sprint_actual (TDA_ProjectDetail *ProjectDetail);

char* get_idsprint_actual(TDA_ProjectDetail *ProjectDetail);

char *get_namesprint_actual(TDA_ProjectDetail *ProjectDetail);

int TDA_ProjectDetailLoadJson (char* root, char** JsonFile);

void free_ProjectDetail (TDA_ProjectDetail *ProjectDetail);

#endif
