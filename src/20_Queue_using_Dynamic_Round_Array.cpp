#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element; // 큐에 저장될 데이터 타입을 element로 정의 (현재는 int)

/* 원형 큐(Circular Queue)를 위한 구조체 정의 */
typedef struct {
	int front, rear;      // 큐의 앞(front)과 뒤(rear) 인덱스
	int capacity;         // 현재 큐의 배열 크기
	int size;             // 큐에 실제 들어있는 데이터 개수
	element* array;       // 동적으로 할당된 큐의 배열
} QueueType;

/* 에러 메시지를 출력하고 프로그램을 종료하는 함수 */
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/* 큐를 초기화하고 메모리를 동적으로 할당하는 함수 */
QueueType* Queue(int size) {
	QueueType* Q = (QueueType*)malloc(sizeof(QueueType)); // 구조체 할당
	if (!Q) {
		error("메모리 할당 실패");
	}
	Q->capacity = size; // 초기 용량 설정
	Q->front = Q->rear = -1; // 비어있는 상태를 나타내기 위해 -1로 초기화
	Q->size = 0;

	// 배열 메모리 동적 할당
	Q->array = (element*)malloc(Q->capacity * sizeof(element));
	if (!Q->array)
		error("메모리 할당 실패");
	return Q;
}

/* 큐가 비어 있는지 확인하는 함수 */
int isEmpty(QueueType* Q) {
	return (Q->front == -1);
}

/* 큐가 꽉 찼는지 확인하는 함수 */
int isFull(QueueType* Q) {
	return Q->size == Q->capacity;
}

/* 큐가 꽉 찼을 때 배열의 크기를 2배로 확장하는 함수 */
void resizeQueue(QueueType* Q) {
	int prev_size = Q->capacity;
	int new_size = prev_size * 2;

	// 새로운 배열 동적 할당
	element* new_array = (element*)malloc(new_size * sizeof(element));
	if (!new_array) {
		error("메모리 재할당 실패");
	}

	// 기존 큐의 데이터를 새로운 배열로 복사 (순서 유지)
	int i = Q->front;
	int j = 0;
	do {
		new_array[j++] = Q->array[i];
		i = (i + 1) % prev_size;
	} while (i != (Q->rear + 1) % prev_size);

	// 기존 배열 해제
	free(Q->array);
	Q->array = new_array;

	// 인덱스 재설정
	Q->front = 0;
	Q->rear = j - 1;
	Q->capacity = new_size;
}

/* 큐 메모리 해제 함수 */
void deleteQueue(QueueType* Q) {
	if (Q) {
		if (Q->array)
			free(Q->array);
		free(Q);
	}
}

/* 큐에 데이터를 삽입하는 함수 (rear 쪽에 삽입) */
void enQueue(QueueType* Q, element item) {
	if (isFull(Q))         // 꽉 찼으면 확장
		resizeQueue(Q);

	Q->rear = (Q->rear + 1) % Q->capacity; // rear 한 칸 이동 (원형 구조)
	Q->array[Q->rear] = item;              // rear 위치에 데이터 저장

	if (Q->front == -1)
		Q->front = Q->rear; // 첫 데이터라면 front도 초기화

	Q->size++; // 큐 크기 증가
}

/* 큐에서 데이터를 삭제하고 반환하는 함수 (front 쪽에서 제거) */
element deQueue(QueueType* Q) {
	if (isEmpty(Q)) {
		error("Queue is empty");
		return -1; // 오류 방지용 (실행되지 않음)
	}

	element item = Q->array[Q->front]; // 삭제할 데이터 저장

	if (Q->front == Q->rear) {
		// 마지막 요소를 제거한 경우 -> 큐를 비움
		Q->front = Q->rear = -1;
	}
	else {
		Q->front = (Q->front + 1) % Q->capacity; // front 한 칸 이동
	}
	Q->size--; // 큐 크기 감소
	return item;
}

/* 큐의 현재 상태를 출력하는 함수 */
void queue_print(QueueType* q)
{
	printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
	if (!isEmpty(q)) {
		int count = q->size;
		int i = q->front;
		while (count--) {
			printf("%d ", q->array[i]);   // 현재 위치의 값 출력
			i = (i + 1) % q->capacity;   // 다음 위치로 이동
		}
	}
	printf("]\n");
}

/* k번째 데이터를 제거하는 함수
   (앞에서부터 k-1개 rotate, k번째 deQueue) */
element remove_k(QueueType* Q, int k)
{
	for (int i = 0; i < k - 1; i++) {
		enQueue(Q, deQueue(Q));  // k-1개 rotate
	}
	return deQueue(Q); // k번째 제거
}

/* 메인 함수 */
int main()
{
	srand((unsigned int)time(NULL)); // 랜덤 초기화

	QueueType* q = Queue(5); // 큐 초기 크기 = 5

	// 초기 큐에 5개 랜덤 데이터 삽입
	printf("첫 5개 랜덤 값 enqueue : ");
	for (int i = 0; i < 5; i++) {
		int val = rand() % 50 + 1; // 1 ~ 50
		enQueue(q, val);
		printf("%d ", val);
	}
	printf("\n");

	printf("0회차 (큐 용량: %d)\n", q->capacity);
	queue_print(q);

	element last_removed = -1;

	// 5회 반복 (매 회마다 k번째 요소 제거 + 새 데이터 5개 삽입)
	for (int round = 1; round <= 5; round++) {
		int size = q->size;
		int k = rand() % size + 1; // 1 ~ 현재 큐 크기 중 하나
		printf("\n%d회차 k = %d (큐 용량: %d)\n", round, k, q->capacity);

		last_removed = remove_k(q, k); // k번째 데이터 제거
		printf("삭제된 데이터 : %d\n", last_removed);
		queue_print(q);

		// 새 데이터 5개 삽입
		printf("5개 랜덤 값 enqueue : ");
		for (int i = 0; i < 5; i++) {
			int new_value = rand() % 50 + 1;
			printf("%d ", new_value);
			enQueue(q, new_value);
		}
		printf("\n");
		queue_print(q);
	}

	printf("\n마지막에 삭제된 데이터 : %d\n", last_removed);

	return 0;
}
