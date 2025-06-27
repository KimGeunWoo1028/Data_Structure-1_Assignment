/* 프로그램 설명:
 * 이 프로그램은 단순 연결 리스트(linked list)를 구현합니다.
 * 두 개의 연결 리스트(list1, list2)를 생성하고, 각각
 * insert_first와 insert_last 함수를 사용하여 노드를 추가한 후,
 * 결과를 출력합니다.
 */

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 안전하지 않은 함수 경고를 무시

#include <stdio.h>   // 표준 입출력 함수들을 사용하기 위한 라이브러리
#include <stdlib.h>  // 동적 메모리 할당 함수들을 사용하기 위한 라이브러리

 // ListNode 구조체: 연결 리스트의 각 노드를 표현합니다.
typedef struct ListNode
{
    int element;                // 노드의 데이터 (정수형)
    struct ListNode* link;      // 다음 노드를 가리키는 포인터
} ListNode;

// linkedlist 구조체: 연결 리스트의 시작(헤드) 노드를 저장합니다.
typedef struct linkedlist
{
    ListNode* head;             // 리스트의 첫 번째 노드를 가리키는 포인터
} linkedlist;

// 함수: insert_first
// 목적: 연결 리스트의 시작 부분에 새로운 노드를 추가 (앞쪽에 삽입)하는 함수
// 매개변수: 
//   linkedlist* list  - 노드를 추가할 연결 리스트의 포인터
//   int data          - 추가할 데이터 값
void insert_first(linkedlist* list, int data)
{
    // 새로운 노드를 위한 동적 메모리 할당
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    // 새 노드의 데이터 초기화
    p->element = data;
    // 새 노드의 link를 현재의 head로 연결 (현재 연결 리스트 앞에 추가)
    p->link = list->head;
    // 리스트의 head를 새 노드로 갱신
    list->head = p;
}

// 함수: insert_last
// 목적: 연결 리스트의 끝 부분에 새로운 노드를 추가 (뒤쪽에 삽입)하는 함수
// 매개변수: 
//   linkedlist* list  - 노드를 추가할 연결 리스트의 포인터
//   int data          - 추가할 데이터 값
void insert_last(linkedlist* list, int data)
{
    // 새로운 노드를 위한 동적 메모리 할당
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    // 새 노드의 데이터 초기화
    p->element = data;
    // 새 노드의 link를 NULL로 설정 (리스트의 끝이므로)
    p->link = NULL;

    // 만약 리스트가 비어있다면 (head가 NULL인 경우)
    if (list->head == NULL)
    {
        // 새 노드를 리스트의 head로 지정 후 함수 종료
        list->head = p;
        return;
    }

    // 리스트가 비어있지 않다면, 마지막 노드를 찾기 위해 임시포인터 temp 선언
    ListNode* temp = list->head;
    // 마지막 노드까지 이동 (temp->link가 NULL이 될 때까지)
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    // 마지막 노드의 link를 새 노드로 연결
    temp->link = p;
}

// 함수: print_list
// 목적: 연결 리스트에 있는 모든 노드의 데이터를 순회하며 출력하는 함수
// 매개변수:
//   linkedlist* list  - 출력할 연결 리스트의 포인터
void print_list(linkedlist* list)
{
    // 리스트 순회를 위한 임시포인터 변수 temp 초기화
    ListNode* temp = list->head;
    // 리스트의 끝 (temp가 NULL)이 될 때까지 반복하면서 데이터 출력
    while (temp != NULL)
    {
        // 현재 노드의 데이터를 출력하고 "->" 기호 출력
        printf("%d -> ", temp->element);
        // 다음 노드로 이동
        temp = temp->link;
    }
    // 리스트 끝 출력 (NULL)
    printf("NULL\n");
}

// main 함수: 프로그램의 시작점
int main()
{
    // 두 개의 연결 리스트(list1, list2)를 선언하고, 빈 리스트로 초기화 (head = NULL)
    linkedlist list1, list2;
    list1.head = NULL;
    list2.head = NULL;

    // insert_first 함수를 이용하여 list1에 노드를 앞에 삽입 (역순으로 추가)
    printf("insert_first 출력 결과\n");
    insert_first(&list1, 50);  // 리스트의 앞쪽에 50 추가
    insert_first(&list1, 40);  // 리스트의 앞쪽에 40 추가
    insert_first(&list1, 30);  // 리스트의 앞쪽에 30 추가
    insert_first(&list1, 20);  // 리스트의 앞쪽에 20 추가
    insert_first(&list1, 10);  // 리스트의 앞쪽에 10 추가

    // list1의 모든 노드 데이터 출력
    print_list(&list1);

    // 줄바꿈 후 insert_last 함수를 이용하여 list2에 노드를 뒤에 삽입 (순서대로 추가)
    printf("\ninsert_last 출력 결과\n");
    insert_last(&list2, 10);  // 리스트의 마지막에 10 추가
    insert_last(&list2, 20);  // 리스트의 마지막에 20 추가
    insert_last(&list2, 30);  // 리스트의 마지막에 30 추가
    insert_last(&list2, 40);  // 리스트의 마지막에 40 추가
    insert_last(&list2, 50);  // 리스트의 마지막에 50 추가

    // list2의 모든 노드 데이터 출력
    print_list(&list2);

    // 프로그램 종료
    return 0;
}