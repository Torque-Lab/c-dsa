#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data; // store value in one box (we have two box in each node)
    struct Node *next; // store address of next node in other box
                       // point to address of next node
};
void linkedlistTraversal(struct Node* ptr){
    while(ptr!=NULL){
    printf("element:%d\n",ptr->data);
    ptr=ptr->next;
    }
}
struct Node * insertAtFirst(struct Node *first,int data){
    struct Node * newboy=(struct Node*)malloc(sizeof(struct Node));
    newboy->next=first;  // this function return new head and i named head as first so it give new first
    newboy->data=data;
}
int main() {
    struct Node *first;
    struct Node *second;
    struct Node *third;
     struct Node *fourth;

    // allocate memory in heap
    first = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth=(struct Node*)malloc(sizeof(struct Node));
    // Assigning data and linking nodes
    first->data = 7;
    first->next = second;

    second->data = 11;
    second->next = third;

    third->data = 66;
    third->next = fourth;
    fourth->data=78;
    fourth->next=NULL;


    // Code to print or manipulate the linked list can be added here
     linkedlistTraversal(first);
     first=insertAtFirst(first,99);
     linkedlistTraversal(first); // traversal by new first
    return 0;
}

