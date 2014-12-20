// AlgoritmoDijkstraCodigo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

void dijkstra(int ***matriz1, int t, int s, int *numcidades, int infinito, char ***cidades1){
	// infinito=999, S = Origem e T = Destino.
    int *dist=NULL /* Vetor Distancias*/, *perm=NULL /* Vetor de permanentes*/, *path=NULL /*Vetor de precedência*/, **matriz=NULL;
    int current /*vertice atual*/, i, k, dc /*Distancia do vertice atual(current)*/;
    int smalldist /*Menor Distancia*/, newdist /*Novo valor da distancia*/;
    char **cidades=(*cidades1);
    FILE *arq=NULL;
    
    matriz = *matriz1;
	
	remove("caminho_minimo.txt");
    arq=fopen("caminho_minimo.txt","w");//cria o arquivo para a escrita do caminho mínimo
    if(arq==NULL){//verificação
         printf(" Erro ! Erro de abertura no arquivo \"caminho_minimo.txt\"(ponteiro)\n");
         system("pause");
         exit(1);
    }

	dist=(int*)malloc((*numcidades)*sizeof(int));
	perm=(int*)malloc((*numcidades)*sizeof(int));
	path=(int*)malloc((*numcidades)*sizeof(int));
	if((dist==NULL)|(perm==NULL)|(path==NULL)){
	   printf("\n Erro na alocacao de algum vetor auxiliar na funcao deijakstra2! \n"); 
	   exit(1);                                                                                                                                                                 
	}

    /* Inicializa todos os índices de 'perm' como 0 e de 'dist' como INFINITY */
    for (i = 0; i < (*numcidades); i++)
    {
        perm[i] = 0; //perm[i] = -1
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
        for (i = 0; i < (*numcidades); i++){
            //se o elemento NÃO está em perm
            if (perm[i] == 0){ //if (perm[i] == -1){
                //calcula distância a partir do vértice corrente ao vértice adjacente i
                newdist = dc + matriz[current][i];//g->arcs[current][i].weight;

                //se a distância partindo do vértice corrente for menor, atualiza o vetor
                //de distâncias e de precedência
                if (newdist < dist[i])
                {
                    dist[i] = newdist;
                    path[i] = current;
                }

                //determina o vértice (entre todos os não pertencentes a perm) com menor distância
                if (dist[i] < smalldist)
                {
                    smalldist = dist[i];
                    k = i;
                }

            }

        } /* fim for */

        /* embora estamos assumindo grafos ponderados e conexos, este if garante que
         em caso de não existência de um caminho o programa não entre em loop infinito */
        if (current == k)
        {
            printf("\n\nCAMINHO NAO EXISTE\n\n");
            return;
        }

        current = k;
        perm[current] = 1;

    } /* fim while */





    /* impressao do resultado ****************/

    printf("\n\nRESULTADO: ");
    int caminho = t;

    printf(" %d - %s <- \t\t", t, cidades[t]);
    fprintf(arq, "%i - %s  <- \t\t", t, cidades[t]);
    
    while (caminho != s)
    {
        printf("%d - %s \t", path[caminho], cidades[path[caminho]]);
        fprintf(arq, "%d - %s \t", path[caminho], cidades[path[caminho]]);
        caminho = path[caminho];

        if (caminho != s)
        {
            printf (" \t <- \t");
            fprintf(arq, " \t <-  \t");
        }
    }
    fprintf(arq, "\n\ncusto: %d\n\n", dist[k]); 
    printf("\n\ncusto: %d\n\n", dist[k]);
    /****************************************/
    free(dist);free(perm);free(path);
    fclose(arq);
}/* fim da função dijkstra */


/*----------------------------------------------------------------------------*/
void leArquivo(int ***matriz1,char ***cidades1,int *numcidades)
{
	int aux /*Usado pra percorrer as cidades do arquivo cidades.txt*/,aux2,i,j, **matriz=NULL;
    char **cidades=NULL, nomearq[200];
    FILE *arq /*Arquivo cidades.txt*/, *arq2=NULL /*Arquivo matriz.txt*/;

    //arquivo
    fflush(stdin);
    printf("\nDigite o nome do arquivo o qual o grafo se encontra\n Sugestao: nome_do_arquivo.txt \n ");
    gets(nomearq);
    arq=fopen(nomearq,"r");
    remove("matriz.txt");
    arq2=fopen("matriz.txt","w");/* abre o arquivo "matriz.txt" pra poder escrever um arquivo apenas com a matriz do grafo*/
	if(arq==NULL|arq2==NULL){//Verificação dos Arquivos txt
       printf(" Erro ! O nome do arquivo e invalido, ou falta estar acompanhado da extensao \".txt\" \n Ou Erro de abertura de um dos dois arquivos (ponteiro)\n");
       system("pause");
       exit(1);
    }

    fscanf(arq,"%d %d",&aux,numcidades);

    //aloca cidades 
    cidades=(char**)malloc((*numcidades)*sizeof(char*));
    if(cidades==NULL){ //verificação com o vetor de ponteiros cidades
            printf("falha alocação");
            system("pause");
            exit(1);
    }

    for(i=0;i<(*numcidades);i++){
         cidades[i]=(char*)malloc(200*sizeof(char));
         if(cidades[i]==NULL){ //Verificação
            printf("falha alocação");
            system("pause");
            exit(1);
         }
    }
    
	//aloca distancias
    matriz=(int**)malloc((*numcidades)*sizeof(int*));
    if(matriz==NULL){ //Verificação
            printf("falha alocação");
            system("pause");
            exit(1);
    }
    for(i=0;i<(*numcidades);i++){
         matriz[i]=(int*)malloc((*numcidades)*sizeof(int));
         if(matriz[i]==NULL)
         {
            printf("falha alocação");
            system("pause");
            exit(1);
         }
    }

	//pega nome das cidades
    for(i=0;i<(*numcidades);i++){
         fscanf(arq,"%d %d %s",&aux,&aux2,cidades[i]);
    }

    //pega distancias
    for(i=0;i<(*numcidades);i++){
         fscanf(arq,"%d %d",&aux,&aux2);
         for(j=0;j<(*numcidades);j++)
            fscanf(arq,"%d",&matriz[i][j]);
    }
    //
    (*matriz1)=matriz;
    (*cidades1)=cidades;

	/* laço para a escrita da matriz no arquivo matriz.txt*/
    for(i=0;i<(*numcidades);i++){ 
		fprintf(arq2, " \n");
        for(j=0;j<(*numcidades);j++){
             fprintf(arq2, "%d \t", matriz[i][j]);
        }
    }
      
    fclose(arq2);
    fclose(arq);
}
/*----------------------------------------------------------------------------*/
int _tmain(int argc, _TCHAR* argv[])
{
      int **matriz = NULL,num /*QTD_Cidades*/,i,j, infinito, x, y, peso,origem,destino;
      char **cidades=NULL,op = 's';
      FILE *arq=NULL;
	  JPrincipal jp = null;
     do{ 
		 printf("\n *********************************\n");
		 printf("\tAlgoritmo Dijkstra\t\n ");
		 printf("\n *********************************\n\n\n\n");
		 infinito=999;/*Observe que o valor de infinito, poderia ser dado pelo usuário ou definido no arquivo, decidi colocar aqui  */
		 printf("\nApenas para lembrar que um valor maior que 999, indica que a distancia\n eh infinita, ou seja, que esses dois grafos nao possuem conexoes! \n");
		 leArquivo(&matriz,&cidades,&num);

		 system("CLS");
		 printf(" numero de cidades: %d \n\n",num);
		 for(i=0;i<num;i++){
			 printf(" %d - %s \n",i,cidades[i]);
		 }

		 do{
			  printf("\nEntre com o valor do no de origem: ");
			  scanf("%d",&origem);
		 }while(origem<0||origem>num);

		 do{
			  printf("\nEntre com o valor do no de destino: ");
			  scanf("%d",&destino);
		 }while(destino<0||destino>num);

		 dijkstra(&matriz, destino, origem, &num, infinito, &cidades);
		  
		 /*laço para liberar a matriz*/
		 for(j=(num-1);j>=0;j--){
			  free(matriz[j]);
			  free(cidades[j]);                 
		 }
		 free(matriz);
		 free(cidades);
		 printf("\nDeseja gerar caminho minimo (S/N)?\n");
		 scanf("%c",&op);
		 system("CLS");
     }while(op == 'S' || op == 's');

     return 0;
}
