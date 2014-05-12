#include "TDA_ProjectDetail.h"

typedef struct
        {

            char id[15];
            char name[51];

        } TDA_tareas;

typedef struct
        {

            char idsprint[15];
            char sprintname[51];
            TListaSimple tareas;

        } TDA_sprint;

void set_id (TDA_tareas *tarea, char * id)
{

    strcpy (tarea->id, id);

}

void set_name (TDA_tareas *tarea, char* name)
{

    strcpy(tarea->name, name);

}

void crear_tarea (TDA_sprint *sprint, char* name, char* id)
{

    TDA_tareas tarea;

    set_id(&tarea,id);
    set_name(&tarea, name);
    if (L_Vacia(sprint->tareas))
        L_Insertar_Cte(&(sprint->tareas), L_Primero, &tarea);
    else
        L_Insertar_Cte(&(sprint->tareas), L_Siguiente, &tarea);

}

void get_sprint_actual(TDA_ProjectDetail *ProjectDetail, TDA_sprint *sprint)
{

    L_Elem_Cte(ProjectDetail->sprints, sprint);

}

void crear_Ltarea (TDA_sprint *sprint)
{

    L_Crear(&(sprint->tareas), sizeof(TDA_tareas));

}

void set_sprintname (TDA_sprint *sprint, char* name)
{

    strcpy(sprint->sprintname, name);

}

void set_sprintid (TDA_sprint *sprint, char* id)
{

    strcpy(sprint->idsprint, id);

}

void new_sprint (TDA_ProjectDetail *ProjectDetail, char* name, char* id)
{

    TDA_sprint* sprint = malloc(sizeof(TDA_sprint));

    set_sprintid (sprint, id);
    set_sprintname (sprint, name);
    L_Crear(&(sprint->tareas), sizeof(TDA_tareas));

    if (L_Vacia(ProjectDetail->sprints))
        L_Insertar_Cte(&(ProjectDetail->sprints), L_Primero, sprint);
    else
        L_Insertar_Cte(&(ProjectDetail->sprints), L_Siguiente, sprint);
    free(sprint);
}

void inicializar_ProjectDetail (TDA_ProjectDetail *ProjecDetail)
{

    L_Crear(&(ProjecDetail->sprints), sizeof(TDA_sprint));

}

int TDA_ProjectDetailCreate (TDA_ProjectDetail* ProjectDetail, char* JsonFile)
{
    char *text, *aux_name, *aux_id;
    char palabra[10];
    int mov;
    TDA_sprint aux_sprint;
    strcpy(palabra, "data");
    text = strstr(JsonFile, palabra);

    if (text)/*archivo no vacio*/
    {

        inicializar_ProjectDetail (ProjectDetail);
        while (strchr(text, '{'))/*hay info para parsear*/
        {
            /*
                parsear id
            */

            strcpy(palabra, "\"id\"");
            aux_id = parsear_campo (&text, palabra, 15, ':',',');

            /*
                parsear name
            */

            strcpy(palabra, "\"name\"");
            aux_name= parsear_campo (&text, palabra, 51, '"', '"');


            if (aux_name[strlen(aux_name)-1] == ':') /*es un sprint*/
            {
                new_sprint (ProjectDetail, aux_name, aux_id);
                get_sprint_actual(ProjectDetail, &aux_sprint);
            }
            else
            {
                crear_tarea (&aux_sprint, aux_name, aux_id);
                L_Modificar_Cte(ProjectDetail->sprints, &aux_sprint);

            }
        }
        return 1;
    }
	return 0;
}

int siguiente_sprint (TDA_ProjectDetail *ProjectDetail)
{

    return L_Mover_Cte(&(ProjectDetail->sprints), L_Siguiente);

}

int primer_tarea (TDA_sprint *sprint)
{

    return L_Mover_Cte(&(sprint->tareas), L_Primero);

}

int primer_tarea_sprint_actual (TDA_ProjectDetail *ProjectDetail)
{
    TDA_sprint aux_sprint; int aux;

    L_Elem_Cte(ProjectDetail->sprints, &aux_sprint);
    aux = primer_tarea(&aux_sprint);
    if (aux) L_Modificar_Cte(ProjectDetail->sprints, &aux_sprint);
    return aux;
}

int siguiente_tarea (TDA_sprint *sprint) /*termina aca*/
{
    int aux;
    TDA_tareas t;
    L_Elem_Cte(sprint->tareas, &t);
    aux = L_Mover_Cte(&(sprint->tareas), L_Siguiente);
    return aux;
}

int siguiente_tarea_sprint_actual (TDA_ProjectDetail *ProjectDetail)/*problema se traslada aca*/
{

    TDA_sprint aux_sprint; int aux;
    get_sprint_actual(ProjectDetail, &aux_sprint);
    aux = siguiente_tarea (&aux_sprint);
    if (aux) L_Modificar_Cte(ProjectDetail->sprints, &aux_sprint);
    return aux;

}

int primer_sprint (TDA_ProjectDetail *ProjectDetail)
{

    return L_Mover_Cte(&(ProjectDetail->sprints), L_Primero);

}

int cantidad_tareas_sprint_actual (TDA_ProjectDetail *ProjectDetail)/*problema aca*/
{

    int total= 0;
    if (primer_tarea_sprint_actual(ProjectDetail))
    {
        do
        {
            total++;

        }while (siguiente_tarea_sprint_actual(ProjectDetail));/*no anda aca....*/

    }

    return total;
}

int cantidad_tareas_total (TDA_ProjectDetail *ProjectDetail)
{

    int total=0, aux=0;
    if (primer_sprint(ProjectDetail))
    {
        do
        {
            aux = cantidad_tareas_sprint_actual(ProjectDetail);
            total += aux;
        }while (siguiente_sprint(ProjectDetail));
    }
    return total;

}

int cantidad_sprints(TDA_ProjectDetail *ProjectDetail)
{

    int total=0;

    if (primer_sprint (ProjectDetail))
    {

        do
        {

            total++;

        }while (siguiente_sprint(ProjectDetail));

    }
    return total;
}

void get_tarea_actual_sprint_actual(TDA_ProjectDetail *ProjectDetail, TDA_tareas *tarea)
{

    TDA_sprint aux_sprint;

    get_sprint_actual(ProjectDetail,&aux_sprint);
    L_Elem_Cte(aux_sprint.tareas, tarea);

}

char* get_name_tarea_actual_sprint_actual (TDA_ProjectDetail *ProjectDetail)
{

    TDA_tareas aux_tarea;
    get_tarea_actual_sprint_actual(ProjectDetail, &aux_tarea);
    return aux_tarea.name;

}

char* get_id_tarea_actual_sprint_actual (TDA_ProjectDetail *ProjectDetail)
{

    TDA_tareas aux_tarea;
    get_tarea_actual_sprint_actual(ProjectDetail, &aux_tarea);
    return aux_tarea.id;

}

char * get_idsprint_actual(TDA_ProjectDetail *ProjectDetail)
{
    TDA_sprint aux_sprint;

    get_sprint_actual(ProjectDetail, &aux_sprint);

    return aux_sprint.idsprint;
}

char *get_namesprint_actual(TDA_ProjectDetail *ProjectDetail)
{
    TDA_sprint aux_sprint;

    get_sprint_actual(ProjectDetail, &aux_sprint);

    return aux_sprint.sprintname;
}

int TDA_ProjectDetailLoadJson (char* root, char** JsonFile)
{

    FILE *FileProjectDetail;
    size_t length;

    FileProjectDetail= fopen (root, "rb");
    if (FileProjectDetail != NULL)
    {

        fseek(FileProjectDetail, 0, SEEK_END);
        length= ftell(FileProjectDetail);
        fseek (FileProjectDetail, 0, SEEK_SET);
        *JsonFile= (char*) malloc(length * sizeof(char));
        fread(*JsonFile, length, 1, FileProjectDetail);
        fclose(FileProjectDetail);


        return 1;

    }
    else return 0;

}

void free_ProjectDetail (TDA_ProjectDetail *ProjectDetail)
{
    TDA_sprint aux_sprint;

    primer_sprint (ProjectDetail);
    do
    {
        get_sprint_actual(ProjectDetail,&aux_sprint);
        L_Vaciar(&(aux_sprint.tareas));
    }while (siguiente_sprint(ProjectDetail));
    L_Vaciar(&(ProjectDetail->sprints));
}
