#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree*)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nilNode = (node_t*)calloc(1, sizeof(node_t));

  nilNode->color = RBTREE_BLACK; // 센티넬 노드 흑색으로 대입
  p->root = nilNode; // 루트노드 센티넬로 설정
  p->nil = nilNode; // 닐노드 센티넬로 설정

  return p;
}

void left_rotate(rbtree* T, node_t* x) {
  //TODO
  node_t *y; // 노드형식 y포인터 선언
  
  y = x->right; // y노드는 x노드의 오른쪽 자식이라고 대입
  x->right = y->left; // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로

  if(y->left != T->nil){ // y의 왼쪽 서브트리가 nil이 아니라면
    y->left->parent = x; // y의 왼쪽 서브트리의 부모를 x노드로
  }

  y->parent = x->parent; // x노드의 부모를 y노드의 부모로 변경

  if(x->parent == T->nil){ // x노드가 트리의 루트일때
    T->root = y; // y노드를 트리의 루트로
  }else if(x == x->parent->left){ // x노드가 왼쪽이라면
    x->parent->left = y; // x노드의 부모의 왼쪽 자식을 y노드로
  }else{ // x노드가 오른쪽이라면
    x->parent->right = y; // x노드의 부모의 오른쪽 자식을 y노드로
  }

  y->left = x; // y노드의 왼쪽 자식을 x노드로
  x->parent = y; // x노드의 부모를 y노드로
}

void right_rotate(rbtree* T, node_t* x) {
  //TODO
  node_t *y;
  y = x->left;
  x->left = y->right;

  if(y->right != T->nil){
    y->right->parent = x;
  }

  y->parent = x->parent;

  if(x->parent == T->nil){
    T->root = y;
  }else if(x == x->parent->right){
    x->parent->right = y;
  }else{
    x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

void rbtree_insert_fixup(rbtree *T, node_t *z){
  node_t *y;
  
  while(z->parent->color == RBTREE_RED){ // z노드의 부모가 적색인 경우
    if(z->parent == z->parent->parent->left){ // z의 부모가 조부모의 왼쪽 서브 트리일 경우

      y = z->parent->parent->right;
      
      if(y->color == RBTREE_RED){ // CASE 1: 노드 z의 삼촌 y가 적색인 경우
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
      }else{
        if(z == z->parent->right){ // CASE 2: z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
        z = z->parent;

        left_rotate(T, z); // 좌회전 수행
        }
        // CASE 3: z의 삼촌 y가 흑색이며 z가 왼쪽 자식인 경우
        z->parent->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;

        right_rotate(T, z); // 우회전 수행

      }
    }else{
      
      y = z->parent->parent->left;

      if(y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
      }else{
        if(z == z->parent->left){
        z = z->parent;

        right_rotate(T, z);

        }
        
        z->parent->color = RBTREE_BLACK;
        z->parent->parent = RBTREE_RED;

        left_rotate(T, z);
      }

    }
  }
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t*)calloc(1, sizeof(node_t));
  z->key = key;

  node_t *y = t->nil;
  node_t *x = t->root;

  while(x != t->nil){
    y = x;
    if(z->key < x->key){
      x = x->left;
    }else{
      x = x->right;
    }
  }

  z->parent = y;

  if(y == t->nil){
    t->root = z;
  }else if(z->key < y->key){
    y->left = z;
  }else{
    y->right = z;
  }

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;

  rbtree_insert_fixup(t, z);

  return z;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *node = t->root;
  while(node != t->nil){
    if(node->key == key){
      return node;
    }

    if(node->key < key){
      node = node->right;
    }else{
      node = node->left;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  if(t->root == t->nil){ // 루트가 nil을 가리키고 있다면(노드가 없다)
    return NULL; // NULL 반환
  }

  node_t *x; // 노드형식 x포인터 선언
  x = t->root; // x노드는 트리의 루트로 초기화

  while(x->left != t->nil){ // x노드의 왼쪽 자식이 nil이 아니라면
    x = x->left; // x노드는 x노드의 왼쪽 자식으로 변경
  }
  
  return x; // x노드 반환
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  if(t->root == t->nil){
    return NULL;
  }

  node_t *x;
  x = t->root;

  while (x->right != t->nil){
    x = x->right;
  }

  return x;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
