#include "../rbtree.h"
#include <stdlib.h>

void left_rotation(rbtree *t, node_t *main) //왼쪽 회전시킬 루트노드 선언
{
    node_t *sub = main->right; //메인 노드의 오른쪽 자식을 sub로 선언(sub = main 위치가 된다.)
    main->right = sub->left;   //메인 노드가 회전하면 우측 노드가 비게되므로 sub노드의 좌측 노드를 main노드의 우측자식노드로 변경(메인 노드보다 작은 값들)

    if (sub->left != t->nil)      // sub의 왼쪽 자식 노드가 nil노드가 아니면
        sub->left->parent = main; // sub의 자식 노드의 부모 노드를 main노드로 변경
    sub->parent = main->parent;   // sub 노드의 부모 노드는 main 노드의 부모노드로 변경

    if (main->parent == t->nil)          // main 노드의 부모 노드가 트리의 nil 노드(main이 루트노드)면
        t->root = sub;                   //트리의 루트노드는 sub 노드로 변경
    else if (main == main->parent->left) // main 노드의 부모의 왼쪽 자식노드면
        main->parent->left = sub;        // main 노드의 부모의 왼쪽 자식노드를 sub 노드로 변경
    else                                 // main 노드의 부모의 오른쪽 자식노드면
        main->parent->right = sub;       // main 노드의 부모의 오른쪽 자식노드를 sub 노드로 변경

    sub->left = main;   // sub 노드의 왼쪽 자식 노드를 main 노드로 변경
    main->parent = sub; // main 노드의 부모 노드를 sub 노드로 변경
}

void right_rotation(rbtree *t, node_t *main)
{
    node_t *sub = main->left;

    main->left = sub->right;

    if (sub->right != t->nil)
        sub->right->parent = main;

    sub->parent = main->parent;

    if (main->parent == t->nil)
        t->root = sub;
    else if (main == main->parent->left)
        main->parent->left = sub;
    else
        main->parent->right = sub;

    sub->right = main;
    main->parent = sub;
}
