#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void)
{
    rbtree *Tree = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *T_nil = (node_t *)calloc(1, sizeof(node_t));
    T_nil->color = RBTREE_BLACK;
    Tree->nil = T_nil;
    Tree->root = T_nil;
    return Tree;
}

void delete_node(rbtree *t, node_t *input)
{
    if (input == t->nil)
    {
        return;
    }
    delete_node(t, input->left);
    delete_node(t, input->right);
    free(input);
}

void delete_rbtree(rbtree *t)
{
    delete_node(t, t->root);
    free(t->nil);
    free(t);
}

void left_rotate(rbtree *t, node_t *input)
//입력 노드에서 좌측으로 회전
{
    node_t *input_right = input->right;
    //입력 노드의 우측 자식을 선언
    input->right = input_right->left;
    //왼쪽으로 회전되기에 입력 노드의 우측 자식이 input_right 노드의 좌측 자식 노드로 변경 한다.
    if (input_right->left != t->nil)       // input_right 노드의 좌측 자식 노드가 nil 노드가 아니면
        input_right->left->parent = input; // input_right 노드의 좌측 자식의 부모 노드는 input 노드로 변경한다.
    input_right->parent = input->parent;   // input_right 노드의 부모노드를 input 노드의 부모 노드로 변경한다.

    if (input->parent == t->nil) //만약 input 노드의 부모 노드가 nill 노드면
        t->root = input_right;   //트리의 루트 노드는 input_right 노드로 변경한다.

    else if (input == input->parent->left) //만약 input 노드가 input 노드의 부모의 좌측 노드면
        input->parent->left = input_right; // input 노드의 부모의 좌측 노드는 input_right 노드로 변경한다.

    else                                    //그렇지 않은 경우
        input->parent->right = input_right; // input 노드의 부모의 우측 노드를 input_right 노드로 변경한다.

    input_right->left = input;   //위 작업을 하고 난 뒤 input_right 노드의 좌측 노드를 input 노드로 변경하고
    input->parent = input_right; // input 노드의 부모 노드를 input_right 노드로 변경한다.
}

void right_rotate(rbtree *t, node_t *input)
//좌측 회전과 반대로 적용
{
    node_t *input_left = input->left;
    input->left = input_left->right;

    if (input_left->right != t->nil)
        input_left->right->parent = input;
    input_left->parent = input->parent;

    if (input->parent == t->nil)
        t->root = input_left;

    else if (input == input->parent->right)
        input->parent->right = input_left;

    else
        input->parent->left = input_left;

    input_left->right = input;
    input->parent = input_left;
}

void rbtree_insert_fixup(rbtree *t, node_t *input)
//새로운 값이 입력되면 트리의 노드들의 색을 변경하기위한 작업
{
    while (input->parent->color == RBTREE_RED) // input 노드의 부모의 색이 붉은 노드면서
    {
        if (input->parent == input->parent->parent->left) // input 노드의 부모 노드가 조부모 노드의 좌측 노드 일 때
        {
            node_t *uncle = input->parent->parent->right; // input 노드의 조부모 노드의 우측 노드를 삼촌 노드로 선언
            if (uncle->color == RBTREE_RED)               //(Case1)삼촌 노드의 색이 붉은색 일 때
            {
                input->parent->color = RBTREE_BLACK;       // input 노드의 부모의 색을 검은색으로 변경하고
                uncle->color = RBTREE_BLACK;               // uncle 노드의 색도 검은색으로 변경 하고
                input->parent->parent->color = RBTREE_RED; // input 노드의 조부모 노드의 색은 붉은색으로 변경한다.
                input = input->parent->parent;             // input 노드의 조부모 노드부터 다시 탐색하기위해 input의 주소값을 조부모 노드로 변경한다.
            }
            else //삼촌 노드의 색이 검은색 일 때
            {
                if (input == input->parent->right) //(Case2)input 노드가 부모의 우측 자식 노드일 경우
                {
                    input = input->parent; // input 의 주소값을 input노드의 부모 주소값 으로 바꾼 뒤
                    left_rotate(t, input); //좌측으로 회전
                }
                input->parent->color = RBTREE_BLACK;       //(Case3)input 노드의 부모 노드의 색이 검은색 일 때
                input->parent->parent->color = RBTREE_RED; // input 노드의 조부모 노드의 색을 붉은색으로 변경하고
                right_rotate(t, input->parent->parent);    // input의 조부모를 기준으로 우측으로 회전시킨다.
            }
        }
        else // input 노드의 부모 노드가 조부모 노드의 우측 노드 일 때
        {    //좌우를 바꿔 똑같이 실행
            node_t *uncle = input->parent->parent->left;
            if (uncle->color == RBTREE_RED)
            {
                input->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                input->parent->parent->color = RBTREE_RED;
                input = input->parent->parent;
            }
            else
            {
                if (input == input->parent->left)
                {
                    input = input->parent;
                    right_rotate(t, input);
                }
                input->parent->color = RBTREE_BLACK;
                input->parent->parent->color = RBTREE_RED;
                left_rotate(t, input->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK; //트리의 루트 노드의 색을 검은색으로 바꾸고 종료
}

node_t *rbtree_insert(rbtree *t, const key_t key)
//새로운 값을 받을때 사용
{
    node_t *input = (node_t *)calloc(1, sizeof(node_t)); //입려된 값을 저장하기 위한 input 노드 선언
    node_t *compare_parent = t->nil;                     //비교를 위한 부모 노드에 트리의 nil 노드 선언
    node_t *compare_child = t->root;                     //비교를 위한 자식 노드에 트리의 root 노드 선언
    while (compare_child != t->nil)                      //비교 자식 노드가 nil 노드가 아닐경우(트리가 비어있지 않은 경우)
    {
        compare_parent = compare_child;           //비교 부모노드에 비교 자식 노드의 값 저장
        if (key < compare_child->key)             //입력 값이 비교 자식 노드보다 작을 경우
            compare_child = compare_child->left;  //비교 노드를 현재 비교노드의 좌측 노드로 변경
        else                                      //입력 값이 비교 자식 노드보다 클 경우
            compare_child = compare_child->right; //비교 노드를 현재 비교노드의 우측 노드로 변경
    }

    input->parent = compare_parent; // input 노드의 부모 노드를 비교 부모 노드로 변경한다.

    if (compare_parent == t->nil) //비교 부모 노드가 nil노드 일 경우(트리가 빈 경우)
        t->root = input;          //트리의 루트 노드를 input 노드로 변경한다.

    else if (key < compare_parent->key) //입력 값이 비교 부모 노드보다 작으면
        compare_parent->left = input;   //비교 부모 노드의 좌측 자식은 input 노드로 변경한다.

    else                               //입력 값이 비교 부모 노드보다 크면
        compare_parent->right = input; //비교 부모 노드의 우측 자식은 input 노드로 변경한다.

    input->key = key;              // input 노드의 key 값
    input->left = t->nil;          // input 노드의 left 값
    input->right = t->nil;         // input 노드의 right 값
    input->color = RBTREE_RED;     // input 노드의 coloer 값(입력 노드는 무조건 빨간색)
    rbtree_insert_fixup(t, input); // input 노드부터 노드 색 변경을 위한 insert_fixup 실행
    return input;
}

node_t *rbtree_find(const rbtree *t, const key_t input)
//원하는 노드를 탐색 할 때 사용
{
    node_t *compare_node = t->root; //비교 노드를 트리의 루트 노드로 선언
    while (compare_node != t->nil)  //비교 노드가 nil 노드가 아니라면
    {
        if (compare_node->key > input)          //비교 노드의 값이 input 값 보다 크면
            compare_node = compare_node->left;  //비교 노드를 비교 노드의 좌측 자식 노드로 변경한다.
        else if (compare_node->key < input)     //비교 노드의 값이 input 값 보다 작으면
            compare_node = compare_node->right; //비교 노드를 비교 노드의 우측 자식 노드로 변경한다.
        else                                    //비교 노드와 입력 input 값이 같으면
            return compare_node;                //비교 노드를 반환
    }
    return NULL; //빈 트리면 NULL 반환
}

node_t *rbtree_min(const rbtree *t)
//트리의 가장 작은 값을 찾을때 사용
{
    node_t *compare_parent = t->nil; //비교 부모 노드를 nil 노드로 선언
    node_t *compare_child = t->root; //비교 자식 노드를 root 노드로 선언

    while (compare_child != t->nil) //비교 자식 노드가 nil 노드가 아니면(끝 노드가 아니면)
    {
        compare_parent = compare_child;      //비교 부모 노드를 비교 자식 노드로 변경
        compare_child = compare_child->left; //비교 자식 노드를 비교 자식 노드의 좌측 자식 노드로 변경
    }
    return compare_parent; //비교 부모 노드를 반환
}

node_t *rbtree_max(const rbtree *t)
//트리의 가장 큰 값을 찾을 때 사용
{
    node_t *compare_parent = t->nil; //비교 부모 노드를 nil 노드로 선언
    node_t *compare_child = t->root; //비교 자식 노드를 root 노드로 선언

    while (compare_child != t->nil) //비교 자식 노드가 nil 노드가 아니면(끝 노드가 아니면)
    {
        compare_parent = compare_child;       //비교 부모 노드를 비교 자식 노드로 변경
        compare_child = compare_child->right; //비교 자식 노드를 비교 자식 노드의 우측 자식 노드로 변경
    }
    return compare_parent; //비교 부모 노드를 반환
}

void rb_transplant(rbtree *t, node_t *input, node_t *input_right)
// erase 함수가 잘 작동하기 위해 트리의 균형을 유지시키도록 자리를 바꿔주는 함수
{
    if (input->parent == t->nil) // input 노드의 부모가 트리의 nil 노드라면(root 노드라면)
        t->root = input_right;   //트리의 root 노드는 input_right 노드로 변경

    else if (input == input->parent->left) // input 노드가 부모의 좌측 자식 노드라면
        input->parent->left = input_right; // input 노드의 부모의 좌측 자식 노드는 input_right 노드로 변경

    else                                    // input 노드가 부모의 우측 자식 노드라면
        input->parent->right = input_right; // input 노드의 부모의 우측 자식 노드는 input_right 노드로 변경
    input_right->parent = input->parent;    // input_right 노드의 부모 노드는 input의 부모 노드로 변경
}

node_t *tree_minimum(rbtree *t, node_t *input)
// min 함수와 동일하게 작동하나 내 위치로 부터의 최소값(루트의 오른쪽 노드에서 쓰면 결과가 달라짐)
{
    node_t *compare_parent;
    node_t *compare_child = input;

    while (compare_child != t->nil)
    {
        compare_parent = compare_child;
        compare_child = compare_child->left;
    }
    return compare_parent;
}

void rb_delete_fixup(rbtree *t, node_t *input)
{
    node_t *uncle;
    while (input != t->nil && input != t->root && input->color == RBTREE_BLACK)
    // input 노드가 nil 노드, root 노드, 검은색 붉은색 노드가 아닐 때
    {
        if (input == input->parent->left)
        {
            uncle = input->parent->right;
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                input->parent->color = RBTREE_RED;
                left_rotate(t, input->parent);
                uncle = input->parent->right;
            }
            if (uncle->left->color == RBTREE_BLACK && uncle->right->color == RBTREE_BLACK)
            {
                uncle->color = RBTREE_RED;
                input = input->parent;
            }
            else
            {
                if (uncle->right->color == RBTREE_BLACK)
                {
                    uncle->left->color = RBTREE_BLACK;
                    uncle->color = RBTREE_RED;
                    right_rotate(t, uncle);
                    uncle = input->parent->right;
                }
                uncle->color = input->parent->color;
                input->parent->color = RBTREE_BLACK;
                uncle->right->color = RBTREE_BLACK;
                left_rotate(t, input->parent);
                input = t->root;
            }
        }
        else
        {
            uncle = input->parent->left;
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                input->parent->color = RBTREE_RED;
                right_rotate(t, input->parent);
                uncle = input->parent->left;
            }
            if (uncle->right->color == RBTREE_BLACK && uncle->left->color == RBTREE_BLACK)
            {
                uncle->color = RBTREE_RED;
                input = input->parent;
            }
            else
            {
                if (uncle->left->color == RBTREE_BLACK)
                {
                    uncle->right->color = RBTREE_BLACK;
                    uncle->color = RBTREE_RED;
                    left_rotate(t, uncle);
                    uncle = input->parent->left;
                }
                uncle->color = input->parent->color;
                input->parent->color = RBTREE_BLACK;
                uncle->left->color = RBTREE_BLACK;
                right_rotate(t, input->parent);
                input = t->root;
            }
        }
        input->color = RBTREE_BLACK;
    }
}

int rbtree_erase(rbtree *t, node_t *input)
// input 노드를 지우기 위해 사용
{
    node_t *compare_node = input;                              // input 노드의 값을 저장하기 위한 compare_node 노드 생성
    node_t *child;                                             //자식 노드가 될 노드 선언
    color_t compare_node_original_color = compare_node->color; // input 노드의 원래 색을 저장

    if (input->left == t->nil) // input 노드의 좌측 자식 노드가 nil노드면
    {
        child = input->right;                  // child 노드는 input 노드의 우측 노드
        rb_transplant(t, input, input->right); // input 노드와 input 노드의 우측 자식 노드를 transplant
    }
    else if (input->right == t->nil) // input 노드의 우측 자식 노드가 nil노드면
    {
        child = input->left;                  // child 노드는 input 노드의 좌측 노드
        rb_transplant(t, input, input->left); // input 노드와 input 노드의 좌측 자식 노드를 transplant
    }

    else
    {
        compare_node = input->left;
        while (compare_node->left != t->nil)
        {
            compare_node = compare_node->left;
        }
        compare_node_original_color = compare_node->color;
        child = compare_node->right;
        if (compare_node->parent == input)
            child->parent = compare_node;
        else
        {
            rb_transplant(t, compare_node, compare_node->right);
            compare_node->right = input->right;
            compare_node->right->parent = compare_node;
        }
        rb_transplant(t, input, compare_node);
        compare_node->left = input->left;
        compare_node->left->parent = compare_node;
        compare_node->color = input->color;
    }
    if (compare_node_original_color == RBTREE_BLACK)
        rb_delete_fixup(t, child);

    free(input);

    return 1;
}

int node_to_array(const rbtree *t, node_t *node, key_t *arr, size_t n, int index)
{
    if (index < n)
    {
        if (node->left != t->nil)
        {
            index = node_to_array(t, node->left, arr, n, index);
        }
        arr[index++] = node->key;
        if (node->right != t->nil)
        {
            index = node_to_array(t, node->right, arr, n, index);
        }
    }
    return index;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    if (t->root == t->nil)
    {
        return 0;
    }
    node_to_array(t, t->root, arr, n, 0);
    return 1;
}