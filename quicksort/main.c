#include <stdio.h>
#include <stdlib.h>

int particiona (int *v, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq=inicio;
    dir=fim;
    pivo=v[inicio];
    while (esq<dir){
        while(v[esq]<=pivo){
            esq++;
        }
        while(v[dir]>pivo){
            dir--;
        }
        if(esq<dir){
            aux=v[esq];
            v[esq]=v[dir];
            v[dir]=aux;
        }
    }
    v[inicio]=v[dir];
    v[dir]=pivo;
    return dir;
}

void quickSort(int *v, int inicio, int fim){
    int pivo;
    if(fim>inicio){
        pivo = particiona(v,inicio,fim);
        quickSort(v,inicio,pivo-1);
        quickSort(v,pivo+1,fim);
    }
}

int main()
{
    int v[10]={9,4,5,3,0,8,1,7,6,2};
    quickSort(v,0,9);
    for(int i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
