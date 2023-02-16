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
