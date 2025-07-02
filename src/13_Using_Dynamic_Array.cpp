/*
   C ���α׷�: ���� �迭�� Ȯ�� ��� ��
   - mode 1: �迭�� ���� �� ������ ���� �뷮�� 2��� Ȯ��
   - mode 2: �迭�� ���� �� ������ �뷮�� 1�� ����
   1000���� ������ �迭�� �����ϸ鼭, �� ����� ���� (���� �ð� �� Ȯ�� Ƚ��)�� ���Ѵ�.
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio���� ���� ��� ��Ȱ��ȭ�ϱ� ���� ��ũ��
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// element�� int�� ���� (�迭 ����� Ÿ��)
typedef int element;

// ���� �迭 ����ü ����
typedef struct {
    element* data;        // ���� �����͸� ������ ���� �迭 �޸��� �ּ�
    int size;             // ���� ����� ������ ����
    int capacity;         // ���� �迭�� ���� ������ �� �뷮
    int extension_count;  // �迭 Ȯ��(���Ҵ�) Ƚ��
} ArrayList;

// �ʱ�ȭ �Լ�: ���� �迭�� �ʱ�ȭ�Ѵ�.
// �ʱ� �뷮�� 1�� �����ϰ�, �迭 �� ���� �������� �ʱ�ȭ�Ѵ�.
void init(ArrayList* list) {
    list->data = (element*)malloc(sizeof(element) * 1);   // �ʱ� �뷮 1�� �޸� �Ҵ�
    list->size = 0;              // �ʱ⿡�� ����� �����Ͱ� �����Ƿ� 0���� ����
    list->capacity = 1;          // �ʱ� �뷮�� 1�� ����
    list->extension_count = 0;   // ���� Ȯ���� �̷������ �ʾ����Ƿ� 0���� �ʱ�ȭ
}

// ���� �Լ�: �迭�� �������� �� �����͸� �߰��Ѵ�.
// mode �Ű������� ���� Ȯ�� ������ ���� (mode 1: 2�� Ȯ��, mode 2: +1 Ȯ��)
void insert_last(ArrayList* list, element value, int mode) {
    // �迭�� ���� �� ���, Ȯ���� �ʿ���
    if (list->size == list->capacity) {
        // mode�� ���� Ȯ�� ��� ����
        if (mode == 1) {
            list->capacity *= 2;    // mode 1: ���� �뷮�� 2��� Ȯ�� (�� ȿ����)
        }
        else if (mode == 2) {
            list->capacity += 1;    // mode 2: ���� �뷮���� 1�� ���� (�� ȿ����)
        }
        // realloc�� ����Ͽ� Ȯ��� ũ�⿡ �°� �޸𸮸� ���Ҵ�
        list->data = (element*)realloc(list->data, sizeof(element) * list->capacity);
        list->extension_count++;    // Ȯ���� �߻������Ƿ�, Ƚ���� 1 ������Ŵ
    }
    // �� �����͸� �迭�� �������� �����ϰ�, �迭�� ũ�⸦ ������Ŵ
    list->data[list->size++] = value;
}

// �޸� ���� �Լ�: ���� �迭�� �Ҵ�� �޸𸮸� �����Ͽ� �޸� ������ �����Ѵ�.
void free_list(ArrayList* list) {
    free(list->data); // �������� �Ҵ�� �޸� ����
}

// ���� ���� �Լ�: ������ Ȯ�� ��带 ����Ͽ� �迭�� 1���� 1000������ �����͸� �����ϰ�, ���� �ð��� Ȯ�� Ƚ���� ����Ѵ�.
void run_test(int mode) {
    ArrayList list;  // ���� �迭 ����ü ���� ����
    init(&list);     // ���� �迭 �ʱ�ȭ

    clock_t start = clock();  // ���� �ð� ���

    // 1���� 1000���� ������ �迭�� ����
    for (int i = 1; i <= 1000; i++) {
        insert_last(&list, i, mode);  // ������ Ȯ�� ��忡 ���� ������ ����
    }

    clock_t end = clock();  // ���� �ð� ���
    // ���� �۾��� �ɸ� �� �ð��� �� ������ ���
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // ���� Ȯ�� ��Ŀ� ���� ���� ���
    if (mode == 1) {
        printf("[2�� Ȯ�� ���]\n");
    }
    else if (mode == 2) {
        printf("[+1 Ȯ�� ���]\n");
    }

    // ���� ���� �ð��� �迭�� Ȯ�� Ƚ�� ���
    printf("���� �ð�: %f��\n", elapsed_time);
    printf("�迭 Ȯ�� Ƚ��: %dȸ\n\n", list.extension_count);

    free_list(&list);  // ���� �迭�� �Ҵ�� �޸� ����
}

// main �Լ�: �� ���� Ȯ�� ����� ���������� �׽�Ʈ�Ѵ�.
int main() {
    // ���α׷� ���� �޽��� ���
    printf("=== Dynamic Array Ȯ�� ��� �� ===\n\n");

    run_test(1);  // ��� 1: �迭 �뷮�� 2�� Ȯ���ϴ� ��� �׽�Ʈ
    run_test(2);  // ��� 2: �迭 �뷮�� +1�� Ȯ���ϴ� ��� �׽�Ʈ

    return 0;     // ���α׷� ����
}