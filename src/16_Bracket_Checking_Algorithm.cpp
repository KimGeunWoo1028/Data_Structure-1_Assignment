#define _CRT_SECURE_NO_WARNINGS  // �������� ���� �Լ� ��뿡 ���� ��� ��Ȱ��ȭ�մϴ�.
#include <stdio.h>     // ǥ�� ����� �Լ����� �����մϴ�.
#include <stdlib.h>    // ���� �޸� �Ҵ� �� ���α׷� ���� �Լ����� �����մϴ�.
#include <string.h>    // ���ڿ� ó�� �Լ����� �����մϴ�.

// StackNode ����ü: ������ �� ���� �ϳ��� ��ȣ ���ڸ� �����ϸ�, ���� ��带 ����Ű�� �����͸� �����ϴ�.
typedef struct StackNode {
    char data;               // ��ȣ ���� �����͸� �����մϴ�.
    struct StackNode* next;  // ���� ��带 ����Ű�� �������Դϴ�.
} StackNode;

// Stack ����ü: ���� ��ü�� ��Ÿ����, �ֻ��� ��带 ����Ű�� �����͸� �����մϴ�.
typedef struct {
    StackNode* top;          // ������ �ֻ��� ��带 ����ŵ�ϴ�.
} Stack;

// create �Լ�: ���ο� �� ������ �����Ͽ� ��ȯ�մϴ�.
Stack* create()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));  // ������ ���� �޸𸮸� �Ҵ��մϴ�.
    if (!stack) {
        return NULL;   // �޸� �Ҵ� ���� �� NULL�� ��ȯ�մϴ�.
    }
    stack->top = NULL; // ������ ��������� ��Ÿ���� ���� �ֻ��� �����͸� NULL�� �ʱ�ȭ�մϴ�.
    return stack;
}

// isEmpty �Լ�: ������ ����ִ��� Ȯ���մϴ�.
// ������ ��������� ���� ��ȯ�մϴ�.
int isEmpty(Stack* stack)
{
    return stack->top == NULL;   // ������ �ֻ��� �����Ͱ� NULL�̸� ������ ��� ������ �ǹ��մϴ�.
}

// push �Լ�: �־��� ��ȣ ���ڸ� ������ �ֻ����� �߰��մϴ�.
void push(Stack* stack, char expr)
{
    StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));  // �� ��带 ���� �޸𸮸� �Ҵ��մϴ�.
    if (!newnode) {
        exit(1);  // �޸� �Ҵ� ���� �� ���α׷��� �����մϴ�.
    }
    newnode->data = expr;         // �� ��忡 ���� �����͸� �����մϴ�.
    newnode->next = stack->top;   // �� ����� ���� �����Ͱ� ���� ������ �ֻ��� ��带 ����ŵ�ϴ�.
    stack->top = newnode;         // ������ �ֻ��� ��带 �� ���� ������Ʈ�մϴ�.
}

// pop �Լ�: ������ �ֻ��� ��Ҹ� �����ϰ� �� ���� ��ȯ�մϴ�.
char pop(Stack* stack) {
    StackNode* temp = stack->top;  // ���� �ֻ��� ��带 �ӽ� ������ �����մϴ�.
    char popped_data = temp->data;   // �ֻ��� ����� ���� �����͸� �����ɴϴ�.
    stack->top = temp->next;         // ������ �ֻ��� �����͸� ���� ���� ������Ʈ�մϴ�.
    free(temp);                      // ���ŵ� ����� �޸𸮸� �����մϴ�.
    return popped_data;              // ���ŵ� ���� �����͸� ��ȯ�մϴ�.
}

// PairCheck �Լ�: ������ ���� ��ȣ�� �ݴ� ��ȣ�� �ùٸ��� �����ϴ��� Ȯ���մϴ�.
// �ùٸ� ���̸� 1��, �ƴϸ� 0�� ��ȯ�մϴ�.
int PairCheck(char open, char close)
{
    if (open == '(' && close == ')')
        return 1;
    else if (open == '{' && close == '}')
        return 1;
    else if (open == '[' && close == ']')
        return 1;
    else
        return 0;
}

// MatchCheck �Լ�: ���ڿ� ���� �ִ� ��ȣ���� �ùٸ��� ��Ī�Ǿ� �ִ��� �˻��մϴ�.
// ��ȯ��:
//  1 : ��� ��ȣ�� �ùٸ��� ��Ī�� ���
//  2 : �������� ������ ���� ��ȣ�� �ִ� ���
//  3 : �������� ��Ī�Ǵ� ���� ��ȣ�� ���� ���
//  4 : ��ȣ�� ��ø ���谡 �߸��� ���
int MatchCheck(const char* expr)
{
    Stack* stack = create();        // ��ȣ ó���� ���� �� ������ �����մϴ�.
    int len = strlen(expr);         // �Էµ� ������ ���̸� ���մϴ�.
    int i;
    char popped_char;
    int result = 1;                 // �⺻ ������� 1�� ���� (���������� ��Ī�� ���)

    // ������ ��� ���ڸ� ���������� Ȯ���մϴ�.
    for (i = 0; i < len; i++) {
        // ���� ��ȣ�� ��� ���ÿ� �߰��մϴ�.
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            push(stack, expr[i]);
        }
        // �ݴ� ��ȣ�� ��� ó���մϴ�.
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']')
        {
            // ������ ����ִٸ� �����ϴ� ���� ��ȣ�� �����Ƿ� ������� 3���� �����մϴ�.
            if (isEmpty(stack)) {
                result = 3;
                break;
            }
            else {
                // ���ÿ��� ���� �������� ���� ��ȣ�� �����ϰ� ��Ī ���θ� Ȯ���մϴ�.
                popped_char = pop(stack);
                if (!PairCheck(popped_char, expr[i])) {
                    result = 4;  // ��ȣ�� ��ø(���԰���)�� �߸��� ��� ������� 4�� �����մϴ�.
                    break;
                }
            }
        }
    }
    // ���� ��ü�� �м��� ��, ���ÿ� �����ִ� ���� ��ȣ�� �ִٸ� ������ ���� ����Դϴ�.
    if (result == 1) {
        if (!isEmpty(stack))
            result = 2;
    }

    // ���� �м� ����� ��ȯ�մϴ�.
    return result;
}

// main �Լ�: ����ڷκ��� ������ �Է¹޾� ��ȣ ��Ī ���θ� �˻��� �� ����� ����մϴ�.
int main()
{
    char MathExpr[300];  // �ִ� 300���ڱ��� �Է��� �� �ִ� ���� �迭�Դϴ�.
    printf("���� �Է� : ");  // ����ڿ��� ���� �Է��� ��û�մϴ�.

    scanf("%s", MathExpr);  // ����ڰ� �Է��� ������ MathExpr �迭�� �����մϴ�.
    printf("�Է¹��� ���� : %s\n", MathExpr);  // �Է¹��� ������ ����մϴ�.

    // �Էµ� ������ ��ȣ �м��� �����մϴ�.
    int check_result = MatchCheck(MathExpr);

    // ��ȣ �м� ����� ���� ��� ������ �����մϴ�.
    printf("��ȣ �м�\n");
    switch (check_result)
    {
    case 1:
        // ��� ��ȣ�� �ùٸ��� ��Ī�� ���
        printf("3-1. ��ȣ ����� �������� ���");
        break;
    case 2:
        // ���� ��ȣ�� ������ ������ ���� ���
        printf("3-2. ���ȴµ� ������ ���� ���");
        break;
    case 3:
        // �ݴ� ��ȣ�� �����ϴ� �߸��� ���
        printf("3-3. ������ �ʾҴµ� ���� ���");
        break;
    case 4:
        // ��ȣ�� �ùٸ� ���԰��踦 ���� ���� ���
        printf("3-4. ��,��,�� ��ȣ������ ���԰��谡 �߸��� ���");
        break;
    }
    return 0;  // ���α׷� ����
}