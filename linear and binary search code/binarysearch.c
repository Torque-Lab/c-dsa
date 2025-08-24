#include<stdio.h>
int binarysearch(int arr[],int size,int element){
    int low,mid,high;
    low=0;high=size-1;
    // start searching
    // keep searching until low is less than high
    while(low<=high){
     mid=low+ (high-low)/2;  //(low+high)/2;we avoided this to prevent overflow of intger which give cause false result // 5+6/2=5.5 but C by default do greatest intger and we get "5"
    if (arr[mid]==element){
        return mid;
    }
    if (arr[mid]<element){
        low=mid+1; // low = mid se bhi result ayega but we play smartyl 
                   // element mid to ha nahi so hum ak aur incraese kar denge
    }
    else{
        high=mid-1;
    }
}
// search ends
return -1; // element not found
}
int main (){
    // for sorted array by binary search
    int arr[]={1,2,2,3,45,12,23,234,45,4554,455,56,45,565,43,};
    int size = sizeof(arr)/sizeof(int);
    int element=43;
    int search_index=binarysearch(arr,size,element);
    printf("the element found at index %d\n",search_index,element);
    return 0;
} 
