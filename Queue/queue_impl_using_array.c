#include<stdio.h>
#include<stdlib.h>
struct queue{
    int size;
    int f;
    int b;
    int*arr;

};
int isFull(struct queue *q){
    if(q->b==q->size-1){
        return 1;
    }
    else {
        return 0;
        }
}
int isEmpty(struct queue *q){
    if(q->f==q->b){
        return 1;
    }
    else {
        return 0;
        }
}
void enqueue(struct queue*q,int value){
           if (isFull(q)){
            printf("This queue is already full");
           }
           else{
              q->b++;
              q->arr[q->b]=value;
           }

}
int dequeue(struct queue*q){
    int z=-1;// to indicate dequeue is full
           if (isEmpty(q)){
            printf("This queue is already Empty");
           }
           else{
              q->f++;
              z=q->arr[q->f];
           }
           return z;
}
int main(){
    struct queue q;
    q.size=100;
    q.f=q.b=-1;
    q.arr=(int*)malloc(q.size*sizeof(int));
     // enqueue element
     enqueue(&q,11);
     enqueue(&q,22);
     enqueue(&q,33);
     enqueue(&q,66);
     printf("removing elements %d\n",dequeue(&q));
     printf("removing elements %d\n",dequeue(&q));
     if(isEmpty(&q)){
        printf("queue is empty");
     }
     if(isFull(&q)){
        printf("queue is full");
     }

}