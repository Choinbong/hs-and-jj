#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
// int main(int argc, char *argv[])
// {
//     printf("hihi\n");
//     return 0;
// }

int main()
{
    rbtree *t = new_rbtree();
    rbtree_insert(t, 10);
    rbtree_insert(t, 5);
    rbtree_insert(t, 20);

    printf("root: %d, left: %d, right: %d\n", t->root->left->color, t->root->right->color);

    return 0;
}