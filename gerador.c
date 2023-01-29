#include "gerador.h"
#include <stdio.h>
#include <stdlib.h>


void escreveArq(Registro* dado){
    
    for(int i=0;i<5000;i++){
        dado->dado2[i]=(char)rand()%127;
    }
}

int criarquivo(){
    FILE *arq;
    int tam,opcao;

    printf("\n\n Qual o tamanho do arquivo?");
    printf("\n |");
    printf("\n -> ");
    scanf("%d", &tam);

    printf("\n             Situacao            ");
    printf("\n --------------------------------");
    printf("\n |Qual a situação do arquivo?   |");
    printf("\n |1. Ordenado Ascedente         |");
    printf("\n |2. Ordenado Descendente       |");
    printf("\n |3. Ordenado Aleatoriamente    |");
    printf("\n -------------------------------\n |\n -> " );
    scanf("%d", &opcao);

    Registro dados;


    
    //Chave *arquivo2 = malloc(aux*sizeof(Chave));
    arq= fopen("DADOS.bin", "wb");
    if(arq==NULL){
        printf("\n Erro 707");
        printf("\n\n Nao foi possivel abrir o arquivo");
        return 10;
    }    


    fflush(stdin);

    switch (opcao)
    {
    case 1:
        for(int i=0; i<tam; i++){
            dados.chave=i;
            dados.dado1=rand();
            escreveArq(&dados);
            fwrite(&dados,sizeof(dados),1,arq);
        }
        break;
    case 2:
        for(int i= tam -1; i>=0;i--){
            dados.chave=i;
            dados.dado1=rand();
            escreveArq(&dados);
            fwrite(&dados, sizeof(dados), 1,arq);
        }
        break;
    case 3:
        Registro *arquivo = malloc(tam*sizeof(Registro));
        for(int i = 0; i<tam; i++){
        fflush(stdin);
        retchave(arquivo,i,tam);
        arquivo[i].dado1 = rand() %100000000000000000;
        for(int j = 0; j<5000;j++)
            arquivo[i].dado2[j] = (char)rand()%127;
        //printf("run: %d\nchave: %d\ndado1: %ld\ndado2: %s",i,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
        salvarEmArquivo(i,arquivo);
        lerDoArquivo(i,arquivo);
       // printf("\nrun: %d\nchave: %d\ndado1: %ld\ndado2: %s\n",i+1,arquivo[i].chave,arquivo[i].dado1,arquivo[i].dado2);
        }
        free(arquivo);
    
        break;

    default:
        printf("\n\n Opcao não existe ");
        return 10;
        break;
    }
 
    fclose(arq);
    return opcao;
    //free(arquivo2);
    
}

void salvarEmArquivo(int i, Registro *arquivo){
    FILE * arq = fopen("DADOS.bin", "wb");
    if(arq){ // verifica se o arquivo foi aberto / criado corretamente
        fwrite(&arquivo[i], sizeof(Registro),1, arq); // escreve todas as chaves de uma vez
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
    fclose(arq); // fecha o arquivo
}


void lerDoArquivo(int i, Registro *arquivo){
    FILE *arq = fopen("DADOS.bin", "rb");
    if(arq){
        //fscanf(arq, "%d\n", &quant);
        fread(&arquivo[i], sizeof(Registro), 1, arq);
        fclose(arq);
    }
    else
        printf("ERRO: nao foi possivel abrir o arquivo.\n\n");
}

void retchave(Registro *arquivo, int i, int aux){
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

