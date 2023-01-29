#ifndef arvoreB_h
#define arvoreB_h

#include "CriaArq.h"
#include <stdbool.h>
//MM == 2m, ou seja, árvore B de ordem 2 => MM = 4
//100 == 2m, m = 50 => ordem 50
#define MM 100

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina{
	short n;
	Registro r[MM];
	TipoApontador p[MM+1];
}TipoPagina;

void InicializaArvoreB(TipoApontador);

void InsereNaPagina(TipoApontador, Registro, TipoApontador, int *);

void Ins(Registro, TipoApontador, bool *, Registro *, TipoApontador *, int *);

void InsereArvoreB(Registro, TipoApontador *, int *);

bool PesquisaArvoreB(Registro* , TipoApontador, int *, bool);

void Imprime(TipoApontador);

void Imprime3(TipoApontador arvore, int);

//--------------------------------------------- METODOS PARA REMOCAO NA ÁRVORE B

void Reconstitui(TipoApontador, TipoApontador, int, bool *);

void Antecessor(TipoApontador, int, TipoApontador, bool *);

void Ret(int, TipoApontador *, bool *);

void Retira(int, TipoApontador *);

#endif