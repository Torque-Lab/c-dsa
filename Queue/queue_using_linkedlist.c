#include <stdio.h>
#include <stdlib.h>
// global variable
struct Node *f = NULL;
struct Node *r = NULL;

struct Node
{
    int data;
    struct Node *next;
};
void LinkedlistTraversal(struct Node *ptr)
{
    printf("printing the element of this linkedlist queue:\n ");
    while (ptr != NULL)
    {
        printf("element:%d\n", ptr->data);
        ptr = ptr->next;
    }
}

void enqueue( int value)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("Queue is full");
    }
    else
    {
        n->data = value;
        n->next = NULL;

        if (f == NULL)
        {
            f = r = n;
        }
        else
        {
            r->next = n;
            r = n;
        }
    }
}

int dequeue(){
    int value=-1;
    struct Node*ptr=f;
    if(f==NULL){
        printf("queue is empty");
    }
    else{
        f=f->next;
        value=ptr->data;
        free(ptr);
    }
    return value;
}
int main()
{
    printf("Dequeuing element %d \n",dequeue());
    enqueue(33);
    enqueue(66);
    enqueue( 99);
    printf("Dequeuing element %d \n",dequeue());
    LinkedlistTraversal(f);
    return 0;
}