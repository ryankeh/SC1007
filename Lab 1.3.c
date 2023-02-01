#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);

int removeNode(ListNode **ptrHead,int index);
void split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList); 

int main()
{
    ListNode *head=NULL;
    int size =0;
    int item;
    int index;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head,size, item)) size++;
    scanf("%*s");

    printList(head);

    while(1){
        printf("Enter the index of the node to be removed: ");
        scanf("%d",&index);

        if(removeNode(&head,index))
            size--;
        else{
            printf("The node cannot be removed.\n");
            break;
        }

        printf("After the removal operation,\n");
        printList(head);
    }

    printList(head);
    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

int removeNode(ListNode **ptrHead,int index)
{
    ListNode *pre, *cur;
    
    if (index == 0){
        cur = (*ptrHead)->next;
		free((*ptrHead));
		(*ptrHead) = cur;
        return 1;
    }
        
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        if (pre->next == NULL){
            return 0;
        }
		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		return 1;
    }
    return 0;
}

split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList){
    int i=0,oddIndex=0,evenIndex=0;
    while(1){
        if(findNode(*ptrHead, i)) == NULL){
            printList(*ptrEvenList);
            printList(*ptrOddList);
            return;
        }
        else if(i%2==0){
            insertNode(ptrEvenList, evenIndex, findNode(*ptrHead,i));
            evenIndex++;
            i++;
        }
        else if(i%2==1){
            insertNode(ptrOddList, oddIndex, findNode(*ptrHead,i));
            oddIndex++;
            i++;
        }
    }
}
