#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>

typedef enum
{
  RBTREE_RED,
  RBTREE_BLACK
} color_t;

typedef int key_t;

typedef struct node_s
{
  color_t color;
  key_t key;
  struct node_s *parent, *left, *right;
} node_t;

typedef struct
{
  node_t *root;
  node_t *nil; // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
node_t *new_node(rbtree *, const key_t);
node_t *find_key(node_t *, node_t *, key_t);
node_t *min_successor(node_t *, node_t *);
node_t *tree_successor(node_t *, node_t *);

void left_rotate(rbtree *, node_t *);
void right_rotate(rbtree *, node_t *);
void rbtree_insert_fixup(rbtree *, node_t *);
void rbtree_delete_fixup(rbtree *, node_t *);
void inorder_trav(node_t *root, node_t *nil, key_t *arr, const size_t n);
void free_rbtree(node_t *root, node_t *nil);

int rbtree_erase(rbtree *, node_t *);
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n);

#endif // _RBTREE_H_
