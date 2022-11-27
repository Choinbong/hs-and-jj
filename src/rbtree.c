#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

void error_msg()
{
    printf("맥북 프로 사십시오.");
}

node_t *new_node(key_t key)
{
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
    if (!new_node)
    {
        error_msg();
        return 0;
    }

    new_node->color = RBTREE_RED;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    return new_node;
}

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));

    if (!p || !nil_node)
    {
        error_msg();
        return 0;
    }
    // TODO: initialize struct if needed
    // initialize nil_node
    nil_node->color = RBTREE_BLACK;
    nil_node->key = 0;
    nil_node->left = NULL;
    nil_node->right = NULL;
    nil_node->parent = NULL;

    p->nil = nil_node;
    p->root = nil_node;
    return p;
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
    node_t *y = new_node(x->right->key);
    y = x->right;          // y 선언 후 x 오른쪽 자식
    x->right = y->left;    // y의 왼쪽 자식을 x의 오른쪽 자식으로 만듦
    y->left->parent = x;   // y의 왼쪽 자식의 부모를 x로 만듦
    y->parent = x->parent; // y의 부모를 x의 부모로 만듦으로써 x를 지 밑으로 보냄

    if (x->parent == t->nil)       // x가 루트 노드 였다면
        t->root = y;               // y를 루트 노드로 만듦
    else if (x == x->parent->left) // x가 지 부모의 왼쪽 자식이면
    {
        x->parent->left = y; // y를 그 부모의 왼쪽 자식으로 등록
    }
    else // x가 원래 오른쪽 자식이었다면
    {
        x->parent->right = y; // y를 그 부모의 오른쪽 자식으로 등록
    }
    y->left = x;   // y의 왼쪽 자식을 x로 등록
    x->parent = y; // x의 부모를 y로 등록
}

void right_rotate(rbtree *t, node_t *y)
{
    node_t *x = new_node(y->left->key);
    x = y->left;           // x 선언 후 y 왼쪽 자식
    y->left = x->right;    // x의 오른쪽 자식을 y의 왼쪽 자식으로 만듦
    x->right->parent = y;  // x의 오른쪽 자식의 부모를 y로 만듦
    x->parent = y->parent; // y의 부모를 x의 부모로 만듦으로써 x를 지 밑으로 보냄

    if (y->parent == t->nil)        // y가 루트 노드 였다면
        t->root = x;                // x를 루트 노드로 만듦
    else if (y == y->parent->right) // y가 지 부모의 오른쪽 자식이면
    {
        y->parent->right = x; // x를 그 부모의 오른쪽 자식으로 등록
    }
    else // y가 원래 왼쪽 자식이었다면
    {
        y->parent->left = x; // x를 그 부모의 왼쪽 자식으로 등록
    }
    x->right = y;  // x의 오른쪽 자식을 y로 등록
    y->parent = x; // y의 부모를 x로 등록
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    // Left-rotate
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = new_node(key);

    while (x->key != t->nil)
    {
        y = x;
        if (y->key == t->nil)
            t->root = key;
        else if (key < y->key)
            y->left = key;
        else
            y->right = key;
    }
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *c_node = t->root;
    while (c_node->key != NULL && key != c_node->key)
    {
        // left node
        if (key < c_node->key)
            c_node = c_node->left;
        // right node
        else
            c_node = c_node->right;
    }
    return c_node;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *min_node = t->root;
    while (min_node->left != t->nil)
    {
        min_node = min_node->left;
    }

    return min_node;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *max_node = t->root;
    while (max_node->right != t->nil)
    {
        max_node = max_node->right;
    }

    return max_node;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}
