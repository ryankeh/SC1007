#include <stdlib.h>
//you can write more than the allocated memory but you would have overwritten parts of the memory that store other data

int main(){
    int n;
    char *str;
    printf("How long is your string? ");
    scanf("%d", &n);
    str = malloc(n+1);
    if (str == NULL) printf("Uh oh.\n");
    scanf("%s", str);
    printf("Your string is: %s\n", str);
}
