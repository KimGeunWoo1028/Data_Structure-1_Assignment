#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 배열 기반 스택 구조체 정의
typedef struct {
    int top;       // 스택의 최상위 인덱스 (스택이 비어있으면 -1)
    int capacity;  // 스택의 최대 용량
    int* array;    // 스택 요소를 저장하는 동적 배열
} ArrayStack;

// 스택 생성 함수: 새로운 ArrayStack을 할당하고 초기화한다.
ArrayStack* createStack()
{
    // 스택 구조체에 대한 메모리 할당
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (!stack) {
        // 메모리 할당 실패 시 NULL 반환
        return NULL;
    }
    // 스택의 초기 용량 설정 (여기서는 5로 설정)
    stack->capacity = 5;
    // 초기 top 값 -1 (스택이 비어있음을 표시)
    stack->top = -1;
    // 스택의 정수 배열에 대한 메모리 할당
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->array) {
        // 배열 메모리 할당 실패 시 동적 할당한 스택 구조체 메모리 해제 후 NULL 반환
        free(stack);
        return NULL;
    }
    return stack;
}

// 스택이 비어있는지 확인하는 함수: top 값이 -1이면 비어 있음
int isEmpty(ArrayStack* stack)
{
    return stack->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수: top 값이 capacity - 1이면 가득 참
int isFull(ArrayStack* stack)
{
    return stack->top == stack->capacity - 1;
}

// 스택에 값을 삽입하는 함수: 가득 찼는지 확인 후 삽입한다.
void push(ArrayStack* stack, int item)
{
    if (isFull(stack)) {
        // 스택이 가득 찼으면 경고 메시지 출력
        printf("스택이 가득 참!\n");
        return;
    }
    // top 값을 증가시키고 배열에 item 삽입
    stack->array[++stack->top] = item;
}

// 스택에서 값을 꺼내는 함수: 스택이 비어있는지 확인 후 pop 수행
int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        // 스택이 비어있으면 경고 메시지 출력
        printf("스택이 비어있음!\n");
        return -1;
    }
    // 현재 top 위치의 값을 리턴한 후, top 값을 감소시킨다.
    return stack->array[stack->top--];
}

int main()
{
    // 스택 생성
    ArrayStack* myStack = createStack();

    // 스택에 값들을 삽입한다.
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);

    // 스택이 이미 가득 찼으므로 추가 push 시 경고 메시지가 출력됨
    push(myStack, 60);

    // 스택에서 6번 pop 실행과 함께 결과 값을 출력한다.
    for (int j = 0; j < 6; j++) {
        int tmp = pop(myStack);
        // 팝된 값을 출력
        printf("팝된 값: %d\n", tmp);
    }

    return 0;
}