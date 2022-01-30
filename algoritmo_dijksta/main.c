#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 20

typedef int bool;
#define true 1
#define false 0

typedef struct adjacencia{
    int vertice; //vertice com o qual a adjacencia acontece
    int peso; //peso da adjacencia
    struct adjacencia *prox; //proxima adjacencia
}ADJACENCIA;

typedef struct vertice{
    ADJACENCIA *cab; //adjacencias q o vertice possui
    int p; //predecessor do vertice
    int d; //distancia do vertice
}VERTICE;

typedef struct grafo{
    int vertices; //quantidade de vertices
    int arestas; //quantidade de arestas
    VERTICE *adj; //vertices do grafo
    int s; //vertice inicial
}GRAFO;

GRAFO* Criar_Grafo(){ //aloca o grafo e zera as variaveis da estrutura
    GRAFO *g;
    g = malloc(sizeof(GRAFO));
    if(g == NULL){
        printf("Erro!");
        exit(0);
    }
    g->vertices = 0;
    g->arestas = 0;
    g->adj = NULL;
    g->s = -1;
    return g;
}

GRAFO* Criar_Vertice(GRAFO *g){ //cria vertice
    if(g == NULL){ //verifica se o grafo existe
        printf("\nGrafo inexistente\n\n");
        return NULL;
    }
    if(g->adj == NULL){//cria vertice inicial
        g->vertices++;
        g->adj = malloc(sizeof(VERTICE));
        g->adj->cab = NULL;
        g->adj->d = 0;
        g->adj->p = -1;
        g->s = 0;
        printf("\nVertice inserido!\n");
        return g;
    }
    if(g->vertices<MAX){//cria vertice se ainda nao houver 20 vertices
        g->vertices++;
        g->adj = realloc(g->adj, g->vertices*sizeof(VERTICE));
        g->adj[g->vertices-1].cab = NULL;
        g->adj[g->vertices-1].d = INT_MAX/2;
        g->adj[g->vertices-1].p = -1;
        printf("\nVertice inserido!\n");
        return g;
    }
    printf("\nLimite de vertices atingido\n\n");
    return g;
}

ADJACENCIA* Criar_Adjacencia(int v, int peso){ //criar adjacencia de um vertice com o outro
    ADJACENCIA *temp;
    temp = malloc(sizeof(ADJACENCIA));
    if(temp == NULL){
        printf("Erro!");
        exit(0);
    }
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

bool Criar_Aresta(GRAFO *g, int vi, int vf, int p){
    if(g == NULL){
        printf("\nGrafo inexistente\n\n");
        return false;
    }
    if(vf<0 || vf>=g->vertices){//verifica se o vertice final e valido
        printf("\nvertice final invalido!\n\n");
        return false;
    }
    if(vi<0 || vi>=g->vertices){//verifica se o vertice inicial e valido
        printf("\nvertice inicial invalido!\n\n");
        return false;
    }
    ADJACENCIA *novo = Criar_Adjacencia(vf, p); //cria adjacencia
    novo->prox = g->adj[vi].cab;
    g->adj[vi].cab = novo;
    g->arestas++;
    return true;
}

void imprime (GRAFO *g){
    if(g == NULL){
        printf("\nGrafo inexistente\n\n");
        return;
    }
    printf("\nVertices: %d Arestas: %d\n",g->vertices, g->arestas);
    for(int i=0; i<g->vertices; i++){
        printf("v%d: ",i);
        ADJACENCIA *ad = g->adj[i].cab;
        while(ad){
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
    printf("\n");
}

void Dijkstra (GRAFO *g){
    int flag = 0;
    if(g == NULL){
        printf("\nGrafo inexistente!\n\n");
        return;
    }
    if(g->adj == NULL){//verifica se o grafo tem vertices
        printf("\nNenhum vertice alocado!\n\n");
        return;
    }
     if(g->vertices == 1){ //verifica se ha mais de um vertice pra poder calcular a menor distancia
        printf("\nSomente um vértice alocado!\n\n");
        return;
    }
    ADJACENCIA *ad;
    for(int i=0; i<g->vertices; i++){
        if (g->adj[i].d == INT_MAX/2)
            flag = 1;
        ad = g->adj[i].cab;
        while(ad != NULL){//enquanto ha adjacencia, verifica se a distancia do predecessor anterior e maior que a do atual
            if(g->adj[i].d+ad->peso<g->adj[ad->vertice].d){
                g->adj[ad->vertice].d = g->adj[i].d+ad->peso;
                g->adj[ad->vertice].p = i;
            }
            ad = ad->prox;
        }
    }
    if(flag == 1)
        Dijkstra(g);
}

void imprime_menor_caminho(GRAFO *g){
    int v;
    printf("\nInsira o vertice desejado: ");
    scanf("%d", &v);
    if(g == NULL){
        printf("\nGrafo inexistente!\n\n");
        return;
    }
    if(g->adj == NULL){
        printf("\nNenhum vertice alocado!\n\n");
        return;
    }
    if(v>=g->vertices){
        printf("\nvertice invalido!\n\n");
        return;
    }
    if(v==0){
        printf("\nvertice inicial!\n\n");
        return;
    }
    int *aux = malloc(g->vertices*sizeof(int));
    int i=0;
    do{
        aux[i] = v; //aux[i] armazena o numero do vertice desejado
        i++;
        v = g->adj[v].p; //v recebe o predecessor
    }while(g->adj[v].p != -1 && v != -1);
    if(v == -1 || v!=0){//nao imprime caso o vertice pedido nao esteja ligado ao vertice inicial
        printf("\nVertice nao acessivel\n\n");
        return;
    }
    aux[i] = 0; //caminho comeca no vertice inicial
    printf("\nMenor caminho para v%d: ", aux[0]);
    for(; i>0; i--){
        printf(" v%d ", aux[i]); //mostra caminho
    }
    printf("\nDistancia: %d\n\n", g->adj[aux[0]].d);
}

int main()
{
    int op, vi, vf, p;
    GRAFO *g;
    g = Criar_Grafo();
    while(true){
        printf("Menu:\n\n1- Inserir vertice\n2- Inserir Aresta\n3- Imprimir\n4- Mostra o menor caminho\n0- Sair do programa\n\nOpcao: ");
        scanf("%d", &op);
        switch(op){
        case 1:
            g=Criar_Vertice(g);
            printf("\n");
            break;
        case 2:
            printf("Insira o vertice inicial: ");
            scanf("%d", &vi);
            printf("Insira o vertice final: ");
            scanf("%d", &vf);
            printf("Insira o peso da aresta: ");
            scanf("%d", &p);
            Criar_Aresta(g,vi, vf, p);
            printf("\n");
            break;
        case 3:
            imprime(g);
            break;
        case 4:
            Dijkstra(g);
            imprime_menor_caminho(g);
            break;
        case 0:
            exit(1);
            break;
        default:
            printf("\nOpcao Invalida!\n\n");
        }
    }
    return 0;
}
