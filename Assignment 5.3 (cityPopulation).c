#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

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

void printGraphList(Graph );
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
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

int* city_population (int N, int* population, int** road, int Q, int** cities) 
{
    Graph g;
    int i,j,k;
    int vertex1, vertex2;
    ListNode *tempList;
    int *result = (int*)malloc(sizeof(int)*(Q));
    // result[0] = 5;
    // printf("N: %d\n", N);
    // printf("population: %d\n", population[0]);
    // printf("N: %d\n", N);

    int size=g.V;
    int root;
    int start, end, maxPop;
    int *arr = (int*)malloc(sizeof(int)*(N+1));
    int *prev = (int*)malloc(sizeof(int)*(N+1));

    //initialising adjacency list
    g.V = N;
    g.list = (ListNode **) malloc(N*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    for(i=0;i<(g.V-1);i++)
    {
        vertex1=road[i][0];
        vertex2=road[i][1];

        if(g.list[vertex1-1]==NULL){
            g.list[vertex1-1] = (ListNode *)malloc(sizeof(ListNode));
            g.list[vertex1-1]->vertex = vertex2;
            g.list[vertex1-1]->next = NULL;
        }
        else{
            tempList = (ListNode *)malloc(sizeof(ListNode));
            tempList->next = g.list[vertex1-1];
            tempList->vertex = vertex2;
            g.list[vertex1-1] = tempList;
        }

        if(g.list[vertex2-1]==NULL){
            g.list[vertex2-1] = (ListNode *)malloc(sizeof(ListNode));
            g.list[vertex2-1]->vertex = vertex1;
            g.list[vertex2-1]->next = NULL;
        }
        else{
            tempList = (ListNode *)malloc(sizeof(ListNode));
            tempList->next = g.list[vertex2-1];
            tempList->vertex = vertex1;
            g.list[vertex2-1] = tempList;
        }
        g.E++;
    }
    //checking adjacency list
    //printGraphList(g);

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    ListNode *temp, *nextNode;

    for(i=0;i<Q;i++){
        for(j=0;j<N;j++){
            arr[j]=0;
        }
        
        removeAllItemsFromQueue(&q);

        
        start = cities[i][0];
        end = cities[i][1];
        maxPop = cities[i][2]+1;
        int indicator=0;
        int tempInt;

        if(start==end){
            if(population[start-1]<maxPop){
                result[i]++;
            }
            continue;
        }
        

        enqueue(&q, start);
        arr[start] = 1;
        prev[start] = 0;
        if(population[start-1]<maxPop){
            result[i]++;
        }
        //printf("start: %d\n", population[start-1]);

        // plotting path using prev[] array
        while(!isEmptyQueue(q)){
            temp = g.list[getFront(q)-1];
            root = getFront(q);
            dequeue(&q);

            while(temp!=NULL){
                tempInt = temp->vertex;
                if(arr[tempInt]==0){
                    enqueue(&q, tempInt);
                    arr[tempInt]=1;
                    prev[tempInt]=root;
                }
                if(tempInt == end){
                    arr[tempInt]=1;
                    prev[tempInt]=root;
                    indicator=1;
                    break;
                }
                temp = temp->next;
            }
            if(indicator==1)break;
        }

        while(prev[tempInt]!=0){
            //printf("tempInt: %d\n", population[tempInt-1]);
            if(population[tempInt-1]<maxPop){
                result[i]++;
            }
            tempInt = prev[tempInt];
        }
    
    }
    //printf("result:");
    return result;
}
