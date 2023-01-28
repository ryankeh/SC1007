#include <stdio.h>
#include <stdlib.h>

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
int sizeList(LinkedList *ll)

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
    
int main(){
    LinkedList ll;
    LinkedList *ptr_ll;
    
    insertNode(&ll, 0, 100);
    printList(&ll);
    printf(“%d nodes\n”, ll.size);
    removeNode(&ll, 0);
    
    ptr_ll = malloc(sizeof(LinkedList));
    insertNode(ptr_ll, 0, 100);
    printList(ptr_ll);
    printf(“%d nodes\n”, ptr_ll->size);
    removeNode(ptr_ll, 0);
    }
}

//Declare a temp pointer instead of using head (it is no longer a local variable; it is the actual head pointer)
void printList(LinkedList *ll){
    ListNode *temp = ll->head;
    if (temp == NULL)
        return;
    while (temp != NULL){
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

ListNode * findNode(
    LinkedList *ll, int index){
    ListNode *temp = ll->head;
    if (temp == NULL || index < 0)
        return NULL;
    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }
    return temp;
}

int sizeList(LinkedList *ll){
    return ll->size;
}

