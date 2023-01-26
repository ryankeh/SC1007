#include <stdio.h>
#include <stdlib.h>

int insertNode(ListNode **ptrHead, int index, int value)
int removeNode(ListNode **ptrHead, int index)

typedef struct _linkedlist{
    ListNode *head;
    int size;
} LinkedList;

int main() {
    ListNode *head = NULL;
    int listsize = 0;
    srand(time(NULL));
    while (listsize < 10){
        insertNode(&head, 0, rand() % 100);
        listsize++;
        printf("List: ");
        printList(head);
        printf("\n");
    }
    printf("%d nodes\n", listsize);
    
    while (size > 0){
        removeNode(&head, listsize-1);
        listsize--;
        printf("List: ");
        printList(head);
        printf("\n");
    }
    printf("%d nodes\n", listsize);
    return 0;
}
