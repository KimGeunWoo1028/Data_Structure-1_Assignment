#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 정수형 데이터를 다루기 위해 element를 int로 정의 */
typedef int element;

/* 원형 연결 리스트의 노드 구조체 정의 */
typedef struct Listnode {
    element data;         // 노드가 저장할 데이터 값
    struct Listnode* link; // 다음 노드를 가리키는 포인터
} Listnode;

/* 첫 번째 노드 삽입 함수
   원형 리스트에서 head->link가 실제 첫 번째 노드를 가리키도록 함 */
Listnode* insert_first(Listnode* head, element data)
{
    // 새 노드를 위한 메모리 할당 및 데이터 저장
    Listnode* node = (Listnode*)malloc(sizeof(Listnode));
    node->data = data;

    if (head == NULL) {  // 리스트가 비어있는 경우
        head = node;         // head에 새 노드 지정 (유일한 노드임)
        node->link = head;   // 자기 자신을 가리켜 원형 구조 형성
    }
    else {  // 리스트에 이미 노드가 존재하는 경우
        node->link = head->link; // 새 노드의 다음 포인터가 기존 첫 노드를 가리킴
        head->link = node;       // head는 그대로 유지, 그 다음 노드가 새 노드로 변경됨
    }
    return head;  // head는 변경되지 않거나, 단일 노드일 경우 그대로 반환
}

/* 마지막 노드(꼬리) 삽입 함수
   head를 꼬리 노드를 가리키게 하며, 새 노드는 head 다음에 삽입됨 */
Listnode* insert_last(Listnode* head, element data)
{
    // 새 노드를 위한 동적 메모리 할당 및 데이터 저장
    Listnode* node = (Listnode*)malloc(sizeof(Listnode));
    node->data = data;

    if (head == NULL) {  // 리스트가 비어있는 경우
        head = node;       // head에 새 노드 지정
        node->link = head; // 자기 자신을 가리키게 하여 원형 리스트 구성
    }
    else {  // 리스트에 노드가 이미 존재하는 경우
        node->link = head->link; // 새 노드가 첫 노드를 가리키도록 함
        head->link = node;       // 기존 tail(head)의 다음 노드로 새 노드 연결
        head = node;             // head를 새 노드(새로운 꼬리)로 갱신
    }
    return head;  // 갱신된 head (꼬리) 반환
}

/* 첫 번째 실제 노드 삭제 함수 */
Listnode* delete_first(Listnode* head)
{
    // 리스트가 비어있으면 삭제할 노드도 없음
    if (head == NULL)
        return NULL;

    // 삭제할 노드(del)는 head->link로 첫 번째 노드를 가리킴
    Listnode* del = head->link;

    // 리스트에 단 하나의 노드가 있는 경우
    if (head == del) {
        free(del); // 유일한 노드 메모리 해제
        return NULL; // 빈 리스트 반환
    }

    // 첫 번째 노드를 건너뛰도록 head->link를 변경 (두 번째 노드가 첫 번째 노드가 됨)
    head->link = del->link;
    free(del); // 삭제 노드의 메모리 해제
    return head; // head(꼬리)는 그대로 반환
}

/* 마지막 노드(꼬리)를 삭제하는 함수 */
Listnode* delete_last(Listnode* head)
{
    // 리스트가 비어있으면 삭제할 노드가 없음
    if (head == NULL)
        return NULL;

    // 첫 번째 노드를 가리키는 포인터
    Listnode* first = head->link;

    // 리스트에 단 하나의 노드인 경우
    if (head == first) {
        free(head); // 유일한 노드 메모리 해제
        return NULL; // 빈 리스트 반환
    }

    // 마지막 노드의 바로 앞 노드를 찾기 위해 포인터 next 사용
    Listnode* next = first;
    while (next->link != head) {
        next = next->link; // next가 tail의 전 노드로 이동
    }
    // next가 새 꼬리가 됨: next의 link를 first(첫 번째 노드)로 연결하여 원형 유지
    next->link = first;
    free(head); // 기존 tail인 head의 메모리 해제
    head = next; // head를 새 꼬리로 갱신
    return head; // 갱신된 head 반환
}

/* 1부터 12까지의 값을 가지는 시계 리스트 생성 함수 */
Listnode* clock_list() {
    Listnode* clock_head = NULL; // 시계 리스트의 시작 노드(첫번째 노드)
    Listnode* clock_tail = NULL; // 시계 리스트의 꼬리 노드

    // 1부터 12까지 반복하여 각 시간 노드 생성
    for (int i = 1; i <= 12; i++) {
        // 새로운 노드 동적 메모리 할당 후 데이터 저장
        Listnode* clock_node = (Listnode*)malloc(sizeof(Listnode));
        clock_node->data = i;
        clock_node->link = NULL; // 초기에는 다음 노드를 NULL로 설정

        if (clock_head == NULL) { // 첫 번째 노드인 경우
            clock_head = clock_node; // 시작 노드 지정
        }
        else { // 두 번째 이후 노드일 경우
            clock_tail->link = clock_node; // 이전 꼬리 노드의 link를 새 노드로 연결
        }
        clock_tail = clock_node; // 꼬리 노드를 현재 노드로 갱신
    }
    // 마지막 노드의 link가 첫 번째 노드를 가리켜 원형 연결 리스트 완성
    clock_tail->link = clock_head;
    return clock_tail; // tail을 반환 (이 디자인에서는 tail이 리스트 전체를 나타냄)
}

/* 주어진 현재 시간(n1)부터 n2만큼 이동한 노드의 데이터 반환 함수 */
int get_time(Listnode* head, int n1, int n2)
{
    // 원형 리스트의 실제 첫 번째 노드 (head->link)에서 시작
    Listnode* p = head->link;

    // 먼저 현재 시간 n1을 가진 노드를 찾음
    while (p->data != n1) {
        p = p->link;
    }
    // 찾은 노드에서 n2번 이동 (원형 리스트에서 순환)
    for (int i = 0; i < n2; i++) {
        p = p->link;
    }
    return p->data; // 최종적으로 도달한 노드의 데이터를 반환
}

/* 원형 리스트 전체를 출력하는 함수 */
void print_list(Listnode* head)
{
    if (head == NULL) {  // 리스트가 비어있는 경우
        printf("리스트가 비어있음\n");
        return;
    }

    // 실제 첫 번째 노드(head->link)에서 시작하여 원형 리스트 순회
    Listnode* p = head->link;
    do {
        printf("%d -> ", p->data); // 노드 데이터 출력 후 화살표 표시
        p = p->link;
    } while (p != head->link); // 시작 노드로 다시 돌아오면 순회 종료
    printf("(원형 리스트로 연결됨)\n\n");
}

int main()
{
    /* 리스트 테스트를 위한 변수 선언 */
    Listnode* head = NULL;

    // insert_first와 insert_last를 이용하여 리스트에 노드 삽입
    head = insert_first(head, 20); // 리스트에 20 삽입 (첫번째 삽입이므로 유일 노드)
    head = insert_first(head, 10); // 10을 첫 노드로 삽입
    head = insert_last(head, 30);  // 30을 마지막 노드로 삽입
    head = insert_last(head, 40);  // 40을 마지막 노드로 삽입
    head = insert_last(head, 50);  // 50을 마지막 노드로 삽입
    printf("초기 리스트 출력:\n");
    print_list(head);

    // 첫 번째 노드 삭제 후 결과 출력
    head = delete_first(head);
    printf("첫 번째 노드 삭제 후 리스트 출력:\n");
    print_list(head);

    // 마지막 노드 삭제 후 결과 출력
    head = delete_last(head);
    printf("마지막 노드 삭제 후 리스트 출력:\n");
    print_list(head);

    // 시계 리스트 생성 후 출력 (1부터 12까지 시계 형태)
    Listnode* clock_tail = clock_list();
    printf("시계 리스트 출력 (1~12):\n");
    print_list(clock_tail);

    int n1, n2;

    // 사용자에게 현재 시간과 몇 시간 후인지를 입력 받아 계산하는 루프
    while (true)
    {
        printf("현재 시간을 입력하세요 (1~12, 종료하려면 0 입력): ");
        scanf("%d", &n1);

        // 0 입력 시 종료
        if (n1 == 0)
            break;

        printf("몇 시간 후인지 입력하세요: ");
        scanf("%d", &n2);

        // get_time 함수를 사용하여 n1부터 n2만큼 이동한 노드의 시간 계산
        int newTime = get_time(clock_tail, n1, n2);
        printf("계산된 시간: %d\n\n", newTime);
    }

    return 0;
}