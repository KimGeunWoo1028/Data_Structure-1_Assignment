#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ť�� �ִ� ũ��, ��ü �½�ũ ����, �½�ũ ���� �ֱ�(��)
#define MAX_QUEUE_SIZE 3
#define TOTAL_TASKS 6
#define TASK_GEN_INTERVAL 7

// Task ����ü: �½�ũ�� id, ���� ó�� �ð�, ���� �ð��� ����
typedef struct {
    int id;            // �½�ũ ���� ��ȣ
    int remain_time;   // �½�ũ�� ó���� �ʿ��� ���� �ð�
    int gen_time;      // �½�ũ�� ������ �ð� (clock ��)
} Task;

// Queue ����ü: ���� ť�� �̿��Ͽ� �½�ũ���� ����
typedef struct {
    Task data[MAX_QUEUE_SIZE]; // �½�ũ���� ������ �迭
    int front;                 // ť�� ���� �ε���
    int rear;                  // ���ο� �½�ũ�� �� ��ġ�� �ε���
    int count;                 // ���� ť�� ����� �½�ũ ��
} Queue;

// ť�� �ʱ� ���·� �����ϴ� �Լ�
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// ť�� ���� á���� Ȯ���ϴ� �Լ�
int isFull(Queue* q) {
    return q->count == MAX_QUEUE_SIZE;
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q) {
    return q->count == 0;
}

// ť�� �½�ũ�� �����ϴ� �Լ�
// ť�� ���� ���� 0�� �����Ͽ� ���� ���и� �˸�
int enqueue(Queue* q, Task t) {
    if (isFull(q)) return 0; // ť�� ���� ���� �½�ũ �ս� �߻�
    q->data[q->rear] = t;    // ���� rear ��ġ�� �½�ũ�� ����
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // ���� ť ������� rear ����
    q->count++;              // ť�� ����� �½�ũ �� ����
    return 1;                // ���������� �½�ũ�� ������
}

// ť���� �½�ũ�� �����ϴ� �Լ�
// ť�� ��������� 0�� �����Ͽ� ���� ���и� �˸�
int dequeue(Queue* q, Task* t) {
    if (isEmpty(q)) return 0; // ť�� ��������� ���� �Ұ�
    *t = q->data[q->front];   // front ��ġ�� �½�ũ�� ������
    q->front = (q->front + 1) % MAX_QUEUE_SIZE; // ���� ť ������� front ����
    q->count--;               // ť�� ����� �½�ũ �� ����
    return 1;                 // ���������� �½�ũ�� ������
}

int main() {
    srand(time(NULL)); // ���� ������ ���� �õ� ����

    Queue q;
    initQueue(&q); // ť �ʱ�ȭ

    int clock = 0;             // ��ü �ùķ��̼� �ð��� ��Ÿ���� clock ����
    int tasks_generated = 0;   // ������ �½�ũ ��
    int tasks_finished = 0;    // �Ϸ�� �½�ũ ��

    Task current_task;         // ���� �������� �½�ũ�� �����ϴ� ����
    int processing = 0;        // �½�ũ ó�� ���� (0: ó�� �� �ƴ�, 1: ó�� ��)

    int processing_time_left = 0;   // ���� �½�ũ�� ���� ó�� �ð�
    int total_processing_time = 0;  // ���� �½�ũ�� �� ó�� �ð� (��¿�)

    // ��ü �½�ũ�� �Ϸ�� ������ �ùķ��̼��� ����
    while (tasks_finished < TOTAL_TASKS) {
        // 1. �½�ũ ���� �ܰ�
        // ����: ��ü ���� �½�ũ ���� TOTAL_TASKS���� ������, clock�� TASK_GEN_INTERVAL�� ����� ��
        if (tasks_generated < TOTAL_TASKS && clock % TASK_GEN_INTERVAL == 0) {
            int t_id = tasks_generated + 1;            // �½�ũ id�� ���� ������� ����
            int t_remain = (rand() % 11) + 5;            // 5�� �̻� 15�� ������ ���� ó�� �ð� ����
            Task new_task = { t_id, t_remain, clock };   // ���ο� �½�ũ ����ü ����

            // ť�� �½�ũ ���� �õ�, ���� �� �½�ũ �ս� �޽��� ���
            if (!enqueue(&q, new_task)) {
                printf("[ Task Loss �߻� at clock %d ]\n", clock);
            }
            else {
                // ���� ���� �� �½�ũ ���� ���
                printf("task enqueue at clock %d : task %d, remain_time %d\n", clock, new_task.id, new_task.remain_time);
            }
            tasks_generated++; // ������ �½�ũ �� ����
        }

        // 2. �½�ũ ó�� ���� �ܰ�
        if (!processing) { // ���� ó������ �½�ũ�� ������
            if (!isEmpty(&q)) { // ��� ���� �½�ũ�� �ִ� ���
                dequeue(&q, &current_task);   // ť���� �½�ũ�� �����Ͽ� ������
                processing = 1; // �½�ũ ó�� ���� Ȱ��ȭ
                processing_time_left = current_task.remain_time; // ���� ó�� �ð��� �ش� �½�ũ�� remain_time���� ����
                total_processing_time = current_task.remain_time; // �� ó�� �ð� ��� (��¿�)
                printf("\n���� ó���� task : %d\n", current_task.id);
            }
        }

        // 3. ���� �½�ũ ó�� ����
        if (processing) {
            // ���� ó�� �ð��� ��� (���� ���� ǥ��)
            printf("%d ", processing_time_left);

            // ť�� ������� �½�ũ�� �ְ�, ���� �ð��� ��ü ó�� �ð��� ���ݿ� �������� ��
            if (q.count > 0 && processing_time_left == total_processing_time / 2) {
                // ���� ó���� �½�ũ id�� ���� ���
                printf("\n[ ���� task ���� : %d ]\n", q.data[q.front].id);
            }

            // ���� �ð��� 1���� ���, 0�� ����Ͽ� ���� �������� �˸�
            if (processing_time_left == 1) {
                printf("0\n");
            }

            processing_time_left--; // 1�� ó�� ���� �� ���� �ð� ����

            // �½�ũ ó�� �Ϸ� ��
            if (processing_time_left == 0) {
                printf("<Task�� %d�� ���� ó���Ϸ�>\n\n", total_processing_time);
                processing = 0;   // ó�� ���¸� ����
                tasks_finished++; // �Ϸ�� �½�ũ �� ����
            }
        }

        clock++; // �ùķ��̼� clock 1�� ����
    }

    // ��ü �ùķ��̼� �ҿ� �ð�(��) ���
    printf("��ü ����ð� : %d��\n", clock);

    return 0; // ���α׷� ���� ����
}
