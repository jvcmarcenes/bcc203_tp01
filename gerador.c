#include "gerador.h"

void criarquivo(){
    printf("0\n");
    int aux;
    printf("\nQual o tamanho que você deseja para o arquivo?");
    scanf("%d",&aux);
    printf("\n");
    //Chave *arquivo2 = malloc(aux*sizeof(Chave));
    printf("1\n");
    fflush(stdin);
    Chave *arquivo = malloc(aux*sizeof(Chave));
    for(int i = 0; i<aux; i++){
        fflush(stdin);
        arquivo[i].chave = rand() %100000000000000000;
        arquivo[i].dado1 = rand() %100000000000000000;
        for(int j = 0; j<5000;j++)
            arquivo[i].dado2[j] = (char)rand()%127;
        //printf("run: %d\nchave: %d\ndado1: %ld\ndado2: %s",i,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
        salvarEmArquivo2(i,arquivo);
        //lerDoArquivo2(i,arquivo2);
        //printf("run: %d\nchave: %d\ndado1: %ld\ndado2: %s\n",i,arquivo2[i].chave,arquivo2[i].dado1,arquivo2[i].dado2);
    }
    free(arquivo);
    //free(arquivo2);
    
}

void salvarEmArquivo2(int i, Chave *arquivo){
    FILE * arq = fopen("./DADOS.txt", "wb");
    if(arq){ // verifica se o arquivo foi aberto / criado corretamente
        //fprintf(arq, "%d\n", ); // escreve a quantidade de pessoas
        fwrite(&arquivo[i], sizeof(Chave),1, arq); // escreve todas as pessoas de uma vez
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    fclose(arq); // fecha o arquivo
}


void lerDoArquivo2(int i, Chave *arquivo){
    FILE *arq = fopen("DADOS.txt", "rb");
    if(arq){
        //fscanf(arq, "%d\n", &quant);
        fread(&arquivo[i], sizeof(Chave), 1, arq);
        fclose(arq);
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
}
