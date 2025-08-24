#include<stdio.h>
/*//traversal function code
void display(int arr[],int n){
    for(int i=0;i<n;i++)
    {
        printf("%d",arr[i]);

    }
    printf("\n");


}
int main (){
    int arr[40]={1,2,3,4,6,8,9,20};
    display(arr,4);

}*/
void display(int arr[],int n){
    for(int i=0;i<n;i++)
    {
        printf("%d \n",arr[i]);

    }
    printf("\n");

}
int inseration(int arr[],int size,int element,int capacity,int index){
    if(size>=capacity){
        return -1; // indicate inseration not happend
    }
    for(int i=size-1;i>=index;i--)
    {
        arr[i+1]=arr[i];

    }
    arr[index]=element;
    return 1; // for inserted succesfully
}

int main (){
    int arr[100]={7,8,12,27,88};
    int size =5,element=45,index=3;
    display(arr,size);
    inseration(arr,size,element,100,index);
    size+=1;
    display(arr,size);
    return 0;
}