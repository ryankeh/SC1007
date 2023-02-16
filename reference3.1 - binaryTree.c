typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

Void TreeTraversal2(BTNode *cur){
    If (cur == NULL) return;
    PrintNode(cur); // visit cur
    TreeTraversal2(cur->left);
    TreeTraversal2(cur->right);
}

int countNode(BTNode *cur){
    if (cur == NULL)
        return 0;
    return (countNode(cur->left) + countNode(cur->right) + 1);
}

void findgrandchildren(
BTNode *cur, int c){
    if (cur == NULL) return;
    if (c == k){
        printf(“%d ”, cur->item);
        return;
    }
    if (c < k){
        findgrandchildren(cur->left, c+1);
        findgrandchildren(cur->right, c+1);
    }
}


