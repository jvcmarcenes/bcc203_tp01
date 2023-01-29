#ifndef arvoreBestre_H
#define arvoreBestre_H

#include "arvoreB.h"

typedef enum {Int, Ext} TIntExt;
typedef struct TPaginaEstrela* TApEstrela;

typedef struct TPaginaEstrela{
	TIntExt Pt;
	union{
		struct{
			int ni;
			int ri[MM];
			TApEstrela pi[MM+1];
		}U0;
		struct {
			int ne;
			Registro re[MM/2];
		}U1;
	}UU;
}TPaginaEstrela;

void inicializaBEstrela(TApEstrela);

void insereNaPagina(TApEstrela, Registro, TApEstrela, int *);

void insere(Registro, TApEstrela, int *, Registro *, TApEstrela *, int *);

void insereBEstrela(Registro, TApEstrela *, int *);

void pesquisaBEstrela(Registro *, TApEstrela *, int *, int *, bool);

#endif