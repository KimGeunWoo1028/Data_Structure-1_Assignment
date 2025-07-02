#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100  // �ִ� �Է� ����

// -------------------------
// ���� ����ü ���� (���ڿ�)
// -------------------------
typedef struct {
    char data[MAX];  // ���� �����͸� ������ �迭
    int top;         // ������ �ֻ�� �ε���
} CharStack;

// -------------------------
// ���� ����ü ���� (������)
// -------------------------
typedef struct {
    int data[MAX];  // ���� �����͸� ������ �迭
    int top;        // ������ �ֻ�� �ε���
} IntStack;

// -------------------------
// ���� ���� ���� �Լ�
// -------------------------
void initCharStack(CharStack* s) { s->top = -1; }           // �ʱ�ȭ
int isEmptyChar(CharStack* s) { return s->top == -1; }      // ��� �ִ��� Ȯ��
void pushChar(CharStack* s, char c) { s->data[++(s->top)] = c; }  // Ǫ��
char popChar(CharStack* s) { return s->data[(s->top)--]; }       // ��
char peekChar(CharStack* s) { return s->data[s->top]; }          // �ֻ�� �� ��ȸ

// -------------------------
// ���� ���� ���� �Լ�
// -------------------------
void initIntStack(IntStack* s) { s->top = -1; }               // �ʱ�ȭ
int isEmptyInt(IntStack* s) { return s->top == -1; }          // ��� �ִ��� Ȯ��
void pushInt(IntStack* s, int v) { s->data[++(s->top)] = v; } // Ǫ��
int popInt(IntStack* s) { return s->data[(s->top)--]; }       // ��

// -------------------------
// ������ �켱���� ��ȯ �Լ�
// -------------------------
int precedence(char op) {
    if (op == '*' || op == '/') return 2;  // ����/������ �켱����: 2
    if (op == '+' || op == '-') return 1;  // ����/���� �켱����: 1
    return 0;                              // �� �ܴ� �켱���� ����
}

// ----------------------------------------------------------------
// ���� ǥ������ ���� ǥ����(Postfix)���� ��ȯ�ϴ� �Լ�
// - �Է�: ���ڿ��� �� ������ (��: "(20+3)*4+9")
// - ���: ������ ���ڿ��� ���� (��: "20 3 + 4 * 9 +")
// ----------------------------------------------------------------
void infixToPostfix(const char* infix, char* postfix) {
    CharStack opStack;           // ������ ���� ����
    initCharStack(&opStack);     // ���� �ʱ�ȭ
    int i = 0, j = 0;            // i: infix Ž�� �ε���, j: postfix ���� �ε���
    char token;

    while (infix[i] != '\0') {
        token = infix[i];

        // (1) ������ ��� (���ӵ� ���� ó��)
        if (isdigit(token)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];  // ���ӵ� ���ڸ� ����
            }
            postfix[j++] = ' ';  // ���� ������ ���� ���� �߰�
            continue;            // ���� ������ �Ѿ (i�� ������ ������)
        }

        // (2) ���� ��ȣ: ������ ���ÿ� push
        if (token == '(') {
            pushChar(&opStack, token);
        }

        // (3) ������ ��ȣ: '('�� ���� ������ pop
        else if (token == ')') {
            while (!isEmptyChar(&opStack) && peekChar(&opStack) != '(') {
                postfix[j++] = popChar(&opStack);  // �����ڸ� postfix�� ����
                postfix[j++] = ' ';
            }
            popChar(&opStack); // '(' ����
        }

        // (4) �������� ���: �켱������ ���� pop/push
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!isEmptyChar(&opStack) && precedence(peekChar(&opStack)) >= precedence(token)) {
                postfix[j++] = popChar(&opStack);  // �� ���� �켱���� ������ pop
                postfix[j++] = ' ';
            }
            pushChar(&opStack, token);  // ���� ������ push
        }

        i++;  // ���� ���ڷ� �̵�
    }

    // (5) ���ÿ� ���� ������ ��� postfix�� �ű�
    while (!isEmptyChar(&opStack)) {
        postfix[j++] = popChar(&opStack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';  // ���ڿ� ����
}

// ----------------------------------------------------------------
// ���� ǥ����(Postfix)�� ����ϴ� �Լ�
// - �Է�: ���� ǥ���� ���ڿ� (��: "20 3 + 4 * 9 +")
// - ���: ��� ��� (����)
// ----------------------------------------------------------------
int evaluatePostfix(const char* postfix) {
    IntStack s;
    initIntStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        // (1) ������ ���: ������ ��ȯ�Ͽ� push
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');  // ���ڿ� �� ����
            }
            pushInt(&s, num);  // ���� ���ÿ� push
        }
        // (2) �������� ���: �� ���� pop �� ���
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            int b = popInt(&s);  // �� ��° �ǿ�����
            int a = popInt(&s);  // ù ��° �ǿ�����
            switch (postfix[i]) {
            case '+': pushInt(&s, a + b); break;
            case '-': pushInt(&s, a - b); break;
            case '*': pushInt(&s, a * b); break;
            case '/': pushInt(&s, a / b); break; // ���� ������
            }
            i++;  // ������ ���� ���ڷ�
        }
        else {
            i++;  // ���� �� ������ ���ڴ� �ѱ�
        }
    }

    return popInt(&s);  // ���� ��� ��ȯ
}

// ----------------------------------------------------------------
// ���� �Լ�: ����ڷκ��� �Է� �ް�, ������ ��ȯ �� ��� ����
// ----------------------------------------------------------------
int main() {
    char infix[MAX];     // ���� ǥ���� �Է¿�
    char postfix[MAX];   // ��ȯ�� ���� ǥ���� �����

    // ����� �Է� �ޱ�
    printf("Infix ���� �Է��ϼ��� (��: (20+3)*4+9) : ");
    fgets(infix, MAX, stdin);  // ǥ�� �Է����� ���ڿ� �б�

    // ���ڿ� �� ���� ���� ����
    infix[strcspn(infix, "\n")] = '\0';

    // (1) ���� �� ���� ��ȯ
    infixToPostfix(infix, postfix);
    printf("Postfix ��ȯ ���: %s\n", postfix);

    // (2) ������ ���
    int result = evaluatePostfix(postfix);
    printf("Postfix ��� ���: %d\n", result);

    return 0;
}