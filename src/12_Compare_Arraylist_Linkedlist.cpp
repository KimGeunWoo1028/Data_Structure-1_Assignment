#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS   // MSVC ȯ�濡�� ���� ��� �����ϱ� ���� ��ũ��
#define SIZE 10000                // �迭�� ���� ����Ʈ�� �� ��� ������ ����

// element �ڷ����� int�� ���� (�ʿ信 ���� �ٸ� �ڷ��� ��� ����)
typedef int element;

// ���� ����Ʈ�� ��� ����ü ����
typedef struct listnode {
    element data;             // ��尡 �����ϴ� ������
    struct listnode* next;    // ���� ��带 ����Ű�� ������
} listnode;

// ���� ���� ����Ʈ�� �Ӹ��� �� ��带 �����ϴ� �Լ� ����
// �Ű�����: ���� ����Ʈ�� �Ӹ�(head), ������ ��(value)
// ��ȯ��: ���� ������ ��尡 ����� ���ο� ����Ʈ�� �Ӹ�
listnode* insert_head(listnode* head, element value)
{
    // �� ��带 ���� �޸� �Ҵ�
    listnode* new_node = (listnode*)malloc(sizeof(listnode));
    // �� ��忡 ������ ����
    new_node->data = value;
    // �� ����� next �����Ͱ� ���� ����Ʈ�� head�� ����Ű�� �� (���� ��ġ: ����Ʈ�� �� ��)
    new_node->next = head;
    // �� ��尡 ���ο� ����Ʈ�� �Ӹ� ������ ��
    return new_node;
}

// ���� ���� ����Ʈ�� ��� ��带 �����ϴ� �Լ� ����
// �Ű�����: ������ ����Ʈ�� �Ӹ�(head)
void freelist(listnode* head)
{
    listnode* temp; // �ӽ� ������: ���� ������ ��带 ����
    // head�� NULL�� �� ������ ��� ����� �޸� ����
    while (head != NULL) {
        temp = head;           // ���� head�� �ӽ� ����
        head = head->next;     // head�� ���� ���� �̵�
        free(temp);            // �ӽ� ����� ��� �޸� ����
    }
}

// ���� ���� ����Ʈ���� Ư�� �ε����� ���� �о���� �Լ� ����
// �Ű�����: ����Ʈ�� �Ӹ�(head), �о�� �ε���(index; 0���� ����)
// ��ȯ��: �ش� �ε����� ��忡 ����� ������
element get(listnode* head, int index)
{
    listnode* cur = head; // Ž�� ���� ���
    // ���ϴ� �ε����� ������ ������ ��带 ���������� �̵�
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    // �ش� ����� �����͸� ��ȯ
    return cur->data;
}

// ���� ���� ����Ʈ���� Ư�� �ε����� ��带 �����ϴ� �Լ� ����
// �Ű�����: ����Ʈ�� �Ӹ�(head), ������ ����� ��ġ(index; 0���� ����)
// ��ȯ��: ������ �Ϸ�� ���� ����Ʈ�� �Ӹ�
listnode* delete_position(listnode* head, int index)
{
    // ������ ��ġ�� 0�̸�, ����Ʈ�� ù ��° ��带 ����
    if (index == 0) {
        listnode* temp = head;    // ������ ù ��° ��带 �ӽ� ����
        head = head->next;        // head�� �� ��° ���� ������Ʈ
        free(temp);               // ������ ù ��° ��� �޸� ����
        return head;
    }

    // ������ ����� �ٷ� ���� ������ Ž��
    listnode* cur = head;
    for (int i = 0; i < index - 1; i++) {
        cur = cur->next;
    }

    // cur->next�� ������ ��带 ����Ŵ
    listnode* temp = cur->next;
    if (temp) {
        // ������ ��带 ����Ʈ���� �����ϰ�, ������ �缳��
        cur->next = temp->next;
        free(temp); // ������ ����� �޸� ����
    }
    return head;
}

// ���� main �Լ�: �迭�� ���� ����Ʈ�� Ȱ���� �ð� ���� �� ��� �׽�Ʈ ����
int main(void)
{
    element array[SIZE];       // ������ �迭 ���� (�� SIZE �� ���)
    clock_t start, end;        // �ð� ������ ���� ����
    double t;                  // ���� �ð� (�� ����) ���� ����
    double sum;                // �հ� ���� ����
    int random[1000];          // ���� �ε��� 1000���� ������ �迭

    // ���� ������ �˸��� ���м� ���
    printf("\n=========================================\n\n");

    // ���� �ð��� �������� ���� ���� �ʱ�ȭ
    srand(time(NULL));

    // ���� �迭 ��� �ʱ�ȭ �� �ð� ���� ����
    start = clock();
    // �迭�� 0���� SIZE-1���� ���������� �� ����
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }
    end = clock();
    // �迭 �ʱ�ȭ�� �ҿ�� �ð� ���
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array �ɸ� �ð� : %f�� \n", t);

    // ���� ���� ����Ʈ �ʱ�ȭ (�� �� ���� ���) �� �ð� ���� ����
    listnode* head = NULL; // ���� ����Ʈ�� �ʱ� �Ӹ��� NULL
    start = clock();
    // SIZE-1���� 0���� �������� �����ϸ� ����Ʈ�� ������ 0���� SIZE-1���� ������
    for (int i = SIZE - 1; i >= 0; i--) {
        head = insert_head(head, i);
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked list �ɸ� �ð� : %f�� \n", t);

    // ���� ���м� ��� ����
    printf("\n=========================================\n\n");

    // ���� 1000���� ���� �ε��� ���� ����
    for (int i = 0; i < 1000; i++) {
        random[i] = rand() % SIZE; // 0���� SIZE-1 ������ ���� �ε��� ����
    }

    // ���� �迭�� �̿��� ���� ���� �� �� ���� ����
    sum = 0;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        // ���� �ε����� �ش��ϴ� �迭 ��� ���� �ջ�
        sum += array[random[i]];
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array random access �ɸ� �ð� : %f�� \n", t);
    printf("Array random access index �� : %.2f \n\n", sum);

    // ���� ���� ����Ʈ�� �̿��� ���� ���� �� �� ���� ����
    sum = 0;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        // ���� ����Ʈ���� get() �Լ��� ȣ���Ͽ� index ��ġ�� �����͸� ��� �ջ�
        sum += get(head, random[i]);
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked List random access �ɸ� �ð� : %f�� \n", t);
    printf("Linked List random access index �� : %.2f \n", sum);

    // ���� ���м� ��� ����
    printf("\n=========================================\n\n");

    // ���� �迭���� ���� ���� ���� ����
    int cur_size = SIZE; // ���� �迭�� ��ȿ ũ�� ���� ����
    start = clock();
    for (int i = 0; i < 1000; i++) {
        int index = rand() % cur_size; // ���� ���� ũ�� �� ������ ���� ��ġ ����
        // ������ ��ġ�� ä��� ����, ������ ��ҵ��� �� ĭ�� ������ �̵�
        for (int j = index; j < cur_size - 1; j++) {
            array[j] = array[j + 1];
        }
        cur_size--; // ���� �� �迭�� ũ�� ����
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Array random deletion �ɸ� �ð� : %f�� \n", t);

    /*
    // ���� ���� ����Ʈ���� ���� ���� ���� ���� ����
    // �迭 ������ �����ϰ�, ���� ���� ��� ����(cur_size)�� ������� ���� ��ġ�� ��带 ������
    cur_size = SIZE;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        int index = rand() % cur_size;
        head = delete_position(head, index); // index ��ġ�� ��带 ����
        cur_size--;                        // ����Ʈ�� ũ�� ����
    }
    end = clock();
    t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Linked List random deletion �ɸ� �ð� : %f�� \n", t);
    */

    // ���� ���� ����Ʈ ������ �޸� ���� ����
    freelist(head);

    return 0;
}