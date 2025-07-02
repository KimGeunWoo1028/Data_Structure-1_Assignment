/*
   프로그램: 큐 (Queue) 구현
   설명: 배열을 이용하여 기본 큐를 구현한 프로그램으로, 큐 생성, 원소 삽입(enqueue), 원소 삭제(dequeue) 및 큐 상태 출력 등의 기능을 포함합니다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// element 타입을 int로 정의 (간단하게 사용)
typedef int element;

// 큐의 구조체 정의: front, rear, capacity, 그리고 원소들을 저장할 배열 포인터 포함
typedef struct {
    int front;      // 큐에서 가장 앞에 있는 원소의 바로 이전 인덱스
    int rear;       // 큐에서 마지막 원소의 인덱스
    int capacity;   // 큐가 저장할 수 있는 총 원소 수
    element* data;  // 큐의 원소들을 저장하는 배열 포인터
} Queue;

// error() 함수: 에러 메시지를 출력하고 프로그램을 강제 종료합니다.
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// create() 함수: 지정된 크기로 큐와 그 내부 배열을 동적 할당하여 생성합니다.
// 매개변수: size - 큐의 총 용량
Queue* create(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));  // 큐 구조체 메모리 할당
    if (q == NULL)
        error("Queue 구조체에 대한 메모리 할당 실패.");

    // 큐의 원소들을 저장할 배열을 size만큼 할당
    q->data = (element*)malloc(size * sizeof(element));
    if (q->data == NULL)
        error("Queue 원소들에 대한 메모리 할당 실패.");

    // 큐의 초기 상태 설정: front와 rear는 -1로 초기화 (빈 큐를 의미)
    q->front = -1;
    q->rear = -1;
    q->capacity = size;  // 사용자가 입력한 큐 크기로 설정
    return q;
}

// isFull() 함수: 큐가 가득 찼는지 확인합니다.
// 리턴값: 큐가 꽉 찼으면 1, 아니면 0을 반환
int isFull(Queue* q)
{
    return q->rear == q->capacity - 1;
}

// isEmpty() 함수: 큐가 비어있는지 확인합니다.
// 리턴값: 큐가 비어있으면 1, 아니면 0을 반환
int isEmpty(Queue* q)
{
    return q->front == q->rear;
}

// enqueue() 함수: 큐에 원소를 삽입합니다.
// 매개변수: q - 큐 구조체 포인터, item - 삽입할 원소
void enqueue(Queue* q, int item)
{
    // 큐가 가득 찼는지 먼저 확인
    if (isFull(q)) {
        // 큐에 원소가 있을 경우, 공간 확보를 위해 앞쪽으로 원소들을 이동시킵니다.
        if (!isEmpty(q)) {
            int j = 0;
            // front 다음 인덱스부터 rear까지의 원소들을 배열의 앞쪽으로 이동
            for (int i = q->front + 1; i <= q->rear; i++) {
                q->data[j++] = q->data[i];
            }
            // 이동 후, rear 포인터를 재조정
            q->rear = q->rear - (q->front + 1);
            // front 포인터는 다시 -1로 초기화 (이동 후 첫 인덱스 전 위치)
            q->front = -1;
        }
    }
    // 이동 후에도 큐가 가득 차면 에러 메시지 출력 및 종료
    if (isFull(q)) {
        error("큐 포화상태.");
        return;
    }
    // rear를 증가시키면서 새로운 원소 삽입
    q->data[++(q->rear)] = item;
}

// dequeue() 함수: 큐에서 front에 위치한 원소를 삭제하고 반환합니다.
// 매개변수: q - 큐 구조체 포인터
// 리턴값: 삭제된 원소
element dequeue(Queue* q)
{
    // 큐가 비어있으면 에러 메시지 출력 후 종료
    if (isEmpty(q)) {
        error("큐가 공백상태.");
        return -1; // 프로그램 종료로 인해 도달하지 않음
    }
    // front 포인터를 증가시키고 해당 위치의 원소를 반환
    int item = q->data[++(q->front)];
    return item;
}

// queue_print() 함수: 큐의 현재 상태를 출력합니다.
// front와 rear 인덱스, 그리고 배열 전체 상태를 출력
void queue_print(Queue* q)
{
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    // 전체 배열 범위를 순회하면서 큐에 존재하는 원소는 출력, 나머지는 'X' 출력
    for (int i = 0; i < q->capacity; i++) {
        if (i > q->front && i <= q->rear)
            printf("%d ", q->data[i]);
        else
            printf(" X ");
    }
    printf("]\n");
}

// main() 함수: 큐의 동작을 시연합니다.
int main(void)
{
    int size;
    // 사용자로부터 큐 크기를 입력 받음
    printf("큐 크기 입력 : ");
    scanf("%d", &size);

    // 입력받은 크기로 큐 생성
    Queue* q = create(size);

    // 원소 10, 20, 30을 큐에 삽입
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    // 현재 큐 상태 출력
    queue_print(q);

    // 두 개의 원소를 큐에서 삭제
    dequeue(q);
    dequeue(q);
    // 삭제 후 큐 상태 출력
    queue_print(q);

    // 원소 40, 50, 60을 추가 삽입하여 shifting 동작 시연
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    // 최종 큐 상태 출력
    queue_print(q);

    return 0;
}