typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void BSTT(BTNode *cur, char c){
    if (cur == NULL) return;
    if (c==cur->item){
        printf(“found!\n”);
        return;
    }
    if (c < cur->item)
        BSTT(cur->left,c);
    else
        BSTT(cur->right,c);
}
