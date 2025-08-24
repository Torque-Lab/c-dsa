#include<stdio.h>
#include<stdlib.h>



struct stack{
    int size; // max size
    int top;
    int *arr;

};
int isEmpty(struct stack*ptr)
{
if(ptr->top==-1){
    return 1;
}
else{
    return 0;
}

}
    int isFull(struct stack*ptr)
    {
    if (ptr->top==ptr->size-1){
        return 1;
    }else{
        return 0;
    }

    }
   
   void push(struct stack*ptr,int value){
       if(isFull(ptr)){
        printf("stack overflow\n");
       }
       else{
        ptr->top++;
        ptr->arr[ptr->top]=value;
       }

   }

     int pop(struct stack*ptr){
       if(isEmpty(ptr)){
        printf("stack underflow ! cannot pop\n");
        return -1;
       }
       else{
      int value=ptr->arr[ptr->top];
      ptr->top--; // top shifted one below from previous top
      return value;
       }

   }

int peek(struct stack *sp,int i){
    int arrayInd=sp->top-i+1;
    if(arrayInd<0){
        printf("not a valid postion ");
        return -1; // indicate invalid postion
    }
    else{
         return sp->arr[sp->top-i+1];
    }
}
 int stackTop(struct stack *sp)
 {
    return sp->arr[sp->top];
 }
 int stackBottom(struct stack*sp)
 {
    return sp->arr[0];
 }
int main(){

    struct stack *sp=(struct stack *) malloc(sizeof(struct stack)); //store address of struct stack
     sp->size=10;
     sp->top=-1;
     sp->arr=(int *)malloc(sp->size*sizeof(int));
    
     
     printf("stack has been created succesfully\n");

     printf(" before pushing,empty:%d\n",isEmpty(sp));
     printf("not full so :%d\n",isFull(sp));

     push (sp,11);
     push (sp,22);
     push (sp,33);
     push (sp,44);
     push (sp,55);
     push (sp,66);
     push (sp,77);
     push (sp,88);
     push (sp,99);
     push (sp,100);
     push (sp,121);
     
   
     printf("After pushing:%d\n",isEmpty(sp));
     printf("After pushing:%d\n",isFull(sp));
      
    /*for(int j=1;j<sp->top+1;j++)
    {
        printf("The value at postion %d is %d\n",j,peek(sp,j));
    }
*/

    printf("the topmost value of this stack is %d\n",stackTop(sp));
    printf("the bottommost value of this stack is %d\n ",stackBottom(sp));
    return 0;
}