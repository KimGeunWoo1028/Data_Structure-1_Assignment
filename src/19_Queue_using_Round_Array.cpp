#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ť ����(element)�� �ڷ����� int�� ����
typedef int element;

// ���� ť�� ����ü ����: front�� rear �ε���, ť�� ũ��, ť ���ҵ��� ������ ���� �迭 ����
typedef struct {
    int front, rear;    // front: ť�� ���� �ε���, rear: ť�� ������ �ε���
    int capacity;       // ť�� �� ũ��
    int* array;         // ť ���ҵ��� ������ �迭
} QueueType;

// ���� �޽����� ����ϰ� ���α׷��� �����ϴ� �Լ�
void error(const char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// ������ ũ��� ť�� �����ϴ� �Լ�
QueueType* Queue(int size) {
    // QueueType ����ü�� �޸� �Ҵ�
    QueueType* Q = (QueueType*)malloc(sizeof(QueueType));
    if (!Q)
        return NULL;

    Q->capacity = size;         // ť�� ũ�� ����
    Q->front = Q->rear = -1;      // �ʱ� ����: ť�� ��������� -1�� ����

    // ť ���ҵ��� ������ �迭 �޸� �Ҵ�
    Q->array = (element*)malloc(Q->capacity * sizeof(element));
    if (!Q->array)
        return NULL;

    return Q;
}

// ť�� ����ִ��� �˻��ϴ� �Լ� (front�� -1�̸� ť�� �������)
int isEmpty(QueueType* Q) {
    return (Q->front == -1);
}

// ���� ť�� ��ȭ �������� �˻��ϴ� �Լ� (rear�� ���� ��ġ�� front�� ������ ��ȭ ����)
int isFull(QueueType* Q) {
    return ((Q->rear + 1) % Q->capacity == Q->front);
}

// ť�� �Ҵ�� �޸𸮸� �����ϴ� �Լ�
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
        error("Queue Overflow\n"); // ť�� �� �� ��� ���� �޽��� ��� �� ����
        return;
    }
    else {
        // ���� ť ��Ŀ� ���� rear �ε��� ����
        Q->rear = (Q->rear + 1) % Q->capacity;
        Q->array[Q->rear] = item;  // item ����
        // ó�� ������ ���� �� front�� rear�� �����ϰ� ����
        if (Q->front == -1)
            Q->front = Q->rear;
    }
}

// ť���� ���Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
element deQueue(QueueType* Q) {
    int data = 0;
    if (isEmpty(Q)) {
        error("Queue is empty");  // ť�� ��������� ���� ��� �� ����
        return -1;
    }
    else {
        data = Q->array[Q->front]; // front ��ġ�� ���Ҹ� ����
        // ť�� �� �ϳ��� ���Ҹ� �����ִٸ� ť�� ����ִ� ���·� �ʱ�ȭ
        if (Q->front == Q->rear)
            Q->front = Q->rear = -1;
        else
            // ���� ť ��Ŀ� ���� front �ε����� ����
            Q->front = (Q->front + 1) % Q->capacity;
    }
    return data;
}

// ť�� ���¸� ����ϴ� �Լ�
void queue_print(QueueType* q)
{
    printf("Queue (front: %d, rear: %d) : [ ", q->front, q->rear);
    if (!isEmpty(q)) {
        int i = q->front;
        // front���� rear���� ť ���ҵ��� ������� ��� (wrap-around ���)
        while (1) {
            printf("%d ", q->array[i]);
            if (i == q->rear)
                break;
            i = (i + 1) % q->capacity;
        }
    }
    printf("]\n");
}

// ť�� ������ Ȯ���ϴ� �Լ�
// front�� rear���� ������ ������, �׷��� ������ ������(���� �迭�� wrap-around ��Ȳ)
int checkDirection(QueueType* q)
{
    if (isEmpty(q)) {
        error("Queue is empty.\n");
        return -1;
    }

    if (q->front < q->rear) {
        return 1;  // ������
    }
    else {
        return 0;  // ������
    }
}

// ���������� �Ǿ� �ִ� ť�� ���������� �����ϴ� �Լ�
void ChangeDirection(QueueType* q)
{
    // �̹� �������̸� ������ �ʿ䰡 �����Ƿ� �Լ� ����
    if (q->front <= q->rear)
        return;

    int size;
    // ť�� ����� �� ������ ���� ��� (wrap-around ���)
    if (q->front <= q->rear)
        size = q->rear - q->front + 1;
    else
        size = (q->capacity - q->front) + (q->rear + 1);

    // �� �迭�� ť�� ���ҵ��� ������� ��迭�ϱ� ���� �޸� �Ҵ�
    element* newArray = (element*)malloc(size * sizeof(element));
    if (!newArray) {
        error("�޸� �Ҵ� ����");
        return;
    }

    int index = 0;
    int i = q->front;
    // front���� rear���� ���ҵ��� �� �迭�� ����
    while (1) {
        newArray[index++] = q->array[i];
        if (i == q->rear)
            break;
        i = (i + 1) % q->capacity;
    }

    // ���� �迭�� �޸𸮸� ����
    free(q->array);

    // ť�� �� �迭�� �����ϰ� front, rear �ε����� �缳�� (������ �迭�� ����)
    q->array = newArray;
    q->front = 0;
    q->rear = size - 1;
}

int main()
{
    int size;
    // ����ڷκ��� ť�� ����� �Է¹���
    printf("ť ������ �Է� : ");
    scanf("%d", &size);

    // �Է¹��� ������� ť ����
    QueueType* q = Queue(size);

    // enQueue ������ �����Ͽ� �����͸� ����
    enQueue(q, 10);
    enQueue(q, 20);
    enQueue(q, 30);

    // ���� ť�� ���¸� ���
    queue_print(q);

    // deQueue ������ ���� �����͸� ����
    deQueue(q);
    deQueue(q);

    // ���� �� ť�� ���� ���
    queue_print(q);

    // �߰� �����͸� ����
    enQueue(q, 40);
    enQueue(q, 50);
    enQueue(q, 60);
    enQueue(q, 70);

    // ���� �� ť�� ���� ���
    queue_print(q);

    // ť�� ����(������/������)�� Ȯ��
    if (!checkDirection(q)) {
        // ť�� �������̸� ���������� ����
        printf("�������Դϴ�. ���������� �ٲߴϴ�.\n");
        ChangeDirection(q);
        queue_print(q);
    }
    else
        printf("�������Դϴ�.");

    // ���� �Ҵ�� �޸� ����
    deleteQueue(q);

    return 0;
}
