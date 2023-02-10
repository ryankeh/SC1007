typedef struct _queue{
    LinkedList ll;
} Queue;

int main(){
    Queue q;
    q.ll.head = NULL;
    q.ll.tail = NULL;
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);
    while (!isEmptyQueue(&q))
    printf("%d ", dequeue(&q));
}

void enqueue(Queue *q, int item){
    insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
    int item;
    item = ((q->ll).head)->item;
    removeNode(&ll, 0);
    return item;
}

int peek(Queue *q){
    return ((q->ll).head)->item;
}

int isEmptyQueue(Queue *q){
    if ((q->ll).size == 0) return 1;
    return 0;
}
