#include <stdio.h>
#include <stdlib.h>

void dualSearch (int[],int, int, int[]);

int main()
{
    int i,size,K;
    int* A;
    int index[2] = {-1,-1};

    //Search key
    printf("Search key:");
    scanf("%d",&K);

    //create an array
    printf("Size:");
    scanf("%d",&size);
    A=(int *)malloc(sizeof(int)*size);
    for(i=0; i<size; i++)
    {
        printf("Input %d: ",i);
        scanf("%d",&A[i]);
    }

    dualSearch(A,size,K,index);

    if(index[0]!=-1)
        printf("%d %d\n",index[0], index[1]);
    else
        printf("Not found");

    free(A);
    return 0;
}

void dualSearch(int A[], int size, int K, int dualIndex[])
{
    int i,j;
   for(i=0;i<size;i++){
       for(j=0;j<size;j++){
           if(A[i]+A[j]==K){
               dualIndex[0] = A[i];
               dualIndex[1] = A[j];
           }
       }
   }

}
