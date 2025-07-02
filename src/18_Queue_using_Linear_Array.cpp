/*
  ���ϸ�: queue_example.c
  ����: ���� �迭�� �̿��Ͽ� ť(Queue)�� �����ϴ� ���� ���α׷�.
       ����ڷκ��� �Է� ���� ť ũ�⿡ ���� ť�� �����ϰ�, �⺻ ������
       enqueue(����), dequeue(����), queue_print(���)�� �����Ѵ�.
       �ۼ���: [�ۼ��� �̸�]
       �ۼ���: [�ۼ���]
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio���� ���� ��� ����
#include <stdio.h>
#include <stdlib.h>

// ť�� ������ ����� �ڷ����� int�� ����
typedef int element;

// Queue ����ü ����
typedef struct {
    int front;      // ť�� �պκ� �ε��� (������ �̷������ ��ġ)
    int rear;       // ť�� �޺κ� �ε��� (������ �̷������ ��ġ)
    int capacity;   // ť�� �ִ� ��� ���� ���� ����
    element* data;  // ť�� ��ҵ��� ������ ���� �迭�� ����Ű�� ������
} Queue;

// ���� �߻� �� �޽����� ����ϰ� ���α׷��� �����ϴ� �Լ�
void error(const char* message)
{
    fprintf(stderr, "%s\n", message); // ���� �޽����� ǥ�� ���� ��Ʈ���� ���
    exit(1);
}

// �־��� ũ��� ť�� �����ϴ� �Լ�
Queue* create(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));   // Queue ����ü�� ���� �޸� �Ҵ�
    q->data = (element*)malloc(sizeof(element));  // ��Ҹ� ������ �迭�� ���� �޸� �Ҵ� (����: ���⼭�� ũ�Ⱑ 1�� �Ҵ��)

    q->front = -1;      // ť �ʱ� ����: front�� -1�� �����Ͽ� ��������� ǥ��
    q->rear = -1;       // ť �ʱ� ����: rear�� -1�� ����
    q->capacity = size; // ����ڰ� �Է��� ���� ť�� �뷮���� ����
    return q;
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int isFull(Queue* q)
{
    // rear �ε����� capacity - 1�̸� ť�� ���� �� ������
    return q->rear == q->capacity - 1;
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q)
{
    // front�� rear�� ������ ť�� ����� ��Ұ� ������ �ǹ��Ѵ�.
    return q->front == q->rear;
}

// ť�� ���(item)�� �����ϴ� �Լ�
void enqueue(Queue* q, int item)
{
    // ���� ť�� ���� á�ٸ�, ������ ��ҷ� ���� �պκп� �� ������ ���� �� ����
    if (isFull(q)) {
        // ť�� ������� ���� ��쿡�� �����͸� �̵�(shift)�Ͽ� �� ������ Ȯ��
        if (!isEmpty(q)) {
            int j = 0;
            // front+1���� rear������ ��Ҹ� �迭�� ���� ��ġ�� �̵�
            for (int i = q->front + 1; i <= q->rear; i++) {
                q->data[j++] = q->data[i];
            }
            // �̵��� �� rear�� front �ε����� ����
            q->rear = q->rear - (q->front + 1);
            q->front = -1;
        }
    }
    // �̵� �Ŀ��� ť�� ������ �� á�ٸ� ���� ó��
    if (isFull(q)) {
        error("ť ��ȭ����.");
        return;
    }
    // rear �����͸� ������Ű�� ��� ����
    q->data[++(q->rear)] = item;
}

// ť���� ��Ҹ� ����(dequeue)�ϰ� ��ȯ�ϴ� �Լ�
element dequeue(Queue* q)
{
    // ť�� ��������� ���� �޽����� ����ϰ� ���α׷� ����
    if (isEmpty(q)) {
        error("ť�� �������.");
        return -1;  // �������� �ʴ� �ڵ�
    }
    // front�� �������� ��� ���� �� �� ��� ��ȯ
    int item = q->data[++(q->front)];
    return item;
}

// ���� ť�� ���¸� ����ϴ� �Լ�
void queue_print(Queue* q)
{
    // ť�� front�� rear �ε��� ������ ���
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    // ��ü �迭�� �� �ε����� �˻��Ͽ� ��ȿ�� ��Ҵ� ���, �׷��� ���� ���� 'X'�� ǥ��
    for (int i = 0; i < q->capacity; i++) {
        if (i > q->front && i <= q->rear)
            printf("%d ", q->data[i]);  // ��ȿ�� ��� ���
        else
            printf(" X ");              // ������� �ʴ� ���� ǥ��
    }
    printf("]\n");
}

// main �Լ�: ���α׷� ������ ������
int main(void)
{
    int size;
    // ����ڷκ��� ť�� ũ�⸦ �Է¹���
    printf("ť ũ�� �Է� : ");
    scanf("%d", &size);

    // �Է¹��� ũ��� ť�� ����
    Queue* q = create(size);

    // ť�� 10, 20, 30�� ���������� ����
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    // ���� ť ���� ��� (����: 10, 20, 30 ����)
    queue_print(q);

    // ť���� �� ��Ҹ� ���� (����: 10, 20 ����)
    dequeue(q);
    dequeue(q);
    // ���� �� ���� ť ���� ��� (����: 30�� ����)
    queue_print(q);

    // �߰����� ��� 40, 50, 60 ���� (�� ���� ���� Ȯ��)
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    // ���� ť ���� ���
    queue_print(q);

    return 0;  // ���α׷� ���� ����
}
