#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 노드(Node) 구조체: 스택의 각 요소를 나타냄
// data에는 정수 데이터, next는 다음 노드의 주소를 저장함
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 연결리스트 기반 스택 구조체: 스택의 최상단(top) 노드를 가리킴
typedef struct {
    Node* top;
} linkedlistStack;

// 스택 생성 함수: 새로운 스택을 동적할당하고 top을 NULL로 초기화함
linkedlistStack* create()
{
    linkedlistStack* stack = (linkedlistStack*)malloc(sizeof(linkedlistStack));
    if (!stack) {
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    stack->top = NULL;
    return stack;
}

// 스택이 가득 찼는지 확인하는 함수 (연결리스트 기반이므로 항상 0을 반환)
int isFull(linkedlistStack* stack)
{
    return 0;
}

// 스택이 비어있는지 확인하는 함수: top이 NULL이면 스택이 비어있음
int isEmpty(linkedlistStack* stack)
{
    return stack->top == NULL;
}

// push 함수: 스택에 새 데이터를 삽입하는 함수
void push(linkedlistStack* stack, int item)
{
    // 새 노드 메모리 할당 및 데이터 저장
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = item;
    // 새 노드가 기존 top을 가리키도록 연결
    newnode->next = stack->top;
    // top을 새 노드로 업데이트
    stack->top = newnode;
}

// pop 함수: 스택에서 top 데이터를 제거하고 반환하는 함수
int pop(linkedlistStack* stack)
{
    // 스택이 비어있는 경우 오류 메시지 출력 후 -1 반환
    if (isEmpty(stack)) {
        printf("스택이 비어있음\n");
        return -1;
    }

    // 삭제할 노드를 임시로 저장하고, top을 다음 노드로 변경
    Node* temp = stack->top;
    int pop_item = temp->data;
    stack->top = stack->top->next;
    // 메모리 해제
    free(temp);
    return pop_item;
}

// display 함수: 스택의 모든 노드를 순회하며 데이터를 출력하는 함수
void display(linkedlistStack* Stack)
{
    Node* cur = Stack->top;
    // 스택의 모든 노드를 출력
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n\n");
}

// reverseList 함수: 연결리스트의 순서를 역전시키는 함수
Node* reverseList(Node* head)
{
    Node* prev = NULL;
    Node* cur = head;
    Node* next = NULL;

    // 노드들의 연결을 역순으로 재조정
    while (cur != NULL) {
        next = cur->next;    // 다음 노드 저장
        cur->next = prev;    // 현재 노드의 next를 이전 노드로 변경
        prev = cur;          // prev를 현재 노드로 이동
        cur = next;          // cur를 다음 노드로 이동
    }
    // 역전된 리스트의 head 반환
    return prev;
}

// deep_copy 함수: 원본 스택을 깊은 복사하여 동일한 순서와 데이터를 가지는 새로운 스택 생성
linkedlistStack* deep_copy(linkedlistStack* originalStack)
{
    // 원본 스택이 NULL이면 NULL 반환
    if (!originalStack) {
        return NULL;
    }

    // 새로운 스택 생성
    linkedlistStack* tempStack = create();
    if (!tempStack) {
        return NULL;
    }

    // 원본 스택의 각 노드를 순회하며 임시 스택에 push (삽입 순서가 역순으로 저장됨)
    Node* cur = originalStack->top;
    while (cur != NULL) {
        push(tempStack, cur->data);
        cur = cur->next;
    }
    // 임시 스택을 역전시켜 원본 스택과 동일한 순서를 복원
    tempStack->top = reverseList(tempStack->top);

    return tempStack;
}

// check 함수: 두 스택의 각 노드 데이터를 비교하여 동일한지 확인하는 함수
bool check(linkedlistStack* original_stack, linkedlistStack* copied_stack)
{
    // 두 스택 모두 NULL인 경우 (비교 대상이 없으면 같다고 판단)
    if (original_stack == NULL && copied_stack == NULL) {
        return true;
    }

    // 한쪽만 NULL인 경우는 다름
    if (original_stack == NULL || copied_stack == NULL) {
        return false;
    }

    Node* original_cur = original_stack->top;
    Node* copied_cur = copied_stack->top;

    // 각 노드의 데이터를 하나씩 비교
    while (original_cur != NULL && copied_cur != NULL) {
        if (original_cur->data != copied_cur->data) {
            return false;
        }
        original_cur = original_cur->next;
        copied_cur = copied_cur->next;
    }

    // 두 스택 비교 후 남은 노드가 없으면 같음
    return original_cur == copied_cur;
}

int main()
{
    // 스택 생성 및 데이터 삽입
    linkedlistStack* myStack = create();

    // 데이터 10, 20, 30, 40, 50을 삽입 (마지막에 삽입된 값이 top)
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);

    // 원본 스택 출력
    printf("OriginalStack : ");
    display(myStack);

    // 원본 스택으로부터 깊은 복사를 수행하여 새로운 스택을 생성
    linkedlistStack* copiedStack = deep_copy(myStack);

    // 복사된 스택 출력
    printf("CopiedStack : ");
    display(copiedStack);

    // 두 스택을 비교하여 내용이 같으면 "같음", 아니면 "다름" 출력
    if (check(myStack, copiedStack)) {
        printf("비교 결과 : 같음\n");
    }
    else
    {
        printf("비교 결과 : 다름\n");
    }

    return 0;
}