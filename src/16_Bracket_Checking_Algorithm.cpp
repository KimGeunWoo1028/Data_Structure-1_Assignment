#define _CRT_SECURE_NO_WARNINGS  // 안전하지 않은 함수 사용에 대한 경고를 비활성화합니다.
#include <stdio.h>     // 표준 입출력 함수들을 포함합니다.
#include <stdlib.h>    // 동적 메모리 할당 및 프로그램 종료 함수들을 포함합니다.
#include <string.h>    // 문자열 처리 함수들을 포함합니다.

// StackNode 구조체: 스택의 각 노드는 하나의 괄호 문자를 저장하며, 다음 노드를 가리키는 포인터를 가집니다.
typedef struct StackNode {
    char data;               // 괄호 문자 데이터를 저장합니다.
    struct StackNode* next;  // 다음 노드를 가리키는 포인터입니다.
} StackNode;

// Stack 구조체: 스택 자체를 나타내며, 최상위 노드를 가리키는 포인터를 포함합니다.
typedef struct {
    StackNode* top;          // 스택의 최상위 노드를 가리킵니다.
} Stack;

// create 함수: 새로운 빈 스택을 생성하여 반환합니다.
Stack* create()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));  // 스택을 위한 메모리를 할당합니다.
    if (!stack) {
        return NULL;   // 메모리 할당 실패 시 NULL을 반환합니다.
    }
    stack->top = NULL; // 스택이 비어있음을 나타내기 위해 최상위 포인터를 NULL로 초기화합니다.
    return stack;
}

// isEmpty 함수: 스택이 비어있는지 확인합니다.
// 스택이 비어있으면 참을 반환합니다.
int isEmpty(Stack* stack)
{
    return stack->top == NULL;   // 스택의 최상위 포인터가 NULL이면 스택이 비어 있음을 의미합니다.
}

// push 함수: 주어진 괄호 문자를 스택의 최상위에 추가합니다.
void push(Stack* stack, char expr)
{
    StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));  // 새 노드를 위한 메모리를 할당합니다.
    if (!newnode) {
        exit(1);  // 메모리 할당 실패 시 프로그램을 종료합니다.
    }
    newnode->data = expr;         // 새 노드에 문자 데이터를 저장합니다.
    newnode->next = stack->top;   // 새 노드의 다음 포인터가 현재 스택의 최상위 노드를 가리킵니다.
    stack->top = newnode;         // 스택의 최상위 노드를 새 노드로 업데이트합니다.
}

// pop 함수: 스택의 최상위 요소를 제거하고 그 값을 반환합니다.
char pop(Stack* stack) {
    StackNode* temp = stack->top;  // 현재 최상위 노드를 임시 변수에 저장합니다.
    char popped_data = temp->data;   // 최상위 노드의 문자 데이터를 가져옵니다.
    stack->top = temp->next;         // 스택의 최상위 포인터를 다음 노드로 업데이트합니다.
    free(temp);                      // 제거된 노드의 메모리를 해제합니다.
    return popped_data;              // 제거된 문자 데이터를 반환합니다.
}

// PairCheck 함수: 제공된 여는 괄호와 닫는 괄호가 올바르게 대응하는지 확인합니다.
// 올바른 쌍이면 1을, 아니면 0을 반환합니다.
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

// MatchCheck 함수: 문자열 내에 있는 괄호들이 올바르게 매칭되어 있는지 검사합니다.
// 반환값:
//  1 : 모든 괄호가 올바르게 매칭된 경우
//  2 : 열렸으나 닫히지 않은 괄호가 있는 경우
//  3 : 닫혔으나 매칭되는 여는 괄호가 없는 경우
//  4 : 괄호의 중첩 관계가 잘못된 경우
int MatchCheck(const char* expr)
{
    Stack* stack = create();        // 괄호 처리를 위한 빈 스택을 생성합니다.
    int len = strlen(expr);         // 입력된 수식의 길이를 구합니다.
    int i;
    char popped_char;
    int result = 1;                 // 기본 결과값을 1로 설정 (정상적으로 매칭된 경우)

    // 수식의 모든 문자를 순차적으로 확인합니다.
    for (i = 0; i < len; i++) {
        // 여는 괄호인 경우 스택에 추가합니다.
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            push(stack, expr[i]);
        }
        // 닫는 괄호인 경우 처리합니다.
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']')
        {
            // 스택이 비어있다면 대응하는 여는 괄호가 없으므로 결과값을 3으로 설정합니다.
            if (isEmpty(stack)) {
                result = 3;
                break;
            }
            else {
                // 스택에서 가장 마지막의 여는 괄호를 제거하고 매칭 여부를 확인합니다.
                popped_char = pop(stack);
                if (!PairCheck(popped_char, expr[i])) {
                    result = 4;  // 괄호의 중첩(포함관계)가 잘못된 경우 결과값을 4로 설정합니다.
                    break;
                }
            }
        }
    }
    // 수식 전체를 분석한 후, 스택에 남아있는 여는 괄호가 있다면 닫히지 않은 경우입니다.
    if (result == 1) {
        if (!isEmpty(stack))
            result = 2;
    }

    // 최종 분석 결과를 반환합니다.
    return result;
}

// main 함수: 사용자로부터 수식을 입력받아 괄호 매칭 여부를 검사한 후 결과를 출력합니다.
int main()
{
    char MathExpr[300];  // 최대 300문자까지 입력할 수 있는 수식 배열입니다.
    printf("수식 입력 : ");  // 사용자에게 수식 입력을 요청합니다.

    scanf("%s", MathExpr);  // 사용자가 입력한 수식을 MathExpr 배열에 저장합니다.
    printf("입력받은 수식 : %s\n", MathExpr);  // 입력받은 수식을 출력합니다.

    // 입력된 수식의 괄호 분석을 수행합니다.
    int check_result = MatchCheck(MathExpr);

    // 괄호 분석 결과에 따라 출력 문구를 결정합니다.
    printf("괄호 분석\n");
    switch (check_result)
    {
    case 1:
        // 모든 괄호가 올바르게 매칭된 경우
        printf("3-1. 괄호 사용이 정상적인 경우");
        break;
    case 2:
        // 여는 괄호는 있으나 닫히지 않은 경우
        printf("3-2. 열렸는데 닫히지 않은 경우");
        break;
    case 3:
        // 닫는 괄호만 존재하는 잘못된 경우
        printf("3-3. 열리지 않았는데 닫힌 경우");
        break;
    case 4:
        // 괄호가 올바른 포함관계를 갖지 못한 경우
        printf("3-4. 소,중,대 괄호사이의 포함관계가 잘못된 경우");
        break;
    }
    return 0;  // 프로그램 종료
}