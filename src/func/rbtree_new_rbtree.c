#include "../rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *T_nil = (node_t *)calloc(1, sizeof(node_t));

    T_nil->color = 1;
    p->nil = T_nil;
    p->root = p->nil;
    return p;
}
