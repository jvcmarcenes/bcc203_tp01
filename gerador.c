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
        retchave(arquivo,i,aux);
        arquivo[i].dado1 = rand() %100000000000000000;
        for(int j = 0; j<5000;j++)
            arquivo[i].dado2[j] = (char)rand()%127;
        //printf("run: %d\nchave: %d\ndado1: %ld\ndado2: %s",i,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
        salvarEmArquivo(i,arquivo);
        lerDoArquivo(i,arquivo);
       // printf("\nrun: %d\nchave: %d\ndado1: %ld\ndado2: %s\n",i+1,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
    }
    free(arquivo);
    //free(arquivo2);
    
}

void salvarEmArquivo(int i, Chave *arquivo){
    FILE * arq = fopen("./DADOS.txt", "wb");
    if(arq){ // verifica se o arquivo foi aberto / criado corretamente
        fwrite(&arquivo[i], sizeof(Chave),1, arq); // escreve todas as chaves de uma vez
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    fclose(arq); // fecha o arquivo
}


void lerDoArquivo(int i, Chave *arquivo){
    FILE *arq = fopen("DADOS.txt", "rb");
    if(arq){
        //fscanf(arq, "%d\n", &quant);
        fread(&arquivo[i], sizeof(Chave), 1, arq);
        fclose(arq);
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
}

void retchave(Chave *arquivo, int i, int aux){
    long int aleat; // Número aleatório gerado
    int count;
    if (i == 0)
        arquivo[i].chave = 0;
    else{
        while (1){
            //printf("Loop\n");
            aleat = rand()%aux+1;
            count = 0;
            for(int j = 0; j<i;j++){
                if(aleat != arquivo[i-1].chave)
                    count++;
            }
            if(count == i){
                arquivo[i].chave = aleat;
                break;
            }
            //printf("count: %d  i: %d  \n",count, i);
        }
    }
}
