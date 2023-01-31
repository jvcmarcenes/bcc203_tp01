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
    if(ITEM != NULL)
        printf("Conteudo da chave -\nDado1: %ld\nDado2: %s\n",ITEM.dado1, ITEM.dado2);

}

Registro Pesquisa(FILE *arq,int chave, Indice *tabela){
    Registro Item;
    for(int i = 0; i<sizeof(tabela); i++){
        if(chave == tabela[i].chave){
            return tabela[i].chave;
        }
        else if(chave < tabela[i].chave){
            for(int j = 0; j<3; j++){
                if(chave == tabela[i-j].chave)
                    return tabela[i-j].chave;
            }
        }
        else if(tabela[i-1].chave < chave && chave < tabela[i].chave){
            for(int j = 0; j<3; j++){
                if(chave == tabela[i+j].chave)
                    return tabela[i+j].chave;
            }
        }
        else
            printf("chave não encontrada")
        return NULL;
    }
}