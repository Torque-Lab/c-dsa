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
 
 // case-1 deleting first element from linked list
 struct Node * deleteFirst(struct Node * head){
    struct Node * ptr=head;
    head=head->next;
    free(ptr);
    return head; // return new head which shifted to next node
 }
    // case-2 deleting the element at given index from the linked list
 /*struct Node * deleteAtIndex(struct Node * head,int index){
    struct Node * p=head;
    struct Node * q=head->next; // q goes to upto that node which has next of p
   for(int i=0;i<index-1;i++)   // example p goes to 5 then q goes to 6 node
   {
    p = p->next;
    q = q->next;
   }
  p->next=q->next;
  free(q);
  return (head);
 }
 */
 
 // case-3 deleting last node
 struct Node * deleteAtLast(struct Node * head){
    struct Node * p=head;
    struct Node * q=head->next;

    while(q->next !=NULL)
    {
        p=p->next; // p go till one before of q
        // p 6 tak jayga to q 7 tak
        q=q->next; // q ko last node tak le gaye
    }
    p->next=NULL; // p ko null kar diye
    free(q); // finally q ko free kar diye
    return head;
 }
 // delete node with given value

 struct Node * deleteAtGiven(struct Node * head,int value){
    struct Node * p=head;
    struct Node * q=head->next; 
   while(q->data!=value && q->next!=NULL) // tab tak jana jab tak q=data and NUll na mil jaye
   {
    p = p->next;
    q = q->next;
   }
   if (q->data==value){
    p->next=q->next;
    free(q);
    
    }
    else
    printf("Given data not found in linkedlist\t");
 
   
  return (head);
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

    third->data = 8;
    third->next = fourth;
    fourth->data=1;
    fourth->next=NULL;

    printf("Linked list before deletion:\n");
    linkedlistTraversal(head);

    // head=deleteFirst(head); // for deleting first element in linked list
     // head=deleteAtIndex(head,2);
     //head=deleteAtLast(head);
     head=deleteAtGiven(head,33);
    printf("Linked list after deletion:\n");
    linkedlistTraversal(head);
    return 0;

}
