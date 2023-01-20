#include "gerador.h"

void criarquivo(){
    int aux;
    printf("\nQual o tamanho que você deseja para o arquivo?");
    scanf("%d",&aux);
    printf("\n");
    Chave *arquivo = malloc(aux*sizeof(Chave));
    for(int i = 0; i<aux; i++){
        arquivo[i].chave = rand() %100000000000000000;
        arquivo[i].dado1 = rand() %100000000000000000;
        for(int j = 0; j<5000;j++)
            arquivo[i].dado2[j] = (char)rand()%127;
        printf("run: %d\nchave: %d\ndado1: %ld\ndado2: %s",i,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
    }
    free(arquivo);
}
