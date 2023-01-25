#include <stdio.h>
#include <stdlib.h>

void printList (ListNode *head)
ListNode * findNode(ListNode *head, int index)


int main() {
    printf("Hello world");
    return 0;
}

void printList(ListNode *head){
    if (head == NULL)
        return;
    while (head != NULL){
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

ListNode * findNode(ListNode *head, int index){
    if (head == NULL || index < 0)
        return NULL;
    while (index > 0){
        head = head->next;
        if (head == NULL)
            return NULL;
        index--;
    }
    return head;
}
