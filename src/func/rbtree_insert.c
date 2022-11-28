#include "rbtree.h"
#include <stdlib.h>

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    node_t *node_parent = t->nil;                        //�θ� �� ��带 ����
    node_t *compare_node = t->root;                      //Ʈ���� ��Ʈ ������ ���ϱ� ���� root ��� ����
    node_t *input = (node_t *)calloc(1, sizeof(node_t)); //�Է��� ���� ��� ����
    input->key = key;                                    //��忡 �Է°� �ο�

    while (compare_node != t->nil) //�� ��尡 Ʈ���� nil ��尡 �� �� ���� ��� Ž��
    {
        node_parent = compare_node;            //�θ� �� ��带 �񱳳��� ����
        if (input->key < compare_node->key)    //�Էµ� ����� ���� �񱳳���� �� ���� ������
            compare_node = compare_node->left; //�� ��带 ���� ���� ����
        else
            compare_node = compare_node->right; //�׷��� ������ ������ ���� ����
    }

    input->parent = node_parent; //�Է� ����� �θ� ��带 ������ �� ���� ����

    if (node_parent == t->nil)              //Ʈ���� �� Ʈ���� ���
        t->root = input;                    //Ʈ���� ��Ʈ ���� �Է� ���
    else if (input->key < node_parent->key) //�Է� ��尪�� ������ �񱳳���� ������ ������
        node_parent->left = input;          //������ �񱳳���� ���� �ڽ��� �Է� ���
    else                                    //�׷��� ������
        node_parent->right = input;         //������ �񱳳���� ������ �ڽ��� �Է� ���

    input->left = t->nil;  //�Է� ����� ���� �ڽ��� nil���
    input->right = t->nil; //�Է� ����� ������ �ڽ��� nil���
    input->color = 0;      //�Է� ����� ���� RED
    return input;
}