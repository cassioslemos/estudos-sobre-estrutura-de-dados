#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
int valor;
struct nodo *esq, *dir;
}NODO;

void* insere(NODO *arvore){
    int num;
    printf("\nDigite um numero: ");
    scanf("%d",&num);
    if(arvore == NULL){
        arvore = malloc(sizeof(NODO));
        arvore->valor = num;
        arvore->dir = NULL;
        arvore->esq = NULL;
        return arvore;
    }
    NODO *pai, *ant;
    ant = arvore;
    pai = arvore;
    do{
        if(num<pai->valor){
        ant = pai;
        pai = pai->esq;
        }
        else{
            ant = pai;
            pai = pai->dir;
        }
    }while(pai!=NULL);
    if(num<ant->valor){
        pai = malloc(sizeof(NODO));
        pai->valor = num;
        pai->dir = NULL;
        pai->esq = NULL;
        ant->esq = pai;
        return arvore;
    }
    else{
        pai = malloc(sizeof(NODO));
        pai->valor = num;
        pai->dir = NULL;
        pai->esq = NULL;
        ant->dir = pai;
        return arvore;
    }
}

void* Excluir(NODO *arvore){
    if(arvore == NULL){
        printf("\nArvore vazia!\n\n");
        return arvore;
    }
    int num;
    printf("\nDigite um numero: ");
    scanf("%d",&num);
    NODO *pai, *filho, *ant;
    filho = arvore;
    ant = NULL;
    while(filho != NULL && filho->valor != num){
        if(num<filho->valor){
            ant = filho;
            filho = filho->esq;
        }
        else{
            ant = filho;
            filho = filho->dir;
        }
    }
    if(filho == NULL){
        printf("\nValor nao encontrado!\n\n");
        return arvore;
    }
    if(filho->esq == NULL && filho->dir == NULL){
        if(ant->dir->valor == num)
            ant->dir = NULL;
        else
            ant->esq = NULL;
        free(filho);
        return arvore;
    }
    if(filho->esq == NULL){
        if(ant == NULL){
            arvore = filho->dir;
            return arvore;
        }
        else{
            if(ant->dir != NULL && ant->dir->valor == num){
                ant->dir = filho->dir;
                return arvore;
            }
            else{
                ant->esq = filho->dir;
                return arvore;
            }
        }
    }
    ant = filho;
    pai = filho->esq;
    while(pai->dir != NULL){
        ant = pai;
        pai = pai->dir;
    }
    ant->dir = NULL;
    filho->valor = pai->valor;
    free(pai);
    return arvore;
}

void Busca(NODO *arvore){
    NODO *valor = arvore;
    if(arvore == NULL){
        printf("\nArvore vazia!\n\n");
        return;
    }
    else{
        int num;
        printf("\nDigite um numero: ");
        scanf("%d",&num);
        while(valor != NULL && valor->valor != num){
            if(num<valor->valor){
                valor = valor->esq;
            }
            else{
                valor = valor->dir;
            }
        }
        if(valor == NULL){
            printf("\nValor nao encontrado!\n\n");
            return;
        }
    printf("\nValor %d encontrado na arvore!\n\n", valor->valor);
    return;
    }
}

int main()
{
    NODO *arvore = NULL;
    unsigned int op;
    while(1){
        printf("Menu:\n\n1- Inserir na arvore\n2- Excluir na arvore\n3- Buscar na arvore\n0- Sair\n\nOpcao: ");
        scanf("%d",&op);
        switch(op){
        case 1:
            arvore = insere(arvore);
            printf("\n");
            break;
        case 2:
            arvore = Excluir(arvore);
            printf("\n");
            break;
        case 3:
            Busca(arvore);
            break;
        case 0:
            printf("\nSaindo...");
            exit(1);
            break;
        default:
            printf("\nOpcao Invalida!\n\n");
        }
    }
    return 0;
}
