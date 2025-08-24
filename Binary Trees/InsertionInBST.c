#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

// function for node creation
struct node *createnode(int data)
{

    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void InOrder(struct node *root)
{

    if (root != NULL)
    {
        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}

void InSertion(struct node*root,int key){
     struct node*prev=NULL;
     while(root!=NULL){
        prev=root;
        if(key==root->data){
            // not do insertion simply return as duplicate not allowed in BST
            printf("Can Not insert %d already in BST",key);
            return;
        }
        else if(key<root->data){
            root=root->left;
        }
        else{
            root=root->right;

        }
        
     }
     struct node*new=createnode(key);
     if(key<prev->data){
        prev->left=new;
     }
     else{
        prev->right=new;
     }
}

int main()
{

    // creating node by function call
    struct node *p = createnode(5);
    struct node *p1 = createnode(3);
    struct node *p2 = createnode(6);
    struct node *p3 = createnode(1);
    struct node *p4 = createnode(4);
    // tree look like
    //       5
    //      / \
    //     3  6
    //    /\
    //   1  4
    // linking node
    p->left = p1;
    p->right = p2;
    p1->left = p3;
    p1->right = p4;

  
    InSertion(p,6);
    printf("\n");
    InOrder(p);
    printf("\n");
    return 0;
}