#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int chave;
    long int dado1;
    char dado2[5000]; 
}Chave;

void criarquivo();

void salvarEmArquivo(int i, Chave *arquivo);

void lerDoArquivo(int i, Chave *arquivo);

void retchave(Chave *arquivo, int i, int aux);
