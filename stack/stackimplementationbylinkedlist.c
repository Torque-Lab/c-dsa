
#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node * next;
};

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
      return top;

    }
}
int pop(struct Node**top){
  if(isEmpty(*top)){
    printf("stack under flow\n");

  }else{
     struct Node*n=*top;
     *top=(*top)->next;
     int x=n->data;
     free(n);
     return x;
  }
}
int main(){
    struct Node*top=NULL;
    top=push(top,66);
    top=push(top,77);
    top=push(top,88);
    top=push(top,99);
    int element=pop(&top);
    printf("poped element is %d\n",element);
    linkedlist_traversal(top);
    return 0;

}