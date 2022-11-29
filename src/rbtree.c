#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

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
  // TODO
  node_t *y; // 노드형식 y포인터 선언
  if(x->right == T->nil){
    return;
  }
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
  // TODO
  node_t *y;
  if(x->left == T->nil){
    return;
  }
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
  // TODO
  node_t *y;
  
  while(z->parent->color == RBTREE_RED){ // z노드의 부모가 적색인 경우
    if(z->parent == z->parent->parent->left){ // z의 부모가 조부모의 왼쪽 서브 트리일 경우

      y = z->parent->parent->right;
      
      if(y->color == RBTREE_RED){ // CASE 1: 노드 z의 삼촌 y가 적색인 경우
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else{
        if(z == z->parent->right){ // CASE 2: z의 삼촌 y가 흑색이며 z가 오른쪽 자식인 경우
        z = z->parent;

        left_rotate(T, z); // 좌회전 수행
        }
        // CASE 3: z의 삼촌 y가 흑색이며 z가 왼쪽 자식인 경우
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        right_rotate(T, z->parent->parent); // 우회전 수행

      }
    }else{
      
      y = z->parent->parent->left;

      if(y->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else{
        if(z == z->parent->left){
        z = z->parent;

        right_rotate(T, z);

        }
        
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;

        left_rotate(T, z->parent->parent);
      }

    }
  }
  T->root->color = RBTREE_BLACK;
}

void free_node(rbtree *t, node_t *x){
  // TODO
  // 후위 순회 방식으로 RB Tree 내의 노드 메모리 반환
  if(x->left != t->nil){ // x노드의 왼쪽 자식이 nilNode가 아니라면
    free_node(t, x->left); // 재귀 호출 (왼쪽 자식)
  }
  if(x->right != t->nil){ // x노드의 오른쪽 자식이 nilNode가 아니라면
    free_node(t, x->right); // 재귀 호출 (오른쪽 자식)
  }
  free(x); // 현재 노드 메모리 반환
  x = NULL; // x값 NULL로 초기화
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if(t->root != t->nil){ // 트리안에 노드가 있다면
    free_node(t, t->root); // 모든 노드 메모리를 반환하는 함수 수행
  }
  free(t->nil); // nilNode의 메모리 반환
  free(t); // 트리 메모리 반환
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *z = (node_t*)calloc(1, sizeof(node_t)); // 노드 메모리 할당
  z->key = key; // 받은 키값을 노드에 저장

  node_t *y = t->nil; // y노드 포인터 nilnode가리킴
  node_t *x = t->root; // x노드 포인터 root가리킴

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
  node_t *node = t->root; // node포인터로 root 가리킴
  while(node != t->nil){ // node가 nilNode가 아니라면
    if(node->key == key){ // node의 키 값이 받은 키 값과 같다면
      return node; // node 반환
    }

    if(node->key < key){ // node의 키 값이 받은 키 값보다 작다면
      node = node->right; // 오른쪽 노드로 이동
    }else{
      node = node->left; // 왼쪽 노드로 이동
    }
  }
  return NULL; // 찾지 못한다면 NULL 반환
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

void rbtree_transplant(rbtree *t, node_t *u, node_t* v){
  // TODO
  if(u->parent == t->nil){
    t->root = v;
  }else if(u == u->parent->left){
    u->parent->left = v;
  }else{
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void rbtree_delete_fixup(rbtree *t, node_t *x){
  node_t* w;
  while(x != t->root && x->color == RBTREE_BLACK){
    if(x == x->parent->left){
      w = x->parent->right;
      // 경우 1: x의 형제 w가 적색인 경우
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }
      // 경우 2: x의 형제 w는 흑색이고 w의 두 자식이 모두 흑색인 경우
      if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      // 경우 3: x의 형제 w는 흑색, w의 왼쪽 자식은 적색, 오른쪽 자식은 흑색인 경우
      }else{
        if(w->right->color == RBTREE_BLACK){
        w->left->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        right_rotate(t, w);
        w = x->parent->right;
        }
        // 경우 4: x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->root;
      }
    }
    else{
      w = x->parent->left;
      // 경우 1: x의 형제 w가 적색인 경우
      if(w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        right_rotate(t, x->parent);
        w = x->parent->left;
      }
      // 경우 2: x의 형제 w는 흑색이고 w의 두 자식이 모두 흑색인 경우
      if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
        w->color = RBTREE_RED;
        x = x->parent;
      // 경우 3: x의 형제 w는 흑색, w의 왼쪽 자식은 적색, 오른쪽 자식은 흑색인 경우
      }else{
        if(w->left->color == RBTREE_BLACK){
        w->right->color = RBTREE_BLACK;
        w->color = RBTREE_RED;
        left_rotate(t, w);
        w = x->parent->left;
        // 경우 4: x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
        }
        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        right_rotate(t, x->parent);
        x = t->root;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  node_t *y;
  node_t *x;
  y = p;
  color_t y_original_color = y->color;

  if(p->left == t->nil){

    x = p->right;
    rbtree_transplant(t, p, p->right);

  }else if(p->right == t->nil){

    x = p->left;
    rbtree_transplant(t, p, p->left);

  }else{

    y = p->right;
    while(y->left != t->nil){
      y = y->left;
    }
    y_original_color = y->color;
    x = y->right;
    if(y->parent == p){
      x->parent = y;
    }else{
      rbtree_transplant(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;

  }

  if(y_original_color == RBTREE_BLACK){
    rbtree_delete_fixup(t, x);
  }

  free(p);

  return 0;
}

void inorder(const rbtree *t, node_t *p, key_t *arr, const size_t n, int *index){
  // TODO
  if(p == t->nil){ // p가 nilNode에 도달한다면
    return; // 함수 종료
  }

  inorder(t, p->left, arr, n, index); // 중위 순회 재귀 호출(왼쪽 자식)

  if(*index < n){ // index가 n보다 작다면
    arr[(*index)++] = p->key; // 배열 index번째에 해당 노드 키 값 저장
  }else{
    return; // index가 n보다 커지면 함수 종료
  }

  inorder(t, p->right, arr, n, index); // 중위 순회 재귀 호출(오른쪽 자식)

}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  if(t->root == t->nil){ // 노드가 하나도 없다면
    return 0; // 0 반환
  }
  int index = 0;
  inorder(t, t->root, arr, n, &index); // 중위 순회

  return 1; // 성공하면 1 반환
}
