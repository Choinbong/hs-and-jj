#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
    void inorder(rbtree *T, node_t *x){
    if(x == T->nil){
        return;
    }
    printf("key: %d, color: %d\n", x->key, x->color);
    inorder(T, x->left);
    inorder(T, x->right);
    }

int main(int argc, char *argv[]) {

    rbtree *T = new_rbtree();
    
    rbtree_insert(T, 50);
    rbtree_insert(T, 40);
    rbtree_insert(T, 30);
    rbtree_insert(T, 70);

    inorder(T, T->root);
}