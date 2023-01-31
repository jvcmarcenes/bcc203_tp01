#include "Acesso.h"

void acessa(FILE arq*){
    Indice tabela[MAXTABELA];
    Registro ITEM;
    int pos = 0,count = 0;
    // Gerar a tabela de Indices
    while(fread(&ITEM,sizeof(ITEM),1,arq) == 1){
        count++;
        tabela[pos].chave = ITEM.chave;
        tabela[pos].posicao = pos+1;
        fseek(arq,4,SEEK_CUR);
        //if(count % ITENSPAGINA == 1){
        //    tabela[pos].chave = ITEM.chave;
        //    tabela[pos].posicao = pos+1;
        //    pos++;
        }
    }
    fflush(stdout);
    int aux;
    printf("Defina a chave a ser pesquisada: ");
    scanf("%d",&aux);
    ITEM = Pesquisa(arq,aux,tabela);

}

Registro Pesquisa(FILE *arq,int chave, Indice *tabela){
    Registro Item;
    for(int i = 0; i<sizeof(tabela); i++){
        if(chave == 1){
            
        }
    }
}