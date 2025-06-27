/*
  ����: linked_list_operations.c
  ����: �� ���α׷��� ���� ���� ����Ʈ�� �����Ͽ� Ư�� ��ġ�� ��带 ����, �����ϰ�,
         Ư�� ���� ���� ��� �ڿ� ���ο� ��带 �����ϸ�, ����Ʈ ��ü�� ����ϴ� ������ �����ݴϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���� ����Ʈ ��忡 ����� ������ Ÿ�� ����
typedef int element;

// ���� ����Ʈ�� ��� ����ü ����
typedef struct ListNode {
    element data;              // ��忡 ����� ������
    struct ListNode* link;     // ���� ��带 ����Ű�� ������
} ListNode;

/*
  �Լ�: insert_position
  ����: ������ ��ġ�� ���ο� ��带 �����ϴ� �Լ�.
  �Ű�����:
    head - ���� ����Ʈ�� ��� ������.
    position - ���ο� ��带 ������ ��ġ (1���� �����ϴ� �ε���).
    value - ���ο� ��忡 ������ ������ ��.
  ��ȯ��:
    ���ŵ� ���� ����Ʈ�� ��� ������.
*/
ListNode* insert_position(ListNode* head, int position, element value) {
    int k = 1;                // ���� ��ġ ī����
    ListNode* p = NULL;       // ����Ʈ ��ȸ�� ���� ������
    ListNode* q = NULL;       // ���� ��ġ�� ���� ��带 ����Ű�� ������

    // �� ��带 ���� �޸� �Ҵ�
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return head;
    }
    newNode->data = value;    // �� ��忡 ������ ����
    newNode->link = NULL;     // �ʱ⿡�� ���� ��尡 �����Ƿ� NULL

    p = head;  // ����Ʈ�� ������ ����

    // ��� 1: ����Ʈ�� ���ۿ� ��� �߰� (position == 1)
    if (position == 1) {
        newNode->link = p;    // �� ��� ���� ��ũ�� ���� ��带 ����Ŵ
        head = newNode;       // ��带 ���ο� ���� ������Ʈ
    }
    else {
        // ������ ��ġ���� ����Ʈ�� ��ȸ
        while ((p != NULL) && (k < position)) {
            k++;              // ��ġ ī���� ����
            q = p;            // ���� ��� ����
            p = p->link;      // ���� ���� �̵�
        }
        // ��� 2: ����Ʈ�� ���� ���� (position�� ����Ʈ ũ�⺸�� ŭ)
        if (p == NULL) {
            q->link = newNode;
            newNode->link = NULL;
        }
        // ��� 3: ����Ʈ �߰��� ����
        else {
            q->link = newNode;
            newNode->link = p;
        }
    }
    return head;  // ������Ʈ�� ��� ��ȯ
}

/*
  �Լ�: delete_position
  ����: ������ ��ġ�� ��带 �����ϴ� �Լ�.
  �Ű�����:
    head - ���� ����Ʈ�� ��� ������.
    position - ������ ����� ��ġ (1���� �����ϴ� �ε���).
  ��ȯ��:
    ���ŵ� ���� ����Ʈ�� ��� ������.
*/
ListNode* delete_position(ListNode* head, int position) {
    ListNode* p = head;  // ������ ��带 ����Ű�� ������
    ListNode* q = NULL;  // ���� ���� ���� ��带 ����Ű�� ������
    int k = 1;           // ���� ��ġ ī����

    // ����Ʈ�� ����ִ� ���
    if (head == NULL) {
        printf("����Ʈ�� ��� ����.\n");
        return head;
    }

    // ��� 1: ù ��° ��带 �����ϴ� ���
    if (position == 1) {
        head = p->link;  // ��带 ���� ���� ������Ʈ
        free(p);         // �����Ǵ� ����� �޸� ����
        return head;
    }
    else {
        // ������ ��ġ���� ����Ʈ�� ��ȸ
        while ((p != NULL) && (k < position)) {
            k++;
            q = p;         // ���� ��带 ���� ���� ����
            p = p->link;   // ���� ���� �̵�
        }
        // ������ ��ġ�� ����Ʈ ������ ��� ���
        if (p == NULL) {
            printf("������ ��ġ�� ����Ʈ ������ ���.\n");
            return head;
        }
        else {
            // ������ ��带 ����Ʈ���� ���ܽ�Ű�� ���� ������ ���� ����
            q->link = p->link;
            free(p);   // �����Ǵ� ����� �޸� ����
            return head;
        }
    }
}

/*
  �Լ�: insert_after
  ����: Ư�� ���� ���� ��� �ڿ� ���ο� ��带 �����ϴ� �Լ�.
  �Ű�����:
    head - ���� ����Ʈ�� ��� ������.
    after - ���ο� ��带 ������ ������ �Ǵ� ��.
    value - ���ο� ��忡 ������ ������ ��.
  ��ȯ��:
    ������Ʈ�� ���� ����Ʈ�� ��� ������.
*/
ListNode* insert_after(ListNode* head, int after, element value) {
    ListNode* p = head;
    // ����Ʈ�� ��ȸ�ϸ� ����� �����Ͱ� ���� ���� ��ġ�ϴ��� Ȯ��
    while (p != NULL) {
        if (p->data == after) {
            // ���� ���� ã����, �� ��带 ���� �޸� �Ҵ�
            ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
            newnode->data = value;     // �� ��忡 ������ ����
            newnode->link = p->link;     // �� ��尡 ���� ��带 ����Ŵ
            p->link = newnode;           // ���� ��� �ڿ� �� ��� ����
            return head;
        }
        p = p->link;
    }
    // ���� ���� ����Ʈ�� ���� ��� �޽��� ���
    printf("�� %d�� ����Ʈ �ȿ� ����.\n", after);
    return head;
}

/*
  �Լ�: print_list
  ����: ���� ����Ʈ�� ����� ��� ����� �����͸� ����ϴ� �Լ�.
  �Ű�����:
    head - ���� ����Ʈ�� ��� ������.
  ��ȯ��:
    ����.
*/
void print_list(ListNode* head) {
    ListNode* p = head;
    // ����Ʈ�� ��� ��带 ��ȸ�ϸ鼭 �����͸� ���
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");  // ����Ʈ�� ���� ǥ��
}

/*
  �Լ�: main
  ����: ���� ����Ʈ�� ����, ����, ��� �۾��� �ÿ��ϴ� ���� �Լ�.
*/
int main() {
    ListNode* head = NULL;  // �� ����Ʈ�� ����

    // insert_position �Լ��� ����Ͽ� Ư�� ��ġ�� ��� ����
    head = insert_position(head, 1, 10); // ����Ʈ: 10
    head = insert_position(head, 1, 20); // ����Ʈ: 20 -> 10
    head = insert_position(head, 3, 30); // ����Ʈ: 20 -> 10 -> 30
    head = insert_position(head, 2, 40); // ����Ʈ: 20 -> 40 -> 10 -> 30

    // insert_after �Լ��� ����Ͽ� �� 30�� ��� �ڿ� �� 35�� ���� ��� ����
    head = insert_after(head, 30, 35);   // ����Ʈ: 20 -> 40 -> 10 -> 30 -> 35
    print_list(head);  // ���: 20 -> 40 -> 10 -> 30 -> 35 -> NULL

    // delete_position �Լ��� ����Ͽ� 3��° ��ġ�� ��� ����
    head = delete_position(head, 3);     // ����Ʈ: 20 -> 40 -> 30 -> 35
    print_list(head);

    // delete_position �Լ��� ����Ͽ� ������ ��ġ(4��°)�� ��� ����
    head = delete_position(head, 4);     // ����Ʈ: 20 -> 40 -> 30
    print_list(head);

    // delete_position �Լ��� ����Ͽ� ù ��° ��� ����
    head = delete_position(head, 1);     // ����Ʈ: 40 -> 30
    print_list(head);

    return 0;
}