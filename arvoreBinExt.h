#ifndef arvoreBinExt_h
#define arvoreBinExt_h
#include "gerador.h"

typedef struct
{
    int pEsq, pDir;
    Registro Registro;

}ArvoreBin;


int criaArvore(int *x,int *y,int w);

int pesquisaArvore(Registro *dado, int x,int *y,int *w);

#endif
