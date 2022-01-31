#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome [50];
}Pessoa;

typedef struct pilha{
    Pessoa *pessoas;
    Pessoa *topo;
    Pessoa *base;
    int limite;
}Pilha;

void Clear(Pilha *pilha1){
    pilha1->base = NULL;
    pilha1->topo = NULL;
    pilha1->pessoas = NULL;
    pilha1->limite = 0;
}

int Empty (Pilha *pilha1){
    if(pilha1->limite==0)
        return 1;
    return 0;
}

void CopiaPilha(Pilha *pilha1, Pessoa *pessoas){
    for(int i=0; i<pilha1->limite; i++){
        pessoas[i] = pilha1->pessoas[i];
    }
}

void* Push (Pilha *pilha1, Pessoa *item, int flag){
    Pessoa *pessoas;
    pessoas = malloc((pilha1->limite+1)*sizeof(Pessoa));
    if(pessoas==NULL){
        printf("Memoria indisponivel");
        exit(1);
    }
    if(pilha1->pessoas!=NULL){
        CopiaPilha(pilha1, pessoas);
        free(pilha1->pessoas);
    }
    pilha1->limite++;
    pilha1->pessoas = pessoas;
    pilha1->pessoas[pilha1->limite-1] = *item;
    pilha1->topo = &pilha1->pessoas[pilha1->limite-1];
    pilha1->base = pilha1->pessoas;
    if(flag)
        printf("\nPessoa inserida com sucesso!\n\n");
    return pilha1;
}

void* Pop(Pilha *pilha1, Pessoa *item, int op, int flag){
    if(Empty(pilha1)){
        printf("\nA Pilha esta vazia!\n\n");
        return pilha1;
    }
    if(op==1){
        pilha1->limite--;
        Pessoa *aux = pilha1->topo;
        *item = *aux;
        if(pilha1->limite==0){
            free(pilha1->pessoas);
            Clear(pilha1);
            if(flag)
                printf("\nPessoa deletada com sucesso!\n\n");
            return pilha1;
        }
        Pessoa *pessoas;
        pessoas = malloc(pilha1->limite*sizeof(Pessoa));
        if(pessoas==NULL){
            printf("Memoria indisponivel");
            exit(1);
        }
        CopiaPilha(pilha1, pessoas);
        free(pilha1->pessoas);
        pilha1->pessoas = pessoas;
        pilha1->topo = &pilha1->pessoas[pilha1->limite-1];
        pilha1->base = pessoas;
        if(flag)
            printf("\nPessoa deletada com sucesso!\n\n");
        return pilha1;
    }
    if (op==2){
        Pessoa pessoaaux;
        Pilha *pilha2;
        pilha2 = malloc(sizeof(Pilha));
        if(pilha2==NULL){
            printf("Memoria indisponivel");
            exit(1);
        }
        Clear(pilha2);
        char nomeaux[50], flag1=0;
        printf("\nInsira um nome: ");
        getchar();
        fgets(nomeaux,50,stdin);
        while (pilha1->limite>0 && flag1==0){
            Pop(pilha1, &pessoaaux, 1, 0);
            if(strcmp(pessoaaux.nome, nomeaux)==0){
                flag1=1;
            }
            else{
                Push(pilha2, &pessoaaux, 0);
            }
        }
        while (pilha2->limite>0){
            Pop(pilha2, &pessoaaux, 1, 0);
            Push(pilha1, &pessoaaux, 0);
        }
        free(pilha2->pessoas);
        free(pilha2);
        if(flag1){
            printf("\nPessoa deletada com sucesso!\n\n");
        }
        else{
            printf("\nPessoa nao encontrada!\n\n");
        }
        return pilha1;
    }
    if (op==4){
        Pilha *pilha2;
        Pessoa *pessoas2, aux;
        pilha2 = malloc(sizeof(Pilha));
        pessoas2 = malloc(pilha1->limite*sizeof(Pessoa));
        if(pessoas2==NULL){
            printf("Memoria indisponivel");
            exit(1);
        }
        if(pilha2==NULL){
            printf("Memoria indisponivel");
            exit(1);
        }
        pilha2->limite=pilha1->limite;
        CopiaPilha(pilha1, pessoas2);
        pilha2->pessoas=pessoas2;
        pilha2->base=pessoas2;
        pilha2->topo=&pilha2->pessoas[pilha2->limite-1];
        while (pilha2->limite!=0){
            Pop(pilha2, &aux, 1, 0);
            printf("\nNome: %s\n\n", aux.nome);
        }
        free(pessoas2);
        Clear(pilha2);
        free(pilha2);
        return pilha1;
    }
}

int main()
{
    int op;
    Pessoa aux;
    Pilha *pilha1;
    pilha1 = malloc(sizeof(Pilha));
    if(pilha1==NULL){
        printf("Memoria indisponivel");
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
            fgets(aux.nome, 50, stdin);
            pilha1 = Push(pilha1, &aux, 1);
            break;
        case 1:
            pilha1 = Pop(pilha1, &aux, op, 1);
            break;
        case 2:
            pilha1 = Pop(pilha1, &aux, op, 0);
            break;
        case 3:
            free(pilha1->pessoas);
            Clear(pilha1);
            printf("\nPilha limpa com sucesso!\n\n");
            break;
        case 4:
            pilha1 = Pop(pilha1, NULL, op, 0);
            break;
        case 5:
            free(pilha1->pessoas);
            free(pilha1);
            exit(1);
            break;
        default:
            printf("\nOpcao Invalida\n\n");
        }
    }
    return 0;
}
