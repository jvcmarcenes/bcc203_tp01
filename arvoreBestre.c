#include <stdio.h>
#include <stdlib.h>
#include "arvoreBestre.h"

void inicializaBEstrela(TApEstrela Ap){
	Ap = NULL;
}

void insereNaPagina(TApEstrela Ap, Registro Reg, TApEstrela ApDir, int *indiceContComp){
	bool NaoAchouPosicao;
	int index;
	if (Ap->Pt == Int) {  // Página Interna
		index = Ap->UU.U0.ni;
		NaoAchouPosicao = (index > 0);
		while (NaoAchouPosicao){
			(*indiceContComp)++;
			if (Reg.chave >= Ap->UU.U0.ri[index-1]){	// Compara se a chave a ser inserida na página é maior ou igual a última chave presente na página 
				NaoAchouPosicao = false;
				break;
			}
			Ap->UU.U0.ri[index] = Ap->UU.U0.ri[index-1];	// Transfere a chave da posição (index-1) para uma posição a frente,
			Ap->UU.U0.pi[index+1] = Ap->UU.U0.pi[index];	// consequentemente o apontador também é transferido
			index--;
			if (index < 1)
				NaoAchouPosicao = false;
		}
		Ap->UU.U0.ri[index] = Reg.chave;	// Copia a nova chave para a posição liberada acima
		Ap->UU.U0.pi[index+1] = ApDir;	// Atualiza o apontador direito dessa nova chave
		(Ap->UU.U0.ni)++;	// Incrementa a quantidade de chaves na página
	} else {	// Página Externa
		index = Ap->UU.U1.ne;
		NaoAchouPosicao = (index > 0);
		while (NaoAchouPosicao){
			(*indiceContComp)++;
			if (Reg.chave >= Ap->UU.U1.re[index-1].chave){	// Compara se a chave do registro ser inserido na página é maior ou igual a chave do último registro presente na página 
				NaoAchouPosicao = false;
				break;
			}
			Ap->UU.U1.re[index] = Ap->UU.U1.re[index-1];	// Transfere o registro da posição (index-1) para uma posição a frente
			index--;
			if (index < 1)
				NaoAchouPosicao = false;
		}
		Ap->UU.U1.re[index] = Reg;	// Copia o novo registro para a posição liberada acima
		(Ap->UU.U1.ne)++;	// Incrementa a quantidade de registros na página
	}
}

void insere(Registro Reg, TApEstrela Ap, int *Cresceu, Registro *RegRetorno, TApEstrela *ApRetorno, int *indiceContComp){
	long num = 1, num2;
	TApEstrela ApTemp;
	Registro aux = Reg;
	if (Ap == NULL || Ap->Pt == Ext){	// Verifica se o apontador é nulo ou aponta para uma página externa
		*Cresceu = 1;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return;
	}
	if (Ap->Pt == Int){
		while (num < Ap->UU.U0.ni && Reg.chave > Ap->UU.U0.ri[num-1]){	// Varre a página interna enquanto o registrador num for menor que a quantidade de chaves dessa página e enquanto a chave a ser inserida for maior do que uma das chaves presentes na página 
			num++;
			(*indiceContComp)++;
		}
		(*indiceContComp) +=2;	//Incrementa a ultima comparacao feita no while juntamente com o if da proxima linha
		
		if (Reg.chave < Ap->UU.U0.ri[num-1]) 	// Verifica se a chave do registro a ser inserido possui valor menor que a da última chave verificada na página
			num--;
			
		insere(Reg, Ap->UU.U0.pi[num], Cresceu, RegRetorno, ApRetorno, indiceContComp);	// Faz a chamada recursiva até que uma página folha seja atingida
		if (*Cresceu)	// Se a página folha não foi atingida retorna
			return;
			
		if (Ap->UU.U0.ni < MM){	// Verifica se a página interna tem espaço para inserção de um novo registro
			insereNaPagina(Ap, *RegRetorno, *ApRetorno, indiceContComp);
			*Cresceu = 0;
			return;
		}
		if (Ap->UU.U0.ni >= MM){	// Verifica se a quantidade de chaves presentes na página extrapola a quantidade máxima permitida
			ApTemp = (TApEstrela)malloc(sizeof(TPaginaEstrela));	// Cria uma nova página interna
			ApTemp->Pt = Int;
			ApTemp->UU.U0.ni = 0;

			if (num < (MM/2 + 1)){	// Insere metade das chaves da página cheia para a nova página criada
				aux.chave = Ap->UU.U0.ri[MM -1];
				insereNaPagina(ApTemp, aux, Ap->UU.U0.pi[MM], indiceContComp);
				Ap->UU.U0.ni--;
				insereNaPagina(Ap, *RegRetorno, *ApRetorno, indiceContComp);
			}else
				insereNaPagina(ApTemp, *RegRetorno, *ApRetorno, indiceContComp);
			
			for(num2 = MM/2+2; num2 <= MM; num2++){
				aux.chave = Ap->UU.U0.ri[num2-1]; 
				insereNaPagina(ApTemp, aux, Ap->UU.U0.pi[num2], indiceContComp);
			}
			Ap->UU.U0.ni = MM/2;	// Atualiza a quantidade de chaves na página
			ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM/2+1];
			aux.chave = Ap->UU.U0.ri[MM/2];	// Copia a chave do meio para a página pai
			*RegRetorno = aux;
			*ApRetorno = ApTemp;
		}
		
	}else
	// A partir desse ponto a página é externa
	if (Ap->UU.U1.ne < MM){	// Verifica se a quantidade de registros presentes na página na extrapola a quantidade máxima permitida
		insereNaPagina(Ap, Reg, *ApRetorno, indiceContComp);
		*Cresceu = 0;
		return;
	}
	ApTemp = (TApEstrela)malloc(sizeof(TPaginaEstrela));	// Cria uma nova página externa
	ApTemp->Pt = Ext;
	ApTemp->UU.U1.ne = 0;
	
	if (num < (MM/2 + 1)){	// Insere metade dos registros da página cheia para a nova página criada
		insereNaPagina(ApTemp, Ap->UU.U1.re[MM-1], Ap, indiceContComp);
		(Ap->UU.U1.ne)--;
		insereNaPagina(Ap, Reg, *ApRetorno, indiceContComp);
	}else
		insereNaPagina(ApTemp, Reg, *ApRetorno, indiceContComp);
		
	for(num2 = MM/2+1; num2 <= MM; num2++)
		insereNaPagina(ApTemp, Ap->UU.U1.re[num2-1], *ApRetorno, indiceContComp);
	Ap->UU.U1.ne = MM/2;	// Atualiza a quantidade de registros na página
	*RegRetorno = Ap->UU.U1.re[MM/2+1];	// Copia o registro do meio para a página pai
	*ApRetorno = ApTemp;
}

void insereBEstrela(Registro Reg, TApEstrela *Ap, int *indiceContComp){
	int Cresceu;
	Registro RegRetorno;
	TPaginaEstrela *ApRetorno, *ApTemp;
	insere(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, indiceContComp);
	if (Cresceu){	// Neste ponto a raiz é dividida, e é gerada uma nova raiz. A altura da árvore aumenta.			
		ApRetorno= (TPaginaEstrela*) malloc (sizeof(TPaginaEstrela));
		ApRetorno->Pt = Ext;
		ApRetorno->UU.U1.ne = 1;
		ApRetorno->UU.U1.re[0] = RegRetorno;
		
		ApTemp = (TPaginaEstrela*) malloc (sizeof(TPaginaEstrela));
		ApTemp->Pt = Int;
		ApTemp->UU.U0.ni = 1;
		ApTemp->UU.U0.ri[0] = RegRetorno.chave;
		ApTemp->UU.U0.pi[1] = ApRetorno;
		ApTemp->UU.U0.pi[0] = *Ap;
		*Ap = ApTemp;
	}
}

void pesquisaBEstrela(Registro *sample, TApEstrela *Ap, int *achou, int *pesqContComp, bool aux){
	int i;
	TApEstrela Pag;
	Pag = *Ap;
	if ((*Ap)->Pt == Int){	
		i=1;
		while (i < Pag->UU.U0.ni && sample->chave > Pag->UU.U0.ri[i-1]){	// Varre a página interna enquanto o número de chaves presentes não seja extrapolado e enquanto a chave pesquisada não seja maior que uma chave comparada na página 
			if (aux)
				printf("%d, ", Pag->UU.U0.ri[i-1]);
			(*pesqContComp)++;
			i++;
		}
		(*pesqContComp)++;
		if (aux)
			printf("%d, ", Pag->UU.U0.ri[i-1]);
		if (sample->chave < Pag->UU.U0.ri[i-1])
			pesquisaBEstrela (sample, &Pag->UU.U0.pi[i-1], achou, pesqContComp, aux);	// Faz a chamada recursiva pelo lado esquerdo da árvore
		else
			pesquisaBEstrela (sample, &Pag->UU.U0.pi[i], achou, pesqContComp, aux);	// Faz a chamada recursiva pelo lado direito da árvore
		return;
	}
	i=1;
	// A partir daqui a página é externa
	while (i < Pag->UU.U1.ne && sample->chave > Pag->UU.U1.re[i-1].chave){	// Varre a página externa enquanto o número de registros presentes não seja extrapolado e enquanto a chave pesquisada não seja maior que a chave de um registro presente na página 
		if (aux)
			printf("%d, ", Pag->UU.U0.ri[i-1]);
		(*pesqContComp)++;
		i++;
	}
	(*pesqContComp)++;
	printf("%d, ", Pag->UU.U0.ri[i-1]);
	if (sample->chave == Pag->UU.U1.re[i-1].chave){	// Retorna o dado e a situação de sucesso na pesquisa
		*sample = Pag->UU.U1.re[i-1];
		*achou = 1;
	}
}
