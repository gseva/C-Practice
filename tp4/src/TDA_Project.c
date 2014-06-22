#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_Project.h"



char* substring ( const char * source, int startIndex, int endIndex) {
    char *result="";
    if (startIndex < 0) {
        printf("startIndex should be a positive value\n");
    }
    else if (endIndex <= startIndex) {
        //printf("endIdnex should larger than startIndex\n");
    } else if (startIndex > (strlen(source))) {
        printf("startIdnex should smaller than source length\n");
    } else if (endIndex > (strlen(source)+1)) {
        printf("endIdnex should smaller than or equal to source length\n");
    } else {
        int len = endIndex - startIndex;
        result = (char*)malloc(sizeof(char)*len+1);
        memset (result, '\0', len+1);
        strncpy (result, source+startIndex, len);
	}
	return result;
}


char* copiarcad(char *cadena){
	int fin=0,ini=0;
	
	ini=strcspn(cadena,":")+2;
	fin=strlen(cadena)-1;
	if (cadena[ini]=='"')
		ini=ini+1;
	while ((cadena[fin]=='"')||(cadena[fin]==',')||(cadena[fin]==' ')||(cadena[fin]=='\n'))
		fin=fin-1;
	fin=fin+1;
	return substring(cadena,ini,fin);
}










void CrearProj(void *pProject){
	//pProject=(Project*) malloc(sizeof(Project));
}

void EliminarProj(Project *pProject){
/*	free(pProject->followers);
	free(pProject->members);
	free(pProject->workspace);
	free(pProject);
	*/
}






void Set_followers_cont(Project *pProject,int Valor){
	pProject->followers_cont=Valor;
}
void Set_members_cont(Project *pProject,int Valor){
	pProject->members_cont=Valor;
}
void Set_workspace_cont(Project *pProject,int Valor){
	pProject->workspace_cont=Valor;
}

int Get_followers_cont(Project* pProject){
	return pProject->followers_cont;
}
int Get_members_cont(Project* pProject){
	return pProject->members_cont;
}
int Get_workspace_cont(Project* pProject){
	return pProject->workspace_cont;
}




void Set_archived(Project *pProject,char* Valor){
	if (strstr(Valor,"true")!=0)
		pProject->archived=1;
	else
		pProject->archived=0;
}
void Set_color(Project *pProject,char *Valor){
	strcpy(pProject->color,Valor);
}
void Set_created_at(Project *pProject,char *Valor){
	strcpy(pProject->created_at,Valor);
	strcpy(pProject->created_at+10,"\0");
}
void Set_followers(Project *pProject,char *sID,char *sName){
	int pos=Get_followers_cont(pProject);
	strcpy(pProject->followers[pos].pID,sID);
	strcpy(pProject->followers[pos].pName,sName);
	Set_followers_cont(pProject,(pos+1));
}
void Set_id(Project *pProject,char *Valor){
	strcpy(pProject->id,Valor);
}
void Set_members(Project *pProject,char *sID,char *sName){
	int pos=Get_members_cont(pProject);
	strcpy(pProject->members[pos].pID,sID);
	strcpy(pProject->members[pos].pName,sName);
	Set_members_cont(pProject,(pos+1));
}
void Set_modified_at(Project *pProject,char *Valor){
	strcpy(pProject->modified_at,Valor);
	strcpy(pProject->modified_at+10,"\0");
}
void Set_name(Project *pProject,char *Valor){
	strcpy(pProject->name,Valor);
}
void Set_notes(Project *pProject,char *Valor){
	strcpy(pProject->notes,Valor);
}
void Set_public(Project *pProject,char* Valor){
	if (strstr(Valor,"true")!=0)
		pProject->public=1;
	else
		pProject->public=0;
}
void Set_workspace(Project *pProject,char *sID,char *sName){
	int pos=Get_workspace_cont(pProject);
	strcpy(pProject->workspace[pos].pID,sID);
	strcpy(pProject->workspace[pos].pName,sName);
	Set_workspace_cont(pProject,(pos+1));
}






char* Get_archived(Project *pProject){
	return (pProject->archived=0)?"False":"True";
}
char* Get_color(Project *pProject){
	return pProject->color;
}
char* Get_created_at(Project *pProject){
	return pProject->created_at;
}
int Get_followers_id(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_followers_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->followers[i].pID)+1)))
		//	return 1;
		strcat(*cadena,pProject->followers[i].pID);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}
int Get_followers_name(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_followers_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->followers[i].pName)+1)))
		//	return 1;
		strcat(*cadena,pProject->followers[i].pName);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}
char* Get_id(Project *pProject){
	return pProject->id;
}
int Get_members_id(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_members_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->members[i].pID)+1)))
		//	return 1;
		strcat(*cadena,pProject->members[i].pID);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}
int Get_members_name(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_members_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->members[i].pName)+1)))
		//	return 1;
		strcat(*cadena,pProject->members[i].pName);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}
char* Get_modified_at(Project *pProject){
	return pProject->modified_at;
}
char* Get_name(Project *pProject){
	return pProject->name;
}
char* Get_notes(Project *pProject){
	return pProject->notes;
}
char* Get_public(Project *pProject){
	return (pProject->public=0)?"False":"True";
}
int Get_workspace_id(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_workspace_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->workspace[i].pID)+1)))
		//	return 1;
		strcat(*cadena,pProject->workspace[i].pID);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}
int Get_workspace_name(Project *pProject,char** cadena){
	int i,cant;
	cant=Get_workspace_cont(pProject);
	*cadena=(char*) malloc(sizeof(char)*(cant*255));
	strcpy(*cadena,"");
	for (i=0;i<(cant);i++){
		//if (realloc(*cadena,(strlen(*cadena)+strlen(pProject->workspace[i].pName)+1)))
		//	return 1;
		strcat(*cadena,pProject->workspace[i].pName);
		if (i!=(cant-1))
			strcat(*cadena,", ");
	}
	return 0;
}























void InicProj(Project *pProject){
	
	Set_archived(pProject,"false");
	Set_color(pProject,"");
	Set_created_at(pProject,"");
	Set_id(pProject,"");
	Set_modified_at(pProject,"");
	Set_name(pProject,"");
	Set_notes(pProject,"");
	Set_public(pProject,"false");
	Set_followers_cont(pProject,0);
	Set_members_cont(pProject,0);
	Set_workspace_cont(pProject,0);
	
}













int TraerLinea(char** Cadena,char** Salida,size_t* pos){
	char* cBusq="{}[],";
	size_t posAnt;
	
	posAnt=*pos;
	*pos=strcspn(*Cadena+posAnt,cBusq)+posAnt;
	if (posAnt==*pos)
		*pos=*pos+1;
	if ((*pos==0)||(*pos>strlen(*Cadena)))
		return 0;
	*Salida=substring(*Cadena,posAnt,*pos);
	//*pos=*pos+1;
	return 1;
}





void CargarProj(Project* pProject,char Archivo[]){
	
	size_t fLen;
	char* Linea;
	char* sID = malloc(255 * sizeof(char));
	char* sName = malloc(255 * sizeof(char));
	int EsperaFin=0;
	InicProj(pProject);
	
	FILE* pFile = fopen(Archivo, "r");
	if (pFile!=NULL){
		fseek(pFile,0,SEEK_END);
		fLen=ftell(pFile);
		fseek(pFile,0,SEEK_SET);
			
		Linea = malloc(fLen);
		if (fread(Linea,fLen,1,pFile)==0)
			return;
		
		fclose(pFile);
		
		
		
		char* nLinea;
		size_t pos=0;
		
		while(TraerLinea(&Linea,&nLinea,&pos)!=0){
			
			if (strstr(nLinea,"archived")!=0) {
				Set_archived(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"color")!=0) {
				Set_color(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"created_at")!=0) {
				Set_created_at(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"followers")!=0) {
				EsperaFin=0;
				while ((strstr(nLinea,"]")==0)&&((EsperaFin==1)||(strstr(nLinea,"}")==0))&&(TraerLinea(&Linea,&nLinea,&pos)!=0)){
					if (strstr(nLinea,"}")!=0){
						Set_followers(pProject,sID,sName);
						strcpy(sID,"");
						strcpy(sName,"");
					}
					else if (strstr(nLinea,"[")!=0)
						EsperaFin=1;
					else if (strstr(nLinea,"id")!=0) 
						sID=copiarcad(nLinea);
					else if (strstr(nLinea,"name")!=0) 
						sName=copiarcad(nLinea);
				}
				if (EsperaFin==0){
					Set_followers(pProject,sID,sName);
					strcpy(sID,"");
					strcpy(sName,"");
				}
			}
			else if (strstr(nLinea,"id")!=0) {
				Set_id(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"members")!=0) {
				EsperaFin=0;
				while ((strstr(nLinea,"]")==0)&&((EsperaFin==1)||(strstr(nLinea,"}")==0))&&(TraerLinea(&Linea,&nLinea,&pos)!=0)){
					if (strstr(nLinea,"}")!=0){
						Set_members(pProject,sID,sName);
						strcpy(sID,"");
						strcpy(sName,"");
					}
					else if (strstr(nLinea,"[")!=0)
						EsperaFin=1;
					else if (strstr(nLinea,"id")!=0) 
						sID=copiarcad(nLinea);
					else if (strstr(nLinea,"name")!=0) 
						sName=copiarcad(nLinea);
				}
				if (EsperaFin==0){
					Set_members(pProject,sID,sName);
					strcpy(sID,"");
					strcpy(sName,"");
				}
			}
			else if (strstr(nLinea,"modified_at")!=0) {
				Set_modified_at(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"name")!=0) {
				Set_name(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"notes")!=0) {
				Set_notes(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"public")!=0) {
				Set_public(pProject,copiarcad(nLinea));
			}
			else if (strstr(nLinea,"workspace")!=0) {
				EsperaFin=0;
				while ((strstr(nLinea,"]")==0)&&((EsperaFin==1)||(strstr(nLinea,"}")==0))&&(TraerLinea(&Linea,&nLinea,&pos)!=0)){
					if (strstr(nLinea,"}")!=0){
						Set_workspace(pProject,sID,sName);
						strcpy(sID,"");
						strcpy(sName,"");
					}
					else if (strstr(nLinea,"[")!=0)
						EsperaFin=1;
					else if (strstr(nLinea,"id")!=0) 
						sID=copiarcad(nLinea);
					else if (strstr(nLinea,"name")!=0) 
						sName=copiarcad(nLinea);
				}
				if (EsperaFin==0){
					Set_workspace(pProject,sID,sName);
					strcpy(sID,"");
					strcpy(sName,"");
				}
			}
			
			
			
		}

		
		
		free(Linea);
		free(sName);
		free(sID);
	
	}
	
}



	
	
