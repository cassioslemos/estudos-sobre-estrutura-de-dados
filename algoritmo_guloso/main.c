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
    bool visitado;
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
        g->adj->visitado = false;
        g->s = 0;
        printf("\nVertice inserido!\n");
        return g;
    }
    if(g->vertices<MAX){//cria vertice se ainda nao houver 20 vertices
        g->vertices++;
        g->adj = realloc(g->adj, g->vertices*sizeof(VERTICE));
        g->adj[g->vertices-1].cab = NULL;
        g->adj[g->vertices-1].visitado = false;
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


void algoritmo_guloso(GRAFO *g, int vf){
    ADJACENCIA *aux = g->adj[0].cab;
    VERTICE *aux2 = g->adj;
    for(int i = 0; i < g->vertices; i++, aux2++)
        aux2->visitado = false;
    int menor = INT_MAX/2;
    int menor_v = -1;
    int soma = 0;
    int v[MAX];
    v[0] = 0;
    int i=1;
    aux2 = g->adj;
    while(aux != NULL && menor_v != vf){
        while(aux != NULL){
            aux2->visitado = true;
            if(menor > aux->peso && g->adj[aux->vertice].visitado != true){
                menor = aux->peso;
                menor_v = aux->vertice;
            }
                aux = aux->prox;
        }
        soma = soma + menor;
        aux = g->adj[menor_v].cab;
        aux2 = g->adj;
        for(int i2 = 0; i2 < menor_v; i2++)
            aux2++;
        menor = INT_MAX/2;
        if(menor_v != vf){
            v[i] = menor_v;
            i++;
        }
    }
    if (menor_v == vf){
        printf("\nCaminho guloso para v%d: ", vf);
        for(int i2=0; i2 < i; i2++)
            printf("v%d ", v[i2]);
        printf("Distancia: %d\n\n", soma);
    }
    else{
        printf("\nNao foi possivel obter um caminho guloso\n\n");
    }
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
            printf("\nInsira o vertice desejado: ");
            scanf("%d", &vf);
            if(g == NULL){
                printf("\nGrafo inexistente!\n\n");
            }
            if(g->adj == NULL){
                printf("\nNenhum vertice alocado!\n\n");
            }
            if(vf>=g->vertices){
                printf("\nvertice invalido!\n\n");
            }
            if(vf==0){
                printf("\nvertice inicial!\n\n");
            }
            else{
                algoritmo_guloso(g, vf);
            }

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
