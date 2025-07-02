#define _CRT_SECURE_NO_WARNINGS  // Visual Studio���� scanf �� ��� �� ���� ��� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000  // �׽�Ʈ�� �迭/���Ḯ��Ʈ�� �⺻ ũ��

typedef int element;  // ����Ʈ�� ����� �������� �ڷ��� ���� (����� int��)

/* ���� ���� ����Ʈ ��带 �����ϴ� ����ü */
typedef struct listnode {
	element data;              // ��忡 ����� ������
	struct listnode* next;     // ���� ��带 ����Ű�� ������
} listnode;

/* ����Ʈ�� �� ��(head)�� �� ��带 �����ϴ� �Լ� */
listnode* insert_head(listnode* head, element value)
{
	// �� ��带 ���� ���� �޸� �Ҵ�
	listnode* new_node = (listnode*)malloc(sizeof(listnode));
	new_node->data = value;     // ������ ����
	new_node->next = head;      // �� ����� next�� ���� head�� ����Ŵ
	return new_node;            // �� ��带 ���ο� head�� ��ȯ
}

/* ����Ʈ�� ��� ��带 �޸𸮿��� �����ϴ� �Լ� */
void freelist(listnode* head)
{
	listnode* temp;
	while (head != NULL) {
		temp = head;           // ���� head�� �ӽ÷� ����
		head = head->next;     // head�� ���� ���� �̵�
		free(temp);            // �ӽ÷� ������ ��带 �޸� ����
	}
}

/* ����Ʈ���� Ư�� �ε���(index)�� ��ġ�� �����͸� ��ȯ�ϴ� �Լ� */
element get(listnode* head, int index)
{
	listnode* cur = head;       // ���� ��带 ����ų ������
	for (int i = 0; i < index; i++) {
		cur = cur->next;        // index ��ġ���� �̵�
	}
	return cur->data;           // index ��° ����� data ��ȯ
}

/* ����Ʈ���� Ư�� ��ġ(index)�� ��带 �����ϴ� �Լ� */
listnode* delete_position(listnode* head, int index)
{
	// ù ��° ��带 �����ϴ� ���
	if (index == 0) {
		listnode* temp = head;      // ������ ��� ����
		head = head->next;          // head�� ���� ���� ����
		free(temp);                 // ������ ��� �޸� ����
		return head;                // ���ο� head ��ȯ
	}

	// ������ ����� �ٷ� ���� ��带 ã��
	listnode* cur = head;
	for (int i = 0; i < index - 1; i++) {
		cur = cur->next;            // index - 1 ��° ������ �̵�
	}

	// ������ ��带 cur->next�� ����
	listnode* temp = cur->next;
	if (temp) {
		cur->next = temp->next;     // ���� ��尡 ���� ��带 �ǳʶٵ��� ����
		free(temp);                 // ���� ��� ����
	}
	return head;                    // ����� ����Ʈ ��ȯ
}

/* main �Լ�: �迭�� ���� ����Ʈ�� ����/����/���� �ӵ� �� */
int main()
{
	element array[SIZE];         // ���� �迭 ����
	clock_t start, end;          // �ð� ������ ����
	double t;                    // ���� �ð� ����
	double sum;                  // �հ� ����
	int random[1000];            // ���� �ε��� ����� �迭

	printf("\n=========================================\n\n");

	srand(time(NULL));           // ���� �õ� �ʱ�ȭ

	/* �迭 �ʱ�ȭ: 0���� SIZE-1������ �� ���� */
	start = clock();
	for (int i = 0; i < SIZE; i++) {
		array[i] = i;
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Array �ɸ� �ð� : %f�� \n", t);

	/* ���� ����Ʈ �ʱ�ȭ: 0���� SIZE-1������ �� ���� */
	listnode* head = NULL;
	start = clock();
	for (int i = SIZE - 1; i >= 0; i--) {
		head = insert_head(head, i);  // �׻� �տ� ���� �� ���� ����� 0 ~ SIZE-1 ����
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Linked list �ɸ� �ð� : %f�� \n", t);

	printf("\n=========================================\n\n");

	/* 0 ~ SIZE-1 ������ ���� �ε��� 1000�� ���� */
	for (int i = 0; i < 1000; i++) {
		random[i] = rand() % SIZE;
	}

	/* �迭���� ���� �ε��� ���� */
	sum = 0;
	start = clock();
	for (int i = 0; i < 1000; i++) {
		sum += array[random[i]];  // O(1) ����
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Array random access �ɸ� �ð� : %f�� \n", t);
	printf("Array random access index �� : %.2f \n\n", sum);

	/* ���� ����Ʈ���� ���� �ε��� ���� */
	sum = 0;
	start = clock();
	for (int i = 0; i < 1000; i++) {
		sum += get(head, random[i]);  // O(n) ����
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Linked List random access �ɸ� �ð� : %f�� \n", t);
	printf("Linked List random access index �� : %.2f \n", sum);

	printf("\n=========================================\n\n");

	/* �迭���� 1000���� ��Ҹ� �������� ���� */
	int cur_size = SIZE; // �迭�� ���� ��ȿ ũ��
	start = clock();
	for (int i = 0; i < 1000; i++) {
		int index = rand() % cur_size;
		for (int j = index; j < cur_size - 1; j++) {
			array[j] = array[j + 1]; // ������ �ε��� ������ ��Ҹ� �������� �� ĭ�� �̵�
		}
		cur_size--; // �迭 ũ�� ����
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("array random delete �ɸ� �ð� : %f��\n", t);

	/* ���� ����Ʈ���� 1000���� ��带 �������� ���� */
	start = clock();
	cur_size = SIZE;
	for (int i = 0; i < 1000; i++) {
		int index = rand() % cur_size;
		head = delete_position(head, index);
		cur_size--;
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("linked list random delete �ɸ� �ð� : %f�� \n", t);

	printf("\n=========================================\n\n");

	/* ���� ����Ʈ�� �Ҵ�� �޸� ���� */
	freelist(head);

	return 0;
}