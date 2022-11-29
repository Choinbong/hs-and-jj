#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

    void preorder(rbtree *T, node_t *x){
    if(x == T->nil){
        return;
    }
    printf("key: %d, color: %d\n", x->key, x->color);
    preorder(T, x->left);
    preorder(T, x->right);
    }

int main(int argc, char *argv[]) {

    rbtree *T = new_rbtree();
    
    rbtree_insert(T, 50);
    rbtree_insert(T, 40);
    rbtree_insert(T, 30);
    rbtree_insert(T, 70);
    rbtree_insert(T, 60);
    rbtree_insert(T, 10);
    rbtree_insert(T, 20);
    rbtree_insert(T, 80);
    printf("max: %d\n", rbtree_max(T)->key);
    printf("min: %d\n", rbtree_min(T)->key);
    printf("search: %d, %d\n", rbtree_find(T, 50)->key, rbtree_find(T, 50)->parent->key);
    preorder(T, T->root);

    int* arr = (int*)malloc(sizeof(int) * 5);

    rbtree_to_array(T, arr, 5);

    printf("arr 5\n");
    for(int i=0;i<5;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}