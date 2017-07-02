#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
Nome: Matheus Vinicius S. de Figueiredo
Trabalho 5: Friends

O trabalho foi feito usando o conceito de Conjuntos Disjuntos, com união por rank
e compressão de caminhos, como visto na disciplina Estrutura de Dados.
*/

typedef struct _conjunto{
  struct _conjunto* pai;
  int rank;
}conjunto;

conjunto* buscar(conjunto* c);//Acha a raiz de um conjunto
void fundir(conjunto* a, conjunto* b);//Une dois conjuntos, com compressão de caminhos
void repeticoes(int r);//Executa o programa r vezes, de acordo com a entrada
void formarrelacoes(int n, int m);//Faz as uniões necessárias e retorna o maior rank

int main(int argc, char **argv){
  int repet;

  scanf("%d", &repet);
  repeticoes(repet);


  return 0;
}

void repeticoes(int r){
  int n,m;

  while(r > 0){
    scanf("%d %d", &n, &m);
    formarrelacoes(n, m);

    r--;
  }
}

void formarrelacoes(int n, int m){
  conjunto* cid = malloc(sizeof(conjunto) * n);
  conjunto* maior;
  int a,b,i;

  for(i = 0; i <= n-1; i++){
    (cid + i)->rank = 0;
    (cid + i)->pai = NULL;
  }

  maior = (cid + n-1);

  while(m > 0){
      scanf("%d %d", &a, &b);


      fundir((cid + a - 1), (cid + b - 1));
      if((cid + a -1)->rank > maior->rank)
        maior = (cid + a - 1);
      if((cid + b - 1)->rank > maior->rank)
        maior = (cid + b - 1);

      m--;
  }

  printf("%d\n", maior->rank + 1);
}

conjunto* buscar(conjunto* c){
  if (c->pai != NULL){
    c->pai = buscar(c->pai);
    return c->pai;
  }
  else
    return c;
}
void fundir(conjunto* a, conjunto* b){
  conjunto* raiza = buscar(a);
  conjunto* raizb = buscar(b);

  if(raiza == raizb)
    return;

  if(raiza->rank <= raizb->rank){
    raiza->pai = raizb;
    raizb->rank++;
    return;
  }
  if(raiza->rank > raizb->rank){
    raizb->pai = raiza;
    raiza->rank++;
    return;
  }
}
