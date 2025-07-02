#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS   // MSVC 환경에서 보안 경고를 무시하기 위한 매크로
#define SIZE 10000                // 배열과 연결 리스트의 총 요소 개수를 정의

// element 자료형을 int로 정의 (필요에 따라 다른 자료형 사용 가능)
typedef int element;

// 연결 리스트의 노드 구조체 정의
typedef struct listnode {
    element data;             // 노드가 저장하는 데이터
    struct listnode* next;    // 다음 노드를 가리키는 포인터
} listnode;

// ── 연결 리스트의 머리에 새 노드를 삽입하는 함수 ──
// 매개변수: 현재 리스트의 머리(head), 삽입할 값(value)
// 반환값: 새로 삽입한 노드가 연결된 새로운 리스트의 머리
listnode* insert_head(listnode* head, element value)
{
    // 새 노드를 위한 메모리 할당
    listnode* new_node = (listnode*)malloc(sizeof(listnode));
    // 새 노드에 데이터 저장
    new_node->data = value;
    // 새 노드의 next 포인터가 기존 리스트의 head를 가리키게 함 (삽입 위치: 리스트의 맨 앞)
    new_node->next = head;
    // 새 노드가 새로운 리스트의 머리 역할을 함
    return new_node;
}

// ── 연결 리스트의 모든 노드를 해제하는 함수 ──
// 매개변수: 해제할 리스트의 머리(head)
void freelist(listnode* head)
{
    listnode* temp; // 임시 포인터: 현재 해제할 노드를 저장
    // head가 NULL이 될 때까지 모든 노드의 메모리 해제
    while (head != NULL) {
        temp = head;           // 현재 head를 임시 저장
        head = head->next;     // head를 다음 노드로 이동
        free(temp);            // 임시 저장된 노드 메모리 해제
    }
}

// ── 연결 리스트에서 특정 인덱스의 값을 읽어오는 함수 ──
// 매개변수: 리스트의 머리(head), 읽어올 인덱스(index; 0부터 시작)
// 반환값: 해당 인덱스의 노드에 저장된 데이터
element get(listnode* head, int index)
{
    listnode* cur = head; // 탐색 시작 노드
    // 원하는 인덱스에 도달할 때까지 노드를 순차적으로 이동
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    // 해당 노드의 데이터를 반환
    return cur->data;
}

// ── 연결 리스트에서 특정 인덱스의 노드를 삭제하는 함수 ──
// 매개변수: 리스트의 머리(head), 삭제할 노드의 위치(index; 0부터 시작)
// 반환값: 삭제가 완료된 후의 리스트의 머리
listnode* delete_position(listnode* head, int index)
{
    // 삭제할 위치가 0이면, 리스트의 첫 번째 노드를 삭제
    if (index == 0) {
        listnode* temp = head;    // 삭제할 첫 번째 노드를 임시 저장
        head = head->next;        // head를 두 번째 노드로 업데이트
        free(temp);               // 원래의 첫 번째 노드 메모리 해제
        return head;
    }

    // 삭제할 노드의 바로 이전 노드까지 탐색
    listnode* cur = head;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->next;
    }

    // cur->next가 삭제할 노드를 가리킴
    listnode* temp = cur->next;
    if (temp) {
        // 삭제할 노드를 리스트에서 제외하고, 연결을 재설정
        cur->next = temp->next;
        free(temp); // 삭제된 노드의 메모리 해제
    }
    return head;
}

// ── main 함수: 배열과 연결 리스트를 활용한 시간 측정 및 기능 테스트 ──
int main(void)
{
    element array[SIZE];       // 정수형 배열 선언 (총 SIZE 개 요소)
    clock_t start, end;        // 시간 측정을 위한 변수
    double t;                  // 실행 시간 (초 단위) 저장 변수
    double sum;                // 합계 계산용 변수
    int random[1000];          // 랜덤 인덱스 1000개를 저장할 배열

    // 실행 시작을 알리는 구분선 출력
    printf("\n=========================================\n\n");

    // 현재 시간을 기준으로 난수 생성 초기화
    srand(time(NULL));

    // ── 배열 방식 초기화 및 시간 측정 ──
    start = clock();
    // 배열에 0부터 SIZE-1까지 순차적으로 값 저장
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }
    end = clock();
    // 배열 초기화에 소요된 시간 계산
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array 걸린 시간 : %f초 \n", t);

    // ── 연결 리스트 초기화 (맨 앞 삽입 방식) 및 시간 측정 ──
    listnode* head = NULL; // 연결 리스트의 초기 머리는 NULL
    start = clock();
    // SIZE-1부터 0까지 역순으로 삽입하면 리스트의 순서는 0부터 SIZE-1까지 형성됨
    for (int i = SIZE - 1; i >= 0; i--) {
        head = insert_head(head, i);
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked list 걸린 시간 : %f초 \n", t);

    // ── 구분선 출력 ──
    printf("\n=========================================\n\n");

    // ── 1000개의 랜덤 인덱스 생성 ──
    for (int i = 0; i < 1000; i++) {
        random[i] = rand() % SIZE; // 0부터 SIZE-1 사이의 랜덤 인덱스 생성
    }

    // ── 배열을 이용한 랜덤 접근 및 합 산출 ──
    sum = 0;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        // 랜덤 인덱스에 해당하는 배열 요소 값을 합산
        sum += array[random[i]];
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array random access 걸린 시간 : %f초 \n", t);
    printf("Array random access index 합 : %.2f \n\n", sum);

    // ── 연결 리스트를 이용한 랜덤 접근 및 합 산출 ──
    sum = 0;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        // 연결 리스트에서 get() 함수를 호출하여 index 위치의 데이터를 얻어 합산
        sum += get(head, random[i]);
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked List random access 걸린 시간 : %f초 \n", t);
    printf("Linked List random access index 합 : %.2f \n", sum);

    // ── 구분선 출력 ──
    printf("\n=========================================\n\n");

    // ── 배열에서 랜덤 삭제 수행 ──
    int cur_size = SIZE; // 현재 배열의 유효 크기 저장 변수
    start = clock();
    for (int i = 0; i < 1000; i++) {
        int index = rand() % cur_size; // 현재 남은 크기 내 임의의 삭제 위치 선정
        // 삭제된 위치를 채우기 위해, 뒤쪽의 요소들을 한 칸씩 앞으로 이동
        for (int j = index; j < cur_size - 1; j++) {
            array[j] = array[j + 1];
        }
        cur_size--; // 삭제 후 배열의 크기 감소
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array random deletion 걸린 시간 : %f초 \n", t);

    /*
    // ── 연결 리스트에서 랜덤 삭제 수행 예시 ──
    // 배열 삭제와 유사하게, 현재 남은 노드 개수(cur_size)를 기반으로 랜덤 위치의 노드를 삭제함
    cur_size = SIZE;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        int index = rand() % cur_size;
        head = delete_position(head, index); // index 위치의 노드를 삭제
        cur_size--;                        // 리스트의 크기 감소
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked List random deletion 걸린 시간 : %f초 \n", t);
    */

    // ── 연결 리스트 노드들의 메모리 해제 ──
    freelist(head);

    return 0;
}