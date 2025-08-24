#include<stdio.h>
int linearsearch(int arr[],int size,int element){
    for(int i=0;i<size;i++)
    {
        if(arr[i]==element){
            return i;// show we found
        }
        else return -1;// show we not found element
    }
}
int main (){
    int arr[]={1,2,2,3,45,56,45,565,43,};
    int size = sizeof(arr)/sizeof(int);
    int element=100;
    int search_index=linearsearch(arr,size,100);
    printf("the element found at index %d\n",search_index,element);
    return 0;
} 