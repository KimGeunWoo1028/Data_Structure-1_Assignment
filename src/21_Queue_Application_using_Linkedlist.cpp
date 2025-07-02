#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// element Ÿ���� int�� �����մϴ�.
typedef int element;

// ���� ����Ʈ�� ��� ����ü ���� (������ ����)
typedef struct Listnode {
    element data;           // ��忡 ������ ������
    struct Listnode* link;  // ���� ��带 ����Ű�� ������
} Listnode;

// ť ����ü ����: front�� rear ������ �� ť�� ũ�⸦ ����
typedef struct Queue {
    Listnode* front; // ť�� ����(ù ��° ���)�� ����Ű�� ������
    Listnode* rear;  // ť�� ����(������ ���)�� ����Ű�� ������
    int size;        // ť�� ����� ����� ��
} Queue;

// �Լ�: create
// ----------------
// ���ο� �� ť�� �����Ͽ� �ʱ�ȭ�� ��, �ش� ť�� �����͸� ��ȯ�մϴ�.
Queue* create() {
    // ť�� ���� �޸𸮸� ���� �Ҵ��մϴ�.
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q)
        return NULL; // �޸� �Ҵ翡 �����ϸ� NULL ��ȯ

    // ť�� �� ���·� �ʱ�ȭ: front�� rear�� NULL, size�� 0
    q->front = q->rear = NULL;
    q->size = 0;
    return q; // ������ ť�� �ּ� ��ȯ
}

// �Լ�: isEmpty
// -----------------
// ť�� ����ִ��� Ȯ���ϴ� �Լ��Դϴ�. (front�� NULL�̸� �������)
int isEmpty(Queue* q) {
    return (q->front == NULL); // front�� NULL�̸� ��������Ƿ� 1 ��ȯ, �ƴϸ� 0 ��ȯ
}

// �Լ�: enqueue
// -----------------
// ť�� ���ο� �����͸� �����մϴ�. ť�� ũ�Ⱑ 10 �̻��̸� ���� �޽����� ����ϰ� ���α׷��� �����մϴ�.
// ����, �ߺ� ���������� Ȯ���Ͽ� �ߺ��̸� �������� �ʽ��ϴ�.
void enqueue(Queue* q, element data) {
    // ť�� ũ�Ⱑ �ִ� ũ��(10)�� ������ ���
    if (q->size >= 10) {
        printf("Queue is Full. Exit program.\n");
        exit(1);
    }

    // ť�� �̹� ������ �����Ͱ� �ִ��� Ȯ�� (�ߺ� Ȯ��)
    Listnode* current = q->front;
    while (current != NULL) {
        if (current->data == data)
            return; // �ߺ� �������̸� �������� �ʰ� ��ȯ
        current = current->link;
    }

    // �� �����͸� ������ ��带 ���� �Ҵ��մϴ�.
    Listnode* newnode = (Listnode*)malloc(sizeof(Listnode));
    if (!newnode)
        return; // �޸� �Ҵ� ���� �� �Լ� ����

    // �� ����� ������ ���� �� ���� ��带 ����Ű�� �����͸� NULL�� �ʱ�ȭ�մϴ�.
    newnode->data = data;
    newnode->link = NULL;

    // ť�� �� �ڿ� �� ��带 �����մϴ�.
    if (q->rear != NULL)
        q->rear->link = newnode; // ���� rear�� link�� �� ��带 ����Ű���� ��
    q->rear = newnode; // rear �����͸� �� ���� ������Ʈ

    // ť�� ����־��ٸ� front �� �� ��带 ����Ű�� ��
    if (q->front == NULL)
        q->front = q->rear;

    // ť�� ũ�⸦ ������Ű�� ���Ե� �����͸� ���
    q->size++;
    printf("Enqueued : %d\n", data);
}

// �Լ�: dequeue
// -----------------
// ť�� ���ʿ� �ִ� �����͸� �����ϰ� �� ���� ��ȯ�մϴ�.
// ť�� ����ִٸ� "Queue is Empty" �޽����� ����ϰ� -1�� ��ȯ�մϴ�.
int dequeue(Queue* q) {
    // ť�� ����ִ� ���
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
        return -1;
    }

    // front ��带 �ӽ� ������ �����ϰ�, �� ����� �����͸� �����ɴϴ�.
    Listnode* temp = q->front;
    int data = q->front->data;

    // front �����͸� ���� ���� �̵���ŵ�ϴ�.
    q->front = q->front->link;

    // ���� ť�� ��� �Ǹ� rear�� NULL�� �����մϴ�.
    if (q->front == NULL)
        q->rear = NULL;

    // ������ ����� �޸𸮸� �����ϰ� ť�� ũ�⸦ ���ҽ�ŵ�ϴ�.
    free(temp);
    q->size--;

    // ������ ������ ���� ����ϰ� ��ȯ
    printf("Dequeued : %d\n", data);
    return data;
}

// �Լ�: printqueue
// --------------------
// ť�� ����Ǿ� �ִ� ��� �����͸� �տ��� �ڱ��� ����մϴ�.
void printqueue(Queue* q) {
    // ť�� ��������� �� ���ȣ�� ����մϴ�.
    if (isEmpty(q)) {
        printf("[ ]\n");
        return;
    }

    // ť�� front���� ��ȸ�ϱ� ���� ������ ����
    Listnode* current = q->front;

    printf("[ ");

    // ��� ��带 ��ȸ�ϸ鼭 �����͸� ����մϴ�.
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }

    printf("]\n"); // ��� ������ ������ �մϴ�.
}

// ���� �Լ�: ���α׷��� ������
int main() {
    // ���� �ð��� ������� ���� ��ȣ ������ �õ带 �����մϴ�.
    srand((unsigned int)time(NULL));

    // �� ť�� �����մϴ�.
    Queue* q = create();

    // ���� �ݺ������� ���� ������ ��� �����մϴ�.
    while (1) {
        // 1���� 100 ������ ���� ���� �����մϴ�.
        int r = rand() % 100 + 1;
        // ������ ���� ���� 3���� ���� �������� ����մϴ�.
        int map = r % 3;

        // ������ ���� ���� map ���� ����մϴ�.
        printf("Random value : %d (map : %d)\n", r, map);

        // map ���� ¦���̸� enqueue, Ȧ���̸� dequeue ����
        if (map % 2 == 0) {
            enqueue(q, r);
        }
        else {
            dequeue(q);
        }

        // ���� ť�� ���¸� ����մϴ�.
        printqueue(q);
    }
}
