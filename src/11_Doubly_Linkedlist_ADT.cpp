/* _CRT_SECURE_NO_WARNINGS 정의: Microsoft 컴파일러에서 보안 경고를 피하기 위한 매크로 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 리스트에 저장될 데이터의 자료형 정의 (현재는 int형) */
typedef int element;

/* 이중 연결리스트의 노드를 정의하는 구조체 */
typedef struct DListnode {
    element data;              /* 노드에 저장된 데이터 */
    struct DListnode* llink;   /* 이전 노드를 가리키는 포인터 */
    struct DListnode* rlink;   /* 다음 노드를 가리키는 포인터 */
} DListnode;

/* 리스트의 맨 앞(더미노드 다음)에 새 노드를 삽입하는 함수 */
void insert_first(DListnode* head, element data)
{
    /* 새 노드를 위한 동적 메모리 할당 */
    DListnode* newnode = (DListnode*)malloc(sizeof(DListnode));
    newnode->data = data;  /* 노드에 데이터 저장 */

    /* 새 노드의 좌측 포인터는 head(더미 노드)를 가리킴 */
    newnode->llink = head;
    /* 새 노드의 우측 포인터는 현재 head가 가리키는 첫번째 노드를 가리킴 */
    newnode->rlink = head->rlink;

    /* 기존 첫번째 노드의 좌측 포인터를 새 노드로 업데이트 */
    head->rlink->llink = newnode;
    /* head의 우측 포인터가 새 노드를 가리키도록 업데이트 */
    head->rlink = newnode;
}

/* 리스트의 맨 뒤(마지막 노드 앞)에 새 노드를 삽입하는 함수 */
void insert_last(DListnode* head, element data)
{
    /* 새 노드를 위한 동적 메모리 할당 */
    DListnode* newnode = (DListnode*)malloc(sizeof(DListnode));
    newnode->data = data;  /* 노드에 데이터 저장 */

    /* 새 노드의 좌측 포인터는 현재 마지막 노드(head->llink)를 가리킴 */
    newnode->llink = head->llink;
    /* 새 노드의 우측 포인터는 head(더미 노드)를 가리킴 */
    newnode->rlink = head;

    /* 기존 마지막 노드의 우측 포인터를 새 노드로 업데이트 */
    head->llink->rlink = newnode;
    /* head의 좌측 포인터가 새 노드를 가리키도록 업데이트 */
    head->llink = newnode;
}

/* 리스트의 첫 번째 노드를 삭제하는 함수 */
void delete_first(DListnode* head)
{
    /* 리스트가 비어있는 경우 (head만 존재) 삭제하지 않음 */
    if (head->rlink == head)
        return; // 리스트가 비어있으면 함수 종료

    /* 삭제할 노드를 head의 오른쪽 첫번째 노드로 지정 */
    DListnode* remove = head->rlink;
    /* head의 우측 포인터를 삭제할 노드의 이후 노드로 업데이트 */
    head->rlink = remove->rlink;
    /* 삭제할 노드 이후의 노드의 좌측 포인터를 head로 업데이트 */
    remove->rlink->llink = head;
    /* 삭제할 노드에 할당된 메모리 해제 */
    free(remove);
}

/* 리스트의 마지막 노드를 삭제하는 함수 */
void delete_last(DListnode* head)
{
    /* 리스트가 비어있는 경우 (head만 존재) 삭제하지 않음 */
    if (head->rlink == head)
        return; // 리스트가 비어있으면 함수 종료

    /* 삭제할 노드를 head의 왼쪽 마지막 노드로 지정 */
    DListnode* remove = head->llink;
    /* head의 좌측 포인터를 삭제할 노드의 이전 노드로 업데이트 */
    head->llink = remove->llink;
    /* 삭제할 노드 이전의 노드의 우측 포인터를 head로 업데이트 */
    remove->llink->rlink = head;
    /* 삭제할 노드에 할당된 메모리 해제 */
    free(remove);
}

/* 리스트의 노드들을 앞에서부터 순서대로 출력하는 함수 */
void print_forward(DListnode* head)
{
    DListnode* p = head->rlink;  /* 첫 번째 노드부터 탐색 시작 */
    printf("Forward: ");
    /* 노드가 head(더미 노드)가 될 때까지 반복하여 데이터 출력 */
    while (p != head) {
        printf("%d ", p->data);
        p = p->rlink;
    }
    printf("\n");
}

/* 리스트의 노드들을 뒤에서부터 순서대로 출력하는 함수 */
void print_backward(DListnode* head)
{
    DListnode* p = head->llink; /* 마지막 노드부터 탐색 시작 */
    printf("Backward: ");
    /* 노드가 head(더미 노드)가 될 때까지 반복하여 데이터 출력 */
    while (p != head) {
        printf("%d ", p->data);
        p = p->llink;
    }
    printf("\n\n");
}

/* main 함수: 이중 연결리스트의 생성, 삽입, 삭제, 출력 기능 테스트 */
int main()
{
    /* 더미 노드(head)를 위한 동적 메모리 할당 및 초기화
       head의 좌측과 우측 포인터 모두 자신을 가리키도록 설정 */
    DListnode* head = (DListnode*)malloc(sizeof(DListnode));
    head->llink = head;
    head->rlink = head;

    /* 리스트 머리 부분에 데이터를 삽입 (앞쪽 추가) */
    insert_first(head, 40);
    insert_first(head, 30);
    insert_first(head, 20);
    insert_first(head, 10);

    /* 리스트 꼬리 부분에 데이터를 삽입 (뒤쪽 추가) */
    insert_last(head, 50);
    insert_last(head, 60);
    insert_last(head, 70);

    /* 현재 리스트를 앞쪽 방향과 뒤쪽 방향으로 출력 */
    print_forward(head);
    print_backward(head);

    /* 리스트의 첫번째 노드 삭제 */
    delete_first(head);
    /* 리스트의 마지막 노드 삭제 */
    delete_last(head);

    /* 삭제 후 리스트 상태를 다시 앞쪽과 뒤쪽에서 출력 */
    print_forward(head);
    print_backward(head);

    /* 프로그램 종료 전에 더미 노드 head의 동적 메모리 해제 */
    free(head);

    return 0;
}