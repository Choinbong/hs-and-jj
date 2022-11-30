#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

#define SENTINEL

int i;

void error_msg()
{
    printf("맥북 프로 사십시오.");
}

node_t *new_node(rbtree *t, const key_t key)
{
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
    if (!new_node)
    {
        error_msg();
        return 0;
    }

    new_node->color = RBTREE_RED; // 새로 추가하는 노드의 색은 빨간색
    new_node->key = key;          // key값은 그대로 넣어줌
    new_node->left = t->nil;      // 일단 닐을 가리키게 만듦
    new_node->right = t->nil;
    new_node->parent = t->nil;

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
    nil_node->color = RBTREE_BLACK; // NIL노드의 색깔은 무조건 BLACK
    nil_node->key = 0;              // 키 값은 무조건 0
    nil_node->left = NULL;          // 닐 주위로는 다 NULL을 가리킴
    nil_node->right = NULL;
    nil_node->parent = NULL;

    p->nil = nil_node; // 새로 만든 트리 p의 NIL을 새로 만든 NIL 노드를 가리키게 만듦
    p->root = p->nil;  // 아직 트리에 아무 노드가 없으므로
    return p;
}

void free_rbtree(node_t *root, node_t *nil)
{
    if (root == nil) // 전위로 타고 내려가다가 NIL노드 만나면 리턴
        return;
    free_rbtree(root->left, nil);
    free_rbtree(root->right, nil);
    free(root); // 끝까지 타고 내려간다음 다시 타고 올라오면서 노드를 free시킴
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    free_rbtree(t->root, t->nil); // 노드들 전부 free시킴
    free(t->nil);                 // 트리의 NIL 노드를 free시킴
    free(t);                      // 최종적으로 트리를 free시킴
}

void left_rotate(rbtree *t, node_t *x)
{
    node_t *y = x->right;    // y 선언 후 x 오른쪽 자식
    x->right = y->left;      // y의 왼쪽 자식을 x의 오른쪽 자식으로 만듦
    if (y->left != t->nil)   // 만약에 y의 왼쪽 자식이 NIL노드면 NIL노드가 다시 부모를 가리킬 일은 없음
        y->left->parent = x; // y의 왼쪽 자식의 부모를 x로 만듦
    y->parent = x->parent;   // y를 x의 부모와 연결하면서 x를 지 밑으로 보냄

    if (x->parent == t->nil)       // x가 루트 노드 였다면 (루트 노드는 NIL 노드를 가리키고 있음)
        t->root = y;               // y를 루트 노드로 만듦
    else if (x == x->parent->left) // x가 지 부모의 왼쪽 자식이면
        x->parent->left = y;       // y를 그 부모의 왼쪽 자식으로 등록
    else                           // x가 원래 오른쪽 자식이었다면
        x->parent->right = y;      // y를 그 부모의 오른쪽 자식으로 등록

    y->left = x;   // y의 왼쪽 자식을 x로 등록
    x->parent = y; // x의 부모를 y로 등록
}

void right_rotate(rbtree *t, node_t *y)
{
    node_t *x = y->left;      // x 선언 후 y 왼쪽 자식
    y->left = x->right;       // x의 오른쪽 자식을 y의 왼쪽 자식으로 만듦
    if (x->right != t->nil)   // x의 오른쪽 자식이 NIL노드면, NIL노드가 y를 가리킬 일은 없음
        x->right->parent = y; // x의 오른쪽 자식의 부모를 y로 만듦
    x->parent = y->parent;    // y의 부모를 x의 부모로 만듦으로써 x를 지 밑으로 보냄

    if (y->parent == t->nil)        // y가 루트 노드 였다면 (루트 노드의 부모는 NIL임)
        t->root = x;                // x를 루트 노드로 만듦
    else if (y == y->parent->right) // y가 지 부모의 오른쪽 자식이면
        y->parent->right = x;       // x를 그 부모의 오른쪽 자식으로 등록
    else                            // y가 원래 왼쪽 자식이었다면
        y->parent->left = x;        // x를 그 부모의 왼쪽 자식으로 등록

    x->right = y;  // x의 오른쪽 자식을 y로 등록
    y->parent = x; // y의 부모를 x로 등록
}

void rbtree_insert_fixup(rbtree *t, node_t *z)
{
    node_t *y;
    // 삽입할 z 부모의 색이 RED이면 새로 삽입하는 노드는 RED이므로 RED-RED Violation이 일어남
    // 부모가 BLACK이면 수정할 필요가 없음
    while (z->parent->color == RBTREE_RED)
    {
        if (z->parent == z->parent->parent->left) // 삽입할 노드 부모가 할배의 왼쪽 자식이면
        {
            y = z->parent->parent->right; // y는 z의 부모의 sibling
            if (y->color == RBTREE_RED)   // y가 RED면
            {
                z->parent->color = RBTREE_BLACK;       // 부모 색깔 BLACK으로 바꾸기
                y->color = RBTREE_BLACK;               // 삼촌 색깔 BLACK으로 바꾸기
                z->parent->parent->color = RBTREE_RED; // 할배 색깔 RED로 바꾸기
                z = z->parent->parent;                 // z의 할배가 RED인데 증조 할배가 RED면 규칙 위반, 재귀 돌리려고 바꿈
            }
            else if (z == z->parent->right) // 삽입할 z가 오른쪽 자식이면 Case2,3 같이 진행
            {
                z = z->parent;                         // 부모를 돌릴 예정
                left_rotate(t, z);                     // 부모를 왼쪽으로 돌림 (왼쪽으로 돌림으로써 자식이 되어버림)
                z->parent->color = RBTREE_BLACK;       // 바뀐 부모의 색을 BLACK으로 바꿈
                z->parent->parent->color = RBTREE_RED; // 할배의 색을 RED로 바꿈
                right_rotate(t, z->parent->parent);    // 오른쪽으로 돌림
            }
            else // Case3
            {
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
        }
        else // 삽입할 노드 부모가 할배의 오른쪽 자식이면
        {
            y = z->parent->parent->left; // y를 z 부모의 sibling (uncle)로 만듦
            if (y->color == RBTREE_RED)  // y의 색이 RED면 부모와 sibling을 전부 BLACK으로 바꿈
            {
                z->parent->color = RBTREE_BLACK;
                y->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED; // 할배를 RED로 바꿈
                z = z->parent->parent;                 // z의 할배가 RED인데 증조 할배가 RED면 규칙 위반, 재귀 돌리려고 바꿈
            }
            else if (z == z->parent->left) // Case2,3 같이 진행
            {
                z = z->parent;                         // z 부모가 오른쪽 회전 후 자식이 될 것이기 때문에 바꿔줌
                right_rotate(t, z);                    // 오른쪽으로 돌림
                z->parent->color = RBTREE_BLACK;       // z 부모의 색을 BLACK으로 바꿈
                z->parent->parent->color = RBTREE_RED; // 할배 색을 RED로 바꿈
                left_rotate(t, z->parent->parent);     // 왼쪽으로 돌림으로써 할배 자리에 부모가 들어가면서 BLACK으로 끝남
            }
            else // Case3
            {
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK; // R-R violation 진행하다가 루트 노드에 도착하면 RED든 BLACK이든 BLACK으로 바꿔버린다.
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = new_node(t, key);

    while (x != t->nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == t->nil)
        t->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    rbtree_insert_fixup(t, z);
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    return find_key(t->root, t->nil, key);
}

node_t *find_key(node_t *root, node_t *nil, key_t key)
{
    if (root == nil)
        return NULL;

    if (root->key == key)
        return root;

    if (root->key < key)
        return find_key(root->right, nil, key);
    else
        return find_key(root->left, nil, key);
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *min_node = t->root;
    while (min_node->left != t->nil)
        min_node = min_node->left;

    return min_node;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *max_node = t->root;
    while (max_node->right != t->nil)
        max_node = max_node->right;

    return max_node;
}

void rbtree_delete_fixup(rbtree *t, node_t *x)
{
    node_t *w;
    while (x != t->root && x->color == RBTREE_BLACK)
    {
        if (x == x->parent->left) // x는 extra BLACK을 가지고 있음
        {
            w = x->parent->right;       // w를 x의 형제노드로 만듦
            if (w->color == RBTREE_RED) // Case 1: w가 RED 노드일 때
            {
                w->color = RBTREE_BLACK;       // w의 색깔을 BLACK으로 만듦
                x->parent->color = RBTREE_RED; // x의 부모 b의 색깔을 RED로 만듦
                left_rotate(t, x->parent);     // 왼쪽으로 돌림
                w = x->parent->right;          // w는 x의 형제노드이므로 왼쪽으로 돌려서 틀어졌기 때문에 다시 x의 부모의 오른쪽 형제를 가리키게 만듦
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) // Case 2: w가 BLACK 노드일 때
            {
                w->color = RBTREE_RED; // x와 w가 가지고 있던 BLACK을 부모에게 줌 (x는 BLACK, w는 red가 됨)
                x = x->parent;         // x를 x의 부모를 가리키게 만든 뒤, 만약 double BLACK이라면 위로 같은 과정을 반복시킴
            }
            else
            {
                if (w->right->color == RBTREE_BLACK) // Case 3: x가 double BLACK, w가 BLACK, w의 왼쪽 자식이 RED
                {
                    w->left->color = RBTREE_BLACK; // w의 왼쪽 자식의 색깔을 BLACK으로 바꾼다.
                    w->color = RBTREE_RED;         // w가 그 왼쪽 자식의 색깔 RED를 물려받는다.
                    right_rotate(t, w);            // 오른쪽으로 회전시킨다.
                    w = x->parent->right;          // 오른쪽으로 회전돼서 w의 왼쪽 자식이 w가 된다. (x의 형제, 위치 재조정)
                }
                // Case 4
                w->color = x->parent->color;     // w의 색을 x의 부모 색깔로 바꾼다.
                x->parent->color = RBTREE_BLACK; // x의 부모 색깔을 BLACK으로 바꾼다.
                w->right->color = RBTREE_BLACK;  // w의 오른쪽 자식을 BLACK으로 바꾼다.
                left_rotate(t, x->parent);       // 왼쪽 회전
                x = t->root;                     // x를 루트노드를 가리키게 만듦
            }
        }
        else
        {
            // TODO: switch right and left
            w = x->parent->left;        // w를 x의 형제노드로 만듦
            if (w->color == RBTREE_RED) // Case 1: w가 RED 노드일 때
            {
                w->color = RBTREE_BLACK;       // w의 색깔을 BLACK으로 만듦
                x->parent->color = RBTREE_RED; // x의 부모 b의 색깔을 RED로 만듦
                right_rotate(t, x->parent);    // 왼쪽으로 돌림
                w = x->parent->left;           // w는 x의 형제노드이므로 왼쪽으로 돌려서 틀어졌기 때문에 다시 x의 부모의 오른쪽 형제를 가리키게 만듦
            }
            if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) // Case 2: w가 BLACK 노드일 때
            {
                w->color = RBTREE_RED; // x와 w가 가지고 있던 BLACK을 부모에게 줌 (x는 BLACK, w는 red가 됨)
                x = x->parent;         // x를 x의 부모를 가리키게 만든 뒤, 만약 double BLACK이라면 위로 같은 과정을 반복시킴
            }
            else
            {
                if (w->left->color == RBTREE_BLACK) // Case 3: x가 double BLACK, w가 BLACK, w의 왼쪽 자식이 RED
                {
                    w->right->color = RBTREE_BLACK; // w의 왼쪽 자식의 색깔을 BLACK으로 바꾼다.
                    w->color = RBTREE_RED;          // w가 그 왼쪽 자식의 색깔 RED를 물려받는다.
                    left_rotate(t, w);              // 오른쪽으로 회전시킨다.
                    w = x->parent->left;            // 오른쪽으로 회전돼서 w의 왼쪽 자식이 w가 된다. (x의 형제, 위치 재조정)
                }                                   // Case 4
                w->color = x->parent->color;        // w의 색을 x의 부모 색깔로 바꾼다.
                x->parent->color = RBTREE_BLACK;    // x의 부모 색깔을 BLACK으로 바꾼다.
                w->left->color = RBTREE_BLACK;      // w의 오른쪽 자식을 BLACK으로 바꾼다.
                right_rotate(t, x->parent);         // 왼쪽 회전
                x = t->root;                        // x를 루트노드를 가리키게 만듦
            }
        }
    }

    x->color = RBTREE_BLACK;
}

node_t *min_successor(node_t *nil, node_t *x)
{
    if (x == nil)
    {
        return nil;
    }

    while (x->left != nil)
        x = x->left;
    return x;
}

node_t *tree_successor(node_t *nil, node_t *x) // successor는 본인보다 큰 수 중 가장 작은 수
{
    if (x->right != nil) // 오른쪽 서브트리가 존재하면, 오른쪽 서브트리의 최소값
        return min_successor(nil, x->right);
    node_t *y = x->parent;            // 오른쪽 서브트리가 없는 경우 y를 x의 부모로 만들어서 따라가게 만듦
    while (y != nil && x == y->right) // y가 루트까지 && x가 y의 오른쪽 자식일때까지
    {                                 // 그럼 while 문을 벗어나면 최종적으로 x가 y의 왼쪽 자식이 됨
        x = y;                        // 계속 위로 타고 올라감
        y = y->parent;                // 위와 동일
    }
    return y;
}

int rbtree_erase(rbtree *t, node_t *z) // BST에서 node z를 삭제하는 과정 + RBTree 에서의 삭제
{
    // TODO: implement erase
    node_t *x, *y;
    if (z->left == t->nil || z->right == t->nil) // 자식이 없거나 자식이 한 명이라면
        y = z;                                   // y가 z 자신이 된다.
    else                                         // 두 상황 모두 아니라면 successor를 y로 놓고 삭제를 진행한다.
        y = tree_successor(t->nil, z);

    // y를 삭제하고 x가 올라가면서 발생하는 예외 케이스들
    if (y->left != t->nil)
        x = y->left; // x는 y의 유일한 자식 이거나 없음
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == t->nil)
        t->root = x;
    else if (y == y->parent->left) // y가 자기 부모의 왼쪽 자식이면
        y->parent->left = x;       // x가 그 자리를 채움
    else                           // y가 자기 부모의 오른쪽 자식이면
        y->parent->right = x;      // x가 그 자리를 채움

    if (y != z) // y가 z가 아니라 successor 였다면
                // TODO: copy y's satellite data into z
        z->key = y->key;
    // 위 과정은 삭제할 노드 y가 RED 노드 였다면 그냥 종료
    if (y->color == RBTREE_BLACK)
        rbtree_delete_fixup(t, x);

    free(y);
    return 1;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    i = 0;
    if (t->root == t->nil)
        return 0;
    inorder_trav(t->root, t->nil, arr, n);
    return 1;
}

void inorder_trav(node_t *root, node_t *nil, key_t *arr, const size_t n)
{
    if (root == nil || i == n)
        return;
    if (root != nil)
    {
        inorder_trav(root->left, nil, arr, n);
        arr[i++] = root->key;
        inorder_trav(root->right, nil, arr, n);
    }
    return;
}