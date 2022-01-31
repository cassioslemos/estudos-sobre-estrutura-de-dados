#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, temp, flag=0;
    int v[10]={9,4,5,3,0,8,1,7,6,2};
    do{
    flag=0;
    for(i=0, j=1; j<10; i++, j++){
        if(v[i]>v[j]){
            flag=1;
            temp=v[i];
            v[i]=v[j];
            v[j]=temp;
        }
    }
    }while(flag==1);
    for(i=0;i<10;i++)
        printf("%d ",v[i]);
    return 0;
}
