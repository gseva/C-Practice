

typedef struct st_Persona{
		char pID[15];
        char pName[255];
		} Persona;

typedef struct st_Project{
		short int archived;
        char color[50];
        char created_at[25];
        Persona followers[100];
		int followers_cont;
        char id[15];
        Persona members[100];
		int members_cont;
        char modified_at[25];
        char name[255];
        char notes[255];
        short int public;
        Persona workspace[100];
		int workspace_cont;
	} Project;


void CrearProj(void *pProject);
void EliminarProj(Project *pProject);
void InicProj(Project* pProject);

void CargarProj(Project* pProject,char Archivo[]);




int Get_followers_cont(Project* pProject);
int Get_members_cont(Project* pProject);
int Get_workspace_cont(Project* pProject);




void Set_archived(Project *pProject,char* Valor);
void Set_color(Project *pProject,char *Valor);
void Set_created_at(Project *pProject,char *Valor);
void Set_followers(Project *pProject,char *id,char *name);
void Set_id(Project *pProject,char *Valor);
void Set_members(Project *pProject,char *id,char *name);
void Set_modified_at(Project *pProject,char *Valor);
void Set_name(Project *pProject,char *Valor);
void Set_notes(Project *pProject,char *Valor);
void Set_public(Project *pProject,char* Valor);
void Set_workspace(Project *pProject,char *id,char *name);



char* Get_archived(Project *pProject);
char* Get_color(Project *pProject);
char* Get_created_at(Project *pProject);
int Get_followers_id(Project *pProject,char** cadena);
int Get_followers_name(Project *pProject,char** cadena);
char* Get_id(Project *pProject);
int Get_members_id(Project *pProject,char** cadena);
int Get_members_name(Project *pProject,char** cadena);
char* Get_modified_at(Project *pProject);
char* Get_name(Project *pProject);
char* Get_notes(Project *pProject);
char* Get_public(Project *pProject);
int Get_workspace_id(Project *pProject,char** cadena);
int Get_workspace_name(Project *pProject,char** cadena);


