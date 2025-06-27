/*
    프로그램 목적: 이 프로그램은 C로 작성된 단일 연결 리스트의 삽입, 삭제, 검색, 출력 기능을 시연합니다.
    작성자: [당신의 이름]
    작성일: 2023-10-XX
    버전: 1.0
    참고: _CRT_SECURE_NO_WARNINGS 매크로는 Visual Studio에서 보안 관련 경고를 무시하기 위해 사용됩니다.
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 보안 경고를 비활성화하기 위한 매크로

// stdio.h: 입력 및 출력 함수 사용을 위함
// stdlib.h: 동적 메모리 할당 함수 사용을 위함
#include <stdio.h>
#include <stdlib.h>

/*
    "element"는 int형의 별칭(alias)입니다.
    만약 데이터 타입을 추후 변경하고자 할 경우 이 부분만 수정하면 됩니다.
*/
typedef int element;

/*
    노드 구조체(ListNode) 정의:
    - 데이터(data): 노드에 저장된 값
    - 링크(link): 다음 노드를 가리키는 포인터
*/
typedef struct ListNode {
    element data;           // 노드의 데이터 값을 저장
    struct ListNode* link;  // 다음 노드의 주소를 저장
} ListNode;

/*
    연결 리스트 구조체(LinkedList) 정의:
    - head: 리스트의 첫 번째 노드를 가리키는 포인터
    모든 연결 리스트 연산은 이 구조체를 통해 이루어집니다.
*/
typedef struct LinkedList {
    ListNode* head;         // 리스트의 시작 노드를 가리키는 포인터
} LinkedList;

/*
    함수: insert_first
    역할: 연결 리스트의 첫번째 위치에 새로운 노드를 삽입합니다.
*/
void insert_first(LinkedList* list, element data) {
    // 새로운 노드를 위한 동적 메모리 할당 및 할당 실패 검사
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    p->data = data;        // 새로운 노드에 데이터 값 저장
    p->link = list->head;  // 새로운 노드의 링크가 기존의 첫 노드를 가리키도록 설정
    list->head = p;        // 리스트의 헤드 포인터를 새로운 노드로 업데이트
}

/*
    함수: insert_last
    역할: 연결 리스트의 마지막 위치에 새로운 노드를 삽입합니다.
*/
void insert_last(LinkedList* list, element data) {
    // 새로운 노드를 위한 동적 메모리 할당 및 할당 실패 검사
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    p->data = data; // 새로운 노드에 데이터 값 저장
    p->link = NULL; // 마지막 노드이므로 링크는 NULL로 설정

    // 리스트가 비어있는 경우, 새로운 노드가 첫 번째 노드가 됩니다.
    if (list->head == NULL) {
        list->head = p;
        return;
    }

    // 리스트가 비어있지 않을 경우, 마지막 노드를 찾을 때까지 탐색
    ListNode* temp = list->head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = p; // 기존 마지막 노드의 링크를 새로운 노드를 가리키도록 설정
}

/*
    함수: delete_first
    역할: 연결 리스트의 첫번째 노드(헤드)를 삭제합니다.
*/
void delete_first(LinkedList* list) {
    // 리스트가 비어 있는지 확인
    if (list->head == NULL) {
        printf("No element in the list!\n");
        return;
    }

    // 기존의 첫 노드를 임시 포인터에 저장
    ListNode* temp = list->head;
    list->head = temp->link; // 헤드 포인터를 두 번째 노드로 업데이트
    free(temp);  // 기존 첫 노드의 메모리 해제
}

/*
    함수: delete_last
    역할: 연결 리스트의 마지막 노드를 삭제합니다.
*/
void delete_last(LinkedList* list) {
    // 리스트가 비어 있을 경우 처리
    if (list->head == NULL) {
        printf("No element in the list!\n");
        return;
    }

    // 노드가 하나만 존재하는 경우
    if (list->head->link == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }

    // 여러 개의 노드가 존재하는 경우, 마지막 노드의 바로 전 노드를 찾기 위함
    ListNode* temp = list->head;
    while (temp->link->link != NULL) {
        temp = temp->link;
    }
    free(temp->link);   // 마지막 노드 메모리 해제
    temp->link = NULL;  // 마지막 노드 이후가 없음을 표시
}

/*
    함수: search
    역할: 연결 리스트에서 주어진 target 값과 일치하는 첫 번째 노드를 검색합니다.
*/
void search(LinkedList* list, element target) {
    ListNode* temp = list->head;  // 리스트 탐색을 위한 임시 포인터
    int position = 1;             // 노드의 위치를 기록하는 변수

    // 리스트의 각 노드를 순차적으로 탐색
    while (temp != NULL) {
        if (temp->data == target) {
            printf("데이터 %d은(는) %d번째 위치에 있습니다.\n", target, position);
            return;
        }
        temp = temp->link;  // 다음 노드로 이동
        position++;         // 노드 위치 증가
    }

    // target 데이터가 리스트에 존재하지 않는 경우
    printf("데이터 %d을(를) 찾을 수 없습니다.\n", target);
}

/*
    함수: print_list
    역할: 연결 리스트의 모든 노드를 순차적으로 출력합니다.
*/
void print_list(LinkedList* list) {
    ListNode* temp = list->head;  // 리스트 탐색을 위한 임시 포인터
    // 리스트의 모든 노드를 순차적으로 출력
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;  // 다음 노드로 이동
    }
    printf("NULL\n");  // 리스트의 끝을 표시
}

/*
    메인 함수: 모든 연결 리스트 기능(삽입, 삭제, 출력 및 검색)을 데모합니다.
*/
int main() {
    // 빈 연결 리스트 생성 (헤드 포인터를 NULL로 초기화)
    LinkedList list;
    list.head = NULL;

    // 첫 노드 삽입: 리스트의 앞쪽에 새 노드를 삽입합니다.
    insert_first(&list, 30);
    insert_first(&list, 20);
    insert_first(&list, 10);
    // 마지막 노드 삽입: 리스트의 끝에 새 노드를 삽입합니다.
    insert_last(&list, 40);
    insert_last(&list, 50);
    insert_last(&list, 60);

    // 현재 리스트 출력
    print_list(&list);

    // 첫 노드 삭제 후 리스트 출력
    delete_first(&list);
    print_list(&list);

    // 마지막 노드 2개 삭제 후 리스트 출력
    delete_last(&list);
    delete_last(&list);
    print_list(&list);

    // 특정 값 40을 검색하여 위치 출력
    search(&list, 40);

    return 0;  // 프로그램 정상 종료
}