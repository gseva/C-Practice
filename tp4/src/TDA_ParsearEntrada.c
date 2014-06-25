
#include "TDA_ParsearEntrada.h"


int pedirInstrucciones(Command* command) {
	char ILinea[MAX_LINE_SIZE];
	char *Laux, cmdAux;

	command->action = ERROR;
	command->format = 0;
	command->keyCount = 0;
	command->valueCount = 0;
	command->sortKey = NULL;
	command->sortOrder = 0;
	command->file = NULL;

	if (fgets(ILinea, MAX_LINE_SIZE, stdin) == NULL)
		return -1;
	ILinea[strlen(ILinea)-1] = '\0'; // saco el ultimo salto de linea

	Laux = strtok (ILinea, " ");
	if (strcmp(Laux,"query")==0)
		command->action = QUERY;
	else if (strcmp(Laux,"report")==0)
		command->action = REPORT;
	else if (strcmp(Laux,"exit")==0){
		command->action = EXIT;
		return 0;
	} else {
		command->action = ERROR;
		return -1; //la instruccion ingresada es incorrecta
	}


	cmdAux='\0';

	Laux = strtok (NULL, " ");
	do {
		if (strcmp(Laux,"-p")==0){
			if (command->format && command->format != MULTIPLE_KEY) {
				command->action = ERROR;
			} else {
				command->format = MULTIPLE_KEY;
				cmdAux='p';
			}
		} else if (strcmp(Laux,"-k") == 0){
			if (command->format && command->format == MULTIPLE_VALUE) {
				command->action = ERROR;
			} else {
				cmdAux='k';
			}
		} else if (strcmp(Laux,"-v") == 0){
			if (command->format) {
				command->action = ERROR;
			} else {
				command->format = SINGLE_VALUE;
				cmdAux='v';
			}
		} else if (strcmp(Laux,"-s")==0) {
			if (command->format) {
				command->action = ERROR;
			} else {
				command->format = MULTIPLE_VALUE;
				cmdAux='s';
			}
		}else if (strcmp(Laux,"-a")==0)
			cmdAux='a';
		else if (strcmp(Laux,"-d")==0)
			cmdAux='d';
		else if (strcmp(Laux,"-o")==0)
			if (command->action != REPORT) {
				command->action = ERROR;
			} else {
				cmdAux='o';
			}
		else {
			if (command->action)
			switch (cmdAux) {
			case 'p':
				strcpy(command->values[command->valueCount], Laux+strcspn(Laux,":")+1);
				Laux[strcspn(Laux,":")]='\0';
				strcpy(command->keys[command->keyCount], Laux);
				command->keyCount++; command->valueCount++;
				cmdAux='\0';
				break;
			case 'k':
				if (command->keyCount==0) {
					strcpy(command->keys[0], Laux);
					command->keyCount++;
				} else {
					strcat(command->keys[0], " ");
					strcat(command->keys[0], Laux);
				}
				break;
			case 'v':
				if (command->valueCount==0) {
					strcpy(command->values[0], Laux);
					command->valueCount++;
				} else {
					strcat(command->values[0], " ");
					strcat(command->values[0], Laux);
				}
				break;
			case 's':
				if (command->valueCount == MAX_VALUES - 1) {
					printf("Too much values\n");
					command->action = ERROR;
				} else {
					strcpy(command->values[command->valueCount], Laux);
					command->valueCount++;
				}
				break;
			case 'a':
			case 'd':
				command->sortKey = malloc(strlen(Laux));
				strcpy(command->sortKey, Laux);
				command->sortOrder = cmdAux;
				cmdAux='\0';
				break;
			case 'o':
				command->file = malloc(strlen(Laux));
				strcpy(command->file, Laux);
				cmdAux='\0';
				break;
			default:
				command->action = ERROR;
				break;
			}
		}
		Laux = strtok (NULL, " ");
	} while (Laux != NULL && command->action != ERROR);

	if ((command->keyCount && !command->valueCount) || (!command->keyCount && command->valueCount))
		command->action = ERROR;

	if (command->action == REPORT && !command->file) {
		printf("Please, specify file name with -o option\n");
		command->action = ERROR;
	}

	return 1;
}



int getAction(Command* command) {
	return command->action;
}

int getFormat(Command* command) {
	return command->format;
}

int getKeyCount(Command* command) {
	return command->keyCount;
}
char* getKeyByIndex(Command* command, int i) {
	return command->keys[i];
}

int getValueCount(Command* command) {
	return command->valueCount;
}
char* getValueByIndex(Command* command, int i) {
	return command->values[i];
}

char* getSortKey(Command* command) {
	return command->sortKey;
}
char getSortOrder(Command* command) {
	return command->sortOrder;
}

char* getFileName(Command* command) {
	return command->file;
}


//report -k <key_field0> -v <value_field0> -v <value_field1> -k <key_field1> -d ord -o file.txt
