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

typedef struct fila{
    Nodo *first;
    Nodo *last;
}Fila;

int Empty(Fila *fila1){
    if(fila1->first == NULL)
        return 1;
    return 0;
}

void* Clear (Fila *fila1){
    Nodo *aux = fila1->first, *aux2;
    while (aux != NULL){
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(fila1);
    return fila1;
}

void* Reset (Fila *fila1){
    if(fila1 != NULL)
        fila1 = Clear(fila1);
    fila1 = malloc(sizeof(Fila));
    if(fila1 == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    fila1->first = NULL;
    fila1->last = NULL;
    return fila1;
}

void* Lerinfo(){
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

void Push (Fila *fila1, Nodo *item, unsigned int flag){
    Nodo *ant, *atual = fila1->first;
    if(fila1->first == NULL){
        fila1->first = item;
        fila1->last = item;
        item->prox = NULL;
        if(flag)
            printf("\nPessoa inserida com sucesso!\n\n");
        return;
    }
    while(atual != NULL){
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = item;
    item->prox = atual;
    fila1->last = item;
    if(flag)
        printf("\nPessoa inserida com sucesso!\n\n");
    return;
}

void Listar(Fila *fila1){
    if(Empty(fila1)){
        printf("\nLista vazia!\n\n");
        return;
    }
    for(Nodo *aux = fila1->first; aux != NULL; aux = aux->prox)
        printf("\nNome: %s\n\n", aux->info.nome);
}

void Pop(Fila *fila1, Nodo *item, unsigned int op, unsigned int flag){
    if(Empty(fila1)){
        printf("\nLista vazia!\n\n");
        return;
    }
    if(op == 1){
        Nodo *aux = fila1->first;
        *item = *aux;
        fila1->first = aux->prox;
        free(aux);
        if(fila1->first == NULL){
            fila1->last = NULL;
        }
        if(flag)
            printf("\nPessoa deletada com sucesso!\n\n");
        return;
    }
    if(op == 2){
        char nome[50];
        int flag1=0;
        Fila *fila2;
        Nodo *aux1, aux2, *aux3;
        fila2 = Reset(NULL);
        printf("\nInforme um nome: ");
        getchar();
        fgets(nome, 50, stdin);
        for(aux1 = fila1->first; aux1 != NULL; aux1 = aux2.prox){
            if(strcmp(nome, aux1->info.nome) == 0){
                Pop(fila1, &aux2, 1, 0);
                flag1 = 1;
                break;
            }
            Pop(fila1, &aux2, 1, 0);
            aux3 = malloc(sizeof(Nodo));
            if(aux3 == NULL){
                printf("Memoria indisponivel!");
                exit(1);
            }
            *aux3 = aux2;
            Push(fila2, aux3, 0);
        }
        if(!flag1)
            printf("\nPessoa nao encontrada!\n\n");
        else
            printf("\nPessoa deletada com sucesso!\n\n");
        for(aux1 = fila1->first; aux1 != NULL; aux1 = aux2.prox){
            Pop(fila1, &aux2, 1, 0);
            aux3 = malloc(sizeof(Nodo));
            if(aux3 == NULL){
                printf("Memoria indisponivel!");
                exit(1);
            }
            *aux3 = aux2;
            Push(fila2, aux3, 0);
        }
        for(aux1 = fila2->first; aux1 != NULL; aux1 = aux2.prox){
            Pop(fila2, &aux2, 1, 0);
            aux3 = malloc(sizeof(Nodo));
            if(aux3 == NULL){
                printf("Memoria indisponivel!");
                exit(1);
            }
            *aux3 = aux2;
            Push(fila1, aux3, 0);
        }
        free(fila2);
        return;
    }
}

int main()
{
    unsigned int op;
    Nodo *aux1, aux2;
    Fila *fila1;
    fila1 = Reset(NULL);
    while(1){
        printf("Escolha uma opcao: \n\n");
        printf("0 - Insere pessoa\n");
        printf("1 - Deleta pessoa do inicio\n");
        printf("2 - Deleta pessoa pelo nome\n");
        printf("3 - Limpa fila\n");
        printf("4 - Lista as pessoas na tela\n");
        printf("5 - Sair do programa\n\n");
        printf("Opcao: ");
        scanf("%d",&op);
        switch(op){
        case 0:
            aux1 = Lerinfo();
            Push(fila1, aux1, 1);
            break;
        case 1:
            Pop(fila1, &aux2, op, 1);
            break;
        case 2:
            Pop(fila1, &aux2, op, 1);
            break;
        case 3:
            Reset(fila1);
            printf("\nFila limpa com sucesso!\n\n");
            break;
        case 4:
            Listar(fila1);
            break;
        case 5:
            Reset(fila1);
            free(fila1);
            exit(1);
            break;
        default:
            printf("\nOpcao Invalida\n\n");
        }
    }
    return 0;
}
