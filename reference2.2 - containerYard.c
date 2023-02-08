int main(){
    int i, j, crane, row, col, targetid;
    Stack containeryard[10][10];
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++){
            containeryard[i][j].ll.head = NULL;
            containeryard[i][j].ll.size = 0;
        }
  
    row = col = 1;
    targetid = 555;
    // Initialize the target stack at (1,1)
    // Each container has an ID number - this will go in the stack
    for (i = 0; i < 10; i++)
        push(&(containeryard[row][col]), i*100+i*10+i);
    // Find a container within a stack
    // Row, col of stack and ID of container are given
    while (!isEmptyStack(&(containeryard[row][col]))){
        crane = pop(&(containeryard[row][col]));
        // Container found
        if (crane == targetid)
        break;
        // Still not found, so store this crane temporarily in (0,0)
        push(&(containeryard[0][0]), crane);
    }
    // Need to rebuild the original stack
    while (!isEmptyStack(&(containeryard[0][0])))
        push(&(containeryard[row][col]),
        pop(&(containeryard[0][0])));
    if (crane == targetid)
        printf("Container found!\n");
    return 0;
}  
  
