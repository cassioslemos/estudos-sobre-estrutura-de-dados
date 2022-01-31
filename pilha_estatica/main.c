#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct pessoa{
    char nome[50];
}Pessoa;

typedef struct pilha{
    Pessoa pessoas[10];
    int topo;
    int base;
    int limite;
}Pilha;

void Clear (Pilha *pilha1){
    pilha1->topo=0;
    pilha1->base=0;
    pilha1->limite=MAX;
}

int Empty (Pilha *pilha1){
    if(pilha1->topo==0){
        return 1;
    }
    return 0;
}

int Full (Pilha *pilha1){
    if(pilha1->topo==pilha1->limite){
        return 1;
    }
    return 0;
}

void Push (Pilha *pilha1, Pessoa *item, int flag){
    if(Full(pilha1)){
        printf("\nPilha cheia!\n\n");
        return;
    }
    pilha1->pessoas[pilha1->topo] = *item;
    pilha1->topo++;
    if(flag)
        printf("\nPessoa inserida com sucesso!\n\n");
}

void Pop (Pilha *pilha1, Pessoa *item, int op, int flag){
    if(Empty(pilha1)){
        printf("\nA pilha esta vazia!\n\n");
        return;
    }
    if(op==1){
        pilha1->topo--;
        *item = pilha1->pessoas[pilha1->topo];
        if (flag)
            printf("\nPessoa removida com sucesso!\n\n");
    }
    if(op==2){
        int flag1=0;
        Pilha *pilha2;
        Pessoa nomeaux, pessoaaux;
        pilha2 = malloc(sizeof(Pilha));
        if(pilha2==NULL){
            printf("Memoria indisponivel!");
            exit(1);
        }
        Clear(pilha2);
        printf("\nInsira um nome: ");
        getchar();
        fgets(nomeaux.nome, 50, stdin);
        while(pilha1->topo>0 && !flag1){
            Pop(pilha1, &pessoaaux, 1, 0);
            if(strcmp(pessoaaux.nome, nomeaux.nome)==0){
                flag1=1;
            }
            if(!flag1)
                Push(pilha2, &pessoaaux,0);
        }
        while(pilha2->topo>0){
            Pop(pilha2, &pessoaaux, 1, 0);
            Push(pilha1, &pessoaaux, 0);
        }
        if(!flag1)
            printf("\nPessoa nao encontrada!\n\n");
        else
            printf("\nPessoa deletada com sucesso!\n\n");
        free(pilha2);
    }
    if(op==4){
        Pilha *pilha2;
        Pessoa aux;
        pilha2 = malloc(sizeof(Pilha));
        if(pilha2==NULL){
            printf("Memoria indisponivel!");
            exit(1);
        }
        *pilha2 = *pilha1;
        while(pilha2->topo>0){
            Pop(pilha2, &aux, 1, 0);
            printf("\nNome: %s\n\n", aux.nome);
        }
        free(pilha2);
    }
}

int main()
{
    int op;
    Pessoa aux;
    Pilha *pilha1;
    pilha1 = malloc(sizeof(Pilha));
    if(pilha1==NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    Clear(pilha1);
    while(1){
        printf("Escolha uma opcao: \n\n");
        printf("0 - Insere pessoa\n");
        printf("1 - Deleta pessoa do topo\n");
        printf("2 - Deleta pessoa por nome\n");
        printf("3 - Limpa pilha\n");
        printf("4 - Lista as pessoas na tela\n");
        printf("5 - Sair do programa\n\n");
        printf("Opcao: ");
        scanf("%d",&op);
        switch(op){
        case 0:
            printf("\nInsira um nome: ");
            getchar();
            fgets(aux.nome,50, stdin);
            Push(pilha1, &aux, 1);
            break;
        case 1:
            Pop(pilha1, &aux, op, 1);
            break;
        case 2:
            Pop(pilha1, &aux, op, 0);
            break;
        case 3:
            Clear(pilha1);
            printf("\nPilha limpa com sucesso!\n\n");
            break;
        case 4:
            Pop(pilha1, &aux, op, 0);
            break;
        case 5:
            free(pilha1);
            exit(1);
            break;
        default:
            printf("\nOpcao Invalida\n\n");
        }
    }
    return 0;
}
