typedef struct _queue{
    LinkedList ll;
} Queue;

void enqueue(Queue *q, int item){
    insertNode(&(q->ll), q->ll.size, item);
}
