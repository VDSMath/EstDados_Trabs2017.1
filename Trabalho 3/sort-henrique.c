#define MAX_INPUT 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Estrutura de Dados - Trabalho 3
Henrique Vermelho de Toledo - DRE 116076549
/////////////////////MERGE SORT, QUICK SORT/////////////////////

INSTRUÇÕES PARA RODAR O ARQUIVO:
N/A

INFORMAÇÕES:
N/A
*/

void print(int* array, int size);
void merge_sort(int* array, int start, int end);
void merge(int* array, int start, int middle, int end);
void quick_sort(int* array, int start, int end);
int partition(int* array, int start, int end);
void swap(int* a, int* b);

int main(int argc, char **argv) {
    int* numbers = malloc(sizeof(int) * MAX_INPUT);
    int i = 0, start = 0, size = 0;

    while(!feof(stdin)) {
        //Recebimento de números
        if(scanf("%d ", &numbers[i]) == 1) {
            i++;
            size++;
            if(feof(stdin)) break;
        }
    }

    print(numbers, size);
    if(!strcmp(argv[1], "-m")) {
        puts("Merge Sort");
        merge_sort(numbers, start, size-1);
        print(numbers, size);
    }
    if(!strcmp(argv[1], "-q")) {
        puts("Quick Sort");
        quick_sort(numbers, start, size-1);
        print(numbers, size);
    }
    return 0;
}

void merge_sort(int* array, int start, int end) {
    int middle;
    if(start < end) {
        middle = (start + end)/2;
        merge_sort(array, start, middle);
        merge_sort(array, middle+1, end);
        merge(array, start, middle, end);
    }
}

void merge(int* array, int start, int middle, int end) {
    int* temp;                 //Vetor auxiliar aonde ficarão os resultados ordenados
    int size = end - start + 1, i, j;  //Aqui fica cada índice para a ordenação
    int counter1  = start, counter2 = middle + 1;
    int end_flag1 = 0, end_flag2 = 0; //Essas flags denotam se o limite de uma metade em ordenamento foi alcançado


    temp = (int*) malloc(size*sizeof(int)); if(!temp) exit(1); //Em caso de erro de memória
    if(temp) {
        for(i = 0; i < size; i++) {
            if(!end_flag1 && !end_flag2) {
                if(array[counter1] < array[counter2]) {
                    temp[i] = array[counter1]; //Se já estiver ordenado, o temp pega o valor da primeira metade.
                    counter1++;
                } else {
                    temp[i] = array[counter2];   //Se não estiver, o temp recebe o valor da segunda
                    counter2++;
                }

                if(counter1 > middle) end_flag1 = 1;  //Limites alcançados
                if(counter2 > end) end_flag2 = 1;

            } else {
                if(!end_flag1) {
                    temp[i] = array[counter1];
                    counter1++;
                } else {
                    temp[i] = array[counter2];
                    counter2++;
                }
            }
        }
        for(i = 0, j = start; i < size; i++, j++) array[j] = temp[i]; //Traduz o vetor ordenado para o original.
    }
    free(temp); //Para evitar acúmulo na memória.
}

void quick_sort(int* array, int start, int end) {
    int pivot;

    if(start < end) {
        pivot = partition(array, start, end);
        quick_sort(array, start, pivot-1);
        quick_sort(array, pivot+1, end);
    }
}
int partition(int* array, int start, int end) {
    int i, pivot, pivot_divider;
    pivot = end;
    pivot_divider = start;
    for(i = start; i < end; i++) {
        if(array[i] < array[pivot]) {
            swap(&array[i], &array[pivot_divider]);
            pivot_divider++;
        }
    }
    swap(&array[pivot], &array[pivot_divider]);

    return pivot_divider;
}

void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void print(int* array, int size) {
    int i;
    puts("Elements:");
    for(i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    puts(""); printf("Size is %d\n", size);
}
