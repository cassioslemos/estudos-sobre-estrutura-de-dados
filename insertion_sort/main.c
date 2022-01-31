#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, temp;
    int v[10]={9,4,5,3,0,8,1,7,6,2};
    for(i=1;i<10;i++){
        j=i-1;
        temp=v[i];
        while(j>=0 && temp<v[j]){
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=temp;
    }
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
