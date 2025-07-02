/*
   ���α׷�: ť (Queue) ����
   ����: �迭�� �̿��Ͽ� �⺻ ť�� ������ ���α׷�����, ť ����, ���� ����(enqueue), ���� ����(dequeue) �� ť ���� ��� ���� ����� �����մϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// element Ÿ���� int�� ���� (�����ϰ� ���)
typedef int element;

// ť�� ����ü ����: front, rear, capacity, �׸��� ���ҵ��� ������ �迭 ������ ����
typedef struct {
    int front;      // ť���� ���� �տ� �ִ� ������ �ٷ� ���� �ε���
    int rear;       // ť���� ������ ������ �ε���
    int capacity;   // ť�� ������ �� �ִ� �� ���� ��
    element* data;  // ť�� ���ҵ��� �����ϴ� �迭 ������
} Queue;

// error() �Լ�: ���� �޽����� ����ϰ� ���α׷��� ���� �����մϴ�.
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// create() �Լ�: ������ ũ��� ť�� �� ���� �迭�� ���� �Ҵ��Ͽ� �����մϴ�.
// �Ű�����: size - ť�� �� �뷮
Queue* create(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));  // ť ����ü �޸� �Ҵ�
    if (q == NULL)
        error("Queue ����ü�� ���� �޸� �Ҵ� ����.");

    // ť�� ���ҵ��� ������ �迭�� size��ŭ �Ҵ�
    q->data = (element*)malloc(size * sizeof(element));
    if (q->data == NULL)
        error("Queue ���ҵ鿡 ���� �޸� �Ҵ� ����.");

    // ť�� �ʱ� ���� ����: front�� rear�� -1�� �ʱ�ȭ (�� ť�� �ǹ�)
    q->front = -1;
    q->rear = -1;
    q->capacity = size;  // ����ڰ� �Է��� ť ũ��� ����
    return q;
}

// isFull() �Լ�: ť�� ���� á���� Ȯ���մϴ�.
// ���ϰ�: ť�� �� á���� 1, �ƴϸ� 0�� ��ȯ
int isFull(Queue* q)
{
    return q->rear == q->capacity - 1;
}

// isEmpty() �Լ�: ť�� ����ִ��� Ȯ���մϴ�.
// ���ϰ�: ť�� ��������� 1, �ƴϸ� 0�� ��ȯ
int isEmpty(Queue* q)
{
    return q->front == q->rear;
}

// enqueue() �Լ�: ť�� ���Ҹ� �����մϴ�.
// �Ű�����: q - ť ����ü ������, item - ������ ����
void enqueue(Queue* q, int item)
{
    // ť�� ���� á���� ���� Ȯ��
    if (isFull(q)) {
        // ť�� ���Ұ� ���� ���, ���� Ȯ���� ���� �������� ���ҵ��� �̵���ŵ�ϴ�.
        if (!isEmpty(q)) {
            int j = 0;
            // front ���� �ε������� rear������ ���ҵ��� �迭�� �������� �̵�
            for (int i = q->front + 1; i <= q->rear; i++) {
                q->data[j++] = q->data[i];
            }
            // �̵� ��, rear �����͸� ������
            q->rear = q->rear - (q->front + 1);
            // front �����ʹ� �ٽ� -1�� �ʱ�ȭ (�̵� �� ù �ε��� �� ��ġ)
            q->front = -1;
        }
    }
    // �̵� �Ŀ��� ť�� ���� ���� ���� �޽��� ��� �� ����
    if (isFull(q)) {
        error("ť ��ȭ����.");
        return;
    }
    // rear�� ������Ű�鼭 ���ο� ���� ����
    q->data[++(q->rear)] = item;
}

// dequeue() �Լ�: ť���� front�� ��ġ�� ���Ҹ� �����ϰ� ��ȯ�մϴ�.
// �Ű�����: q - ť ����ü ������
// ���ϰ�: ������ ����
element dequeue(Queue* q)
{
    // ť�� ��������� ���� �޽��� ��� �� ����
    if (isEmpty(q)) {
        error("ť�� �������.");
        return -1; // ���α׷� ����� ���� �������� ����
    }
    // front �����͸� ������Ű�� �ش� ��ġ�� ���Ҹ� ��ȯ
    int item = q->data[++(q->front)];
    return item;
}

// queue_print() �Լ�: ť�� ���� ���¸� ����մϴ�.
// front�� rear �ε���, �׸��� �迭 ��ü ���¸� ���
void queue_print(Queue* q)
{
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    // ��ü �迭 ������ ��ȸ�ϸ鼭 ť�� �����ϴ� ���Ҵ� ���, �������� 'X' ���
    for (int i = 0; i < q->capacity; i++) {
        if (i > q->front && i <= q->rear)
            printf("%d ", q->data[i]);
        else
            printf(" X ");
    }
    printf("]\n");
}

// main() �Լ�: ť�� ������ �ÿ��մϴ�.
int main(void)
{
    int size;
    // ����ڷκ��� ť ũ�⸦ �Է� ����
    printf("ť ũ�� �Է� : ");
    scanf("%d", &size);

    // �Է¹��� ũ��� ť ����
    Queue* q = create(size);

    // ���� 10, 20, 30�� ť�� ����
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    // ���� ť ���� ���
    queue_print(q);

    // �� ���� ���Ҹ� ť���� ����
    dequeue(q);
    dequeue(q);
    // ���� �� ť ���� ���
    queue_print(q);

    // ���� 40, 50, 60�� �߰� �����Ͽ� shifting ���� �ÿ�
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    // ���� ť ���� ���
    queue_print(q);

    return 0;
}