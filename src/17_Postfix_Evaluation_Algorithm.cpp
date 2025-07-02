#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100  // 최대 입력 길이

// -------------------------
// 스택 구조체 정의 (문자용)
// -------------------------
typedef struct {
    char data[MAX];  // 문자 데이터를 저장할 배열
    int top;         // 스택의 최상단 인덱스
} CharStack;

// -------------------------
// 스택 구조체 정의 (정수용)
// -------------------------
typedef struct {
    int data[MAX];  // 정수 데이터를 저장할 배열
    int top;        // 스택의 최상단 인덱스
} IntStack;

// -------------------------
// 문자 스택 관련 함수
// -------------------------
void initCharStack(CharStack* s) { s->top = -1; }           // 초기화
int isEmptyChar(CharStack* s) { return s->top == -1; }      // 비어 있는지 확인
void pushChar(CharStack* s, char c) { s->data[++(s->top)] = c; }  // 푸시
char popChar(CharStack* s) { return s->data[(s->top)--]; }       // 팝
char peekChar(CharStack* s) { return s->data[s->top]; }          // 최상단 값 조회

// -------------------------
// 정수 스택 관련 함수
// -------------------------
void initIntStack(IntStack* s) { s->top = -1; }               // 초기화
int isEmptyInt(IntStack* s) { return s->top == -1; }          // 비어 있는지 확인
void pushInt(IntStack* s, int v) { s->data[++(s->top)] = v; } // 푸시
int popInt(IntStack* s) { return s->data[(s->top)--]; }       // 팝

// -------------------------
// 연산자 우선순위 반환 함수
// -------------------------
int precedence(char op) {
    if (op == '*' || op == '/') return 2;  // 곱셈/나눗셈 우선순위: 2
    if (op == '+' || op == '-') return 1;  // 덧셈/뺄셈 우선순위: 1
    return 0;                              // 그 외는 우선순위 없음
}

// ----------------------------------------------------------------
// 중위 표현식을 후위 표현식(Postfix)으로 변환하는 함수
// - 입력: 문자열로 된 중위식 (예: "(20+3)*4+9")
// - 출력: 후위식 문자열로 저장 (예: "20 3 + 4 * 9 +")
// ----------------------------------------------------------------
void infixToPostfix(const char* infix, char* postfix) {
    CharStack opStack;           // 연산자 스택 선언
    initCharStack(&opStack);     // 스택 초기화
    int i = 0, j = 0;            // i: infix 탐색 인덱스, j: postfix 저장 인덱스
    char token;

    while (infix[i] != '\0') {
        token = infix[i];

        // (1) 숫자인 경우 (연속된 숫자 처리)
        if (isdigit(token)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];  // 연속된 숫자를 복사
            }
            postfix[j++] = ' ';  // 숫자 구분을 위한 공백 추가
            continue;            // 다음 루프로 넘어감 (i는 위에서 증가됨)
        }

        // (2) 왼쪽 괄호: 무조건 스택에 push
        if (token == '(') {
            pushChar(&opStack, token);
        }

        // (3) 오른쪽 괄호: '('가 나올 때까지 pop
        else if (token == ')') {
            while (!isEmptyChar(&opStack) && peekChar(&opStack) != '(') {
                postfix[j++] = popChar(&opStack);  // 연산자를 postfix에 저장
                postfix[j++] = ' ';
            }
            popChar(&opStack); // '(' 제거
        }

        // (4) 연산자일 경우: 우선순위에 따라 pop/push
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!isEmptyChar(&opStack) && precedence(peekChar(&opStack)) >= precedence(token)) {
                postfix[j++] = popChar(&opStack);  // 더 높은 우선순위 연산자 pop
                postfix[j++] = ' ';
            }
            pushChar(&opStack, token);  // 현재 연산자 push
        }

        i++;  // 다음 문자로 이동
    }

    // (5) 스택에 남은 연산자 모두 postfix로 옮김
    while (!isEmptyChar(&opStack)) {
        postfix[j++] = popChar(&opStack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';  // 문자열 종료
}

// ----------------------------------------------------------------
// 후위 표현식(Postfix)을 계산하는 함수
// - 입력: 후위 표현식 문자열 (예: "20 3 + 4 * 9 +")
// - 출력: 계산 결과 (정수)
// ----------------------------------------------------------------
int evaluatePostfix(const char* postfix) {
    IntStack s;
    initIntStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        // (1) 숫자인 경우: 정수로 변환하여 push
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');  // 문자열 → 정수
            }
            pushInt(&s, num);  // 숫자 스택에 push
        }
        // (2) 연산자인 경우: 두 숫자 pop 후 계산
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            int b = popInt(&s);  // 두 번째 피연산자
            int a = popInt(&s);  // 첫 번째 피연산자
            switch (postfix[i]) {
            case '+': pushInt(&s, a + b); break;
            case '-': pushInt(&s, a - b); break;
            case '*': pushInt(&s, a * b); break;
            case '/': pushInt(&s, a / b); break; // 정수 나눗셈
            }
            i++;  // 연산자 다음 문자로
        }
        else {
            i++;  // 공백 등 무시할 문자는 넘김
        }
    }

    return popInt(&s);  // 최종 결과 반환
}

// ----------------------------------------------------------------
// 메인 함수: 사용자로부터 입력 받고, 후위식 변환 및 계산 수행
// ----------------------------------------------------------------
int main() {
    char infix[MAX];     // 중위 표현식 입력용
    char postfix[MAX];   // 변환된 후위 표현식 저장용

    // 사용자 입력 받기
    printf("Infix 식을 입력하세요 (예: (20+3)*4+9) : ");
    fgets(infix, MAX, stdin);  // 표준 입력으로 문자열 읽기

    // 문자열 끝 개행 문자 제거
    infix[strcspn(infix, "\n")] = '\0';

    // (1) 중위 → 후위 변환
    infixToPostfix(infix, postfix);
    printf("Postfix 변환 결과: %s\n", postfix);

    // (2) 후위식 계산
    int result = evaluatePostfix(postfix);
    printf("Postfix 계산 결과: %d\n", result);

    return 0;
}