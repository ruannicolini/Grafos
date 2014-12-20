// AlgoritmoPrim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define TAMLIN 7
#define TAMCOL 7
//#define TAMLIN 6
//#define TAMCOL 6

typedef struct TVertice{
	int numero;
	int qtdVizinhos;
	bool selecionado;
	TVertice *vetorPonteiroVizinhos[TAMLIN];
}Vertice;

typedef struct TAresta{
	//Vertice verticeLIN;
    //Vertice verticeCOL;
	Vertice *verticeLIN;
    Vertice *verticeCOL;
	bool selecionado;
	int peso;
}Aresta;

typedef struct grafo{
	int numVertice;
	int numArestas;
	int matriz[TAMLIN][TAMCOL];
	Vertice vetVertices[TAMLIN];
	Aresta vetArestasOrdenadasPorPeso[TAMLIN * TAMCOL];
	Aresta *agm[(TAMLIN - 1)];
}Grafo;

int indAresta = 0;

void inicializaVetorPonteiroVizinho(Vertice **vetor){
	for(int i =0; i < TAMLIN; i++){
		vetor[i] = NULL;
	}
}

//==============================================================================
	// Bubble Sort
int verificarMaior(Aresta p, Aresta p2){
    int i; 
	Aresta maior;
	if(p.peso > p2.peso)
        maior = p;
    else
        maior = p2;
 
	for(i = 0; i < maior.peso;i++){
		if(p.peso > p2.peso)
              return 0;
		else if(p.peso < p2.peso) 
              return 1;
		else if((i+1) == maior.peso && p.peso == p2.peso )
              return 0;
          
    }
}

void swapbubble(Aresta vetNum[TAMLIN * TAMCOL], int i ){
     Aresta aux;
     aux = vetNum[i];
     vetNum[i] = vetNum[i+1];
     vetNum[i+1] = aux; 
}

void bubbleSort(Aresta vetNum[TAMLIN * TAMCOL], int qtd){ // qtd é a quantidade de numeros inseridos no vetor 
     int i;
	 Aresta p, p2;
     int trocou;
     do{
         qtd--;
         trocou = 0;
         for(i = 0; i < qtd; i++){
			 p = vetNum[i];
			 p2 = vetNum[i+1];
             if(verificarMaior(  p, p2  ) == 0){
                   swapbubble(&(*vetNum), i);
                   trocou = 1;     
             }
         }
     }while(trocou);    
}

//==============================================================================
Vertice* buscaVertice(int num, Grafo *grafo){
	Vertice *v = NULL;
	for(int i = 0; i< (grafo->numVertice); i++){
		if(grafo->vetVertices[i].numero == num){
			return (&(grafo)->vetVertices[i]);
		}
	}
	return (v);
}

void inicializaGrafo(Grafo**grafo){
	Vertice *vertice = (Vertice*) malloc(sizeof(Vertice));;
	(*grafo)->numArestas = 0;
	(*grafo)->numVertice = 0;

	//Inicializa "(*grafo)->matriz"
	for(int lin = 0; lin < TAMLIN; lin++){
		for(int col = 0; col < TAMLIN; col++){
			(*grafo)->matriz[lin][col] = 0;
		}
	}

	// Inicializa "vetVertices" e "vetArestasOrdenadasPorPeso"
	for(int i = 0; i< (TAMLIN * TAMCOL); i++){
		//Inicializa "vetVetrice"
		(*grafo)->vetVertices[i].numero = 0;
		(*grafo)->vetVertices[i].qtdVizinhos = 0;
		(*grafo)->vetVertices[i].selecionado = false;
		for(int c = 0; c < (TAMLIN-1); c++){ //TAMLIN-1 pq se temos 10 vertices, apenas 9 podem ser vizinhos.
			(*grafo)->vetVertices[i].vetorPonteiroVizinhos[c] = NULL;
		}

		//Inicializa "vetArestasOrdenadasPorPeso"
		(*grafo)->vetArestasOrdenadasPorPeso[i].peso = 0;
		(*grafo)->vetArestasOrdenadasPorPeso[i].selecionado = false;
		(*grafo)->vetArestasOrdenadasPorPeso[i].verticeCOL = vertice;
		(*grafo)->vetArestasOrdenadasPorPeso[i].verticeLIN = vertice;
	}

	//Inicializa "(*grafo)->agm"
	for(int i = 0; i < (TAMLIN-1); i++){
		/*
		(*grafo)->agm[i].peso = 0;
		(*grafo)->agm[i].verticeCOL = NULL;
		(*grafo)->agm[i].verticeLIN = NULL;
		*/
		(*grafo)->agm[i] = NULL;
	}
}

void geraGrafo(Grafo**grafo , int m[TAMLIN][TAMCOL]){
	int indPontVizim = 0;
	Aresta aresta;
	Vertice vertice;

	//Contabiliza e Atribui os vértices da matriz no grafo
	for(int lin = 0; lin < TAMLIN; lin++){
		vertice.numero = lin;
		vertice.selecionado = false;
		(*grafo)->vetVertices[lin] = vertice;
		(*grafo)->numVertice++;
	}

	//Atribui Vizinhos aos Vertices
	for(int lin = 0; lin < TAMLIN; lin++){
		indPontVizim = 0;
		(*grafo)->vetVertices[lin].qtdVizinhos = 0;
		
		for(int col = 0; col < TAMCOL; col++){
			if(m[lin][col] != 0){
				(*grafo)->vetVertices[lin].vetorPonteiroVizinhos[indPontVizim] = (&((*grafo)->vetVertices[col]));
				(*grafo)->vetVertices[lin].qtdVizinhos++;
				indPontVizim++;
			}
		}
	}

	//Passa a Matriz para o grafo;
	//Contabiliza e Atribui as arestas da matriz no grafo 
	for(int lin = 0; lin < TAMLIN; lin++){
		for(int col = 0; col < TAMCOL; col++){
			(*grafo)->matriz[lin][col] = m[lin][col];
			if(m[lin][col] != 0){
				(*grafo)->numArestas++;
				aresta.peso = m[lin][col];
				aresta.selecionado = false;
				aresta.verticeLIN = (buscaVertice(lin, (*grafo)));
				aresta.verticeCOL = (buscaVertice(col, (*grafo)));
				(*grafo)->vetArestasOrdenadasPorPeso[indAresta] = aresta;
				indAresta++;
			}
		}
	}
	bubbleSort((&(*(*grafo)->vetArestasOrdenadasPorPeso)), indAresta);

}
Aresta* retornaAresta(Grafo*grafo, Vertice *ponta1, Vertice *ponta2){
	Aresta *aresta = NULL;
	bool validador = false;
	for(int i = 0;((i<grafo->numArestas)); i++){
		if((grafo->vetArestasOrdenadasPorPeso[i].verticeLIN == ponta1)&&(grafo->vetArestasOrdenadasPorPeso[i].verticeCOL == ponta2)){
			aresta = &(grafo->vetArestasOrdenadasPorPeso[i]);
			return aresta;
		}
	}
	return (aresta);
}

void prim(Grafo**grafo, Vertice *ponta1, Vertice *ponta2, int ind){
	Vertice *verticeAUX = NULL;
	int qtdArestasSelecionadas = 1;
	Aresta* aresta = NULL;
	Aresta* arestaMenorPeso = NULL;
	ponta1->selecionado = true;
	ponta2->selecionado = true;
	(*grafo)->agm[ind] = retornaAresta((*grafo), ponta1, ponta2);
	ind++;
	while(qtdArestasSelecionadas < (*grafo)->numVertice - 1){
		verticeAUX = NULL;
		aresta = NULL;
		arestaMenorPeso = NULL;
		for(int x = 0; x < (*grafo)->numVertice; x++){
			ponta1 = &(*grafo)->vetVertices[x];
 			if(ponta1->selecionado == true){
				for(int i=0; i<ponta1->qtdVizinhos; i++){
					if(ponta1->vetorPonteiroVizinhos[i]->selecionado == false){
						aresta = retornaAresta((*grafo), ponta1, ponta1->vetorPonteiroVizinhos[i]);
						if(aresta->selecionado == false){
							if(arestaMenorPeso == NULL){
								arestaMenorPeso = aresta;
								verticeAUX = (ponta1->vetorPonteiroVizinhos[i]);
							}else{
								if( aresta->peso <= arestaMenorPeso->peso){
									arestaMenorPeso = aresta;
									verticeAUX = (ponta1->vetorPonteiroVizinhos[i]);
								}//if
							}//else
						}//if

					}//if
				}//for
			}//if
			
		}//for
		arestaMenorPeso->selecionado = true;
		verticeAUX->selecionado = true;
		(*grafo)->agm[ind] = arestaMenorPeso;
		qtdArestasSelecionadas++;
		ind++;
	}//while
}

void processamento(int m[TAMLIN][TAMCOL]){
	Vertice *ponta1LIN = NULL;
	Vertice *ponta2COL = NULL;

	Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
	inicializaGrafo(&(grafo));
	geraGrafo(&grafo, m);
	system("cls");

	ponta1LIN = (grafo)->vetArestasOrdenadasPorPeso[0].verticeLIN;
	ponta2COL = (grafo)->vetArestasOrdenadasPorPeso[0].verticeCOL;

	prim(&grafo, ponta1LIN, ponta2COL, 0);

	//Informações do Grafo
	system("cls");
	printf("Informações do Grafo: ");
	printf("\n\n Numero de Vertices: %d \n\n\n\n VERTICES: \n\n", grafo->numVertice);
	for(int i = 0; i< TAMLIN; i++){
		printf("\n\n Vizinhos do Vertice %d : ",(grafo->vetVertices[i].numero));
		for(int c = 0; c < (grafo->vetVertices[i].qtdVizinhos); c++ ){
			printf(" %d -",(grafo->vetVertices[i].vetorPonteiroVizinhos[c]->numero));
		}
	}
	printf("\n\n Numero de Arestas: %d \n\n\n\n ARESTAS: \n\n", grafo->numArestas);
	for(int i = 0; i < (grafo->numArestas); i++){
		printf("\nAresta %d%d - Peso: %d ", (grafo->vetArestasOrdenadasPorPeso[i].verticeLIN->numero), (grafo->vetArestasOrdenadasPorPeso[i].verticeCOL->numero), (grafo->vetArestasOrdenadasPorPeso[i].peso));
	}

	printf("\n\n\n Arvore Geradora Minima com Algoritmo de Prim: \n\n");
	for(int i = 0; i < (grafo)->numVertice - 1; i++){
		printf("\nAresta %d%d - Peso: %d ", (grafo->agm[i]->verticeLIN->numero), (grafo->agm[i]->verticeCOL->numero), (grafo->agm[i]->peso));
	}
	printf("\n\n\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	int m[TAMLIN][TAMCOL] = 
				  {0,7,0,5,0,0,0,
				   7,0,8,9,7,0,0,
				   0,8,0,0,5,0,0,
				   5,9,0,0,15,6,0,
				   0,7,5,15,0,8,9,
				   0,0,0,6,8,0,11,
				   0,0,0,0,9,11,0};

	/*
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
	processamento(m);
	return 0;
}