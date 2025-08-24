#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

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

    return 0;
}

