#include "../rbtree.h"
#include <stdlib.h>

void insert_fixup(rbtree *t, node_t *input)
{
    while (input->parent->color == 0) //입력 노드의 부모 노드가 붉은 노드일 때
    {
        if (input->parent == input->parent->parent->left) //입력 노드의 부모노드가 왼쪽 자식 노드일 경우
        {
            node_t *uncle = input->parent->parent->right; //입력 노드의 할아버지 오른쪽 자식 노드(삼촌 노드)를 선언

            if (uncle->color == 0) //삼촌 노드의 색이 붉은 노드면(Case 1)
            {
                input->parent->color = 1;         //입력노드의 부모 노드의 색을 검은 노드로 변경
                uncle->color = 1;                 //삼촌 노드도 검은 노드로 변경
                input->parent->parent->color = 0; //입력 노드의 조부모 노드는 붉은 노드로 변경
                input = input->parent->parent;    //조부모 노드부터 노드 색을 비교하기위해 입력 노드 주소 값을 조부모 노드로 변경
            }
            else //삼촌 노드가 검은 노드 일 때
            {
                if (input == input->parent->right) //입력 노드가 부모의 우측 노드면(Case 2)
                {
                    input = input->parent;   //입력 노드에 입력 노드의 부모노드를 저장하고
                    left_rotation(t, input); //입력 노드를 기준으로 레프트 로테이션을 실행
                }
                input->parent->color = 1;                 //입력 노드의 부모 노드를 검은 노드로 변경(Case 3)
                input->parent->parent->color = 0;         //입력 노드의 조부모 노드의 색은 붉은 노드로 변경
                right_rotation(t, input->parent->parent); //입력 노드의 조부모 노드를 기준으로 라이트 로테이션 실행
            }
        }

        else //입력 노드의 부모 노드가오른쪽 자식인 경우 같은 실행을 반대로 실행
        {
            node_t *uncle = input->parent->parent->left;

            if (uncle->color == 1)
            {
                input->parent->color = 0;
                uncle->color = 0;
                input->parent->parent->color = 1;
                input = input->parent->parent;
            }
            else
            {
                if (input == input->parent->left)
                {
                    input = input->parent;
                    right_rotation(t, input);
                }
                input->parent->color = 0;
                input->parent->parent->color = 1;
                left_rotation(t, input->parent->parent);
            }
        }
    }
    t->root->color = 0; // 트리의 루트 노드롤 검은 노드로 변환
}