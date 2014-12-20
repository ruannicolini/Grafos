// AlgoritmoFordFulkerson.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define TAMLIN 7
#define TAMCOL 7
//#define TAMLIN 5
//#define TAMCOL 5

bool verificaBloqueio_S(int s,int m[TAMLIN][TAMCOL],int vizinhos_S[TAMLIN],int qtdVizinhos_S, bool bloqueio[TAMLIN][TAMCOL]){
	bool resposta = true;

	for(int i = 0; i<qtdVizinhos_S; i++){
		//printf("\n\n %d \n\n", m[s][vizinhos_S[i]]);
		if(bloqueio[s][vizinhos_S[i]] == false){
			resposta = false;
			return resposta;
		}
	}
	return resposta;
}

int indiceAtual(int atual, int caminho[TAMLIN]){
	int ind = 0;
	for(int i = 0; i<TAMLIN; i++ ){
		if((caminho[i]) == atual){
			ind = i;
			return ind;
		}
	}
	return ind;
}

void fordFulkerson(int m[TAMLIN][TAMCOL], int t, int s){
	int vizinhos_S[TAMLIN], qtdVizinhos_S = 0, atual = 0, arestax =0, fluxoMaximo = 0;
	int /*bloqueio[TAMLIN],*/ caminho[TAMLIN], aux =0, i = 0, menorValor = 9999, k=0,indCaminho = 0;
	bool bloqueio[TAMLIN][TAMCOL];

	for(i = 0; i<TAMLIN; i++){
		//inicializa matriz Bloqueio
		for(int j = 0; j<TAMCOL; j++){ bloqueio[i][j] = false;}
		//registra e conta vizinhos de S
		if(m[s][i] > 0){
			vizinhos_S[qtdVizinhos_S] = i;
			qtdVizinhos_S++;
		}
	}

	while(verificaBloqueio_S(s, m,vizinhos_S,qtdVizinhos_S, bloqueio) == false){
		atual = s;
		for(i = 0; i<TAMLIN; i++){
			caminho[i] = -999;
			
			for(int j = 0; j<TAMCOL; j++){
				bloqueio[i][j] = false;
			}
		}
		while((atual != t)&&((verificaBloqueio_S(s, m,vizinhos_S,qtdVizinhos_S, bloqueio) == false))){
			k = -1;
			arestax = 0;
			for(i = 0; i<TAMLIN; i++){
				if((m[atual][i] != 0)&&(m[atual][i] != -999)&&(i != s)&&(m[atual][i] > arestax)&&(bloqueio[atual][i] != true)){
					if(caminho[i] != atual){
						arestax = m[atual][i];
						k = i;
						caminho[atual] = i;
					}
				}else{
					if((m[atual][i] == arestax)&&(i == t)&&(m[atual][i] != 0)&&(m[atual][i] != -999)){
						arestax = m[atual][i];
						k = i;
						caminho[atual] = i;
					}else{
						if((m[atual][i] == 0)||(m[atual][i] == -999)||(i == s)){
							bloqueio[atual][i] = true;
						}
					}
				}
			}//..for
			if(k == t){
				menorValor = 9999;
				for(int j = 0; j<TAMLIN;j++){
					if(caminho[j] != -999){
						if((m[j][caminho[j]])<(menorValor)){
							menorValor = m[j][caminho[j]];
						}
					}
				}
				fluxoMaximo += menorValor;
				aux = s;
				while(aux != t){
					m[aux][caminho[aux]] = m[aux][caminho[aux]] - menorValor;
					m[caminho[aux]][aux] = m[caminho[aux]][aux] + menorValor;
					aux = caminho[aux];
				}//..While
			}//..if
			if(k == -1){
				aux = atual;
				atual = indiceAtual(atual, caminho);
				bloqueio[atual][aux] = true;
			}else{
				atual = k;
			}
		}
	}

	// Impressão do Fluxo Máximo
	printf("\n\n Fluxo Maximo = %d", fluxoMaximo);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numSaida = 0, numFim = 0;

	/*
	int m[TAMLIN][TAMCOL] = 
				  {-999,1,-999,3,-999,0,-999,
				   0,-999,2,4,5,0,-999,
				   -999,0,-999,-999,4,0,-999,
				   0,0,-999,-999,0,-999,9,
				   -999,0,0,1,-999,-999,6,
				   5,7,4,-999,-999,-999,-999,
				   -999,-999,-999,0,0,-999,-999};
				   */
	
	int m[TAMLIN][TAMCOL] = 
				  {-999,7,9,5,-999,-999,-999,
				   2,-999,2,-999,3,-999,-999,
				   1,1,-999,2,3,2,-999,
				   0,-999,3,-999,-999,4,-999,
				   -999,3,2,-999,-999,3,8,
				   -999,-999,2,2,2,-999,9,
				   -999,-999,-999,-999,4,1,-999};
	

	/*
	int m[TAMLIN][TAMCOL] = 
				  {-999,20,30,10,-999,
				   0,-999,40,-999,30,
				   0,0,-999,10,20,
				   0,-999,5,-999,20,
				   -999,0,0,0,-999};
	*/

	printf("Vertice Saida: ");
	scanf("%d", &numSaida);
	printf("\n\nVertice Chegada: ");
	scanf("%d", &numFim);

	fordFulkerson(m, numFim, numSaida);
	return 0;
}

