#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element; // ť�� ����� ������ Ÿ���� element�� ���� (����� int)

/* ���� ť(Circular Queue)�� ���� ����ü ���� */
typedef struct {
	int front, rear;      // ť�� ��(front)�� ��(rear) �ε���
	int capacity;         // ���� ť�� �迭 ũ��
	int size;             // ť�� ���� ����ִ� ������ ����
	element* array;       // �������� �Ҵ�� ť�� �迭
} QueueType;

/* ���� �޽����� ����ϰ� ���α׷��� �����ϴ� �Լ� */
void error(const char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/* ť�� �ʱ�ȭ�ϰ� �޸𸮸� �������� �Ҵ��ϴ� �Լ� */
QueueType* Queue(int size) {
	QueueType* Q = (QueueType*)malloc(sizeof(QueueType)); // ����ü �Ҵ�
	if (!Q) {
		error("�޸� �Ҵ� ����");
	}
	Q->capacity = size; // �ʱ� �뷮 ����
	Q->front = Q->rear = -1; // ����ִ� ���¸� ��Ÿ���� ���� -1�� �ʱ�ȭ
	Q->size = 0;

	// �迭 �޸� ���� �Ҵ�
	Q->array = (element*)malloc(Q->capacity * sizeof(element));
	if (!Q->array)
		error("�޸� �Ҵ� ����");
	return Q;
}

/* ť�� ��� �ִ��� Ȯ���ϴ� �Լ� */
int isEmpty(QueueType* Q) {
	return (Q->front == -1);
}

/* ť�� �� á���� Ȯ���ϴ� �Լ� */
int isFull(QueueType* Q) {
	return Q->size == Q->capacity;
}

/* ť�� �� á�� �� �迭�� ũ�⸦ 2��� Ȯ���ϴ� �Լ� */
void resizeQueue(QueueType* Q) {
	int prev_size = Q->capacity;
	int new_size = prev_size * 2;

	// ���ο� �迭 ���� �Ҵ�
	element* new_array = (element*)malloc(new_size * sizeof(element));
	if (!new_array) {
		error("�޸� ���Ҵ� ����");
	}

	// ���� ť�� �����͸� ���ο� �迭�� ���� (���� ����)
	int i = Q->front;
	int j = 0;
	do {
		new_array[j++] = Q->array[i];
		i = (i + 1) % prev_size;
	} while (i != (Q->rear + 1) % prev_size);

	// ���� �迭 ����
	free(Q->array);
	Q->array = new_array;

	// �ε��� �缳��
	Q->front = 0;
	Q->rear = j - 1;
	Q->capacity = new_size;
}

/* ť �޸� ���� �Լ� */
void deleteQueue(QueueType* Q) {
	if (Q) {
		if (Q->array)
			free(Q->array);
		free(Q);
	}
}

/* ť�� �����͸� �����ϴ� �Լ� (rear �ʿ� ����) */
void enQueue(QueueType* Q, element item) {
	if (isFull(Q))         // �� á���� Ȯ��
		resizeQueue(Q);

	Q->rear = (Q->rear + 1) % Q->capacity; // rear �� ĭ �̵� (���� ����)
	Q->array[Q->rear] = item;              // rear ��ġ�� ������ ����

	if (Q->front == -1)
		Q->front = Q->rear; // ù �����Ͷ�� front�� �ʱ�ȭ

	Q->size++; // ť ũ�� ����
}

/* ť���� �����͸� �����ϰ� ��ȯ�ϴ� �Լ� (front �ʿ��� ����) */
element deQueue(QueueType* Q) {
	if (isEmpty(Q)) {
		error("Queue is empty");
		return -1; // ���� ������ (������� ����)
	}

	element item = Q->array[Q->front]; // ������ ������ ����

	if (Q->front == Q->rear) {
		// ������ ��Ҹ� ������ ��� -> ť�� ���
		Q->front = Q->rear = -1;
	}
	else {
		Q->front = (Q->front + 1) % Q->capacity; // front �� ĭ �̵�
	}
	Q->size--; // ť ũ�� ����
	return item;
}

/* ť�� ���� ���¸� ����ϴ� �Լ� */
void queue_print(QueueType* q)
{
	printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
	if (!isEmpty(q)) {
		int count = q->size;
		int i = q->front;
		while (count--) {
			printf("%d ", q->array[i]);   // ���� ��ġ�� �� ���
			i = (i + 1) % q->capacity;   // ���� ��ġ�� �̵�
		}
	}
	printf("]\n");
}

/* k��° �����͸� �����ϴ� �Լ�
   (�տ������� k-1�� rotate, k��° deQueue) */
element remove_k(QueueType* Q, int k)
{
	for (int i = 0; i < k - 1; i++) {
		enQueue(Q, deQueue(Q));  // k-1�� rotate
	}
	return deQueue(Q); // k��° ����
}

/* ���� �Լ� */
int main()
{
	srand((unsigned int)time(NULL)); // ���� �ʱ�ȭ

	QueueType* q = Queue(5); // ť �ʱ� ũ�� = 5

	// �ʱ� ť�� 5�� ���� ������ ����
	printf("ù 5�� ���� �� enqueue : ");
	for (int i = 0; i < 5; i++) {
		int val = rand() % 50 + 1; // 1 ~ 50
		enQueue(q, val);
		printf("%d ", val);
	}
	printf("\n");

	printf("0ȸ�� (ť �뷮: %d)\n", q->capacity);
	queue_print(q);

	element last_removed = -1;

	// 5ȸ �ݺ� (�� ȸ���� k��° ��� ���� + �� ������ 5�� ����)
	for (int round = 1; round <= 5; round++) {
		int size = q->size;
		int k = rand() % size + 1; // 1 ~ ���� ť ũ�� �� �ϳ�
		printf("\n%dȸ�� k = %d (ť �뷮: %d)\n", round, k, q->capacity);

		last_removed = remove_k(q, k); // k��° ������ ����
		printf("������ ������ : %d\n", last_removed);
		queue_print(q);

		// �� ������ 5�� ����
		printf("5�� ���� �� enqueue : ");
		for (int i = 0; i < 5; i++) {
			int new_value = rand() % 50 + 1;
			printf("%d ", new_value);
			enQueue(q, new_value);
		}
		printf("\n");
		queue_print(q);
	}

	printf("\n�������� ������ ������ : %d\n", last_removed);

	return 0;
}
