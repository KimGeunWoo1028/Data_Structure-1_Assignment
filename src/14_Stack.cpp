#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// �迭 ��� ���� ����ü ����
typedef struct {
    int top;       // ������ �ֻ��� �ε��� (������ ��������� -1)
    int capacity;  // ������ �ִ� �뷮
    int* array;    // ���� ��Ҹ� �����ϴ� ���� �迭
} ArrayStack;

// ���� ���� �Լ�: ���ο� ArrayStack�� �Ҵ��ϰ� �ʱ�ȭ�Ѵ�.
ArrayStack* createStack()
{
    // ���� ����ü�� ���� �޸� �Ҵ�
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (!stack) {
        // �޸� �Ҵ� ���� �� NULL ��ȯ
        return NULL;
    }
    // ������ �ʱ� �뷮 ���� (���⼭�� 5�� ����)
    stack->capacity = 5;
    // �ʱ� top �� -1 (������ ��������� ǥ��)
    stack->top = -1;
    // ������ ���� �迭�� ���� �޸� �Ҵ�
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->array) {
        // �迭 �޸� �Ҵ� ���� �� ���� �Ҵ��� ���� ����ü �޸� ���� �� NULL ��ȯ
        free(stack);
        return NULL;
    }
    return stack;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�: top ���� -1�̸� ��� ����
int isEmpty(ArrayStack* stack)
{
    return stack->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�: top ���� capacity - 1�̸� ���� ��
int isFull(ArrayStack* stack)
{
    return stack->top == stack->capacity - 1;
}

// ���ÿ� ���� �����ϴ� �Լ�: ���� á���� Ȯ�� �� �����Ѵ�.
void push(ArrayStack* stack, int item)
{
    if (isFull(stack)) {
        // ������ ���� á���� ��� �޽��� ���
        printf("������ ���� ��!\n");
        return;
    }
    // top ���� ������Ű�� �迭�� item ����
    stack->array[++stack->top] = item;
}

// ���ÿ��� ���� ������ �Լ�: ������ ����ִ��� Ȯ�� �� pop ����
int pop(ArrayStack* stack) {
    if (isEmpty(stack)) {
        // ������ ��������� ��� �޽��� ���
        printf("������ �������!\n");
        return -1;
    }
    // ���� top ��ġ�� ���� ������ ��, top ���� ���ҽ�Ų��.
    return stack->array[stack->top--];
}

int main()
{
    // ���� ����
    ArrayStack* myStack = createStack();

    // ���ÿ� ������ �����Ѵ�.
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);

    // ������ �̹� ���� á���Ƿ� �߰� push �� ��� �޽����� ��µ�
    push(myStack, 60);

    // ���ÿ��� 6�� pop ����� �Բ� ��� ���� ����Ѵ�.
    for (int j = 0; j < 6; j++) {
        int tmp = pop(myStack);
        // �˵� ���� ���
        printf("�˵� ��: %d\n", tmp);
    }

    return 0;
}