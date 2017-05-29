#define STRINGSIZE 30

#include<stdio.h>
#include<stdlib.h>

void ComparaIP(int *mIP, int *mNIP, int n, int i,char *mDOM);
int rasterizaNumero(int m, int limite);

int main (void){
	int n, i;
	//Matriz com IPs modelo
	int *mIP;
	//Matriz com IPs a serem avaliados
	int *mNIP;
	//Matriz com os "dominios"
	char *mDOM;

	//Recebe o numero de IPs base
	scanf("%d",&n);
	
	//Aloca memoria para as matrizes
	mIP = (int*) malloc(sizeof(int)*(n*5));
	mNIP = (int*) malloc(sizeof(int)*(n*5));
	mDOM = (char*) malloc(sizeof(char)*n*STRINGSIZE);

	//Recebe como Input os IPs e sua parte significativa
	for(i=0;i<n;i++){
		scanf("%d.%d.%d.%d/%d ",mIP+(i*5), mIP+(i*5+1), mIP+(i*5+2), mIP+(i*5+3), mIP+(i*5+4));
		gets(mDOM+i*STRINGSIZE);
	}
	//Recebe os IPs a serem testados ate o arquivo de entrada acabar
	i=0;
	while(!feof(stdin)){
		scanf("%d.%d.%d.%d",mNIP+(i*5), mNIP+(i*5 +1), mNIP+(i*5+2), mNIP+(i*5+3));
		i++;
	}
	//Compara IPs
	ComparaIP(mIP,mNIP,n,i,mDOM);
}

void ComparaIP(int *mIP,int *mNIP,int n,int i,char *mDOM){
	int ultimoFixo=0,lim=8;
	int maiorS=0,indiceChave=0;

	for(int j=0; j < i-1;j++){
		for(int k=0; k < n;k++){
			ultimoFixo = (mIP[k*5+4]/8) +1;
			for(int l=0;l<ultimoFixo;l++){
				lim = mIP[k*5+4] - l*8;
				if(rasterizaNumero(mNIP[j*5+l],lim) != rasterizaNumero(mIP[k*5+l],lim)){
					break;
				}
				if(l == ultimoFixo-1 && l >= maiorS){
					maiorS = l;
					indiceChave = k;
				}
			}
		}
		printf("%d.%d.%d.%d ",mNIP[j*5],mNIP[j*5+1],mNIP[j*5+2],mNIP[j*5+3]);
		puts(mDOM+indiceChave*STRINGSIZE);
		indiceChave=0;
		maiorS=0;
	}

}
//Rasterizar eh o mesmo que transformar um int A em um numero decimal que seus digitos sao binarios. Ex.: 11 -> 1011
int rasterizaNumero(int m,int limite){
	int vetor[8] = {0,0,0,0,0,0,0,0};
	int i = 0;
	int valor = 0;

	if(limite>8){
		limite=8;
	}else if (limite < 0){
		return 0;
	}
	while(7-i>=0){
		vetor[7-i] = m - (m/2)*2;
		m = m/2;
		i++;
	}
	i=0;
	while(limite-i>0){
		valor = valor*10 + vetor[i];
		i++;
			
	}
	return valor;	
}
