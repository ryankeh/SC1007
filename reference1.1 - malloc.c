#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mallocInt();
int mallocChar();
int mallocStruct();
int mallocString();

#define BUFFER_SIZE 4096

//-----------------------------------------------------------------------------------------------------------

int mallocInt(){
    int i, n;
    printf("Enter number of integers: ");
    scanf("%d", &n);
    int *ptr = (int *)malloc(n*sizeof(int));
    
    if (ptr==NULL){
       printf("Memory not available.");
       exit(1);
    }
    for(i=0;i<n;i++){
       printf("Enter an integer: ");
       scanf("%d", ptr+i);
    }
    for(i=0;i<n;i++){
       printf("%d ", *(ptr+i));
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------
//you can write more than the allocated memory but you would have overwritten parts of the memory that store other data
int mallocChar(){
    int n;
    char *str;
    printf("How long is your string? ");
    scanf("%d", &n);
    str = malloc(n+1);
    if (str == NULL) printf("Uh oh.\n");
    scanf("%s", str);
    printf("Your string is: %s\n", str);
}

//-----------------------------------------------------------------------------------------------------------

struct mystruct{
    int number;
    struct mystruct *nextstruct;
};

int mallocStruct(){
    struct mystruct *firststruct;
    firststruct = malloc(sizeof(struct mystruct));
    firststruct->number = 1;
    firststruct->nextstruct = malloc(sizeof(struct mystruct));
    firststruct->nextstruct->number = 2;
    firststruct->nextstruct->nextstruct = NULL;
}

//-----------------------------------------------------------------------------------------------------------

int mallocString(){
    char **strings;
    int total = 0;
    printf("Enter Number Of Strings: ");
    scanf("%d", &total);
    strings = malloc(total * sizeof(char *));
    
    char buffer[BUFFER_SIZE];
    int length = 0;

    while (getchar() != '\n');
    printf("\n");
    for (int i = 0; i < total; i++){
        printf("Enter string %d: ", i + 1);
        fgets(buffer, BUFFER_SIZE, stdin);
        length = strlen(buffer);
        buffer[length - 1] = '\0';
        strings[i] = malloc(length * sizeof(char));
        strcpy(strings[i], buffer);
    }
  
    printf("\nResulting strings array:\n");
    for (int i = 0; i < total; i++){
        printf("strings[%d] = %s\n", i, strings[i]);
    }
      
    printf("\n");
    return 0;
}
