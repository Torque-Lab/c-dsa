#include<stdio.h>



void printArray(int *A,int n){

   for (int i=0;i<n;i++){

    printf("%d ",A[i]);
   }
   printf("\n");
}


/*void bubbleSort(int *A,int n){
       int temp;
    for(int i=0;i<n-1;i++) // outer loop for doing all pass
    {
     for(int j=0;j<n-1-i;j++) // inner loop for doing comparsion in each pass
     {
        if(A[j]>A[j+1]){
            // swapping
            temp=A[j];
            A[j]=A[j+1];
            A[j+1]=temp;
        }
     }
    }
}*/

// making adaptive in case of already sorted
void bubbleSort(int *A,int n){
       int temp;
       int isSorted=0; // indicate not sorted
    for(int i=0;i<n-1;i++) // outer loop for doing all pass
    {
        printf("working on pass number %d\n",i+1);
        isSorted=1; // indicated sorted if not they enter in loop
     for(int j=0;j<n-1-i;j++) // inner loop for doing comparsion in each pass
     {
        if(A[j]>A[j+1]){
            // swapping
            temp=A[j];
            A[j]=A[j+1];
            A[j+1]=temp;
            isSorted=0;
        }
     }
     if(isSorted){
        return;
     }
    }
}
int main (){

    int A[]={12,14,15,16,99,101};
    int n =6;
    printf("Array before sorting:\n");
    printArray(A,n);// print array before sorting

    bubbleSort(A,n);// function to sort array
    printf("Array after sorting:\n");
    printArray(A,n);// print Array after sort
    return 0;
}