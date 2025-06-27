#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ������ �����͸� �ٷ�� ���� element�� int�� ���� */
typedef int element;

/* ���� ���� ����Ʈ�� ��� ����ü ���� */
typedef struct Listnode {
    element data;         // ��尡 ������ ������ ��
    struct Listnode* link; // ���� ��带 ����Ű�� ������
} Listnode;

/* ù ��° ��� ���� �Լ�
   ���� ����Ʈ���� head->link�� ���� ù ��° ��带 ����Ű���� �� */
Listnode* insert_first(Listnode* head, element data)
{
    // �� ��带 ���� �޸� �Ҵ� �� ������ ����
    Listnode* node = (Listnode*)malloc(sizeof(Listnode));
    node->data = data;

    if (head == NULL) {  // ����Ʈ�� ����ִ� ���
        head = node;         // head�� �� ��� ���� (������ �����)
        node->link = head;   // �ڱ� �ڽ��� ������ ���� ���� ����
    }
    else {  // ����Ʈ�� �̹� ��尡 �����ϴ� ���
        node->link = head->link; // �� ����� ���� �����Ͱ� ���� ù ��带 ����Ŵ
        head->link = node;       // head�� �״�� ����, �� ���� ��尡 �� ���� �����
    }
    return head;  // head�� ������� �ʰų�, ���� ����� ��� �״�� ��ȯ
}

/* ������ ���(����) ���� �Լ�
   head�� ���� ��带 ����Ű�� �ϸ�, �� ���� head ������ ���Ե� */
Listnode* insert_last(Listnode* head, element data)
{
    // �� ��带 ���� ���� �޸� �Ҵ� �� ������ ����
    Listnode* node = (Listnode*)malloc(sizeof(Listnode));
    node->data = data;

    if (head == NULL) {  // ����Ʈ�� ����ִ� ���
        head = node;       // head�� �� ��� ����
        node->link = head; // �ڱ� �ڽ��� ����Ű�� �Ͽ� ���� ����Ʈ ����
    }
    else {  // ����Ʈ�� ��尡 �̹� �����ϴ� ���
        node->link = head->link; // �� ��尡 ù ��带 ����Ű���� ��
        head->link = node;       // ���� tail(head)�� ���� ���� �� ��� ����
        head = node;             // head�� �� ���(���ο� ����)�� ����
    }
    return head;  // ���ŵ� head (����) ��ȯ
}

/* ù ��° ���� ��� ���� �Լ� */
Listnode* delete_first(Listnode* head)
{
    // ����Ʈ�� ��������� ������ ��嵵 ����
    if (head == NULL)
        return NULL;

    // ������ ���(del)�� head->link�� ù ��° ��带 ����Ŵ
    Listnode* del = head->link;

    // ����Ʈ�� �� �ϳ��� ��尡 �ִ� ���
    if (head == del) {
        free(del); // ������ ��� �޸� ����
        return NULL; // �� ����Ʈ ��ȯ
    }

    // ù ��° ��带 �ǳʶٵ��� head->link�� ���� (�� ��° ��尡 ù ��° ��尡 ��)
    head->link = del->link;
    free(del); // ���� ����� �޸� ����
    return head; // head(����)�� �״�� ��ȯ
}

/* ������ ���(����)�� �����ϴ� �Լ� */
Listnode* delete_last(Listnode* head)
{
    // ����Ʈ�� ��������� ������ ��尡 ����
    if (head == NULL)
        return NULL;

    // ù ��° ��带 ����Ű�� ������
    Listnode* first = head->link;

    // ����Ʈ�� �� �ϳ��� ����� ���
    if (head == first) {
        free(head); // ������ ��� �޸� ����
        return NULL; // �� ����Ʈ ��ȯ
    }

    // ������ ����� �ٷ� �� ��带 ã�� ���� ������ next ���
    Listnode* next = first;
    while (next->link != head) {
        next = next->link; // next�� tail�� �� ���� �̵�
    }
    // next�� �� ������ ��: next�� link�� first(ù ��° ���)�� �����Ͽ� ���� ����
    next->link = first;
    free(head); // ���� tail�� head�� �޸� ����
    head = next; // head�� �� ������ ����
    return head; // ���ŵ� head ��ȯ
}

/* 1���� 12������ ���� ������ �ð� ����Ʈ ���� �Լ� */
Listnode* clock_list() {
    Listnode* clock_head = NULL; // �ð� ����Ʈ�� ���� ���(ù��° ���)
    Listnode* clock_tail = NULL; // �ð� ����Ʈ�� ���� ���

    // 1���� 12���� �ݺ��Ͽ� �� �ð� ��� ����
    for (int i = 1; i <= 12; i++) {
        // ���ο� ��� ���� �޸� �Ҵ� �� ������ ����
        Listnode* clock_node = (Listnode*)malloc(sizeof(Listnode));
        clock_node->data = i;
        clock_node->link = NULL; // �ʱ⿡�� ���� ��带 NULL�� ����

        if (clock_head == NULL) { // ù ��° ����� ���
            clock_head = clock_node; // ���� ��� ����
        }
        else { // �� ��° ���� ����� ���
            clock_tail->link = clock_node; // ���� ���� ����� link�� �� ���� ����
        }
        clock_tail = clock_node; // ���� ��带 ���� ���� ����
    }
    // ������ ����� link�� ù ��° ��带 ������ ���� ���� ����Ʈ �ϼ�
    clock_tail->link = clock_head;
    return clock_tail; // tail�� ��ȯ (�� �����ο����� tail�� ����Ʈ ��ü�� ��Ÿ��)
}

/* �־��� ���� �ð�(n1)���� n2��ŭ �̵��� ����� ������ ��ȯ �Լ� */
int get_time(Listnode* head, int n1, int n2)
{
    // ���� ����Ʈ�� ���� ù ��° ��� (head->link)���� ����
    Listnode* p = head->link;

    // ���� ���� �ð� n1�� ���� ��带 ã��
    while (p->data != n1) {
        p = p->link;
    }
    // ã�� ��忡�� n2�� �̵� (���� ����Ʈ���� ��ȯ)
    for (int i = 0; i < n2; i++) {
        p = p->link;
    }
    return p->data; // ���������� ������ ����� �����͸� ��ȯ
}

/* ���� ����Ʈ ��ü�� ����ϴ� �Լ� */
void print_list(Listnode* head)
{
    if (head == NULL) {  // ����Ʈ�� ����ִ� ���
        printf("����Ʈ�� �������\n");
        return;
    }

    // ���� ù ��° ���(head->link)���� �����Ͽ� ���� ����Ʈ ��ȸ
    Listnode* p = head->link;
    do {
        printf("%d -> ", p->data); // ��� ������ ��� �� ȭ��ǥ ǥ��
        p = p->link;
    } while (p != head->link); // ���� ���� �ٽ� ���ƿ��� ��ȸ ����
    printf("(���� ����Ʈ�� �����)\n\n");
}

int main()
{
    /* ����Ʈ �׽�Ʈ�� ���� ���� ���� */
    Listnode* head = NULL;

    // insert_first�� insert_last�� �̿��Ͽ� ����Ʈ�� ��� ����
    head = insert_first(head, 20); // ����Ʈ�� 20 ���� (ù��° �����̹Ƿ� ���� ���)
    head = insert_first(head, 10); // 10�� ù ���� ����
    head = insert_last(head, 30);  // 30�� ������ ���� ����
    head = insert_last(head, 40);  // 40�� ������ ���� ����
    head = insert_last(head, 50);  // 50�� ������ ���� ����
    printf("�ʱ� ����Ʈ ���:\n");
    print_list(head);

    // ù ��° ��� ���� �� ��� ���
    head = delete_first(head);
    printf("ù ��° ��� ���� �� ����Ʈ ���:\n");
    print_list(head);

    // ������ ��� ���� �� ��� ���
    head = delete_last(head);
    printf("������ ��� ���� �� ����Ʈ ���:\n");
    print_list(head);

    // �ð� ����Ʈ ���� �� ��� (1���� 12���� �ð� ����)
    Listnode* clock_tail = clock_list();
    printf("�ð� ����Ʈ ��� (1~12):\n");
    print_list(clock_tail);

    int n1, n2;

    // ����ڿ��� ���� �ð��� �� �ð� �������� �Է� �޾� ����ϴ� ����
    while (true)
    {
        printf("���� �ð��� �Է��ϼ��� (1~12, �����Ϸ��� 0 �Է�): ");
        scanf("%d", &n1);

        // 0 �Է� �� ����
        if (n1 == 0)
            break;

        printf("�� �ð� ������ �Է��ϼ���: ");
        scanf("%d", &n2);

        // get_time �Լ��� ����Ͽ� n1���� n2��ŭ �̵��� ����� �ð� ���
        int newTime = get_time(clock_tail, n1, n2);
        printf("���� �ð�: %d\n\n", newTime);
    }

    return 0;
}