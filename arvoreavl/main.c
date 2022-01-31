#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
}NODO;

int Altura(NODO *raiz){
    int iesq, idir;
    if(raiz == NULL)
        return 0;
    iesq = Altura(raiz->esq);
    idir = Altura (raiz->dir);
    if(iesq > idir)
        return iesq+1;
    else
        return idir+1;
}

int FB (NODO *arvore){
    if(arvore == NULL)
        return 0;
    return Altura(arvore->esq) - Altura(arvore->dir);
}

void* Rotacaodir (NODO *arvore){
    NODO *aux;
    aux = arvore->esq->dir;
    arvore->esq->dir = arvore;
    arvore = arvore->esq;
    arvore->dir->esq = aux;
    return arvore;
}

void* Rotacaoesq (NODO *arvore){
    NODO *aux;
    aux = arvore->dir->esq;
    arvore->dir->esq = arvore;
    arvore = arvore->dir;
    arvore->esq->dir = aux;
    return arvore;
}

void* Rotacaoduplaesq(NODO *arvore){
    arvore->dir = Rotacaodir(arvore->dir);
    arvore = Rotacaoesq(arvore);
    return arvore;
}

void* Rotacaodupladir(NODO *arvore){
    arvore->esq = Rotacaoesq(arvore->esq);
    arvore = Rotacaodir(arvore);
    return arvore;
}

void* Inserir (NODO *arvore){
    int num;
    printf("\nDigite um numero: ");
    scanf("%d", &num);
    if(arvore == NULL){
        arvore = malloc(sizeof(NODO));
        if(arvore == NULL){
            printf("Memoria indisponivel!");
            exit(1);
        }
        arvore->valor = num;
        arvore->dir = NULL;
        arvore->esq = NULL;
        return arvore;
    }
    else{
        NODO *pai, *filho;
        pai = arvore;
        filho = arvore;
        while(filho != NULL){
            pai = filho;
            if(num < filho->valor)
                filho = filho->esq;
            else
                filho = filho->dir;
        }
        filho = malloc(sizeof(NODO));
        if(filho == NULL){
            printf("Memoria indisponivel!");
            exit(1);
        }
        if(num<pai->valor)
            pai->esq = filho;
        else
            pai->dir = filho;
        filho->valor = num;
        filho->dir = NULL;
        filho->esq = NULL;
        if(FB(arvore)>1 && FB(arvore->esq)>=0)
            arvore = Rotacaodir(arvore);
        if(FB(arvore)<-1 && FB(arvore->dir)<=0)
            arvore = Rotacaoesq(arvore);
        if(FB(arvore)>1 && FB(arvore->esq)<0)
            arvore = Rotacaodupladir(arvore);
        if(FB(arvore)<-1 && FB(arvore->dir)>0)
            arvore = Rotacaoduplaesq(arvore);
        return arvore;
    }
}

void* Remover(NODO *arvore){
    if (arvore == NULL){
        printf("\nArvore vazia!\n");
        return arvore;
    }
    else{
        int num;
        NODO *pai, *filho, *aux;
        printf("\nDigite um numero: ");
        scanf("%d", &num);
        if(arvore->valor == num && arvore->esq == NULL && arvore->dir == NULL){
            free(arvore);
            return NULL;
        }
        else{
            filho = arvore;
            pai = NULL;
            while(filho != NULL && filho->valor != num){
                pai = filho;
                if(num<filho->valor){
                    filho = filho->esq;
                }
                else{
                    filho = filho->dir;
                }
            }
            if(filho == NULL){
                printf("\nValor nao encontrado!\n");
                return arvore;
            }
            if(filho->esq == NULL && filho->dir == NULL){
                if(pai->esq != NULL && pai->esq->valor == num)
                    pai->esq = NULL;
                else
                    pai->dir = NULL;
                free(filho);
                if(FB(arvore)>1 && FB(arvore->esq)>=0)
                    arvore = Rotacaodir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)<=0)
                    arvore = Rotacaoesq(arvore);
                if(FB(arvore)>1 && FB(arvore->esq)<0)
                    arvore = Rotacaodupladir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)>0)
                    arvore = Rotacaoduplaesq(arvore);
                return arvore;
            }
            if(filho->esq == NULL || filho->dir == NULL){
                if(pai != NULL){
                    if(pai->esq->valor == num)
                        if(filho->esq != NULL)
                            pai->esq = filho->esq;
                        else
                            pai->esq = filho->dir;
                    else
                        if(filho->esq != NULL)
                            pai->dir = filho->esq;
                        else
                            pai->dir = filho->dir;
                }
                else
                    arvore = filho->dir;
                free(filho);
                if(FB(arvore)>1 && FB(arvore->esq)>=0)
                    arvore = Rotacaodir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)<=0)
                    arvore = Rotacaoesq(arvore);
                if(FB(arvore)>1 && FB(arvore->esq)<0)
                    arvore = Rotacaodupladir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)>0)
                    arvore = Rotacaoduplaesq(arvore);
                return arvore;
            }
            else{
                pai = filho->esq;
                aux = NULL;
                while(pai->dir != NULL){
                    aux = pai;
                    pai = pai->dir;
                }
                if(aux != NULL)
                    aux->dir = NULL;
                else
                    filho->esq = NULL;
                filho->valor = pai->valor;
                free(pai);
                if(FB(arvore)>1 && FB(arvore->esq)>=0)
                    arvore = Rotacaodir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)<=0)
                    arvore = Rotacaoesq(arvore);
                if(FB(arvore)>1 && FB(arvore->esq)<0)
                    arvore = Rotacaodupladir(arvore);
                if(FB(arvore)<-1 && FB(arvore->dir)>0)
                    arvore = Rotacaoduplaesq(arvore);
                return arvore;
            }
        }
    }
}

void Buscar (NODO *arvore){
    if(arvore == NULL){
        printf("\nArvore vazia!\n\n");
        return;
    }
    else{
        NODO *no = arvore;
        int num;
        printf("\nDigite um numero: ");
        scanf("%d", &num);
        while(no != NULL && no->valor != num){
            if(num < no->valor)
                no = no->esq;
            else
                no = no->dir;
        }
        if(no == NULL){
            printf("\nValor nao encontrado!\n\n");
            return;
        }
        else{
            printf("\nValor %d encontrado na arvore!\n\n", no->valor);
            return;
        }
    }
}

int main()
{
    int op;
    NODO *arvore = NULL;
    while(1){
        printf("Menu: \n\n1- Inserir na arvore\n2- Excluir na arvore\n3- Buscar na arvore\n4- Testes\n0- Sair do programa\n\nOpcao: ");
        scanf("%d",&op);
        switch(op){
        case 0:
            printf("\nSaindo...");
            exit(1);
            break;
        case 1:
            arvore = Inserir(arvore);
            printf("\n");
            break;
        case 2:
            arvore = Remover(arvore);
            printf("\n");
            break;
        case 3:
            Buscar(arvore);
            break;
        case 4:
            printf("\n%d\n\n",arvore->esq->valor);
            break;
        default:
            printf("\nOpcao invalida!\n\n");
        }
    }
    return 0;
}
