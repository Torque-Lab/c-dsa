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
int main() {
    struct Node *first;
    struct Node *second;
    struct Node *third;

    // allocate memory in heap
    first = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    // Assigning data and linking nodes
    first->data = 7;
    first->next = second;

    second->data = 11;
    second->next = third;

    third->data = 66;
    third->next = NULL;

    // Code to print or manipulate the linked list can be added here
     linkedlistTraversal(first);
    return 0;
}

