#include<stdio.h>
#include<stdlib.h>


void printArray(int *A,int n){

   for (int i=0;i<n;i++){

    printf("%d ",A[i]);
   }
   printf("\n");
}
void SelectionSort(int*A,int n){
    int indexOfMin;int temp;
printf("Running selection sort algorithm:\n");
for(int i=0;i<=n-1;i++){
 indexOfMin=i;
 for(int j=i+1;j<=n-1;j++){
     if(A[j]<A[indexOfMin]){
        indexOfMin=j;
     }
 }
 // swap A[i] with A[iindexOfMin]
 temp=A[i];
 A[i]=A[indexOfMin];
 A[indexOfMin]=temp;
}

}
int main(){

    int A[]={3,44,5,6,67,8,1};
    int n=7;
    printArray(A,7);
    SelectionSort(A,7);
    printArray(A,7);

return 0;
}