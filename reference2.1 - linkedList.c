#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
} ListNode;

int main() {
    ListNode *head = NULL, *temp;
    int i = 0;
    
    scanf("%d", &i);
    while (i != -1){
        if (head==NULL){
            head = malloc(sizeof(ListNode));
            temp = head;
        }
        else{
            temp->next = malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
        scanf("%d",&i);
    }
    temp->next = NULL;

    return 0;
}
