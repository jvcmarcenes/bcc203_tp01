#ifndef Acesso_h
#define Acesso_h

#include "gerador.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

#define ITENSPAGINA 4
#define MAXTABELA 100


typedef struct {
    int chave;
    int posicao;
}Indice;

void acessa(FILE arq*);
Registro Pesquisa(FILE *arq,int chave, Indice *tabela);