/* _CRT_SECURE_NO_WARNINGS ����: Microsoft �����Ϸ����� ���� ��� ���ϱ� ���� ��ũ�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ����Ʈ�� ����� �������� �ڷ��� ���� (����� int��) */
typedef int element;

/* ���� ���Ḯ��Ʈ�� ��带 �����ϴ� ����ü */
typedef struct DListnode {
    element data;              /* ��忡 ����� ������ */
    struct DListnode* llink;   /* ���� ��带 ����Ű�� ������ */
    struct DListnode* rlink;   /* ���� ��带 ����Ű�� ������ */
} DListnode;

/* ����Ʈ�� �� ��(���̳�� ����)�� �� ��带 �����ϴ� �Լ� */
void insert_first(DListnode* head, element data)
{
    /* �� ��带 ���� ���� �޸� �Ҵ� */
    DListnode* newnode = (DListnode*)malloc(sizeof(DListnode));
    newnode->data = data;  /* ��忡 ������ ���� */

    /* �� ����� ���� �����ʹ� head(���� ���)�� ����Ŵ */
    newnode->llink = head;
    /* �� ����� ���� �����ʹ� ���� head�� ����Ű�� ù��° ��带 ����Ŵ */
    newnode->rlink = head->rlink;

    /* ���� ù��° ����� ���� �����͸� �� ���� ������Ʈ */
    head->rlink->llink = newnode;
    /* head�� ���� �����Ͱ� �� ��带 ����Ű���� ������Ʈ */
    head->rlink = newnode;
}

/* ����Ʈ�� �� ��(������ ��� ��)�� �� ��带 �����ϴ� �Լ� */
void insert_last(DListnode* head, element data)
{
    /* �� ��带 ���� ���� �޸� �Ҵ� */
    DListnode* newnode = (DListnode*)malloc(sizeof(DListnode));
    newnode->data = data;  /* ��忡 ������ ���� */

    /* �� ����� ���� �����ʹ� ���� ������ ���(head->llink)�� ����Ŵ */
    newnode->llink = head->llink;
    /* �� ����� ���� �����ʹ� head(���� ���)�� ����Ŵ */
    newnode->rlink = head;

    /* ���� ������ ����� ���� �����͸� �� ���� ������Ʈ */
    head->llink->rlink = newnode;
    /* head�� ���� �����Ͱ� �� ��带 ����Ű���� ������Ʈ */
    head->llink = newnode;
}

/* ����Ʈ�� ù ��° ��带 �����ϴ� �Լ� */
void delete_first(DListnode* head)
{
    /* ����Ʈ�� ����ִ� ��� (head�� ����) �������� ���� */
    if (head->rlink == head)
        return; // ����Ʈ�� ��������� �Լ� ����

    /* ������ ��带 head�� ������ ù��° ���� ���� */
    DListnode* remove = head->rlink;
    /* head�� ���� �����͸� ������ ����� ���� ���� ������Ʈ */
    head->rlink = remove->rlink;
    /* ������ ��� ������ ����� ���� �����͸� head�� ������Ʈ */
    remove->rlink->llink = head;
    /* ������ ��忡 �Ҵ�� �޸� ���� */
    free(remove);
}

/* ����Ʈ�� ������ ��带 �����ϴ� �Լ� */
void delete_last(DListnode* head)
{
    /* ����Ʈ�� ����ִ� ��� (head�� ����) �������� ���� */
    if (head->rlink == head)
        return; // ����Ʈ�� ��������� �Լ� ����

    /* ������ ��带 head�� ���� ������ ���� ���� */
    DListnode* remove = head->llink;
    /* head�� ���� �����͸� ������ ����� ���� ���� ������Ʈ */
    head->llink = remove->llink;
    /* ������ ��� ������ ����� ���� �����͸� head�� ������Ʈ */
    remove->llink->rlink = head;
    /* ������ ��忡 �Ҵ�� �޸� ���� */
    free(remove);
}

/* ����Ʈ�� ������ �տ������� ������� ����ϴ� �Լ� */
void print_forward(DListnode* head)
{
    DListnode* p = head->rlink;  /* ù ��° ������ Ž�� ���� */
    printf("Forward: ");
    /* ��尡 head(���� ���)�� �� ������ �ݺ��Ͽ� ������ ��� */
    while (p != head) {
        printf("%d ", p->data);
        p = p->rlink;
    }
    printf("\n");
}

/* ����Ʈ�� ������ �ڿ������� ������� ����ϴ� �Լ� */
void print_backward(DListnode* head)
{
    DListnode* p = head->llink; /* ������ ������ Ž�� ���� */
    printf("Backward: ");
    /* ��尡 head(���� ���)�� �� ������ �ݺ��Ͽ� ������ ��� */
    while (p != head) {
        printf("%d ", p->data);
        p = p->llink;
    }
    printf("\n\n");
}

/* main �Լ�: ���� ���Ḯ��Ʈ�� ����, ����, ����, ��� ��� �׽�Ʈ */
int main()
{
    /* ���� ���(head)�� ���� ���� �޸� �Ҵ� �� �ʱ�ȭ
       head�� ������ ���� ������ ��� �ڽ��� ����Ű���� ���� */
    DListnode* head = (DListnode*)malloc(sizeof(DListnode));
    head->llink = head;
    head->rlink = head;

    /* ����Ʈ �Ӹ� �κп� �����͸� ���� (���� �߰�) */
    insert_first(head, 40);
    insert_first(head, 30);
    insert_first(head, 20);
    insert_first(head, 10);

    /* ����Ʈ ���� �κп� �����͸� ���� (���� �߰�) */
    insert_last(head, 50);
    insert_last(head, 60);
    insert_last(head, 70);

    /* ���� ����Ʈ�� ���� ����� ���� �������� ��� */
    print_forward(head);
    print_backward(head);

    /* ����Ʈ�� ù��° ��� ���� */
    delete_first(head);
    /* ����Ʈ�� ������ ��� ���� */
    delete_last(head);

    /* ���� �� ����Ʈ ���¸� �ٽ� ���ʰ� ���ʿ��� ��� */
    print_forward(head);
    print_backward(head);

    /* ���α׷� ���� ���� ���� ��� head�� ���� �޸� ���� */
    free(head);

    return 0;
}