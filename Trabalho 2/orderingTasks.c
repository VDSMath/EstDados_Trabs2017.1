#include<stdio.h>
#include<stdlib.h>

typedef struct _tarefa{
	int numero;
	struct _tarefa* prox;
} TAREFA;

void PegaRelacoes(TAREFA* pTarefa, int* grauSaida);
void AdicionaTarefa(TAREFA* pTarefa, int prim, int segu);
void Ordena(TAREFA* pTarefa, int* grauSaida, int numeroTarefas);
void RetiraTarefa(TAREFA* pTarefa,int* grauSaida, int indice);

int main(void){
	TAREFA* pTarefa;
	int* grauSaida;
	int numeroTarefas;
	int numeroRelacoes;
	int i=0;

	scanf("%d %d", &numeroTarefas, &numeroRelacoes);
	pTarefa = (TAREFA*)malloc(numeroTarefas*sizeof(TAREFA));
	grauSaida = (int*)malloc(numeroTarefas*sizeof(int));

	PegaRelacoes(pTarefa, grauSaida);
	Ordena(pTarefa, grauSaida, numeroTarefas);

	return 0;
}

void PegaRelacoes(TAREFA* pTarefa, int* grauSaida){
	int primeira; 
	int segunda;

	do{
		scanf("%d %d", &primeira, &segunda);
		if(primeira == 0 && segunda == 0){
			return;
		}

		*(grauSaida+segunda-1) = *(grauSaida+segunda-1) + 1;
		AdicionaTarefa(pTarefa,primeira,segunda);
	}while(1);
}

void AdicionaTarefa(TAREFA* pTarefa, int prim, int segu){
	TAREFA* temp;
	temp = (TAREFA*)malloc(sizeof(TAREFA));
	temp->numero = segu;
	temp->prox = NULL;

	TAREFA* tarefaAtual;
	tarefaAtual = pTarefa+prim-1;
	while(tarefaAtual->prox != NULL){
		tarefaAtual = tarefaAtual->prox;
	}
	tarefaAtual->prox = temp;
}

void Ordena(TAREFA* pTarefa, int* grauSaida, int numeroTarefas){
	int indice = 0;
	int tarefasRestantes = numeroTarefas;
	while(tarefasRestantes > 0){
		for (indice = 0;indice <= numeroTarefas; indice++){
			if(grauSaida[indice] == 0){
				grauSaida[indice] = -1;
				tarefasRestantes--;
				RetiraTarefa(pTarefa,grauSaida,indice);
				printf("%d\n",indice + 1);
			}
		}
	}
}

void RetiraTarefa(TAREFA* pTarefa,int* grauSaida, int indice){
	TAREFA* tarefaAtual;
	tarefaAtual = (pTarefa+indice)->prox;
	while(tarefaAtual != NULL){
		grauSaida[tarefaAtual->numero-1]--;
		tarefaAtual = tarefaAtual->prox;
	}

}