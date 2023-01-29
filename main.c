#include "gerador.h"
#include "arvoreBinExt.h"
#include "arvoreB.h"
#include "arvoreBestre.h"
#include <stdio.h>
#include <stdlib.h>


void printaAnalise(){



}



int main(){
//--------------------------------------------------------------------- Variaveis    
    int situacao,teste,chavePesq,nLeituras,contadorCompara=0, leiturasCriacaoIndice =0, contadorComparaCriacaoIndice=0;;
    Registro pesq;
    Registro dado;    
    int resultado,bin;
    TApEstrela arvoreEstrela = NULL;
    FILE *arquivo;
    
//--------------------------------------------------------------------- Testes    
    situacao=criarquivo();

    if(situacao>5){
        printf("\n\n Erro ao criar o arquivo!!");
        return 0;
    }

    fflush(stdin);
//----------------------------------------------------------------------- Menus   
    printf("\n               Metodo              ");
    printf("\n ----------------------------------");
    printf("\n |Qual Metodo de pesquisa Externa?|");
    printf("\n |1. Pesquisa sequencial          |");
    printf("\n |2. Arvore binaria externa       |");
    printf("\n |3. Arvore B                     |");
    printf("\n |4. Arvore B estrela             |");
    printf("\n ----------------------------------\n|\n -> " );
    scanf("%d", &teste);



    printf("\n |\n-> Qual a chave para pesquisa?   ");
    scanf("%d", &chavePesq);

    arquivo= fopen("DADOS.bin","rb");
    if(arquivo==NULL){
        printf("\n\n Erro ao abrir o arquivo!");
        printf("\n Caso 2");
        return 0;
    }


//-------------------------------------------------------------------------- Inicio da pesquisa

    pesq.chave=chavePesq;
    bin=1;
    switch (teste)
    {
    case 1:
        printf("\n\n Ainda nao implementado!");
        break;
    case 2:
        if(criaArvore(&contadorComparaCriacaoIndice,&leiturasCriacaoIndice,situacao)==1){
            resultado=pesquisaArvore(&pesq,bin,&contadorCompara,&nLeituras);
            if(resultado==1){
                printf("\n\n Chave %d encontrada, com %d transferencias, %d pesquisas, %d comparacoes \n\n", pesq.chave,leiturasCriacaoIndice,nLeituras,contadorComparaCriacaoIndice);

            }
            else printf("\n\n Chave %d nao encontrada", pesq.chave);
        }
        break;
    case 3:
        printf("\n\n Ainda nao implementado!");
        break;
    case 4:
        inicializaBEstrela(arvoreEstrela);
        while((fread(&dado,sizeof(dado),1,arquivo))==1){
            leiturasCriacaoIndice++;
            insereBEstrela(dado,&arvoreEstrela,&contadorComparaCriacaoIndice);
        }
        if(bin){
            printf("\n Procurando Chave...");
            pesquisaBEstrela(&pesq,&arvoreEstrela,&resultado,&contadorCompara,bin);
            if(resultado==1)
                printf("\n\n Chave %d encontrada, com %d transferencias, %d pesquisas, %d comparacoes \n\n", pesq.chave,leiturasCriacaoIndice,nLeituras,contadorComparaCriacaoIndice);
            else
                printf("\n\n Chave %d nao encontrada", pesq.chave);
        }        
        break;    
    default:
        printf("\n\n Opcao invalida!");
        break;
    }

    fclose(arquivo);
    return 0;
}
