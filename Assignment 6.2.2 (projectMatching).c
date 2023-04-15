//Melvins check both side individually method but realised won't work for test case

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

int checkPrjPath(int student);

//Global Variables
int Prj, Std, Mtr; //Project, Student and Mentor;
int maxMatch;

int **std_Prj_matrix;
int **std_Mtr_matrix;

int* prj_visited;
int* mtr_visited;

int* std1_visited;
int* std2_visited;

int main()
{
   scanf("%d %d %d", &Std, &Prj, &Mtr);
   
   // Build graph

   // Allocate memory for the adjacency matrix
   std_Prj_matrix = (int **)malloc(Prj * sizeof(int *));
   for (int i = 0; i < Std; i++) {
      std_Prj_matrix[i] = (int *)malloc(Std * sizeof(int));
   }

   std_Mtr_matrix = (int **)malloc(Std * sizeof(int *));
   for (int i = 0; i < Std; i++) {
      std_Mtr_matrix[i] = (int *)malloc(Mtr * sizeof(int));
   }


   // Initialize all elements of the adjacency matrix to 0
   for (int i = 0; i < Std; i++) {
      for (int j = 0; j < Prj; j++) {
         std_Prj_matrix[i][j] = 0;
         //i is student, j is project
      }
   }
   for (int i = 0; i < Std; i++) {
      for (int j = 0; j < Mtr; j++) {
         std_Mtr_matrix[i][j] = 0;
         //i is student, j is mentor
      }
   }

   //---------------------------------------------------------------------------------------------------------------

   //reading input
   int i=0,j=0;
   int numPrj, numMtr;
   int stdID, prjID, mtrID;

   for(i=0;i<Std;i++){
      scanf("%d %d", &numPrj, &numMtr);
      //printf("Student %d: %d proj, %d mentor\n",i+1,numPrj,numMtr);
      for(j=0;j<numPrj;j++){
         scanf("%d", &prjID);
         std_Prj_matrix[i][prjID-1] = 1;
         //printf("scan proj\n");
      }
      for(j=0;j<numMtr;j++){
         scanf("%d", &mtrID);
         std_Mtr_matrix[i][mtrID-1] = 1;
         //printf("scan mentor\n");
      }
   }

   //initialising visited array for project and mentor
   //student will have 2 visited arrays, if is visited in both arrays there will be a path;

   prj_visited = (int *)malloc(Prj * sizeof(int));
   mtr_visited = (int *)malloc(Mtr * sizeof(int));
   std1_visited = (int *)malloc(Std * sizeof(int));;
   std2_visited = (int *)malloc(Std * sizeof(int));;

   for(i=0;i<Prj;i++){
      prj_visited[i]=0;
   }
   for(i=0;i<Mtr;i++){
      mtr_visited[i]=0;
   }
   for(i=0;i<Std;i++){
      std1_visited[i]=0;
      std2_visited[i]=0;
   }
   
   //-------------------------------------------------------------------------------------------------------------


   //testing input
   //  printf("The project student adjacency matrix is:\n");
   //  for (int i = 0; i < Std; i++) {
   //     for (int j = 0; j < Prj; j++) {
   //        printf("%d ", std_Prj_matrix[i][j]);
   //     }
   //     printf("\n");
   //  }

   //  printf("The student mentor adjacency matrix is:\n");
   //  for (int i = 0; i < Std; i++) {
   //     for (int j = 0; j < Mtr; j++) {
   //        printf("%d ", std_Mtr_matrix[i][j]);
   //     }
   //     printf("\n");
   //  }

   //---------------------------------------------------------------------------------------------------------------------

   for(i=0;i<Std;i++){
      printf("iteration: %d\n", i);
      checkPrjPath(i);

      for(int x=0;x<Prj;x++){
         printf("prj_visited[%d]=%d\n", x,prj_visited[x]);
      }
   }

   printf("\n");
   for(i=0;i<Std;i++){
      printf("Student %d: %d\n",i,std1_visited[i]);
   }
      
   


   maxMatch = 0;
   //  for(i=0;i<Std;i++){
   //     if(std1_visited[i]==1 && std2_visited[i]==1){
   //       maxMatch++;
   //     }
   //  }

   printf("%d\n", maxMatch);
   return 0;
}









int checkPrjPath(int i){
   //initialising stacks
   Stack s;
   s.head = NULL;
   s.size = 0;

   Stack indiStack;
   indiStack.head = NULL;
   indiStack.size = 0;

   //initialising queue for recording path
   Queue path;
   path.head = NULL;
   path.size = 0;
   path.tail = NULL;

   int indicator;
   int j,k;
   //indicator: 0=student, 1=project

   //---------------------------------------------------------------------------------------------------------------------
   push(&s, i+1);
   printf("pushed student: %d\n", peek(s));
   push(&indiStack, 0);

   while(!isEmptyStack(s)){
      int cur = peek(s);
      int indicator = peek(indiStack);
      printf("pop: %d, indicator:%d\n", peek(s),peek(indiStack));
      pop(&s);
      pop(&indiStack);

      //student is top of the stack
      if(indicator==0){
         enqueue(&path, cur);

         for(j=0;j<Prj;j++){
            //project successfully found
            printf("j: %d, vertice: %d, visited: %d\n", j,std_Prj_matrix[cur-1][j],prj_visited[j]);
            if(std_Prj_matrix[cur-1][j]==1 && prj_visited[j]==0){
               prj_visited[j]=1;
               enqueue(&path, j+1);

               //printing path
               printQ(path.head);

               while(path.size>2){
                  printf("Clash\n");
                  int pre,next;
                  pre = getFront(path);
                  dequeue(&path);
                  next = getFront(path);
                  //flipping arrow
                  printf("next, pre: %d  %d\n",next,pre);
                  std_Prj_matrix[pre-1][next-1] = -1;

                  pre = getFront(path);
                  dequeue(&path);
                  next = getFront(path);
                  //flipping arrow
                  printf("next, pre: %d  %d\n",next,pre);
                  std_Prj_matrix[next-1][pre-1] = 1;
               }

               while(!isEmptyQueue(path)){
                  int pre,next;
                  pre = getFront(path);
                  dequeue(&path);
                  next = getFront(path);
                  dequeue(&path);
                  //flipping arrow
                  std_Prj_matrix[pre-1][next-1] = -1;
                     
                  printf("next, pre: %d  %d\n",next,pre);
                  std1_visited[pre-1]=1;
                  return 0;

               }
            }
         }

         //pushing projects to stack
         for(j=0;j<Prj;j++){
            if(std_Prj_matrix[cur-1][j]==1){
               push(&s, j+1);
               push(&indiStack, 1);
               printf("pushed project: %d\n", peek(s));
            }
         }

         //-----------------------------------------------------------------------------------------------------------------

         //project is top of the stack
         if(indicator==1){
            enqueue(&path, cur);

         for(j=0;j<Std;j++){
            if(std_Prj_matrix[cur-1][j]==-1){
               push(&s, i+1);
               push(&indiStack, 0);
               }
            }         
         }
      }
   }
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
