#include "rbtree.h"
#include <stdlib.h>

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    node_t *node_parent = t->nil;                        //부모가 될 노드를 선언
    node_t *compare_node = t->root;                      //트리의 루트 노드부터 비교하기 위해 root 노드 선언
    node_t *input = (node_t *)calloc(1, sizeof(node_t)); //입력한 값의 노드 선언
    input->key = key;                                    //노드에 입력값 부여

    while (compare_node != t->nil) //비교 노드가 트리의 nil 노드가 될 때 까지 노드 탐색
    {
        node_parent = compare_node;            //부모가 될 노드를 비교노드로 변경
        if (input->key < compare_node->key)    //입력된 노드의 값이 비교노드의 값 보다 작으면
            compare_node = compare_node->left; //비교 노드를 왼쪽 노드로 변경
        else
            compare_node = compare_node->right; //그렇지 않으면 오른쪽 노드로 변경
    }

    input->parent = node_parent; //입력 노드의 부모 노드를 마지막 비교 노드로 변경

    if (node_parent == t->nil)              //트리가 빈 트리일 경우
        t->root = input;                    //트리의 루트 노드는 입력 노드
    else if (input->key < node_parent->key) //입력 노드값이 마지막 비교노드의 값보다 작으면
        node_parent->left = input;          //마지막 비교노드의 왼쪽 자식은 입력 노드
    else                                    //그렇지 않으면
        node_parent->right = input;         //마지막 비교노드의 오른쪽 자식은 입력 노드

    input->left = t->nil;  //입력 노드의 왼쪽 자식은 nil노드
    input->right = t->nil; //입력 노드의 오른쪽 자식은 nil노드
    input->color = 0;      //입력 노드의 색은 RED
    return input;
}