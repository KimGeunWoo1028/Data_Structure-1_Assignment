#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 큐 원소(element)의 자료형을 int로 정의
typedef int element;

// 원형 큐의 구조체 정의: front와 rear 인덱스, 큐의 크기, 큐 원소들을 저장할 동적 배열 포함
typedef struct {
    int front, rear;    // front: 큐의 시작 인덱스, rear: 큐의 마지막 인덱스
    int capacity;       // 큐의 총 크기
    int* array;         // 큐 원소들을 저장할 배열
} QueueType;

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 지정한 크기로 큐를 생성하는 함수
QueueType* Queue(int size) {
    // QueueType 구조체의 메모리 할당
    QueueType* Q = (QueueType*)malloc(sizeof(QueueType));
    if (!Q)
        return NULL;

    Q->capacity = size;         // 큐의 크기 설정
    Q->front = Q->rear = -1;      // 초기 상태: 큐가 비어있음을 -1로 설정

    // 큐 원소들을 저장할 배열 메모리 할당
    Q->array = (element*)malloc(Q->capacity * sizeof(element));
    if (!Q->array)
        return NULL;

    return Q;
}

// 큐가 비어있는지 검사하는 함수 (front가 -1이면 큐가 비어있음)
int isEmpty(QueueType* Q) {
    return (Q->front == -1);
}

// 원형 큐가 포화 상태인지 검사하는 함수 (rear의 다음 위치가 front와 같으면 포화 상태)
int isFull(QueueType* Q) {
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

// 큐에 할당된 메모리를 해제하는 함수
void deleteQueue(QueueType* Q) {
    if (Q) {
        if (Q->array)
            free(Q->array);
    }
    free(Q);
}

// 큐의 rear 위치에 원소를 삽입하는 함수
void enQueue(QueueType* Q, element item) {
    if (isFull(Q)) {
        error("Queue Overflow\n"); // 큐가 꽉 찬 경우 에러 메시지 출력 후 종료
        return;
    }
    else {
        // 원형 큐 방식에 따라 rear 인덱스 증가
        Q->rear = (Q->rear + 1) % Q->capacity;
        Q->array[Q->rear] = item;  // item 삽입
        // 처음 데이터 삽입 시 front를 rear와 동일하게 설정
        if (Q->front == -1)
            Q->front = Q->rear;
    }
}

// 큐에서 원소를 삭제하고 반환하는 함수
element deQueue(QueueType* Q) {
    int data = 0;
    if (isEmpty(Q)) {
        error("Queue is empty");  // 큐가 비어있으면 에러 출력 후 종료
        return -1;
    }
    else {
        data = Q->array[Q->front]; // front 위치의 원소를 저장
        // 큐에 단 하나의 원소만 남아있다면 큐를 비어있는 상태로 초기화
        if (Q->front == Q->rear)
            Q->front = Q->rear = -1;
        else
            // 원형 큐 방식에 따라 front 인덱스를 증가
            Q->front = (Q->front + 1) % Q->capacity;
    }
    return data;
}

// 큐의 상태를 출력하는 함수
void queue_print(QueueType* q)
{
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    if (!isEmpty(q)) {
        int i = q->front;
        // front부터 rear까지 큐 원소들을 순서대로 출력 (wrap-around 고려)
        while (1) {
            printf("%d ", q->array[i]);
            if (i == q->rear)
                break;
            i = (i + 1) % q->capacity;
        }
    }
    printf("]\n");
}

// 큐의 방향을 확인하는 함수
// front가 rear보다 작으면 정방향, 그렇지 않으면 역방향(원형 배열의 wrap-around 상황)
int checkDirection(QueueType* q)
{
    if (isEmpty(q)) {
        error("Queue is empty.\n");
        return -1;
    }

    if (q->front < q->rear) {
        return 1;  // 정방향
    }
    else {
        return 0;  // 역방향
    }
}

// 역방향으로 되어 있는 큐를 정방향으로 변경하는 함수
void ChangeDirection(QueueType* q)
{
    // 이미 정방향이면 변경할 필요가 없으므로 함수 종료
    if (q->front <= q->rear)
        return;

    int size;
    // 큐에 저장된 총 원소의 개수 계산 (wrap-around 고려)
    if (q->front <= q->rear)
        size = q->rear - q->front + 1;
    else
        size = (q->capacity - q->front) + (q->rear + 1);

    // 새 배열에 큐의 원소들을 순서대로 재배열하기 위한 메모리 할당
    element* newArray = (element*)malloc(size * sizeof(element));
    if (!newArray) {
        error("메모리 할당 실패");
        return;
    }

    int index = 0;
    int i = q->front;
    // front부터 rear까지 원소들을 새 배열에 복사
    while (1) {
        newArray[index++] = q->array[i];
        if (i == q->rear)
            break;
        i = (i + 1) % q->capacity;
    }

    // 기존 배열의 메모리를 해제
    free(q->array);

    // 큐를 새 배열로 갱신하고 front, rear 인덱스를 재설정 (정방향 배열로 변경)
    q->array = newArray;
    q->front = 0;
    q->rear = size - 1;
}

int main()
{
    int size;
    // 사용자로부터 큐의 사이즈를 입력받음
    printf("큐 사이즈 입력 : ");
    scanf("%d", &size);

    // 입력받은 사이즈로 큐 생성
    QueueType* q = Queue(size);

    // enQueue 연산을 수행하여 데이터를 삽입
    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 30);

    // 현재 큐의 상태를 출력
    queue_print(q);

    // deQueue 연산을 통해 데이터를 삭제
    deQueue(q);
    deQueue(q);

    // 삭제 후 큐의 상태 출력
    queue_print(q);

    // 추가 데이터를 삽입
    enQueue(q, 40);
    enQueue(q, 50);
    enQueue(q, 60);
    enQueue(q, 70);

    // 삽입 후 큐의 상태 출력
    queue_print(q);

    // 큐의 방향(정방향/역방향)을 확인
    if (!checkDirection(q)) {
        // 큐가 역방향이면 정방향으로 변경
        printf("역방향입니다. 정방향으로 바꿉니다.\n");
        ChangeDirection(q);
        queue_print(q);
    }
    else
        printf("정방향입니다.");

    // 동적 할당된 메모리 해제
    deleteQueue(q);

    return 0;
}
