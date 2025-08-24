#include<stdio.h>
#include<stdlib.h>
struct circularQueue{
    int size;
    int f;
    int b;
    int*arr;

};
int isFull(struct circularQueue *q){
    if((q->b+1)%q->size==q->f){
        return 1;
    }
    else {
        return 0;
        }
}
int isEmpty(struct circularQueue*q){
    if(q->f==q->b){
        return 1;
    }
    else {
        return 0;
        }
}
void enqueue(struct circularQueue*q,int value){
           if (isFull(q)){
            printf("This queue is already full\n");
           }
           else{
            printf("the enqued elements :%d\n",value);
              q->b=(q->b+1)%q->size;
              q->arr[q->b]=value;
           }

}
int dequeue(struct circularQueue*q){
    int z=-1;// to indicate dequeue is full
           if (isEmpty(q)){
            printf("This queue is already Empty\n");
           }
           else{
              q->f=(q->f+1)%q->size;
              z=q->arr[q->f];
           }
           return z;
}
int main(){
    struct circularQueue q;
    q.size=4;
    q.f=q.b=0;
    q.arr=(int*)malloc(q.size*sizeof(int));
     // enqueue element
     enqueue(&q,11);
     enqueue(&q,22);
     enqueue(&q,33);
     enqueue(&q,99);
     printf("removing elements %d\n",dequeue(&q));
     printf("removing elements %d\n",dequeue(&q));
     printf("removing elements %d\n",dequeue(&q));
     printf("removing elements %d\n",dequeue(&q));
     

     if(isEmpty(&q)){
        printf("queue is empty");
     }
     if(isFull(&q)){
        printf("queue is full");
     }

}