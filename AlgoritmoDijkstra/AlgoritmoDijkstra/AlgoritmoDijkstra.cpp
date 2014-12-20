// AlgoritmoDijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#define TAMLIN 7
//#define TAMCOL 7
#define TAMLIN 6
#define TAMCOL 6

void dijkstra(int matriz[TAMLIN][TAMCOL], int t, int s, int infinito){
	// infinito=999, S = Origem e T = Destino.
    int *dist=NULL /* Vetor Distancias*/, *perm=NULL /* Vetor de permanentes*/, *path=NULL /*Vetor de precedência*/;
    int current /*vertice atual*/, i, k, dc /*Distancia do vertice atual(current)*/;
    int smalldist /*Menor Distancia*/, newdist /*Novo valor da distancia*/;

	dist=(int*)malloc((TAMLIN)*sizeof(int));
	perm=(int*)malloc((TAMLIN)*sizeof(int));
	path=(int*)malloc((TAMLIN)*sizeof(int));
	if((dist==NULL)|(perm==NULL)|(path==NULL)){
	   printf("\n Erro na alocacao de algum vetor auxiliar na funcao deijakstra2! \n"); 
	   exit(1);                                                                                                                                                                 
	}

    /* Inicializa todos os índices de 'perm' como 0 e de 'dist' como INFINITO */
    for (i = 0; i < (TAMLIN); i++){
        perm[i] = 0; 
        dist[i] = infinito;
    }

    /* Inclui 's' em perm (perm[s]=1) e configura(armazena) sua distancia como sendo zero */
    perm[s] = 1;
    dist[s] = 0;

    /* define 's' como origem (fonte) da busca */
    current = s;
    k = current;

    while (current != t){
        smalldist = infinito;
        dc = dist[current];
        for (i = 0; i < (TAMLIN); i++){
            //se o elemento NÃO está em perm
            if (perm[i] == 0){ 
                //calcula distância a partir do vértice corrente ao vértice adjacente i
                newdist = dc + matriz[current][i];

                //se a distância partindo do vértice corrente for menor, atualiza o vetor
                //de distâncias e de precedência
                if (newdist < dist[i]){
                    dist[i] = newdist;
                    path[i] = current;
                }

                //determina o vértice (entre todos os não pertencentes a perm) com menor distância
                if (dist[i] < smalldist){
                    smalldist = dist[i];
                    k = i;
                }
            }
        } /* fim for */

        /* Este if garante que em caso de não existência de um caminho o programa não entre em loop infinito */
        if (current == k){
            printf("\n\nCAMINHO NAO EXISTE\n\n");
            return;
        }
        current = k;
        perm[current] = 1;
    } 

    /* impressao do resultado */
    printf("\n\nRESULTADO: ");
    int caminho = t;

    printf(" %d  <- ", t);
    
    while (caminho != s){
        printf(" %d ", path[caminho]);
        caminho = path[caminho];
        if (caminho != s){
            printf (" <-  ");
        }
    } 

    printf("\n\ncusto: %d\n\n", dist[k]);
    free(dist);free(perm);free(path);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numSaida = 0, numFim = 0;
	int m[TAMLIN][TAMCOL] = 
				  {999,2,1,999,999,999,
				   2,999,999,1,999,999,
				   1,999,999,3,4,999,
				   999,1,3,999,999,2,
				   999,999,4,999,999,2,
				   999,999,999,2,2,999};

	/*
	int m[TAMLIN][TAMCOL] = 
				  {0,7,0,5,0,0,0,
				   7,0,8,9,7,0,0,
				   0,8,0,0,5,0,0,
				   5,9,0,0,15,6,0,
				   0,7,5,15,0,8,9,
				   0,0,0,6,8,0,11,
				   0,0,0,0,9,11,0};

	int m[TAMLIN][TAMCOL] = 
				  {0,0,5,8,0,0,0,
				   0,0,16,0,30,0,26,
				   5,16,0,10,3,0,0,
				   8,0,10,0,2,18,0,
				   0,30,3,2,0,12,14,
				   0,0,0,18,12,0,4,
				   0,26,0,0,14,4,0};
	*/
	/*
	int m[TAMLIN][TAMCOL] = 
				  {0,5,0,0,15,2,
				   5,0,0,9,22,4,
				   0,0,0,12,1,0,
				   0,9,12,0,0,6,
				   15,22,1,0,0,0,
				   2,4,0,6,0,0};
	*/
	printf("Vertice Saida: ");
	scanf("%d", &numSaida);
	printf("\n\nVertice Chegada: ");
	scanf("%d", &numFim);

	dijkstra(m, numFim, numSaida,999);
	return 0;
}
