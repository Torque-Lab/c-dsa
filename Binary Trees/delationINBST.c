#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

// Function for node creation
struct node *createnode(int data) {
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// In-order traversal
void InOrder(struct node *root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}

// Find the in-order predecessor
struct node* inOrderPredecessor(struct node *root) {
    root = root->left;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Delete a node from the binary search tree
struct node* DeleteNode(struct node *root, int value) {
    struct node *iPre;
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }
    if (value < root->data) {
        root->left = DeleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = DeleteNode(root->right, value);  // Corrected this line
    } else {
        iPre = inOrderPredecessor(root);
        root->data = iPre->data;
        root->left = DeleteNode(root->left, iPre->data);
    }
    return root;
}

int main() {
    struct node *p = createnode(5);
    struct node *p1 = createnode(3);
    struct node *p2 = createnode(6);
    struct node *p3 = createnode(1);
    struct node *p4 = createnode(4);

    p->left = p1;
    p->right = p2;
    p1->left = p3;
    p1->right = p4;

    printf("\nIn-order before deletion:\n");
    InOrder(p);
    printf("\n");

    DeleteNode(p, 5);

    printf("\nIn-order after deletion:\n");
    InOrder(p);
    printf("\n");

    return 0;
}
