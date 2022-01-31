#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void merge (int *v, int inicio, int meio, int fim){
    int p1, p2, tamanho, *temp, i, j, k;
    int fim1=0, fim2=0;
    tamanho=fim-inicio+1;
    p1=inicio;
    p2=meio+1;
    temp=malloc(tamanho*sizeof(int));
    if(temp!=NULL){
        for (i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(v[p1]<v[p2]){
                    temp[i]=v[p1++];
                }
                else{
                    temp[i]=v[p2++];
                }
                if(p1>meio){
                    fim1=1;
                }
                if(p2>fim){
                    fim2=1;
                }
            }
            else{
                if(!fim1){
                        temp[i]=v[p1++];
                }
                else{
                    temp[i]=v[p2++];
                }
            }
        }
         for (j=0, k=inicio; j<tamanho; j++, k++){
                v[k]=temp[j];
            }
            free(temp);
    }
}

void mergeSort (int *v, int inicio, int fim){
    int meio;
    meio = floor((inicio+fim)/2);
    if(inicio<fim){
        mergeSort(v, inicio, meio);
        mergeSort(v, meio+1, fim);
        merge(v,inicio,meio,fim);
    }
}

int main()
{
    int v[10]={9,4,5,3,0,8,1,7,6,2};
    mergeSort(v,0,9);
    for(int i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
