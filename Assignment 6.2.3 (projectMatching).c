//first draft
//did not account for mentor allowing backtracking via the backwards arrow even if it has been assigned

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
 int vertex;
 struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
 int V;
 int E;
 ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
 int size;
 QueueNode *head;
 QueueNode *tail;
} Queue;

typedef struct _stack
{
 int size;
 StackNode *head;
} Stack;

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int hasPath(int** prj_Std_matrix, int** std_Mtr_matrix, int* vertices, int start);
int matching(Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

//Global Variables
int Prj, Std, Mtr; //Project, Student and Mentor;
int maxMatch;

int **prj_Std_matrix;
int *std_Std_matrix;
int **std_Mtr_matrix;

int* prj_visited;
int* std_visited;
int* mtr_visited;
//can tell if student was visited by the std_Std_matrix
//----------------------------------------------------------------------------------------------------

int main()
{
   scanf("%d %d %d", &Std, &Prj, &Mtr);

   // Build graph

   // Allocate memory for the adjacency matrix
   prj_Std_matrix = (int **)malloc(Prj * sizeof(int *));
   for (int i = 0; i < Prj; i++) {
      prj_Std_matrix[i] = (int *)malloc(Std * sizeof(int));
   }
   std_Mtr_matrix = (int **)malloc(Std * sizeof(int *));
   for (int i = 0; i < Std; i++) {
      std_Mtr_matrix[i] = (int *)malloc(Mtr * sizeof(int));
   }
   // Allocate memory for student array, kinda like std_Std matrix
   std_Std_matrix = (int *)malloc(Std * sizeof(int));

   //----------------------------------------------------------------------------------------------------
   
   // Initialize all elements of the adjacency matrix to 0
   for (int i = 0; i < Prj; i++) {
      for (int j = 0; j < Std; j++) {
         prj_Std_matrix[i][j] = 0;
         //i is project, j is student
      }
   }
   for (int i = 0; i < Std; i++) {
      for (int j = 0; j < Mtr; j++) {
         std_Mtr_matrix[i][j] = 0;
         //i is student, j is mentor
      }
   }
   for (int i = 0; i < Std; i++) {
      std_Std_matrix[i] = 1;
      //initialized to 1 instead
   }

   //----------------------------------------------------------------------------------------------------

   //reading input
   int i=0,j=0;
   int numPrj, numMtr;
   int stdID, prjID, mtrID;

   for(i=0;i<Std;i++){
      scanf("%d %d", &numPrj, &numMtr);
      //printf("Student %d: %d proj, %d mentor\n",i+1,numPrj,numMtr);
      for(j=0;j<numPrj;j++){
         scanf("%d", &prjID);
         prj_Std_matrix[prjID-1][i] = 1;
         //printf("scan proj\n");
      }
      for(j=0;j<numMtr;j++){
         scanf("%d", &mtrID);
         std_Mtr_matrix[i][mtrID-1] = 1;
         //printf("scan mentor\n");
      }
   }

   //----------------------------------------------------------------------------------------------------

   //testing input
   printf("The project student adjacency matrix is:\n");
   for (int i = 0; i < Prj; i++) {
      for (int j = 0; j < Std; j++) {
         printf("%d ", prj_Std_matrix[i][j]);
      }
      printf("\n");
   }

   printf("The student student adjacency matrix is:\n");
   for (int i = 0; i < Std; i++) {
      printf("%d ", std_Std_matrix[i]);
      printf("\n");
   }

   printf("The student mentor adjacency matrix is:\n");
   for (int i = 0; i < Std; i++) {
      for (int j = 0; j < Mtr; j++) {
         printf("%d ", std_Mtr_matrix[i][j]);
      }
      printf("\n");
   }

   //----------------------------------------------------------------------------------------------------

   //initialising visited arrays
   prj_visited = (int *)malloc(Prj * sizeof(int));
   std_visited = (int *)malloc(Std * sizeof(int));
   mtr_visited = (int *)malloc(Mtr * sizeof(int));

   //  hasPath(1);
   //  hasPath(2);
   //  hasPath(3);



   printf("Mentor allocation\n");
   for(i=0;i<Mtr;i++){
      printf("Mentor %d: %d\n", i,mtr_visited[i]);
   }

   printf("Max match: %d\n", maxMatch);
   return 0;
}







int hasPath(int start)
{
   //initialising queues for recording path
   Queue path;
   path.head = NULL;
   path.size = 0;
   path.tail = NULL;

   Queue path2;
   path2.head = NULL;
   path2.size = 0;
   path2.tail = NULL;

   //initialising stacks
   Stack s;
   s.head = NULL;
   s.size = 0;

   Stack s2;
   s2.head = NULL;
   s2.size = 0;

   //----------------------------------------------------------------------------------------------------

   push(&s, start);
   push(&s2, 0);
   prj_visited[start]=1;

   int i,j,k;
   int indicator;
   //indicator: 0=project, 1=student, 2=mentor

   while(!isEmptyStack(s)){
      int cur = peek(s);
      int indicator = peek(s2);
      pop(&s);
      pop(&s2);

      //project is top of the stack
      if(indicator==0){
         prj_visited[cur-1]=1;
         //enqueue project to path
         enqueue(&path, cur);
         enqueue(&path2, 0);

         for(i=0;i<Std;i++){
            if(prj_Std_matrix[cur-1][i]==1 && std_visited[i]==0){
               push(&s, i+1);
               push(&s2, 1);
            }
         }
      }

      //student is top of the stack
      if(indicator==1){
         std_visited[cur-1]=1;
         enqueue(&path, cur);
         enqueue(&path2, 1);
         int hello=0;

         //student is facing towards mentor
         if(std_Std_matrix[cur-1]==1){
            for(i=0;i<Mtr;i++){
               if(std_Mtr_matrix[cur-1][i]==1 && mtr_visited[i]==0){
                  //successfully reached mentor
                  mtr_visited[i]=1;
                  enqueue(&path, i+1);

                  printQ(path.head);
                  while(path.size>3){
                     int pre,next;
                     pre = getFront(path);
                     dequeue(&path);
                     next = getFront(path);
                     //flipping arrow
                     prj_Std_matrix[pre-1][next-1] = -1;

                     pre = getFront(path);
                     dequeue(&path);
                     next = getFront(path);
                     //flipping arrow
                     prj_Std_matrix[next-1][pre-1] = 1;
                  }

                  while(!isEmptyQueue(path)){
                     int pre,next;
                     pre = getFront(path);
                     dequeue(&path);
                     next = getFront(path);
                     //flipping arrow
                     prj_Std_matrix[pre-1][next-1] = -1;

                     pre = getFront(path);
                     dequeue(&path);
                     next = getFront(path);
                     //flipping arrow
                     printf("next, pre: %d  %d\n",next,pre);
                     std_Mtr_matrix[pre-1][next-1] = -1;
                     dequeue(&path);

                  }

                  return 1;
               }
            }
            

            for(i=0;i<Prj;i++){
               if(prj_Std_matrix[cur-1][i]==-1 && prj_visited[i]==0){
                  push(&s, i+1);
                  push(&s2, 0);
               }
            }
         }

         

      }

   }


   printf("The project student adjacency matrix is:\n");
   for (int i = 0; i < Prj; i++) {
      for (int j = 0; j < Std; j++) {
         printf("%d ", prj_Std_matrix[i][j]);
      }
      printf("\n");
   }

   printf("The student mentor adjacency matrix is:\n");
   for (int i = 0; i < Std; i++) {
      for (int j = 0; j < Mtr; j++) {
         printf("%d ", std_Mtr_matrix[i][j]);
      }
      printf("\n");
   }
 


 return 0;
}







void removeAdjVertex(ListNode** AdjList,int vertex)
{
 ListNode *temp, *preTemp;
 if(*AdjList != NULL)
 {
    if((*AdjList)->vertex ==vertex){//first node
      temp = *AdjList;
      *AdjList = (*AdjList)->next;
      free(temp);
      return;
    }
    preTemp = *AdjList;
    temp = (*AdjList)->next;
    while(temp!=NULL && temp->vertex != vertex)
    {
      preTemp= temp;
      temp = temp->next;
    }
    preTemp->next = temp->next;
    free(temp);
   }
}

void insertAdjVertex(ListNode** AdjList,int vertex)
{
  ListNode *temp;
  if(*AdjList==NULL)
  {
     *AdjList = (ListNode *)malloc(sizeof(ListNode));
     (*AdjList)->vertex = vertex;
     (*AdjList)->next = NULL;
  }
  else{
     temp = (ListNode *)malloc(sizeof(ListNode));
     temp->vertex = vertex;
     temp->next = *AdjList;
     *AdjList = temp;
  }
}

void enqueue(Queue *qPtr, int vertex) {
  QueueNode *newNode;
  newNode = malloc(sizeof(QueueNode));
  if(newNode==NULL) exit(0);

  newNode->vertex = vertex;
  newNode->next = NULL;

  if(isEmptyQueue(*qPtr))
     qPtr->head=newNode;
  else
     qPtr->tail->next = newNode;

     qPtr->tail = newNode;
     qPtr->size++;
}

int dequeue(Queue *qPtr) {
   if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
     return 0;
   }
   else{
     QueueNode *temp = qPtr->head;
     qPtr->head = qPtr->head->next;
     if(qPtr->head == NULL) //Queue is emptied
       qPtr->tail = NULL;

     free(temp);
     qPtr->size--;
     return 1;
}
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
   if(q.size==0) return 1;
   else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
  while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
 if(cur==NULL) printf("Empty");

 while (cur != NULL){
    printf("%d ", cur->vertex);
    cur = cur->next;
  }
 printf("\n");
}

void push(Stack *sPtr, int vertex)
{
  StackNode *newNode;
  newNode= malloc(sizeof(StackNode));
  newNode->vertex = vertex;
  newNode->next = sPtr->head;
  sPtr->head = newNode;
  sPtr->size++;
}

int pop(Stack *sPtr)
{
  if(sPtr==NULL || sPtr->head==NULL){
     return 0;
  }
  else{
     StackNode *temp = sPtr->head;
     sPtr->head = sPtr->head->next;
     free(temp);
     sPtr->size--;
     return 1;
   }
}

int isEmptyStack(Stack s)
{
    if(s.size==0) return 1;
    else return 0;
}

int peek(Stack s){
   return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
   while(pop(sPtr));
}
