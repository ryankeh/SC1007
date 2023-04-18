//Draft 4
//Recusrive fkin works LFG

#include <stdio.h>
#include <stdlib.h>

int hasPath(int start);
int recursiveHasPath(int start, int indicator);
void cleanVisitedArray();
void testInput();

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

int* mtr_assigned;
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
   //testInput();

   //initialising visited arrays
   prj_visited = (int *)malloc(Prj * sizeof(int));
   std_visited = (int *)malloc(Std * sizeof(int));
   mtr_visited = (int *)malloc(Mtr * sizeof(int));

   //initialising assigned array
   mtr_assigned = (int *)malloc(Mtr * sizeof(int));
   for (int i = 0; i < Mtr; i++) {
      mtr_assigned[i] = 0;
   }

   for(i=0;i<Prj;i++){
      cleanVisitedArray();
      prj_visited[i]=1;
      if(recursiveHasPath(i+1,0)) maxMatch++;
      //testInput();
   }

   // printf("Mentor allocation\n");
   // for(i=0;i<Mtr;i++){
   //    printf("Mentor %d: %d\n", i,mtr_assigned[i]);
   // }
   // printf("Max match: %d\n", maxMatch);

   printf("%d", maxMatch);
   return 0;
}

//----------------------------------------------------------------------------------------------------

int recursiveHasPath(int start, int indicator){

   //project
   if(indicator==0){
      for(int i=0;i<Std;i++){
         if(prj_Std_matrix[start-1][i]==1 && std_visited[i]==0){
            std_visited[i]=1;
            //call recursive function on student
            if(recursiveHasPath(i+1, 1)){
               prj_Std_matrix[start-1][i] = -1; //flip prj_Std arrow
               return 1;
            }
         }
      }
      return 0;
   }

   //student
   if(indicator==1){
      //student is facing towards mentor
      if(std_Std_matrix[start-1]==1){
         for(int i=0;i<Mtr;i++){
            if(std_Mtr_matrix[start-1][i]==1 && mtr_assigned[i]==0){
               //successfully reached mentor
               std_Std_matrix[start-1]=-1; //flip std_Std arrow
               std_Mtr_matrix[start-1][i] = -1; //flip std_Mtr arrow
               mtr_assigned[i]=1;
               return 1;
            }
         }

         for(int i=0;i<Mtr;i++){
            if(std_Mtr_matrix[start-1][i]==1 && mtr_visited[i]==0){
               //reached already assigned mentor
               mtr_visited[i]=1;
               //call recursive function on mentor
               if(recursiveHasPath(i+1, 2)){
                  std_Std_matrix[start-1]=-1; //flip std_Std arrow
                  std_Mtr_matrix[start-1][i] = -1; //flip std_Mtr arrow
                  return 1;
               }
            }
         }
      }

      //looking for unvisited project nodes to go back
      for(int i=0;i<Prj;i++){
         if(prj_Std_matrix[i][start-1]==-1 && prj_visited[i]==0){
            prj_visited[i]=1;
            if(recursiveHasPath(i+1, 0)){
               prj_Std_matrix[i][start-1] = 1; //flip back prj_Std arrow
               return 1;
            }
         }
      }

      return 0;
   }

   //mentor
   if(indicator==2){
      //looking for unvisited student nodes to go back
      for(int i=0;i<Std;i++){
         if(std_Mtr_matrix[i][start-1]==-1 && std_visited[i]==0){
            std_visited[i]=1;
            if(recursiveHasPath(i+1, 1)){
               std_Mtr_matrix[i][start-1] = 1; //flip back prj_Std arrow
               return 1;
            }
         }
      }
      return 0;
   }
   return 0;
}

//----------------------------------------------------------------------------------------------------

void testInput(){
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
}

//----------------------------------------------------------------------------------------------------

void cleanVisitedArray(){
   for (int i = 0; i < Prj; i++) {
      prj_visited[i] = 0;
   }
   for (int i = 0; i < Std; i++) {
      std_visited[i] = 0;
   }
   for (int i = 0; i < Mtr; i++) {
      mtr_visited[i] = 0;
   }
}
