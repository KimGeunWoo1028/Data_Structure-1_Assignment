#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ť�� ������ ������ �ڷ��� ���� (������)
typedef int element;

// ���� ť�� ǥ���ϴ� ����ü ����
typedef struct {
    int front, rear;    // front: ���� ��ġ, rear: ���� ��ġ
    int capacity;       // ť�� �ִ� ���� ������ ������ ����
    int* array;         // ť ���ҵ��� ������ �迭
} QueueType;

// ���� �߻� �� �޽����� ����ϰ� ���α׷��� �����ϴ� �Լ�
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ������ ũ���� ���� ť�� �����ϴ� �Լ�
QueueType* Queue(int size) {
    QueueType* Q = (QueueType*)malloc(sizeof(QueueType)); // ť ����ü �����Ҵ�
    if (!Q)
        return NULL;
    Q->capacity = size;               // ť�� �뷮 ����
    Q->front = Q->rear = -1;          // �ʱ� ����: ť�� ��� ����
    Q->array = (element*)malloc(Q->capacity * sizeof(element)); // ť ���� ����� �迭 �����Ҵ�
    if (!Q->array)
        return NULL;
    return Q;
}

// ���� ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(QueueType* Q) {
    return (Q->front == -1);
}

// ���� ť�� ���� á���� Ȯ���ϴ� �Լ�
int isFull(QueueType* Q) {
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

// ť�� ť�� �迭 �޸𸮸� �����ϴ� �Լ�
void deleteQueue(QueueType* Q) {
    if (Q) {
        if (Q->array)
            free(Q->array);
    }
    free(Q);
}

// ť�� rear ��ġ�� ���Ҹ� �����ϴ� �Լ�
void enQueue(QueueType* Q, element item) {
    if (isFull(Q)) {
        error("Queue Overflow\n");
        return;
    }
    // rear �ε����� ���� (���� ������ ���� ���� ���� ���)
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->array[Q->rear] = item;         // ���ο� ���� ����
    // ù ��° ���� ������ ��� front�� ����
    if (Q->front == -1)
        Q->front = Q->rear;
}

// ť�� front ��ġ�� ���Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element deQueue(QueueType* Q) {
    int data = 0;
    if (isEmpty(Q)) {
        error("Queue is empty");
        return -1;
    }
    // front ��ġ�� ���� ��ȯ
    data = Q->array[Q->front];
    // ���� ť�� �� ���� ���Ҹ� �־��� ���, ť�� �� ���·� ����
    if (Q->front == Q->rear)
        Q->front = Q->rear = -1;
    else
        Q->front = (Q->front + 1) % Q->capacity; // ���� ���ҷ� front �̵�
    return data;
}

// ť�� ���� ����(�ε����� ���ҵ�)�� ����ϴ� �Լ�
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

// ť ������ ���ҵ��� ���� ������ ������(�տ��� �ڷ�)�̸� 1, �������̸� 0�� ��ȯ�ϴ� �Լ�
int checkDirection(QueueType* q)
{
    if (isEmpty(q)) {
        error("Queue is empty.\n");
        return -1;
    }
    if (q->front < q->rear)
        return 1; // ������: front�� rear���� ����
    else
        return 0; // ������: ���Ұ� wrap-around�� ����
}

// �������� ť�� ������ ���������� �����ϴ� �Լ�
void ChangeDirection(QueueType* q)
{
    // �������̸� ������ �ʿ䰡 ����
    if (q->front <= q->rear)
        return;

    int size;
    // �������� ���, ť�� ����� ������ �� ���
    if (q->front >= q->rear)
        size = (q->capacity - q->front) + (q->rear + 1);

    // �� �迭 �����Ҵ� (queue�� ����� ���� ����ŭ)
    element* newArray = (element*)malloc(size * sizeof(element));
    if (!newArray)
        error("Memory allocation failed in ChangeDirection");

    int index = 0;
    int i = q->front;
    // front���� rear���� ���������� ����
    while (1) {
        newArray[index++] = q->array[i];
        if (i == q->rear)
            break;
        i = (i + 1) % q->capacity;
    }

    // ���� �迭 �޸� ���� �� �� �迭�� ��ü
    free(q->array);
    q->array = newArray;
    q->front = 0;         // front �缳��
    q->rear = size - 1;   // rear�� ������ ������ �ε����� �缳��
}

int main()
{
    int size;
    // ����ڷκ��� ť�� ũ�⸦ �Է� ����
    printf("ť ������ �Է� : ");
    scanf("%d", &size);

    // ������ ũ���� ť ����
    QueueType* q = Queue(size);

    // �⺻ enQueue ����: ť�� ���� ����
    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 30);

    // ���� ť ���� ���
    queue_print(q);

    // deQueue ����: ť���� ���� 2�� ����
    deQueue(q);
    deQueue(q);

    // ���� �� ť ���� ���
    queue_print(q);

    // �߰� enQueue ����: wrap-around ��Ȳ�� ����� ���� ���� ���� ����
    enQueue(q, 40);
    enQueue(q, 50);
    enQueue(q, 60);
    enQueue(q, 70);

    // ����� ť ���� ���
    queue_print(q);

    // ť�� ���������� ���������� Ȯ��
    if (!checkDirection(q)) {
        printf("�������Դϴ�. ���������� �ٲߴϴ�.\n");
        // �������̸� ���������� ������ ����
        ChangeDirection(q);
        // ���� �� ť ���� ���
        queue_print(q);
    }
    else
        printf("�������Դϴ�.\n");

    // ����� �޸� ����
    deleteQueue(q);
    return 0;
}