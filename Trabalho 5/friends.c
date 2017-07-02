#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _conjunto{
  struct _conjunto* pai;
  int rank;
}conjunto;

conjunto* buscar(conjunto* c);
void fundir(conjunto* a, conjunto* b);
void repeticoes(int r);
void formarrelacoes(int n, int m);

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

      fundir((cid + a), (cid + b));
      if((cid + a)->rank > maior->rank)
        maior = (cid + a);
      if((cid + b)->rank > maior->rank)
        maior = (cid + b);

      m--;
  }

  printf("%d", maior->rank);
}

conjunto* buscar(conjunto* c){
  if (c->pai != NULL)
    c->pai = buscar(c->pai);
  return c->pai;
}
void fundir(conjunto* a, conjunto* b){
  conjunto* raiza = buscar(a);
  conjunto* raizb = buscar(b);

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
