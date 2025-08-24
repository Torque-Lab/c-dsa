#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data; // store value in one box (we have two box in each node)
    struct Node *previous; // point to previous node
    struct Node *next; // store address of next node in other box
                       // point to address of next node
};
// transversal from first to last
void doublylinkedlistTraversalfrom1st_to_last(struct Node* ptr){
    while(ptr!=NULL){
    printf("element:%d\n",ptr->data);
    ptr=ptr->next;
    }
}
// transversal from last to first
void doublylinkedlistTraversal_last_to_1st(struct Node* ptr){
    while(ptr!=NULL){
    printf("element:%d\n",ptr->data);
    ptr=ptr->previous;
    }
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
    head->previous=NULL;
    head->next = second;

    second->data = 11;
    second->previous=head;
    second->next = third;

    third->data = 66;
    third->previous=second;
    third->next = fourth;

    fourth->data=78;
    fourth->previous=third;
    fourth->next=NULL;


    // Code to print or manipulate the linked list can be added here
    printf("elment from strating to last:\n");
     doublylinkedlistTraversalfrom1st_to_last(head);
    
    printf(" last to first:\n");
     doublylinkedlistTraversal_last_to_1st(fourth);
    return 0;
}

