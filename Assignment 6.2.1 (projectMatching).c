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

int main()
{
 int Prj, Std, Mtr; //Project, Student and Mentor;
 int maxMatch;
 scanf("%d %d %d", &Std, &Prj, &Mtr);
 
 int vertices[3] = {Prj,Std,Mtr};
 int np,nm; //number of projects and number of mentors

 // Build graph

 // Allocate memory for the adjacency matrix
 int **prj_Std_matrix = (int **)malloc(Prj * sizeof(int *));
 for (int i = 0; i < Prj; i++) {
     prj_Std_matrix[i] = (int *)malloc(Std * sizeof(int));
 }
 int **std_Mtr_matrix = (int **)malloc(Std * sizeof(int *));
 for (int i = 0; i < Std; i++) {
     std_Mtr_matrix[i] = (int *)malloc(Mtr * sizeof(int));
 }


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

 //testing input
//  printf("The project student adjacency matrix is:\n");
//  for (int i = 0; i < Prj; i++) {
//     for (int j = 0; j < Std; j++) {
//        printf("%d ", prj_Std_matrix[i][j]);
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

 //Initialising array of allocated projects
 int *allocated = (int *)malloc(Prj * sizeof(int));
 for (int i = 0; i < Prj; i++) {
    allocated[i]=0;
 }

//  hasPath(prj_Std_matrix, std_Mtr_matrix, vertices, 1);
//  hasPath(prj_Std_matrix, std_Mtr_matrix, vertices, 2);
//  hasPath(prj_Std_matrix, std_Mtr_matrix, vertices, 3);

 int* mtr_visited = (int *)malloc(Mtr * sizeof(int));

 int iteration;
for(iteration=1;iteration<4;iteration++){

   //initialising visited arrays
   int* prj_visited = (int *)malloc(Prj * sizeof(int));
   int* std_visited = (int *)malloc(Std * sizeof(int));

   int i;
   for(i=0;i<Prj;i++){
      prj_visited[i]=0;
   }
   for(i=0;i<Std;i++){
      std_visited[i]=0;
   }

   //initialising queue for recording path
   Queue path;
   path.head = NULL;
   path.size = 0;
   path.tail = NULL;

   //initialising stacks
   Stack s;
   s.head = NULL;
   s.size = 0;

   Stack indiStack;
   indiStack.head = NULL;
   indiStack.size = 0;

   push(&s, iteration);
   push(&indiStack, 0);
   prj_visited[iteration]=1;

   int indicator;
   //indicator: 0=project, 1=student

   while(!isEmptyStack(s)){
      int cur = peek(s);
      int indicator = peek(indiStack);
      pop(&s);
      pop(&indiStack);

      //project is top of the stack
      if(indicator==0){
         prj_visited[cur-1]=1;
         enqueue(&path, cur);

         for(i=0;i<Std;i++){
            if(prj_Std_matrix[cur-1][i]==1 && std_visited[i]==0){
               push(&s, i+1);
               push(&indiStack, 1);
            }
         }
      }

      //student is top of the stack
      if(indicator==1){
         std_visited[cur-1]=1;
         enqueue(&path, cur);
         int hello=0;

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

               hello=1;
               break;
            }
         }
         if(hello==1) break;

         for(i=0;i<Prj;i++){
            if(prj_Std_matrix[cur-1][i]==-1 && prj_visited[i]==0){
               push(&s, i+1);
               push(&indiStack, 0);
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

   printf("mentor allocation\n");
   for(i=0;i<Mtr;i++){
      printf("Mentor %d: %d\n", i,mtr_visited[i]);
   }
 }

 //apply Ford Fulkerson algorithm
 // use DFS or BFS to find a path
 
 printf("Max match: %d\n", maxMatch);
 return 0;
}

int hasPath(int** prj_Std_matrix, int** std_Mtr_matrix, int* vertices, int start)
{
   int Prj = vertices[0];
   int Std = vertices[1];
   int Mtr = vertices[2];

   //initialising visited arrays
   int* prj_visited = (int *)malloc(Prj * sizeof(int));
   int* std_visited = (int *)malloc(Std * sizeof(int));
   int* mtr_visited = (int *)malloc(Mtr * sizeof(int));

   //Mentor might need to initialise outside

   //initialising queue for recording path
   Queue path;
   path.head = NULL;
   path.size = 0;
   path.tail = NULL;

   //initialising stacks
   Stack s;
   s.head = NULL;
   s.size = 0;

   Stack indiStack;
   indiStack.head = NULL;
   indiStack.size = 0;

   push(&s, start);
   push(&indiStack, 0);
   prj_visited[start]=1;

   int i,j,k;
   int indicator;
   //indicator: 0=project, 1=student

   while(!isEmptyStack(s)){
      int cur = peek(s);
      int indicator = peek(indiStack);
      pop(&s);
      pop(&indiStack);

      //project is top of the stack
      if(indicator==0){
         prj_visited[cur-1]=1;
         enqueue(&path, cur);

         for(i=0;i<Std;i++){
            if(prj_Std_matrix[cur-1][i]==1 && std_visited[i]==0){
               push(&s, i+1);
               push(&indiStack, 1);
            }
         }
      }

      //student is top of the stack
      if(indicator==1){
         std_visited[cur-1]=1;
         enqueue(&path, cur);
         int hello=0;

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

               hello=1;
               break;
            }
         }
         if(hello==1) break;

         for(i=0;i<Prj;i++){
            if(prj_Std_matrix[cur-1][i]==-1 && prj_visited[i]==0){
               push(&s, i+1);
               push(&indiStack, 0);
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
