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
// case-1
struct Node * insertAtFirst(struct Node *head,int data){
    struct Node * newboy=(struct Node*)malloc(sizeof(struct Node));
    newboy->next=head;  // this function return new head 
    newboy->data=data; 
    return newboy;
} // case-2
/*struct Node *insertBetween(struct Node *prevNode, int data){
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.");
        return NULL;
    }
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data; // data for new node
    newNode->next = prevNode->next; // making next of new node same as previous node next
    prevNode->next = newNode; // previous node now point to new node
    return newNode;   
    }  */      // this way a node is inseretd between two earilier node
    //case-3
struct NOde *insertbetweenIndex(struct Node*head,int data,int index){
    struct Node *ptr=(struct Node*)malloc(sizeof(struct Node));
    struct Node *p =head;
    int i=0;

    while(i!=index-1) /*struct Node *p = head;: This line declares a pointer p of type struct Node* and initializes it with the address of the head node of the linked list. Essentially, p now points to the beginning of the linked list, which is the head node.
int i = 0;: This line initializes a counter variable i to 0. This variable will be used to keep track of the current position while traversing the linked list.
while (i != index - 1) { p = p->next; i++; }: This is a while loop that traverses the linked list until it reaches the node just before the desired insertion point (at index index - 1). Here's how it works:
i != index - 1: This condition checks if the current position i is not equal to the index just before the desired insertion point. If it's not, the loop continues.
p = p->next: Inside the loop, p is updated to point to the next node in the linked list. This effectively moves p to the next node, allowing traversal through the list.
i++: After moving to the next node, the counter i is incremented to keep track of the current position.*/
    {
        p=p->next;
        i++;

    }
    ptr->data=data; // ptr is new node
    ptr->next=p->next;
    p->next =ptr;
    return head;
}
// case-4
struct Node * inserationAtEnd (struct Node *head,int data){
  struct Node *ptr=(struct Node*)malloc(sizeof(struct Node));
  ptr->data=data;
  struct Node *p =head;
  while (p->next!=NULL){
    p=p->next;
  }
  p->next=ptr;
  ptr->next=NULL;
  return head;  


} 
// other variety of case-2
struct Node * insertAfterNode (struct Node *head,struct Node *prevNode,int data){
  struct Node *ptr=(struct Node*)malloc(sizeof(struct Node));
  ptr->data=data;
  ptr->next=prevNode->next;
  prevNode->next=ptr;

  return head;  


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
    printf("Linked list before inseration\n"
    );

     linkedlistTraversal(head);
     head=insertbetweenIndex(head,99,1); // this will not work for index zero
     //insertBetween(second,101);
     head=insertAtFirst(head,333);
     head=inserationAtEnd(head,108);
     head=insertAfterNode(head,second,33);
     printf("\n Linked list After inseration\n");

     linkedlistTraversal(head); // traversal by new first
    return 0;
}

