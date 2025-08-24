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

void preOrder(struct node *root)
{
  if (root != NULL)
  {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}
void postOrder(struct node *root)
{

  if (root != NULL)
  {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
  }
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
int main()
{

  // creating node by function call
  struct node *p = createnode(4);
  struct node *p1 = createnode(1);
  struct node *p2 = createnode(6);
  struct node *p3 = createnode(5);
  struct node *p4 = createnode(2);
  // tree look like
  //       4
  //      / \
    //      1  6
  //     /\
    //     5 2
  // linking node
  p->left = p1;
  p->right = p2;
  p1->left = p3;
  p1->right = p4;

  preOrder(p);
  printf("\n");
  postOrder(p);
  printf("\n");
  InOrder(p);
  return 0;
}