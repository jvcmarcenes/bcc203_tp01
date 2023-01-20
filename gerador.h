#include <time.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct{
    int chave;
    long int dado1;
    char dado2[5000]; 
}Chave;

void criarquivo();

void salvarEmArquivo2(int i, Chave *arquivo);

void lerDoArquivo2(int i, Chave *arquivo);
