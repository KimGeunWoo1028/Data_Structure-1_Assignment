#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// element 타입을 int로 정의합니다.
typedef int element;

// 연결 리스트의 노드 구조체 정의 (정수를 저장)
typedef struct Listnode {
    element data;           // 노드에 저장할 데이터
    struct Listnode* link;  // 다음 노드를 가리키는 포인터
} Listnode;

// 큐 구조체 정의: front와 rear 포인터 및 큐의 크기를 저장
typedef struct Queue {
    Listnode* front; // 큐의 앞쪽(첫 번째 노드)를 가리키는 포인터
    Listnode* rear;  // 큐의 뒤쪽(마지막 노드)를 가리키는 포인터
    int size;        // 큐에 저장된 노드의 수
} Queue;

// 함수: create
// ----------------
// 새로운 빈 큐를 생성하여 초기화한 후, 해당 큐의 포인터를 반환합니다.
Queue* create() {
    // 큐에 대한 메모리를 동적 할당합니다.
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q)
        return NULL; // 메모리 할당에 실패하면 NULL 반환

    // 큐를 빈 상태로 초기화: front와 rear는 NULL, size는 0
    q->front = q->rear = NULL;
    q->size = 0;
    return q; // 생성한 큐의 주소 반환
}

// 함수: isEmpty
// -----------------
// 큐가 비어있는지 확인하는 함수입니다. (front가 NULL이면 비어있음)
int isEmpty(Queue* q) {
    return (q->front == NULL); // front가 NULL이면 비어있으므로 1 반환, 아니면 0 반환
}

// 함수: enqueue
// -----------------
// 큐에 새로운 데이터를 삽입합니다. 큐의 크기가 10 이상이면 에러 메시지를 출력하고 프로그램을 종료합니다.
// 또한, 중복 데이터인지 확인하여 중복이면 삽입하지 않습니다.
void enqueue(Queue* q, element data) {
    // 큐의 크기가 최대 크기(10)에 도달한 경우
    if (q->size >= 10) {
        printf("Queue is Full. Exit program.\n");
        exit(1);
    }

    // 큐에 이미 동일한 데이터가 있는지 확인 (중복 확인)
    Listnode* current = q->front;
    while (current != NULL) {
        if (current->data == data)
            return; // 중복 데이터이면 삽입하지 않고 반환
        current = current->link;
    }

    // 새 데이터를 저장할 노드를 동적 할당합니다.
    Listnode* newnode = (Listnode*)malloc(sizeof(Listnode));
    if (!newnode)
        return; // 메모리 할당 실패 시 함수 종료

    // 새 노드의 데이터 설정 및 다음 노드를 가리키는 포인터를 NULL로 초기화합니다.
    newnode->data = data;
    newnode->link = NULL;

    // 큐의 맨 뒤에 새 노드를 연결합니다.
    if (q->rear != NULL)
        q->rear->link = newnode; // 기존 rear의 link가 새 노드를 가리키도록 함
    q->rear = newnode; // rear 포인터를 새 노드로 업데이트

    // 큐가 비어있었다면 front 도 새 노드를 가리키게 함
    if (q->front == NULL)
        q->front = q->rear;

    // 큐의 크기를 증가시키고 삽입된 데이터를 출력
    q->size++;
    printf("Enqueued : %d\n", data);
}

// 함수: dequeue
// -----------------
// 큐의 앞쪽에 있는 데이터를 삭제하고 그 값을 반환합니다.
// 큐가 비어있다면 "Queue is Empty" 메시지를 출력하고 -1을 반환합니다.
int dequeue(Queue* q) {
    // 큐가 비어있는 경우
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    // front 노드를 임시 변수에 저장하고, 그 노드의 데이터를 가져옵니다.
    Listnode* temp = q->front;
    int data = q->front->data;

    // front 포인터를 다음 노드로 이동시킵니다.
    q->front = q->front->link;

    // 만약 큐가 비게 되면 rear도 NULL로 설정합니다.
    if (q->front == NULL)
        q->rear = NULL;

    // 삭제된 노드의 메모리를 해제하고 큐의 크기를 감소시킵니다.
    free(temp);
    q->size--;

    // 삭제된 데이터 값을 출력하고 반환
    printf("Dequeued : %d\n", data);
    return data;
}

// 함수: printqueue
// --------------------
// 큐에 저장되어 있는 모든 데이터를 앞에서 뒤까지 출력합니다.
void printqueue(Queue* q) {
    // 큐가 비어있으면 빈 대괄호를 출력합니다.
    if (isEmpty(q)) {
        printf("[ ]\n");
        return;
    }

    // 큐의 front부터 순회하기 위한 포인터 변수
    Listnode* current = q->front;

    printf("[ ");

    // 모든 노드를 순회하면서 데이터를 출력합니다.
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }

    printf("]\n"); // 출력 형식을 마무리 합니다.
}

// 메인 함수: 프로그램의 시작점
int main() {
    // 현재 시간을 기반으로 랜덤 번호 생성의 시드를 설정합니다.
    srand((unsigned int)time(NULL));

    // 빈 큐를 생성합니다.
    Queue* q = create();

    // 무한 반복문으로 랜덤 연산을 계속 진행합니다.
    while (1) {
        // 1부터 100 사이의 랜덤 값을 생성합니다.
        int r = rand() % 100 + 1;
        // 생성된 랜덤 값을 3으로 나눈 나머지를 계산합니다.
        int map = r % 3;

        // 생성된 랜덤 값과 map 값을 출력합니다.
        printf("Random value : %d (map : %d)\n", r, map);

        // map 값이 짝수이면 enqueue, 홀수이면 dequeue 수행
        if (map % 2 == 0) {
            enqueue(q, r);
        }
        else {
            dequeue(q);
        }

        // 현재 큐의 상태를 출력합니다.
        printqueue(q);
    }
}
