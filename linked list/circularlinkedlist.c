#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data; // store value in one box (we have two box in each node)
    struct Node *next; // store address of next node in other box
                       // point to address of next node
};
// ineration at first in circular linked list ,new element became new head also
void linkedlistTraversal(struct Node* head){
   struct Node*ptr=head;
   /* 1st method printf("element is %d\n",ptr->data);
     ptr=ptr->next;// one time push to ptr otherwise loop not start*/  
  do{
    printf("element is %d\n",ptr->data);
     ptr=ptr->next;
   } while(ptr!=head);


    }

    struct Node*insertAtFirst(struct Node*head,int data){
        struct Node * ptr=(struct Node*)malloc(sizeof(struct Node));
        ptr->data=data;
        struct Node *p= head->next;
        while(p->next!=head){
            p=p->next;
        } // finally p point  last that to those ponting to head
  
       p->next=ptr;
       ptr->next=head; // ptr next to prrevious head
       head=ptr; // now ptr become new head
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
    head->data = 4;
    head->next = second;

    second->data = 3;
    second->next = third;

    third->data = 6;
    third->next = fourth;
    fourth->data=1;
    fourth->next=head; // last point head that is circular


    // Code to print or manipulate the linked list can be added here

     head=insertAtFirst(head,80);
     linkedlistTraversal(head);
    return 0;
}

