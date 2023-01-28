#include "arvoreBinExt.h"   
#include <stdlib.h>
#include <stdio.h>


int criaArvore(int *x,int *y,int w){
    FILE *arqArv, *arquivo;

    arquivo=fopen("Arquivo.bin","rb");
    if(arquivo==NULL){
        printf("\n Erro ao ler o arquivo");
        return 0;
    }

    arqArv= fopen("arvoreBin.bin","w+b");
    if(arqArv==NULL){
        printf("\n\n Erro ao ler arquivo da arvore");
        return 0;
    }    

    (*y)++;
    Registro dado;
    ArvoreBin nodo;
    int index=1;
    fread(&dado, sizeof(dado),1,arquivo);
    nodo.Registro=dado;
    nodo.pEsq=-1;
    nodo.pDir=-1;
    fwrite(&nodo,sizeof(nodo),1,arqArv);

    while(fread(&dado,sizeof(dado),1,arquivo)==1){
        (*y)++;
        nodo.Registro=dado;
        nodo.pEsq= -1;
        nodo.pDir= -1;
        fseek(arqArv,0,SEEK_END);
        fwrite(&nodo,sizeof(nodo),1,arqArv);
        if(w==1||w==2){
            fseek(arqArv, -2 * ((long long int)sizeof(nodo)),SEEK_CUR);
            fread(&nodo,sizeof(nodo),1,arqArv);
            (*x)++;
            fseek(arqArv, -1 * ((long long int)sizeof(nodo)),SEEK_CUR);

        }else{
            rewind(arqArv);
            if(fread(&nodo,sizeof(nodo),1,arqArv)==1)
                (*x)++;
            rewind(arqArv);    
        }
        while(1){
            (*y)++;
            if(dado.chave<nodo.Registro.chave){
                if(nodo.pEsq==-1){
                    nodo.pEsq= index;
                    fwrite(&nodo, sizeof(nodo),1,arqArv);
                    break;
                }else{
                    fseek(arqArv, nodo.pEsq* sizeof(nodo), SEEK_SET);
                    if(fread(&nodo,sizeof(nodo),1,arqArv)==1)
                        (*x)++;
                    fseek(arqArv,-1 * ((long long int) sizeof(nodo)), SEEK_CUR);    
                }
            }else{
                if(nodo.pDir== -1){
                    nodo.pDir= index;
                    fwrite(&nodo,sizeof(nodo),1,arqArv);
                    break;
                }else{
                    fseek(arqArv, nodo.pDir *sizeof(nodo),SEEK_SET);
                    if(fread(&nodo, sizeof(nodo),1,arqArv)==1)
                        (*x)++;
                    fseek(arqArv,-1 * (( long long int) sizeof( nodo)), SEEK_CUR);    
                }
            }
        }
        index++;

    }
    fclose(arqArv);
    fclose(arquivo);
    return 1;    
}

int pesquisaArvore(Registro *dado, int x,int *y,int *w){
    FILE *arqArv;
    ArvoreBin nodo;

    arqArv= fopen("arvoreBin.bin","rb");
    if(arqArv==NULL){
        printf("\n\n Erro ao abrir o arquivo");
        return 0;
    }

    while (fread(&nodo, sizeof(nodo), 1, arqArv) == 1){
		(*w)++;
		(*y)++;
		if (dado->chave == nodo.Registro.chave){
			if (x){
				printf("%d, ", nodo.Registro.chave);
				fflush(stdout);
			}
			*dado = nodo.Registro;
			fclose(arqArv);
			return 1;
		}else{
			(*y)++;
			if (dado->chave < nodo.Registro.chave){
				if (x){
					printf("%d, ", nodo.Registro.chave);
					fflush(stdout);
				}
				if (nodo.pEsq != -1) 
					fseek(arqArv, nodo.pEsq * sizeof(nodo), SEEK_SET); // Movimentação do apontador até a chave ser encontrada;
				else{ // Se o apontador chegar em -1 não foi possível encontrar a chave no arquivo;
					fclose(arqArv);
					return 0;
				}
			}else{
				if (x)
					printf("%d, ", nodo.Registro.chave);
				if (nodo.pDir != -1)
					fseek(arqArv, nodo.pDir * sizeof(nodo), SEEK_SET); // Movimentação do apontador até a chave ser encontrada;
				else{ // Se o apontador chegar em -1 não foi possível encontrar a chave no arquivo;
					fclose(arqArv);
					return 0;
				}
			}
		}
	}
	fclose(arqArv);
	return 1;
}
