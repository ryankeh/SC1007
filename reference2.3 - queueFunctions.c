typedef struct _queue{
    LinkedList ll;
} Queue;

void enqueue(Queue *q, int item){
    insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
        int item;
        item = ((q->ll).head)->item;
        removeNode(&ll, 0);
        return item;
}
