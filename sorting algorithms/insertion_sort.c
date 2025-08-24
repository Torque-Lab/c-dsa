#include<stdio.h>
#include<stdlib.h>

void printArray(int *A,int n){

   for (int i=0;i<n;i++){

    printf("%d ",A[i]);
   }
   printf("\n");
}
void insertionSort(int*A,int n){
    int key,j;
    // Loop for to do pass
  for(int i=0;i<=n-1;i++){
    // Loop for each and every pass to compare
     key=A[i];
     j=i-1;
     while(j>=0 && A[j]>key){ // j>=0 to avoid -1
        A[j+1]=A[j];
        j--;  // decrese j after each itration 
     }
     // for one value of i ,while loop run for all possible value of j then finallly A[j+1]=key;
   A[j+1]=key;
  }

}
int main(){
 //index: -1 0  1  2  3 4  5
 //          12 54 65 7 23 5
    int A[]={12,54,65,7,23,9};
     int n=6;
      printArray(A,n);
     insertionSort(A,n);
     printArray(A,n);
     return 0;
}