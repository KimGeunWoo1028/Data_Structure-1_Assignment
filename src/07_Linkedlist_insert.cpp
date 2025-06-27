/* ���α׷� ����:
 * �� ���α׷��� �ܼ� ���� ����Ʈ(linked list)�� �����մϴ�.
 * �� ���� ���� ����Ʈ(list1, list2)�� �����ϰ�, ����
 * insert_first�� insert_last �Լ��� ����Ͽ� ��带 �߰��� ��,
 * ����� ����մϴ�.
 */

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio���� �������� ���� �Լ� ��� ����

#include <stdio.h>   // ǥ�� ����� �Լ����� ����ϱ� ���� ���̺귯��
#include <stdlib.h>  // ���� �޸� �Ҵ� �Լ����� ����ϱ� ���� ���̺귯��

 // ListNode ����ü: ���� ����Ʈ�� �� ��带 ǥ���մϴ�.
typedef struct ListNode
{
    int element;                // ����� ������ (������)
    struct ListNode* link;      // ���� ��带 ����Ű�� ������
} ListNode;

// linkedlist ����ü: ���� ����Ʈ�� ����(���) ��带 �����մϴ�.
typedef struct linkedlist
{
    ListNode* head;             // ����Ʈ�� ù ��° ��带 ����Ű�� ������
} linkedlist;

// �Լ�: insert_first
// ����: ���� ����Ʈ�� ���� �κп� ���ο� ��带 �߰� (���ʿ� ����)�ϴ� �Լ�
// �Ű�����: 
//   linkedlist* list  - ��带 �߰��� ���� ����Ʈ�� ������
//   int data          - �߰��� ������ ��
void insert_first(linkedlist* list, int data)
{
    // ���ο� ��带 ���� ���� �޸� �Ҵ�
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    // �� ����� ������ �ʱ�ȭ
    p->element = data;
    // �� ����� link�� ������ head�� ���� (���� ���� ����Ʈ �տ� �߰�)
    p->link = list->head;
    // ����Ʈ�� head�� �� ���� ����
    list->head = p;
}

// �Լ�: insert_last
// ����: ���� ����Ʈ�� �� �κп� ���ο� ��带 �߰� (���ʿ� ����)�ϴ� �Լ�
// �Ű�����: 
//   linkedlist* list  - ��带 �߰��� ���� ����Ʈ�� ������
//   int data          - �߰��� ������ ��
void insert_last(linkedlist* list, int data)
{
    // ���ο� ��带 ���� ���� �޸� �Ҵ�
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    // �� ����� ������ �ʱ�ȭ
    p->element = data;
    // �� ����� link�� NULL�� ���� (����Ʈ�� ���̹Ƿ�)
    p->link = NULL;

    // ���� ����Ʈ�� ����ִٸ� (head�� NULL�� ���)
    if (list->head == NULL)
    {
        // �� ��带 ����Ʈ�� head�� ���� �� �Լ� ����
        list->head = p;
        return;
    }

    // ����Ʈ�� ������� �ʴٸ�, ������ ��带 ã�� ���� �ӽ������� temp ����
    ListNode* temp = list->head;
    // ������ ������ �̵� (temp->link�� NULL�� �� ������)
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    // ������ ����� link�� �� ���� ����
    temp->link = p;
}

// �Լ�: print_list
// ����: ���� ����Ʈ�� �ִ� ��� ����� �����͸� ��ȸ�ϸ� ����ϴ� �Լ�
// �Ű�����:
//   linkedlist* list  - ����� ���� ����Ʈ�� ������
void print_list(linkedlist* list)
{
    // ����Ʈ ��ȸ�� ���� �ӽ������� ���� temp �ʱ�ȭ
    ListNode* temp = list->head;
    // ����Ʈ�� �� (temp�� NULL)�� �� ������ �ݺ��ϸ鼭 ������ ���
    while (temp != NULL)
    {
        // ���� ����� �����͸� ����ϰ� "->" ��ȣ ���
        printf("%d -> ", temp->element);
        // ���� ���� �̵�
        temp = temp->link;
    }
    // ����Ʈ �� ��� (NULL)
    printf("NULL\n");
}

// main �Լ�: ���α׷��� ������
int main()
{
    // �� ���� ���� ����Ʈ(list1, list2)�� �����ϰ�, �� ����Ʈ�� �ʱ�ȭ (head = NULL)
    linkedlist list1, list2;
    list1.head = NULL;
    list2.head = NULL;

    // insert_first �Լ��� �̿��Ͽ� list1�� ��带 �տ� ���� (�������� �߰�)
    printf("insert_first ��� ���\n");
    insert_first(&list1, 50);  // ����Ʈ�� ���ʿ� 50 �߰�
    insert_first(&list1, 40);  // ����Ʈ�� ���ʿ� 40 �߰�
    insert_first(&list1, 30);  // ����Ʈ�� ���ʿ� 30 �߰�
    insert_first(&list1, 20);  // ����Ʈ�� ���ʿ� 20 �߰�
    insert_first(&list1, 10);  // ����Ʈ�� ���ʿ� 10 �߰�

    // list1�� ��� ��� ������ ���
    print_list(&list1);

    // �ٹٲ� �� insert_last �Լ��� �̿��Ͽ� list2�� ��带 �ڿ� ���� (������� �߰�)
    printf("\ninsert_last ��� ���\n");
    insert_last(&list2, 10);  // ����Ʈ�� �������� 10 �߰�
    insert_last(&list2, 20);  // ����Ʈ�� �������� 20 �߰�
    insert_last(&list2, 30);  // ����Ʈ�� �������� 30 �߰�
    insert_last(&list2, 40);  // ����Ʈ�� �������� 40 �߰�
    insert_last(&list2, 50);  // ����Ʈ�� �������� 50 �߰�

    // list2�� ��� ��� ������ ���
    print_list(&list2);

    // ���α׷� ����
    return 0;
}