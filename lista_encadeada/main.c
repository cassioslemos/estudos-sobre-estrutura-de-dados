#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[50];
}Pessoa;

typedef struct nodo{
    Pessoa info;
    struct nodo *prox;
}Nodo;

typedef struct lista{
    Nodo *first;
}Lista;

void* Clear (Lista *lista1){
    Nodo *prox, *atual=lista1->first;
    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(lista1);
    return NULL;
}

void* Reset (Lista *lista1){
    if(lista1 != NULL)
        lista1=Clear(lista1);
    lista1 = malloc(sizeof(Lista));
    if(lista1==NULL){
        printf("Memoria Indisponivel!");
        exit(1);
    }
    lista1->first = NULL;
    return lista1;
}

void* Lerinfo (){
    Nodo *aux;
    aux = malloc(sizeof(Nodo));
    if(aux==NULL){
        printf("Memoria Indisponivel!");
        exit(1);
    }
    printf("\nDigite um  nome: ");
    getchar();
    fgets(aux->info.nome, 50, stdin);
    return aux;
}

void Push(Lista *lista1, Nodo *info, unsigned int nindex){
    Nodo *atual, *anterior;
    if(lista1->first == NULL && nindex != 0){
        printf("\nnIndex Invalido!\n\n");
        return;
    }
    if(lista1->first == NULL && nindex == 0){
        info->prox = NULL;
        lista1->first = info;
        printf("\nElemento inserido com sucesso!\n\n");
        return;
    }
    if(nindex == 0){
        info->prox = lista1->first;
        lista1->first = info;
        printf("\nElemento inserido com sucesso!\n\n");
        return;
    }
    atual = lista1->first;
    for(int i=0; i<nindex && atual != NULL; i++){
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = info;
    info->prox = atual;
    printf("\nElemento inserido com sucesso!\n\n");
}

void Listar(Lista *lista1){
    Nodo *aux=lista1->first;
    if(aux==NULL)
        printf("\nLista vazia!\n\n");
    while(aux!=NULL){
        printf("\nNome: %s\n\n", aux->info.nome);
        aux = aux->prox;
    }
}

void Pop(Lista *lista1, int op){
    if(lista1->first == NULL){
        printf("\nLista vazia!\n\n");
        return;
    }
    if(op == 1){
        Nodo *anterior, *atual=lista1->first;
        unsigned int nindex;
        printf("\nDigite um index: ");
        scanf("%d", &nindex);
        if(nindex==0){
            lista1->first = atual->prox;
            free(atual);
            printf("\nElemento removido com sucesso!\n\n");
            return;
        }
        for(int i=0; i!=nindex && atual!=NULL; i++){
            anterior = atual;
            atual = atual->prox;
        }
        if(atual == NULL){
            printf("\nIndex invalido!\n\n");
            return;
        }
        anterior->prox = atual->prox;
        free(atual);
        printf("\nElemento removido com sucesso!\n\n");
        return;
    }
    if(op==2){
        int i;
        Nodo *anterior, *atual=lista1->first;
        char nomeaux[50];
        printf("\nInforme um nome: ");
        getchar();
        fgets(nomeaux, 50, stdin);
        for(i=0; atual!=NULL && strcmp(nomeaux, atual->info.nome)!=0; i++){
            anterior = atual;
            atual = atual->prox;
        }
        if(atual == NULL){
            printf("\nNome nao encontrado!\n\n");
            return;
        }
        if(i==0){
            anterior = lista1->first;
            lista1->first = lista1->first->prox;
            free(anterior);
            printf("\nElemento removido com sucesso!\n\n");
            return;
        }
        anterior->prox = atual->prox;
        free(atual);
        printf("\nElemento removido com sucesso!\n\n");
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
                aux = Lerinfo();
                printf("Digite um index: ");
                scanf("%d", &nindex);
                Push(lista1, aux, nindex);
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
