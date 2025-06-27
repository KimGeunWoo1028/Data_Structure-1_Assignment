/*
    ���α׷� ����: �� ���α׷��� C�� �ۼ��� ���� ���� ����Ʈ�� ����, ����, �˻�, ��� ����� �ÿ��մϴ�.
    �ۼ���: [����� �̸�]
    �ۼ���: 2023-10-XX
    ����: 1.0
    ����: _CRT_SECURE_NO_WARNINGS ��ũ�δ� Visual Studio���� ���� ���� ��� �����ϱ� ���� ���˴ϴ�.
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio���� ���� ��� ��Ȱ��ȭ�ϱ� ���� ��ũ��

// stdio.h: �Է� �� ��� �Լ� ����� ����
// stdlib.h: ���� �޸� �Ҵ� �Լ� ����� ����
#include <stdio.h>
#include <stdlib.h>

/*
    "element"�� int���� ��Ī(alias)�Դϴ�.
    ���� ������ Ÿ���� ���� �����ϰ��� �� ��� �� �κи� �����ϸ� �˴ϴ�.
*/
typedef int element;

/*
    ��� ����ü(ListNode) ����:
    - ������(data): ��忡 ����� ��
    - ��ũ(link): ���� ��带 ����Ű�� ������
*/
typedef struct ListNode {
    element data;           // ����� ������ ���� ����
    struct ListNode* link;  // ���� ����� �ּҸ� ����
} ListNode;

/*
    ���� ����Ʈ ����ü(LinkedList) ����:
    - head: ����Ʈ�� ù ��° ��带 ����Ű�� ������
    ��� ���� ����Ʈ ������ �� ����ü�� ���� �̷�����ϴ�.
*/
typedef struct LinkedList {
    ListNode* head;         // ����Ʈ�� ���� ��带 ����Ű�� ������
} LinkedList;

/*
    �Լ�: insert_first
    ����: ���� ����Ʈ�� ù��° ��ġ�� ���ο� ��带 �����մϴ�.
*/
void insert_first(LinkedList* list, element data) {
    // ���ο� ��带 ���� ���� �޸� �Ҵ� �� �Ҵ� ���� �˻�
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }
    p->data = data;        // ���ο� ��忡 ������ �� ����
    p->link = list->head;  // ���ο� ����� ��ũ�� ������ ù ��带 ����Ű���� ����
    list->head = p;        // ����Ʈ�� ��� �����͸� ���ο� ���� ������Ʈ
}

/*
    �Լ�: insert_last
    ����: ���� ����Ʈ�� ������ ��ġ�� ���ο� ��带 �����մϴ�.
*/
void insert_last(LinkedList* list, element data) {
    // ���ο� ��带 ���� ���� �޸� �Ҵ� �� �Ҵ� ���� �˻�
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }
    p->data = data; // ���ο� ��忡 ������ �� ����
    p->link = NULL; // ������ ����̹Ƿ� ��ũ�� NULL�� ����

    // ����Ʈ�� ����ִ� ���, ���ο� ��尡 ù ��° ��尡 �˴ϴ�.
    if (list->head == NULL) {
        list->head = p;
        return;
    }

    // ����Ʈ�� ������� ���� ���, ������ ��带 ã�� ������ Ž��
    ListNode* temp = list->head;
    while (temp->link != NULL) {
        temp = temp->link;
    }
    temp->link = p; // ���� ������ ����� ��ũ�� ���ο� ��带 ����Ű���� ����
}

/*
    �Լ�: delete_first
    ����: ���� ����Ʈ�� ù��° ���(���)�� �����մϴ�.
*/
void delete_first(LinkedList* list) {
    // ����Ʈ�� ��� �ִ��� Ȯ��
    if (list->head == NULL) {
        printf("No element in the list!\n");
        return;
    }

    // ������ ù ��带 �ӽ� �����Ϳ� ����
    ListNode* temp = list->head;
    list->head = temp->link; // ��� �����͸� �� ��° ���� ������Ʈ
    free(temp);  // ���� ù ����� �޸� ����
}

/*
    �Լ�: delete_last
    ����: ���� ����Ʈ�� ������ ��带 �����մϴ�.
*/
void delete_last(LinkedList* list) {
    // ����Ʈ�� ��� ���� ��� ó��
    if (list->head == NULL) {
        printf("No element in the list!\n");
        return;
    }

    // ��尡 �ϳ��� �����ϴ� ���
    if (list->head->link == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }

    // ���� ���� ��尡 �����ϴ� ���, ������ ����� �ٷ� �� ��带 ã�� ����
    ListNode* temp = list->head;
    while (temp->link->link != NULL) {
        temp = temp->link;
    }
    free(temp->link);   // ������ ��� �޸� ����
    temp->link = NULL;  // ������ ��� ���İ� ������ ǥ��
}

/*
    �Լ�: search
    ����: ���� ����Ʈ���� �־��� target ���� ��ġ�ϴ� ù ��° ��带 �˻��մϴ�.
*/
void search(LinkedList* list, element target) {
    ListNode* temp = list->head;  // ����Ʈ Ž���� ���� �ӽ� ������
    int position = 1;             // ����� ��ġ�� ����ϴ� ����

    // ����Ʈ�� �� ��带 ���������� Ž��
    while (temp != NULL) {
        if (temp->data == target) {
            printf("������ %d��(��) %d��° ��ġ�� �ֽ��ϴ�.\n", target, position);
            return;
        }
        temp = temp->link;  // ���� ���� �̵�
        position++;         // ��� ��ġ ����
    }

    // target �����Ͱ� ����Ʈ�� �������� �ʴ� ���
    printf("������ %d��(��) ã�� �� �����ϴ�.\n", target);
}

/*
    �Լ�: print_list
    ����: ���� ����Ʈ�� ��� ��带 ���������� ����մϴ�.
*/
void print_list(LinkedList* list) {
    ListNode* temp = list->head;  // ����Ʈ Ž���� ���� �ӽ� ������
    // ����Ʈ�� ��� ��带 ���������� ���
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;  // ���� ���� �̵�
    }
    printf("NULL\n");  // ����Ʈ�� ���� ǥ��
}

/*
    ���� �Լ�: ��� ���� ����Ʈ ���(����, ����, ��� �� �˻�)�� �����մϴ�.
*/
int main() {
    // �� ���� ����Ʈ ���� (��� �����͸� NULL�� �ʱ�ȭ)
    LinkedList list;
    list.head = NULL;

    // ù ��� ����: ����Ʈ�� ���ʿ� �� ��带 �����մϴ�.
    insert_first(&list, 30);
    insert_first(&list, 20);
    insert_first(&list, 10);
    // ������ ��� ����: ����Ʈ�� ���� �� ��带 �����մϴ�.
    insert_last(&list, 40);
    insert_last(&list, 50);
    insert_last(&list, 60);

    // ���� ����Ʈ ���
    print_list(&list);

    // ù ��� ���� �� ����Ʈ ���
    delete_first(&list);
    print_list(&list);

    // ������ ��� 2�� ���� �� ����Ʈ ���
    delete_last(&list);
    delete_last(&list);
    print_list(&list);

    // Ư�� �� 40�� �˻��Ͽ� ��ġ ���
    search(&list, 40);

    return 0;  // ���α׷� ���� ����
}