#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT 50000

void print(int* array, int size);

void mergeSort(int* V, int ini, int fim);

void merge(int* V, int ini, int meio, int fim);

  int main(int argc, char **argv){
    int *V;
    V = malloc(sizeof(int) * MAX_INPUT);

    int i = 0, start = 0, end = 0;

    while(!feof(stdin)){

      if(scanf("%d", &V[i]) == 1){
        i++;
        end++;
        if(feof(stdin)) break;
      }
    }

    if(!strcmp(argv[1], "-m")){
      puts("Merge Sort");
      mergeSort(V, start, end-1);
      print(V, end);
    }

    if(!strcmp(argv[1], "-q")){
      puts("Quick Sort");
    }

    return 0;
  }

  void print(int* array, int size){
    int i;
    puts("Elements:");
    for(i = 0; i<size;i++){
      printf("%d", array[i]);
    }
    puts(""); printf("Size is %d\n", size);
  }

  void mergeSort(int* V, int ini, int fim){
    int meio;
    if(ini < fim){
      meio = (ini + fim)/2; //Calcula o elemento na metade do vetor, arredondado para baixo
      mergeSort(V, ini, meio);   //
      mergeSort(V, meio+1, fim); //Divide o vetor em dois vetores menores
      merge(V, ini, meio, fim);//Junta os dois vetores menores, os ordenando
    }
  }

  void merge(int* V, int ini, int meio, int fim){
    int* temp;
    int p1, p2, tam, i, j, k;
    int fim1 = 0, fim2 = 0;

    tam = fim-ini+1; //Define o tamanho do vetor(já que não começa em zero)
    p1 = ini; //Inicio do primeiro vetor a ser mergido
    p2 = meio + 1; //Inicio do segundo vetor

    temp = (int*) malloc(tam*sizeof(int)); //Vetor de destino dos dois vetores a serem juntados
                                           //com o tamanho de p1 + tamanho de p2

    if(temp != NULL){
      for(i = 0; i < tam; i++){
        if(!fim1 && !fim2){ // Testa se os vetores ainda tem elementos
          if(V[p1] < V[p2])     //Verifica qual dos primeiros elementos dos dois vetores
            temp[i] = V[p1++];  //a serem unidos e o coloca no vetor auxiliar
          else                  //
            temp[i] = V[p2++];
                      // ^-- Copia a posição atual no vetor e a move para o próximo elemento

          if(p1 > meio) fim1 = 1;   //Se um dos vetores chegar ao fim, sua variavel
          if(p2 > fim) fim2 = 1;    //correpondente será verdadeira
        }
        else{ //Se um dos vetores terminou não é mais necessário comparar elementos entre eles
          if(!fim1)
            temp[i] = V[p1++];
          else
            temp[i] = V[p2++];
        }
        //printf("%d", temp[i]);
      }
      for(j = 0, k = ini; j < tam; j++, k++){

        V[k] = temp[j]; //Passa o vetor auxiliar já ordenado para o vetor original
      }
    }
    free(temp);
    }
