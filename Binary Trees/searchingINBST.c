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
int isBST(struct node *root)
{
    static struct node *prev = NULL; // prev is that node ,jiske children ko hum check kar rahe hai
    if (root != NULL)
    {
        if (!isBST(root->left))
        {
            return 0;
        }
        if (prev != NULL && root->data <= prev->data)
        {
            return 0;
        }
        prev = root;
        return isBST(root->right);
    }
    else
    {
        return 1; // indicate BST hai
    }
}
// Recursive search in BST
struct node *Search(struct node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (key == root->data)
    {
        return root;
    }
    else if (root->data > key)
    {
        return Search(root->left, key);
    }
    else
    {
        return Search(root->right, key);
    }
}
// iterative search in BST
 struct node*SearchIter(struct node*root,int key){
    while(root!=NULL){
    if(key==root->data){
        return root;
    }
    else if(key<root->data){
        root=root->left;
    }
    else{ // when key> root->data
        root=root->right;
    }
 }
 // when we not enter in loop
 return NULL;
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

    printf("\n");
    InOrder(p);
    printf("\n");
    // printf("%d", isBST(p));
    //struct node *n = Search(p, 10);
    struct node *n = SearchIter(p, 10);
    if (n != NULL)
    {
        printf("value found:%d", n->data);
    }
    else
    {
        printf("Element is Not Found");
    }

    return 0;
}