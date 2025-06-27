/*
  파일: linked_list_operations.c
  설명: 이 프로그램은 단일 연결 리스트를 구현하여 특정 위치에 노드를 삽입, 삭제하고,
         특정 값을 가진 노드 뒤에 새로운 노드를 삽입하며, 리스트 전체를 출력하는 예제를 보여줍니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 노드에 저장될 데이터 타입 정의
typedef int element;

// 연결 리스트의 노드 구조체 정의
typedef struct ListNode {
    element data;              // 노드에 저장된 데이터
    struct ListNode* link;     // 다음 노드를 가리키는 포인터
} ListNode;

/*
  함수: insert_position
  목적: 지정된 위치에 새로운 노드를 삽입하는 함수.
  매개변수:
    head - 연결 리스트의 헤드 포인터.
    position - 새로운 노드를 삽입할 위치 (1부터 시작하는 인덱스).
    value - 새로운 노드에 저장할 데이터 값.
  반환값:
    갱신된 연결 리스트의 헤드 포인터.
*/
ListNode* insert_position(ListNode* head, int position, element value) {
    int k = 1;                // 현재 위치 카운터
    ListNode* p = NULL;       // 리스트 순회를 위한 포인터
    ListNode* q = NULL;       // 삽입 위치의 이전 노드를 가리키는 포인터

    // 새 노드를 위한 메모리 할당
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        return head;
    }
    newNode->data = value;    // 새 노드에 데이터 저장
    newNode->link = NULL;     // 초기에는 다음 노드가 없으므로 NULL

    p = head;  // 리스트의 시작점 설정

    // 경우 1: 리스트의 시작에 노드 추가 (position == 1)
    if (position == 1) {
        newNode->link = p;    // 새 노드 다음 링크가 기존 헤드를 가리킴
        head = newNode;       // 헤드를 새로운 노드로 업데이트
    }
    else {
        // 지정된 위치까지 리스트를 순회
        while ((p != NULL) && (k < position)) {
            k++;              // 위치 카운터 증가
            q = p;            // 이전 노드 저장
            p = p->link;      // 다음 노드로 이동
        }
        // 경우 2: 리스트의 끝에 삽입 (position이 리스트 크기보다 큼)
        if (p == NULL) {
            q->link = newNode;
            newNode->link = NULL;
        }
        // 경우 3: 리스트 중간에 삽입
        else {
            q->link = newNode;
            newNode->link = p;
        }
    }
    return head;  // 업데이트된 헤드 반환
}

/*
  함수: delete_position
  목적: 지정된 위치의 노드를 삭제하는 함수.
  매개변수:
    head - 연결 리스트의 헤드 포인터.
    position - 삭제할 노드의 위치 (1부터 시작하는 인덱스).
  반환값:
    갱신된 연결 리스트의 헤드 포인터.
*/
ListNode* delete_position(ListNode* head, int position) {
    ListNode* p = head;  // 삭제할 노드를 가리키는 포인터
    ListNode* q = NULL;  // 삭제 전의 이전 노드를 가리키는 포인터
    int k = 1;           // 현재 위치 카운터

    // 리스트가 비어있는 경우
    if (head == NULL) {
        printf("리스트가 비어 있음.\n");
        return head;
    }

    // 경우 1: 첫 번째 노드를 삭제하는 경우
    if (position == 1) {
        head = p->link;  // 헤드를 다음 노드로 업데이트
        free(p);         // 삭제되는 노드의 메모리 해제
        return head;
    }
    else {
        // 지정된 위치까지 리스트를 순회
        while ((p != NULL) && (k < position)) {
            k++;
            q = p;         // 현재 노드를 이전 노드로 저장
            p = p->link;   // 다음 노드로 이동
        }
        // 지정된 위치가 리스트 범위를 벗어날 경우
        if (p == NULL) {
            printf("삭제할 위치가 리스트 범위를 벗어남.\n");
            return head;
        }
        else {
            // 삭제할 노드를 리스트에서 제외시키기 위해 포인터 연결 수정
            q->link = p->link;
            free(p);   // 삭제되는 노드의 메모리 해제
            return head;
        }
    }
}

/*
  함수: insert_after
  목적: 특정 값을 가진 노드 뒤에 새로운 노드를 삽입하는 함수.
  매개변수:
    head - 연결 리스트의 헤드 포인터.
    after - 새로운 노드를 삽입할 기준이 되는 값.
    value - 새로운 노드에 저장할 데이터 값.
  반환값:
    업데이트된 연결 리스트의 헤드 포인터.
*/
ListNode* insert_after(ListNode* head, int after, element value) {
    ListNode* p = head;
    // 리스트를 순회하며 노드의 데이터가 기준 값과 일치하는지 확인
    while (p != NULL) {
        if (p->data == after) {
            // 기준 값을 찾으면, 새 노드를 위한 메모리 할당
            ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
            newnode->data = value;     // 새 노드에 데이터 저장
            newnode->link = p->link;     // 새 노드가 다음 노드를 가리킴
            p->link = newnode;           // 기준 노드 뒤에 새 노드 삽입
            return head;
        }
        p = p->link;
    }
    // 기준 값이 리스트에 없을 경우 메시지 출력
    printf("값 %d가 리스트 안에 없음.\n", after);
    return head;
}

/*
  함수: print_list
  목적: 연결 리스트에 저장된 모든 노드의 데이터를 출력하는 함수.
  매개변수:
    head - 연결 리스트의 헤드 포인터.
  반환값:
    없음.
*/
void print_list(ListNode* head) {
    ListNode* p = head;
    // 리스트의 모든 노드를 순회하면서 데이터를 출력
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");  // 리스트의 끝을 표시
}

/*
  함수: main
  목적: 연결 리스트의 삽입, 삭제, 출력 작업을 시연하는 메인 함수.
*/
int main() {
    ListNode* head = NULL;  // 빈 리스트로 시작

    // insert_position 함수를 사용하여 특정 위치에 노드 삽입
    head = insert_position(head, 1, 10); // 리스트: 10
    head = insert_position(head, 1, 20); // 리스트: 20 -> 10
    head = insert_position(head, 3, 30); // 리스트: 20 -> 10 -> 30
    head = insert_position(head, 2, 40); // 리스트: 20 -> 40 -> 10 -> 30

    // insert_after 함수를 사용하여 값 30인 노드 뒤에 값 35를 가진 노드 삽입
    head = insert_after(head, 30, 35);   // 리스트: 20 -> 40 -> 10 -> 30 -> 35
    print_list(head);  // 출력: 20 -> 40 -> 10 -> 30 -> 35 -> NULL

    // delete_position 함수를 사용하여 3번째 위치의 노드 삭제
    head = delete_position(head, 3);     // 리스트: 20 -> 40 -> 30 -> 35
    print_list(head);

    // delete_position 함수를 사용하여 마지막 위치(4번째)의 노드 삭제
    head = delete_position(head, 4);     // 리스트: 20 -> 40 -> 30
    print_list(head);

    // delete_position 함수를 사용하여 첫 번째 노드 삭제
    head = delete_position(head, 1);     // 리스트: 40 -> 30
    print_list(head);

    return 0;
}