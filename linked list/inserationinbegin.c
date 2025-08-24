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
struct Node * insertAtFirst(struct Node *head,int data){
    struct Node * newboy=(struct Node*)malloc(sizeof(struct Node));
    newboy->next=head;  // this function return new head 
    newboy->data=data; 
}
int main() {
    struct Node *head;
    struct Node *second;
    struct Node *third;
     struct Node *fourth;

    // allocate memory in heap
    head= (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth=(struct Node*)malloc(sizeof(struct Node));
    // Assigning data and linking nodes
    head->data = 7;
    head->next = second;

    second->data = 11;
    second->next = third;

    third->data = 66;
    third->next = fourth;
    fourth->data=78;
    fourth->next=NULL;


    // Code to print or manipulate the linked list can be added here
     linkedlistTraversal(head);
     head=insertAtFirst(head,99);
     linkedlistTraversal(head); // traversal by new first
    return 0;
}

