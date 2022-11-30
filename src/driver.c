#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
void print_tree(rbtree *t, node_t *node, int level)
{
    if (node == t->nil)
        return;
    print_tree(t, node->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%d:%d\n", node->key, node->color);
    print_tree(t, node->left, level + 1);
}

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();

    rbtree_insert(t, 35);
    rbtree_insert(t, 20);
    rbtree_insert(t, 50);
    rbtree_insert(t, 10);
    rbtree_insert(t, 30);
    rbtree_insert(t, 40);
    rbtree_insert(t, 80);
    rbtree_insert(t, 5);
    rbtree_insert(t, 15);
    rbtree_insert(t, 25);
    rbtree_insert(t, 33);
    rbtree_insert(t, 37);
    rbtree_insert(t, 45);
    rbtree_insert(t, 2);
    rbtree_insert(t, 27);

    // print_tree(t, t->root, 0);

    printf("***********************************\n");

    node_t *p1 = rbtree_find(t, 15);
    rbtree_erase(t, p1);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    node_t *p2 = rbtree_find(t, 33);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 37);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 35);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 40);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 50);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 80);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    p2 = rbtree_find(t, 27);
    rbtree_erase(t, p2);
    print_tree(t, t->root, 0);
    printf("***********************************\n");

    // key_t a, b, c, d, e, f, g, h, i, j, k, l, m, n;

    // a = 10;
    // b = 5;
    // c = 8;
    // d = 34;
    // e = 67;
    // f = 23;
    // g = 156;
    // h = 24;
    // i = 2;
    // j = 12;
    // k = 24;
    // l = 36;
    // m = 990;
    // n = 25;

    // rbtree_insert(t, a);
    // rbtree_insert(t, b);
    // rbtree_insert(t, c);
    // rbtree_insert(t, d);
    // rbtree_insert(t, e);
    // rbtree_insert(t, f);
    // rbtree_insert(t, g);
    // rbtree_insert(t, h);
    // rbtree_insert(t, i);
    // rbtree_insert(t, j);
    // rbtree_insert(t, k);
    // rbtree_insert(t, l);
    // rbtree_insert(t, m);
    // rbtree_insert(t, n);
    // node_t *root = t->root;
    // print_tree(t, root, 0);
}