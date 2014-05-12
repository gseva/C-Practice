#ifndef parserDetail_h
#define parserDetail_h
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
    parsear_campo

    PRE:
        *palabra campo y final_char en texto a parsear
    POST:
        *parsear_campo contiene un puntero a el resultado del parseo
        *la variable debe ser destruida con free por el usuario luego
*/
char* parsear_campo (char **text, char *campo, int sizemax_dat, char init_char, char final_char);
#endif
