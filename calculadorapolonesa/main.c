#include <stdio.h>
#include <stdlib.h>

typedef struct pilha{
    int *numeros;
    int *topo;
    int *base;
    int limite;
}Pilha;

void Clear(Pilha *pilha1){
    free(pilha1->numeros);;
    pilha1->numeros = NULL;
    pilha1->topo = NULL;
    pilha1->base = NULL;
    pilha1->limite = 0;
}

int Empty(Pilha *pilha1){
    if(pilha1->limite == 0)
        return 1;
    return 0;
}

void Copiapilha (Pilha *pilha1, int *numeros){
    int *aux = pilha1->numeros, *aux2 = numeros;
    for(int i = pilha1->limite; i > 0; i--){
        aux2[i-1] = aux[i-1];
    }
}

void pop(Pilha *pilha1){
    if(Empty(pilha1)){
        printf("\nPilha vazia!\n\n");
    }
    pilha1->limite--;
    if(pilha1->limite == 0){
        Clear(pilha1);
        return;
    }
    int *numeros;
    numeros = malloc(pilha1->limite*sizeof(int));
    if(numeros == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    Copiapilha(pilha1, numeros);
    free(pilha1->numeros);
    pilha1->numeros = numeros;
    pilha1->topo = &numeros[pilha1->limite-1];
    pilha1->base = numeros;
}

void soma(Pilha *pilha1){
    if(pilha1->limite<2){
        printf("\nOperandos insuficientes!\n\n");
        return;
    }
    int op1, op2, *aux = pilha1->topo, resultado;
    op2 = *aux;
    pop(pilha1);
    aux = pilha1->topo;
    op1 = *aux;
    pop(pilha1);
    resultado = op1+op2;
    if(pilha1->limite == 0){
        pilha1->numeros = malloc(sizeof(int));
        pilha1->numeros[0] = resultado;
        pilha1->base = pilha1->numeros;
        pilha1->topo = pilha1->numeros;
        pilha1->limite++;
        return;
    }
    int *numeros;
    numeros = malloc(pilha1->limite+1*sizeof(int));
    if(numeros == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    Copiapilha(pilha1, numeros);
    pilha1->limite++;
    pilha1->numeros[pilha1->limite-1] = resultado;
    pilha1->topo = &pilha1->numeros[pilha1->limite-1];
}

void divisao(Pilha *pilha1){
    if(pilha1->limite<2){
        printf("\nOperandos insuficientes!\n\n");
        return;
    }
    int op1, op2, *aux = pilha1->topo, resultado;
    if(*aux == 0){
        printf("\nDivisao por 0 nao e possivel!\n\n");
        return;
    }
    op2 = *aux;
    pop(pilha1);
    aux = pilha1->topo;
    op1 = *aux;
    pop(pilha1);
    resultado = op1/op2;
    if(pilha1->limite == 0){
        pilha1->numeros = malloc(sizeof(int));
        pilha1->numeros[0] = resultado;
        pilha1->base = pilha1->numeros;
        pilha1->topo = pilha1->numeros;
        pilha1->limite++;
        return;
    }
    int *numeros;
    numeros = malloc(pilha1->limite+1*sizeof(int));
    if(numeros == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    Copiapilha(pilha1, numeros);
    pilha1->limite++;
    pilha1->numeros[pilha1->limite-1] = resultado;
    pilha1->topo = &pilha1->numeros[pilha1->limite-1];
}

int main()
{
    Pilha *pilha1;
    int vetor[3]={1,6,2}, *aux;
    pilha1 = malloc(sizeof(Pilha));
    if(pilha1 == NULL){
        printf("Memoria indisponivel!");
        exit(1);
    }
    Clear(pilha1);
    pilha1->base = vetor;
    pilha1->numeros = vetor;
    pilha1->limite = 3;
    pilha1->topo = &vetor[2];
    divisao(pilha1);
    aux = pilha1->topo;
    printf("%d", pilha1->numeros[1]);
    return 0;
}
