#include <stdlib.h>
#include "TDA_ProjectDetail.h"
#include <stdio.h>

int main(int argc, char** argv)
{

	char *JsonFile;
	TDA_ProjectDetail ProjectDetail;
    int  i, tareas_sprint;

	if (argc == 2)
	{

		if (TDA_ProjectDetailLoadJson (argv[1], &JsonFile)) /*Se cargó el archivo en JsonFile?*/
		{

			if (TDA_ProjectDetailCreate(&ProjectDetail, JsonFile))
			{
                printf ("tareas: %d\n", cantidad_tareas_total(&ProjectDetail));
                printf ("sprints: %d\n", cantidad_sprints(&ProjectDetail));
                if (primer_sprint(&ProjectDetail))
                {
                    do
                    {
                        printf ("%s",get_namesprint_actual(&ProjectDetail));
                        tareas_sprint= cantidad_tareas_sprint_actual(&ProjectDetail);
                        if(primer_tarea_sprint_actual(&ProjectDetail))
                        {
                            i=0;
                            do
                            {
                                printf(" %s",get_id_tarea_actual_sprint_actual(&ProjectDetail));
                                i++;
                                if(i<tareas_sprint)
                                    printf(",");
                            }while(siguiente_tarea_sprint_actual(&ProjectDetail));
                        }printf("\n");
                    }while(siguiente_sprint(&ProjectDetail));
                }
                free_ProjectDetail(&ProjectDetail);
/*falta liberar memoria, armar los free en primitivas*/
			}
            free (JsonFile);

        }

	}

	return 0;
}
