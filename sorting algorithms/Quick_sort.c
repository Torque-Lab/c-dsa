#include<stdio.h>
#include<stdlib.h>


void printArray(int *A,int n){

   for (int i=0;i<n;i++){

    printf("%d ",A[i]);
   }
   printf("\n");
}
 int partition (int A[],int low,int high){
    int pivot=A[low];
    int i=low+1;
    int j=high;
    int temp;
    do{
    while(A[i]<=pivot){
        i++; // i ko aage karte jayo
    }

    while(A[j]>pivot){
        j--; // j ko peeche karte jayo
    }
    if(i<j){
        temp=A[i];
        A[i]=A[j];
        A[j]=temp;


    }
    }
    while(i<j);
     // swap A[low] which is pivot with A[j]
    temp=A[low];
    A[low]=A[j];
    A[j]=temp;
    return j;
 }
void QuickSort(int A[],int low,int high){
    int partitionIndex;// index of pivot after partition
    if(low<high){
    partitionIndex=partition(A,low,high);
    printArray(A,9); // array after each partition
    QuickSort(A,low,partitionIndex-1);// sort left sub array
    QuickSort(A,partitionIndex+1,high); // sort right sub array
    
    }
}

int main(){
    int A[]={3,5,2,13,12,3,2,13,45};
    int n=9;
    /*  // 3,5,2,13,12,3,2,13,45 
    pivot=3,i at 5 & j at 45
        // 3,2,2,13i,12,3j,5,13,45 exchange b/w 
        // 3,2,2,3j,12i,13,5,13,45 exchange b/w then swap pivot with j -->
          This is first call to partition ,it return 3 as postion of j
        */ // now do same thing in left subarray {3,2,2} and right sub  {12,13,..,45}
    printArray(A,n);
    QuickSort(A,0,n-1);
    printArray(A,n);

    return 0;
}