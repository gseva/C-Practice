
#include <stdio.h>
#include "TDA_ParsearEntrada.h"

int main(int argc, char* argv[]) {
	CmdIn pCmdIn;
	while (pedirInstrucciones(&pCmdIn))
		printf("Secuencia de comandos Incorrecta.\n");
	
	if (pCmdIn.Accion==0)
		return 0;
	
	printf("\nAccion: %d\n",pCmdIn.Accion);
	printf("fltCant: %d\n",pCmdIn.fltCant);
	int i;
	for(i=0;i<(pCmdIn.fltCant);i++){
		printf("fltKey-%d: %s\n",i,pCmdIn.fltKey[i]);
		printf("fltValue-%d: %s\n",i,pCmdIn.fltValue[i]);
	}
	printf("ordKey: %s\n",pCmdIn.ordKey);
	printf("ordOrient: %c\n",pCmdIn.ordOrient);
	printf("FName: %s\n",pCmdIn.FName);
	
	return 0;
}





