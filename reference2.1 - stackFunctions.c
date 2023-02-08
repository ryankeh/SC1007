//Stack structure
typedef struct _stack{
    LinkedList ll;
} Stack;

//Stack functions
void push(Stack *s, int item){
    insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
    int item;
    item = ((s->ll).head->item;
    removeNode(&(s->ll), 0);
    return item;
}
            
int peek(Stack *s){
    return ((s->ll).head)->item;
}
            
int isEmptyStack(Stack *s){
    if ((s->ll).size == 0) return 1;
    return 0;
}            

            
//Application reverseString
int main(){
    int i = 0;
    Stack s;
    s.ll.head = NULL;
    
    printf("Enter a number: ");
    scanf("%d", &i);
    while (i != -1){
        push(&s, i);
        printf("Enter a number: ");
        scanf("%d", &i);
    }
    printf("Popping stack: ");
    while (!isEmptyStack(&s))
        printf("%d ", pop(&s));
    return 0;
}
