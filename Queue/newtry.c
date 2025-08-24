#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void LinkedlistTraversal(struct Node *ptr) {
    printf("Printing the elements of this linked list queue:\n");
    while (ptr != NULL) {
        printf("Element: %d\n", ptr->data);
        ptr = ptr->next;
    }
}

void enqueue(struct Node **front, struct Node **rear, int value) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Queue is full\n");
    } else {
        n->data = value;
        n->next = NULL;
        if (*front == NULL) {
            *front = *rear = n;
        } else {
            (*rear)->next = n;
            *rear = n;
        }
    }
}

int dequeue(struct Node **front) {
    int value = -1;
    struct Node *ptr = *front;
    if (*front == NULL) {
        printf("Queue is empty\n");
    } else {
        *front = (*front)->next;
        value = ptr->data;
        free(ptr);
    }
    return value;
}

int main() {
    struct Node *front = NULL;
    struct Node *rear = NULL;

    printf("Dequeuing element %d\n", dequeue(&front));
    enqueue(&front, &rear, 33);
    enqueue(&front, &rear, 66);
    enqueue(&front, &rear, 99);
    printf("Dequeuing element %d\n", dequeue(&front));
    LinkedlistTraversal(front);
    return 0;
}
