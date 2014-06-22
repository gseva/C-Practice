#include "parserDetail.h"
char* parsear_campo (char **text, char *campo, int sizemax_dat, char init_char,char final_char)
{/*campo= "id" o "name", sin espacios ni :*/
    int i, dospuntos;
    char *aux;

    *text= strstr(*text, campo) + strlen(campo); /*me paro luego de de que aparece el nombre del campo*/
    i= 0;
    dospuntos= 0;
    while (((*text)[i] == ' ') || ((*text)[i] == '\t') || ((*text)[i] == '\n') ||
            ((*text)[i] == ':') || ((*text)[i] == init_char))
    {
        if ((*text)[i] == ':')
            dospuntos= 1;
        i++;

    }
    *text= *text + i;
    if (dospuntos)
    {
        aux= malloc(sizemax_dat);
        i= 0;
        while ((i < sizemax_dat) && ((*text)[i] != final_char)) /*cargo aux copiando caracter a caracter mientras
                                                                el tamaño sea valido y no se encuentre el caracter
                                                                que indica finaliazacion de campo
                                                            */
        {

            aux[i]= (*text)[i];
            i++;

        }
        aux[i]= '\0';
        *text= *text + i;
        return(aux);
    }
    return "";

}
