// _CRT_SECURE_NO_WARNINGS: Visual Studio���� ���� ��� �����ϱ� ���� ��ũ��
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>    // ǥ�� ����� �Լ� ���
#include <stdlib.h>   // ���� �޸� �Ҵ� �Լ� ���

// element: �迭 ����Ʈ�� ������ ������ Ÿ�� (���⼭�� int)
typedef int element;

// ArrayList ����ü�� ���� �迭 ����Ʈ�� ǥ���մϴ�.
// size: ����Ʈ�� �ִ� ũ��
// count: ���� ����� ����� ����
// capacity: ���� �����͸� �����ϴ� ���� �迭 ������
typedef struct
{
    int size;
    int count;
    element* capacity;
} ArrayList;

// create: ������ ũ��� ���� �迭 ����Ʈ�� �����Ͽ� �ʱ�ȭ�մϴ�.
// �޸� �Ҵ� ���� �� ���� �޽����� ����ϰ� ���α׷��� �����մϴ�.
ArrayList* create(int size)
{
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    if (list == NULL)
    {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    list->size = size;
    list->count = 0;
    list->capacity = (element*)malloc(sizeof(element) * size);
    if (list->capacity == NULL)
    {
        printf("�޸� �Ҵ� ����\n");
        free(list);
        exit(1);
    }
    return list;
}

// is_full: ����Ʈ�� ���� á���� �Ǵ��մϴ�.
// ���� count�� �ִ� ũ�� size�� ������ ����Ʈ�� ���� �� ����
int is_full(ArrayList* list)
{
    return list->count == list->size;
}

// is_empty: ����Ʈ�� ����ִ��� �Ǵ��մϴ�.
// count�� 0�̸� ����Ʈ�� ����ֽ��ϴ�.
int is_empty(ArrayList* list)
{
    return list->count == 0;
}

// print_list: ����Ʈ�� ����� ��� ��ҵ��� ����մϴ�.
// ����Ʈ�� ��������� �ƹ��͵� ������� �ʽ��ϴ�.
void print_list(ArrayList* list)
{
    printf("����Ʈ: ");
    for (int i = 0; i < list->count; i++)
        // �� ��Ҹ� ������� ���
        printf("%d ", list->capacity[i]);
    printf("\n");
}

// insert_first: ����Ʈ�� ù ��° ��ġ�� ���� �����մϴ�.
// ����Ʈ�� ���� �� ��� �������� �ʰ� ��� �޽����� ����մϴ�.
// ���� �� ���� ��ҵ��� ���������� �̵���ŵ�ϴ�.
void insert_first(ArrayList* list, element value)
{
    if (is_full(list))
    {
        printf("����Ʈ�� ���� á���ϴ�.\n");
        return;
    }

    // ���� ��ҵ��� ���������� �� ĭ�� �̵�
    for (int i = list->count; i > 0; i--)
        list->capacity[i] = list->capacity[i - 1];
    // ù ��° ��ġ�� �� ���� ����
    list->capacity[0] = value;
    list->count++;
}

// insert: ������ index(pos) ��ġ�� ���� �����մϴ�.
// index ������ ��ҵ��� ���������� �� ĭ�� �̵����� ���� ������ �����մϴ�.
void insert(ArrayList* list, int pos, element value)
{
    if (is_full(list))
    {
        printf("����Ʈ�� ���� á���ϴ�.\n");
        return;
    }

    // pos ��ġ ������ ��Ҹ� ���������� �̵�
    for (int i = list->count; i > pos; i--)
        list->capacity[i] = list->capacity[i - 1];
    // ������ ��ġ�� ���� ����
    list->capacity[pos] = value;
    list->count++;
}

// insert_last: ����Ʈ�� ������ ��ġ�� ���� �����մϴ�.
// ����Ʈ ���� ���� �߰��ϰ�, count ���� 1 ������ŵ�ϴ�.
void insert_last(ArrayList* list, element value)
{
    if (is_full(list))
    {
        printf("����Ʈ�� ���� á���ϴ�.\n");
        return;
    }

    // ������ ��ġ�� �� ���� ����
    list->capacity[list->count] = value;
    list->count++;
}

// delete_first: ����Ʈ�� ù ��° ��Ҹ� �����մϴ�.
// ���� �� ������ ��ҵ��� �������� �̵����� ������ �޿�ϴ�.
void delete_first(ArrayList* list)
{
    if (is_empty(list))
    {
        printf("����Ʈ�� ����ֽ��ϴ�.\n");
        return;
    }

    // ù ��° ��Ҹ� �����ϰ� ������ ��ҵ��� �������� �̵�
    for (int i = 0; i < list->count - 1; i++)
        list->capacity[i] = list->capacity[i + 1];
    list->count--;
}

// delete_: ������ index(pos) ��ġ�� ��Ҹ� �����մϴ�.
// ���� ��, �ش� ��ġ ������ ��ҵ��� �� ĭ�� �������� �̵��մϴ�.
void delete_(ArrayList* list, int pos)
{
    if (is_empty(list))
    {
        printf("����Ʈ�� ����ֽ��ϴ�.\n");
        return;
    }

    // pos ��ġ�� ��� ���� ��, ���� ��ҵ��� �̵�
    for (int i = pos; i < list->count - 1; i++)
        list->capacity[i] = list->capacity[i + 1];
    list->count--;
}

// delete_last: ����Ʈ�� ������ ��Ҹ� �����մϴ�.
// count ���� 1 ���ҽ��� ������ ��Ҹ� �����մϴ�.
void delete_last(ArrayList* list)
{
    if (is_empty(list))
    {
        printf("����Ʈ�� ����ֽ��ϴ�.\n");
        return;
    }

    // ������ ��� ������ ���� count ���� ����
    list->count--;
}

// free_arraylist: ����Ʈ�� �������� �Ҵ�� �޸𸮸� �����մϴ�.
// capacity �迭�� ���� ������ ��, ArrayList ����ü �޸𸮸� �����մϴ�.
void free_arraylist(ArrayList* list)
{
    free(list->capacity);
    free(list);
}

// main: ���α׷��� ���� �Լ�. ����� �Է��� �޾� ����Ʈ�� �����ϰ�,
// �پ��� ���� �� ���� ������ �����մϴ�.
// �� ���� �� ����Ʈ ���¸� ����Ͽ� ����� Ȯ���մϴ�.
// ���α׷� ���� ���� �Ҵ��� �޸𸮸� free_arraylist ȣ��� �����մϴ�.
int main()
{
    int size;
    printf("����Ʈ�� ũ�⸦ �Է��Ͻÿ�: ");
    scanf("%d", &size);
    ArrayList* list = create(size);

    // ù ��° ��ġ�� ���������� �� ���� (�ڷ� �̴� ���)
    insert_first(list, 40);
    insert_first(list, 30);
    insert_first(list, 20);
    insert_first(list, 10);
    print_list(list);  // ���� ��� ���

    // �ε��� 2�� �� 25 ���� (�߰� ����)
    insert(list, 2, 25);
    print_list(list);  // ���� ��� ���

    // ������ ��ġ�� �� 50 ����
    insert_last(list, 50);
    print_list(list);  // ���� ��� ���

    // ù ��° ��� ����
    delete_first(list);
    print_list(list);  // ���� ��� ���

    // �ε��� 3�� ��� ����
    delete_(list, 3);
    print_list(list);  // ���� ��� ���

    // ������ ��� ����
    delete_last(list);
    print_list(list);  // ���� ��� ���

    // �޸� ����
    free_arraylist(list);

    return 0;
}