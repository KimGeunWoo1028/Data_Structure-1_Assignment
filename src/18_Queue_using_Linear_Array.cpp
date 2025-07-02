/*
  파일명: queue_example.c
  설명: 동적 배열을 이용하여 큐(Queue)를 구현하는 예제 프로그램.
       사용자로부터 입력 받은 큐 크기에 따라 큐를 생성하고, 기본 연산인
       enqueue(삽입), dequeue(삭제), queue_print(출력)을 수행한다.
       작성자: [작성자 이름]
       작성일: [작성일]
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 보안 경고 무시
#include <stdio.h>
#include <stdlib.h>

// 큐에 저장할 요소의 자료형을 int로 정의
typedef int element;

// Queue 구조체 정의
typedef struct {
    int front;      // 큐의 앞부분 인덱스 (삭제가 이루어지는 위치)
    int rear;       // 큐의 뒷부분 인덱스 (삽입이 이루어지는 위치)
    int capacity;   // 큐의 최대 요소 저장 가능 개수
    element* data;  // 큐의 요소들을 저장할 동적 배열을 가리키는 포인터
} Queue;

// 에러 발생 시 메시지를 출력하고 프로그램을 종료하는 함수
void error(const char* message)
{
    fprintf(stderr, "%s\n", message); // 에러 메시지를 표준 오류 스트림에 출력
    exit(1);
}

// 주어진 크기로 큐를 생성하는 함수
Queue* create(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));   // Queue 구조체에 동적 메모리 할당
    q->data = (element*)malloc(sizeof(element));  // 요소를 저장할 배열에 동적 메모리 할당 (주의: 여기서는 크기가 1로 할당됨)

    q->front = -1;      // 큐 초기 상태: front를 -1로 설정하여 비어있음을 표시
    q->rear = -1;       // 큐 초기 상태: rear도 -1로 설정
    q->capacity = size; // 사용자가 입력한 값을 큐의 용량으로 설정
    return q;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(Queue* q)
{
    // rear 인덱스가 capacity - 1이면 큐가 가득 찬 상태임
    return q->rear == q->capacity - 1;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* q)
{
    // front와 rear가 같으면 큐에 저장된 요소가 없음을 의미한다.
    return q->front == q->rear;
}

// 큐에 요소(item)를 삽입하는 함수
void enqueue(Queue* q, int item)
{
    // 만약 큐가 가득 찼다면, 삭제된 요소로 인해 앞부분에 빈 공간이 있을 수 있음
    if (isFull(q)) {
        // 큐가 비어있지 않을 경우에만 데이터를 이동(shift)하여 빈 공간을 확보
        if (!isEmpty(q)) {
            int j = 0;
            // front+1부터 rear까지의 요소를 배열의 시작 위치로 이동
            for (int i = q->front + 1; i <= q->rear; i++) {
                q->data[j++] = q->data[i];
            }
            // 이동한 후 rear와 front 인덱스를 갱신
            q->rear = q->rear - (q->front + 1);
            q->front = -1;
        }
    }
    // 이동 후에도 큐가 여전히 꽉 찼다면 에러 처리
    if (isFull(q)) {
        error("큐 포화상태.");
        return;
    }
    // rear 포인터를 증가시키며 요소 삽입
    q->data[++(q->rear)] = item;
}

// 큐에서 요소를 삭제(dequeue)하고 반환하는 함수
element dequeue(Queue* q)
{
    // 큐가 비어있으면 에러 메시지를 출력하고 프로그램 종료
    if (isEmpty(q)) {
        error("큐가 공백상태.");
        return -1;  // 도달하지 않는 코드
    }
    // front를 증가시켜 요소 삭제 후 그 요소 반환
    int item = q->data[++(q->front)];
    return item;
}

// 현재 큐의 상태를 출력하는 함수
void queue_print(Queue* q)
{
    // 큐의 front와 rear 인덱스 정보를 출력
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    // 전체 배열의 각 인덱스를 검사하여 유효한 요소는 출력, 그렇지 않은 곳은 'X'로 표시
    for (int i = 0; i < q->capacity; i++) {
        if (i > q->front && i <= q->rear)
            printf("%d ", q->data[i]);  // 유효한 요소 출력
        else
            printf(" X ");              // 사용하지 않는 공간 표시
    }
    printf("]\n");
}

// main 함수: 프로그램 실행의 시작점
int main(void)
{
    int size;
    // 사용자로부터 큐의 크기를 입력받음
    printf("큐 크기 입력 : ");
    scanf("%d", &size);

    // 입력받은 크기로 큐를 생성
    Queue* q = create(size);

    // 큐에 10, 20, 30을 순차적으로 삽입
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    // 현재 큐 상태 출력 (예상: 10, 20, 30 삽입)
    queue_print(q);

    // 큐에서 두 요소를 삭제 (예상: 10, 20 삭제)
    dequeue(q);
    dequeue(q);
    // 삭제 후 현재 큐 상태 출력 (예상: 30만 남음)
    queue_print(q);

    // 추가적인 요소 40, 50, 60 삽입 (빈 공간 재사용 확인)
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    // 최종 큐 상태 출력
    queue_print(q);

    return 0;  // 프로그램 정상 종료
}
