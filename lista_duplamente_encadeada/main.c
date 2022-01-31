#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[50];
}Pessoa;

typedef struct nodo{
    Pessoa info;
    struct nodo *ant;
    struct nodo *prox;
}Nodo;

typedef struct lista{
    unsigned int nCount;
    Nodo *last;
    Nodo *first;
}Lista;

void* Clear (Lista *lista1){
    Nodo *atual=lista1->first, *prox;
    for (int i=0; i<lista1->nCount; i++){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista1);
    return NULL;
}

void* Reset (Lista *lista1){
    if(lista1 != NULL)
        lista1 = Clear(lista1);
    lista1 = malloc(sizeof(Lista));
    if(lista1 == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    lista1->nCount = 0;
    lista1->first = NULL;
    lista1->last = NULL;
    return lista1;
}

void* lerInfo(){
    Nodo *aux;
    aux = malloc(sizeof(Nodo));
    if(aux == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    printf("\nDigite um nome: ");
    getchar();
    fgets(aux->info.nome, 50, stdin);
    return aux;
}

void* Push(Lista *lista1, Nodo *info, unsigned int nIndex){
    Nodo *ant, *atual = lista1->first;
    if(lista1->first == NULL && nIndex != 0){
        printf("\nIndex invalido\n\n");
        return lista1;
    }
    if(lista1->first == NULL && nIndex == 0){
        info->ant = NULL;
        info->prox = NULL;
        lista1->first = info;
        lista1->last = info;
        lista1->nCount++;
        printf("\nPessoa inserida com sucesso!\n\n");
        return lista1;
    }
    if(nIndex == 0){
        info->ant = NULL;
        info->prox = atual;
        lista1->first = info;
        atual->ant = info;
        lista1->nCount++;
        printf("\nPessoa inserida com sucesso!\n\n");
        return lista1;
    }
    for(int i=0; i != nIndex && i < lista1->nCount; i++){
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = info;
    info->ant = ant;
    info->prox = atual;
    if(atual != NULL)
        atual->ant = info;
    else
        lista1->last = info;
    lista1->nCount++;
    printf("\nElemento inserido com sucesso!\n\n");
    return lista1;
}

void Listar (Lista *lista1){
    Nodo *aux=lista1->first;
    if(lista1->nCount == 0){
        printf("\n Lista vazia!\n\n");
        return;
    }
    for(int i = 0; i < lista1->nCount; i++){
        printf("\nNome: %s\n\n", aux->info.nome);
        aux = aux->prox;
    }
}

void Ver (Lista *lista1){
    Nodo *aux=lista1->first;
    int nindex;
    scanf("%d",&nindex);
    if(lista1->nCount == 0){
        printf("\n Lista vazia!\n\n");
        return;
    }
    for(int i = 0; i != nindex; i++){
        aux = aux->prox;
    }
    printf("Nome: %s Anterior: %s Proximo: %s\n", aux->info.nome, aux->ant->info.nome, aux->prox->info.nome);
}

void Pop (Lista *lista1, int op){
    if(lista1->first == NULL){
        printf("\n Lista vazia!\n\n");
        return;
    }
    if(op == 1){
        Nodo *ant, *atual = lista1->first;
        unsigned int nindex;
        printf("\nInforme o index: ");
        scanf("%d", &nindex);
        if(nindex >= lista1->nCount){
            printf("\nIndex invalido!\n\n");
            return;
        }
        if(lista1->nCount == 1){
            Reset(lista1);
            printf("\nElemento removido!\n\n");
            return;
        }
        if(nindex == 0){
            lista1->first = atual->prox;
            if(lista1->first->prox == NULL)
                lista1->last = atual->prox;
            atual->prox->ant = atual->ant;
            free(atual);
            lista1->nCount--;
            printf("\nElemento removido!\n\n");
            return;
        }
        for (int i = 0; i != nindex; i++){
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = atual->prox;
        if(atual->prox != NULL)
            atual->prox->ant = ant;
        else
            lista1->last = ant;
        free(atual);
        lista1->nCount--;
        printf("\nElemento removido!\n\n");
        return;
    }
    if(op == 2){
        Nodo *ant, *atual = lista1->first;
        int flag = 0, i;
        char nome[50];
        printf("\nInforme um nome: ");
        getchar();
        fgets(nome, 50, stdin);
        for(i=0; i < lista1->nCount; i++){
            if(strcmp(nome, atual->info.nome) == 0){
                flag = 1;
                break;
            }
            ant = atual;
            atual = atual->prox;
        }
        if(!flag){
            printf("\nNome nao encontrado!\n\n");
            return;
        }
        if(lista1->nCount == 1){
            Reset(lista1);
            printf("\nElemento removido!\n\n");
            return;
        }
        if(i == 0){
            lista1->first = atual->prox;
            if(lista1->first->prox == NULL)
                lista1->last = atual->prox;
            lista1->first->ant = NULL;
            free(atual);
            lista1->nCount--;
            printf("\nElemento removido!\n\n");
            return;
        }
        ant->prox = atual->prox;
        if(atual->prox == NULL)
            lista1->last = ant;
        else
            atual->prox->ant = ant;
        free(atual);
        lista1->nCount--;
        printf("\nElemento removido!\n\n");
            return;
    }
}

int main()
{
    Lista *lista1;
    Nodo *aux;
    int op,nindex;
    lista1 = Reset(NULL);
    while (1){
        printf("Escolha uma opcao:\n\n");
        printf("0 - Insere elemento\n");
        printf("1 - Exclui elemento por indice\n");
        printf("2 - Exclui elemento por nome\n");
        printf("3 - Limpa lista\n");
        printf("4 - Listar elementos\n");
        printf("5 - Sair do programa\n\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch(op){
            case 0:
                aux = lerInfo();
                printf("Informe o index: ");
                scanf("%d", &nindex);
                lista1 = Push(lista1, aux, nindex);
                break;
            case 1:
                Pop(lista1, op);
                break;
            case 2:
                Pop(lista1, op);
                break;
            case 3:
                lista1 = Reset(lista1);
                printf("\nLista Limpa!\n\n");
                break;
            case 4:
                Listar(lista1);
                break;
            case 5:
                Reset(lista1);
                free(lista1);
                exit(1);
                break;
            default:
                printf("\nOpcao Invalida!\n\n");
        }
    }
    return 0;
}
