#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 큐에 저장할 원소의 자료형 정의 (정수형)
typedef int element;

// 원형 큐를 표현하는 구조체 정의
typedef struct {
    int front, rear;    // front: 삭제 위치, rear: 삽입 위치
    int capacity;       // 큐의 최대 저장 가능한 원소의 개수
    int* array;         // 큐 원소들을 저장할 배열
} QueueType;

// 에러 발생 시 메시지를 출력하고 프로그램을 종료하는 함수
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 지정한 크기의 원형 큐를 생성하는 함수
QueueType* Queue(int size) {
    QueueType* Q = (QueueType*)malloc(sizeof(QueueType)); // 큐 구조체 동적할당
    if (!Q)
        return NULL;
    Q->capacity = size;               // 큐의 용량 설정
    Q->front = Q->rear = -1;          // 초기 상태: 큐가 비어 있음
    Q->array = (element*)malloc(Q->capacity * sizeof(element)); // 큐 원소 저장용 배열 동적할당
    if (!Q->array)
        return NULL;
    return Q;
}

// 원형 큐가 비어있는지 확인하는 함수
int isEmpty(QueueType* Q) {
    return (Q->front == -1);
}

// 원형 큐가 가득 찼는지 확인하는 함수
int isFull(QueueType* Q) {
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

// 큐와 큐의 배열 메모리를 해제하는 함수
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
        error("Queue Overflow\n");
        return;
    }
    // rear 인덱스를 갱신 (원형 구조를 위해 모듈로 연산 사용)
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->array[Q->rear] = item;         // 새로운 원소 삽입
    // 첫 번째 원소 삽입인 경우 front도 갱신
    if (Q->front == -1)
        Q->front = Q->rear;
}

// 큐의 front 위치의 원소를 삭제하고 반환하는 함수
element deQueue(QueueType* Q) {
    int data = 0;
    if (isEmpty(Q)) {
        error("Queue is empty");
        return -1;
    }
    // front 위치의 원소 반환
    data = Q->array[Q->front];
    // 만약 큐에 한 개의 원소만 있었던 경우, 큐를 빈 상태로 만듦
    if (Q->front == Q->rear)
        Q->front = Q->rear = -1;
    else
        Q->front = (Q->front + 1) % Q->capacity; // 다음 원소로 front 이동
    return data;
}

// 큐의 현재 상태(인덱스와 원소들)를 출력하는 함수
void queue_print(QueueType* q)
{
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    if (!isEmpty(q)) {
        int i = q->front;
        while (1) {
            printf("%d ", q->array[i]);
            if (i == q->rear)
                break;
            i = (i + 1) % q->capacity;
        }
    }
    printf("]\n");
}

// 큐 내부의 원소들의 저장 순서가 정방향(앞에서 뒤로)이면 1, 역방향이면 0을 반환하는 함수
int checkDirection(QueueType* q)
{
    if (isEmpty(q)) {
        error("Queue is empty.\n");
        return -1;
    }
    if (q->front < q->rear)
        return 1; // 정방향: front가 rear보다 작음
    else
        return 0; // 역방향: 원소가 wrap-around된 상태
}

// 역방향인 큐의 순서를 정방향으로 변경하는 함수
void ChangeDirection(QueueType* q)
{
    // 정방향이면 변경할 필요가 없음
    if (q->front <= q->rear)
        return;

    int size;
    // 역방향인 경우, 큐에 저장된 원소의 수 계산
    if (q->front >= q->rear)
        size = (q->capacity - q->front) + (q->rear + 1);

    // 새 배열 동적할당 (queue에 저장된 원소 수만큼)
    element* newArray = (element*)malloc(size * sizeof(element));
    if (!newArray)
        error("Memory allocation failed in ChangeDirection");

    int index = 0;
    int i = q->front;
    // front부터 rear까지 순차적으로 복사
    while (1) {
        newArray[index++] = q->array[i];
        if (i == q->rear)
            break;
        i = (i + 1) % q->capacity;
    }

    // 기존 배열 메모리 해제 후 새 배열로 교체
    free(q->array);
    q->array = newArray;
    q->front = 0;         // front 재설정
    q->rear = size - 1;   // rear는 마지막 원소의 인덱스로 재설정
}

int main()
{
    int size;
    // 사용자로부터 큐의 크기를 입력 받음
    printf("큐 사이즈 입력 : ");
    scanf("%d", &size);

    // 지정한 크기의 큐 생성
    QueueType* q = Queue(size);

    // 기본 enQueue 연산: 큐에 원소 삽입
    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 30);

    // 현재 큐 상태 출력
    queue_print(q);

    // deQueue 연산: 큐에서 원소 2개 삭제
    deQueue(q);
    deQueue(q);

    // 삭제 후 큐 상태 출력
    queue_print(q);

    // 추가 enQueue 연산: wrap-around 상황을 만들기 위해 여러 원소 삽입
    enQueue(q, 40);
    enQueue(q, 50);
    enQueue(q, 60);
    enQueue(q, 70);

    // 변경된 큐 상태 출력
    queue_print(q);

    // 큐가 정방향인지 역방향인지 확인
    if (!checkDirection(q)) {
        printf("역방향입니다. 정방향으로 바꿉니다.\n");
        // 역방향이면 정방향으로 순서를 변경
        ChangeDirection(q);
        // 변경 후 큐 상태 출력
        queue_print(q);
    }
    else
        printf("정방향입니다.\n");

    // 사용한 메모리 해제
    deleteQueue(q);
    return 0;
}