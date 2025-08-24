#include <stdio.h>
#include <stdlib.h>
// global variable
struct Node *f = NULL;
struct Node *r = NULL;

struct Node
{
    int data;
    struct Node *next;
    struct Node *previous;
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

void enqueueRear(int value)
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
        n->previous=r;

        if (r == NULL)
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
void enqueueFront(int value)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("Queue is full");
    }
    else
    {
        n->data = value;
        n->next = f;
        n->previous=NULL;

        if (f == NULL)
        {
            f = r = n;
        }
        else
        {
            f->previous = n;
            f = n;
        }
    }
}

int dequeueFront()
{
    int value = -1;
    struct Node *ptr = f;
    if (f == NULL)
    {
        printf("queue is empty");
    }
    else
    {
        f = f->next;
        value = ptr->data;
        free(ptr);
        if(f==NULL){
            r==NULL;
        }
        else{
            f->previous=NULL;
        }
    }
    return value;
}
int dequeueRear()
{
    int value = -1;
    struct Node *ptr = r;
    if (r == NULL)
    {
        printf("queue is empty\n");
    }
    else
    {
        r = r->previous;
        value = ptr->data;
        free(ptr);
        if(r==NULL){
            f=NULL;
        }
        else{
            r->next=NULL;
        }
    }
    return value;
}
int main()
{
    printf("Dequeuing element %d \n", dequeueRear());
    enqueueFront(33);
    enqueueFront(66);
    enqueueFront(99);
    printf("Dequeuing element %d \n", dequeueRear());
    LinkedlistTraversal(f);
    return 0;
}