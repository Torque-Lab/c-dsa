
#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node * next;
};
struct Node*top=NULL; // we made top as global variable

void linkedlist_traversal(struct Node *ptr){
    while(ptr !=NULL)
    {
     printf("element:%d\n",ptr->data);
     ptr=ptr->next;
    }
}
int isEmpty(struct Node*top)
{
  if(top==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

int isFull(struct Node*top)
{
  struct Node*m=(struct Node*)malloc (sizeof(struct Node));
  if(m==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

struct Node* push(struct Node*top,int x)
{
    if(isFull(top)){
     printf("stack overflow\n");
       return top;
    }
    else{
         struct Node* n=(struct Node*)malloc (sizeof(struct Node));
       n->data= x;
       n->next= top;
        top=n;
      return top; // this return new top

    }
}
int pop(struct Node*tp){
  if(isEmpty(tp)){
    printf("stack under flow\n");

  }else{
     struct Node*n=tp;
     top=tp->next;
     int x=n->data;
     free(n);
     return x;
  }
}
// peek give value at a postion
int peek(int position){
  struct Node *ptr=top;
  for (int i=0;(i<position-1 && ptr!=NULL);i++){
    ptr=ptr->next;
  }
  if (ptr!=NULL){
    return ptr->data;
  }
  else {
    return -1; // indicate null or something encounter
  }

}
int main(){
    top=push(top,66);
    top=push(top,77);
    top=push(top,88);
    top=push(top,99);
    int element=pop(top);
    printf("poped element is %d\n",element);
    linkedlist_traversal(top);

    for(int i=1;i<=7;i++){
        printf("value at postion 1%d is:%d\n",i,peek(i));
    }
    return 0;

}