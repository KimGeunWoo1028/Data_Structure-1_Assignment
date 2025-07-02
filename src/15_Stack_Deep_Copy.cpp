#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���(Node) ����ü: ������ �� ��Ҹ� ��Ÿ��
// data���� ���� ������, next�� ���� ����� �ּҸ� ������
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ���Ḯ��Ʈ ��� ���� ����ü: ������ �ֻ��(top) ��带 ����Ŵ
typedef struct {
    Node* top;
} linkedlistStack;

// ���� ���� �Լ�: ���ο� ������ �����Ҵ��ϰ� top�� NULL�� �ʱ�ȭ��
linkedlistStack* create()
{
    linkedlistStack* stack = (linkedlistStack*)malloc(sizeof(linkedlistStack));
    if (!stack) {
        return NULL; // �޸� �Ҵ� ���� �� NULL ��ȯ
    }
    stack->top = NULL;
    return stack;
}

// ������ ���� á���� Ȯ���ϴ� �Լ� (���Ḯ��Ʈ ����̹Ƿ� �׻� 0�� ��ȯ)
int isFull(linkedlistStack* stack)
{
    return 0;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�: top�� NULL�̸� ������ �������
int isEmpty(linkedlistStack* stack)
{
    return stack->top == NULL;
}

// push �Լ�: ���ÿ� �� �����͸� �����ϴ� �Լ�
void push(linkedlistStack* stack, int item)
{
    // �� ��� �޸� �Ҵ� �� ������ ����
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = item;
    // �� ��尡 ���� top�� ����Ű���� ����
    newnode->next = stack->top;
    // top�� �� ���� ������Ʈ
    stack->top = newnode;
}

// pop �Լ�: ���ÿ��� top �����͸� �����ϰ� ��ȯ�ϴ� �Լ�
int pop(linkedlistStack* stack)
{
    // ������ ����ִ� ��� ���� �޽��� ��� �� -1 ��ȯ
    if (isEmpty(stack)) {
        printf("������ �������\n");
        return -1;
    }

    // ������ ��带 �ӽ÷� �����ϰ�, top�� ���� ���� ����
    Node* temp = stack->top;
    int pop_item = temp->data;
    stack->top = stack->top->next;
    // �޸� ����
    free(temp);
    return pop_item;
}

// display �Լ�: ������ ��� ��带 ��ȸ�ϸ� �����͸� ����ϴ� �Լ�
void display(linkedlistStack* Stack)
{
    Node* cur = Stack->top;
    // ������ ��� ��带 ���
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n\n");
}

// reverseList �Լ�: ���Ḯ��Ʈ�� ������ ������Ű�� �Լ�
Node* reverseList(Node* head)
{
    Node* prev = NULL;
    Node* cur = head;
    Node* next = NULL;

    // ������ ������ �������� ������
    while (cur != NULL) {
        next = cur->next;    // ���� ��� ����
        cur->next = prev;    // ���� ����� next�� ���� ���� ����
        prev = cur;          // prev�� ���� ���� �̵�
        cur = next;          // cur�� ���� ���� �̵�
    }
    // ������ ����Ʈ�� head ��ȯ
    return prev;
}

// deep_copy �Լ�: ���� ������ ���� �����Ͽ� ������ ������ �����͸� ������ ���ο� ���� ����
linkedlistStack* deep_copy(linkedlistStack* originalStack)
{
    // ���� ������ NULL�̸� NULL ��ȯ
    if (!originalStack) {
        return NULL;
    }

    // ���ο� ���� ����
    linkedlistStack* tempStack = create();
    if (!tempStack) {
        return NULL;
    }

    // ���� ������ �� ��带 ��ȸ�ϸ� �ӽ� ���ÿ� push (���� ������ �������� �����)
    Node* cur = originalStack->top;
    while (cur != NULL) {
        push(tempStack, cur->data);
        cur = cur->next;
    }
    // �ӽ� ������ �������� ���� ���ð� ������ ������ ����
    tempStack->top = reverseList(tempStack->top);

    return tempStack;
}

// check �Լ�: �� ������ �� ��� �����͸� ���Ͽ� �������� Ȯ���ϴ� �Լ�
bool check(linkedlistStack* original_stack, linkedlistStack* copied_stack)
{
    // �� ���� ��� NULL�� ��� (�� ����� ������ ���ٰ� �Ǵ�)
    if (original_stack == NULL && copied_stack == NULL) {
        return true;
    }

    // ���ʸ� NULL�� ���� �ٸ�
    if (original_stack == NULL || copied_stack == NULL) {
        return false;
    }

    Node* original_cur = original_stack->top;
    Node* copied_cur = copied_stack->top;

    // �� ����� �����͸� �ϳ��� ��
    while (original_cur != NULL && copied_cur != NULL) {
        if (original_cur->data != copied_cur->data) {
            return false;
        }
        original_cur = original_cur->next;
        copied_cur = copied_cur->next;
    }

    // �� ���� �� �� ���� ��尡 ������ ����
    return original_cur == copied_cur;
}

int main()
{
    // ���� ���� �� ������ ����
    linkedlistStack* myStack = create();

    // ������ 10, 20, 30, 40, 50�� ���� (�������� ���Ե� ���� top)
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    push(myStack, 40);
    push(myStack, 50);

    // ���� ���� ���
    printf("OriginalStack : ");
    display(myStack);

    // ���� �������κ��� ���� ���縦 �����Ͽ� ���ο� ������ ����
    linkedlistStack* copiedStack = deep_copy(myStack);

    // ����� ���� ���
    printf("CopiedStack : ");
    display(copiedStack);

    // �� ������ ���Ͽ� ������ ������ "����", �ƴϸ� "�ٸ�" ���
    if (check(myStack, copiedStack)) {
        printf("�� ��� : ����\n");
    }
    else
    {
        printf("�� ��� : �ٸ�\n");
    }

    return 0;
}