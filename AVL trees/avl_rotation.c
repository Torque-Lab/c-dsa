#include<stdio.h>
#include<stdlib.h>

struct Node{

    int key;
    struct Node*left;
    struct Node *right;
    int height; // use to check balance factor
};

int getHeight(struct Node *n){
    if(n==NULL){
    return 0;
    }

    else{
        return n->height;
    }

}

struct Node * createNode(int key){

    struct Node* node=(struct Node*) malloc(sizeof(struct Node));
    node->left=NULL;
    node->right=NULL;
    node->key=key;
    node->height=1;
    return node;
}
int max(int a,int b){
    return a>b?a:b;
}

int getBalanceFactor(struct Node*n){
    if(n==NULL){
        return 0;
    }
    else{
        return getHeight(n->left) - getHeight(n->right);
    }
}

struct Node* rightRotate(struct Node*y){

    struct Node* x=y->left;
    struct Node*T2=x->right;
    x->right=y;
    y->left=T2;
    y->height=max(getHeight(y->right),getHeight(y->left)) +1;
    x->height=max(getHeight(x->right),getHeight(x->left)) +1;
    return x;
}

struct Node* leftRotate(struct Node*x){

    struct Node* y=x->left;
    struct Node*T2=T2->right;
    x->right=T2;
    y->left=x;
    y->height=max(getHeight(y->right),getHeight(y->left)) +1;
    x->height=max(getHeight(x->right),getHeight(x->left)) +1;
    return y;
}
struct Node* insert(struct Node*node,int key){
    if(node==NULL){
        return(createNode(key));
    }
    else if(key<node->key){
        node->left=insert(node->left,key);
    }
      else if(key>node->key){
        node->right=insert(node->right,key);
    }

    return node;

    node->height=1+max(getHeight(node->left),getHeight(node->right)); // running for leaf node
    int bf=getBalanceFactor(node);
    //left left case
    if(bf>1&& key < node->left->key){
       return rightRotate(node);

    }
    //right right case
     if(bf<-11&& key >node->right->key){
       return leftRotate(node);

    }
    //left right case
       if(bf>1 && key >node->right->key){
           node->left=leftRotate(node->left);

           return  rightRotate(node);

       }
    //right left case
   if(bf<-11&& key <node->right->key){
       node->right=rightRotate(node->right);
       return leftRotate(node);
   }
   return node;
}

void InOrder(struct Node *root)
{

    if (root != NULL)
    {
        InOrder(root->left);
        printf("%d ", root->key);
        InOrder(root->right);
    }
}

int main(){
     struct Node*root=NULL;
    root=insert(root,45);
    root=insert(root,5);
    root=insert(root,4);
    root=insert(root,3);
    root=insert(root,5);
    root=insert(root,98);
    InOrder(root);
    return 0;
}