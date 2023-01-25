#include <stdlib.h>
//school one but why tf does it work

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
