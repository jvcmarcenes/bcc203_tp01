#ifndef gerador_h
#define gerador_h
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Registro{
    int chave;
    long int dado1;
    char dado2[5000]; 
}Registro;

void escreveArq(Registro* dado);

int criarquivo();

void salvarEmArquivo(int i, Registro *arquivo);

void lerDoArquivo(int i, Registro *arquivo);

void retchave(Registro *arquivo, int i, int aux);

#endif
