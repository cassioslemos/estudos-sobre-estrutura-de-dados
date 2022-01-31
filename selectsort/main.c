#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, k, temp, aux, flag=0;
    int v[10]={9,4,5,3,0,8,1,7,6,2};
    for(i=0;i<10;i++){
        temp=v[i];
        k=v[i];
        for(j=i+1;j<10;j++){
            if(k>v[j]){
                k=v[j];
                aux=j;
                flag=1;
            }
        }
    v[i]=k;
    if(flag==1)
    v[aux]=temp;
    flag=0;
    }
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
