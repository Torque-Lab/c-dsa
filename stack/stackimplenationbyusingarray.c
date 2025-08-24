#include<stdio.h>
#include<stdlib.h>
struct stack{
    int size;
    int top;
    int*arr;

};

int isEmpty(struct stack *ptr){

    if(ptr->top==-1){
        return 1; // indicate stack is empty
    }
    else{
        return 0;
    }
}
int isFull(struct stack*ptr){

    if(ptr->top==ptr->size-1){ // full when top is equal to size-1
        return 1; // indicate stack is full
    }
    else{
        return 0;
    }
}

int main(){
   /*struct stack s;
   s.size=80;
   s.top=-1; // -1 indicate array is vacant
   s.arr=(int *)malloc(s.size* sizeof(int));*/
   // both are valid
   struct stack *s;
   s->size=80;
   s->top=-1; // -1 indicate array is vacant
   s->arr=(int *)malloc(s->size* sizeof(int));
   // pushing element
   s->arr[0]=8;
   s->top++;

   // check stack full or empty
     if(isEmpty(s)){
        printf("the stack is empty");

     }
     else{
        printf("the stack is not empty");
     }
    return 0;

}