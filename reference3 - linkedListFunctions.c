#include <stdio.h>
#include <stdlib.h>

void printList (ListNode *head)
ListNode * findNode(ListNode *head, int index)
int insertNode(ListNode **ptrHead, int index, int value)
int removeNode(ListNode **ptrHead, int index)


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

int insertNode(ListNode **ptrHead, int index, int value){
    ListNode *pre, *cur;
    // For empty list and inserting node at index 0
    // If empty list or inserting first node, need to update head pointer
    if (*ptrHead == NULL || index == 0){
        cur = *ptrHead;
        *ptrHead = malloc(sizeof(ListNode));
        (*ptrHead)->item = value;
        (*ptrHead)->next = cur;
        return 0;
    }
    // Normal Case
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(*ptrHead, index-1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        return 0;
    }
    return -1;
}

    
