// _CRT_SECURE_NO_WARNINGS�� �����Ͽ� �Ϻ� �����Ϸ����� ���� ��� ��Ȱ��ȭ
#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>      // ǥ�� ����� �Լ� ���
#include <stdlib.h>     // ���� �޸� �Ҵ� �Լ� ���
#include <malloc.h>     // malloc �Լ��� ����ϱ� ���� ��� (�Ϻ� �����Ϸ� �ʿ�)

// Student ����ü ����: �л��� �̸�, ����, ���� ������ ����
struct Student {
    char name[50];   // �л� �̸� (�ִ� 49�� + �� ���� ����)
    int age;         // �л� ����
    float grade;     // �л� ����
} student;           // student ���� ���� (�� ���������� ������ ����)

// �л� ������ ����ϴ� �Լ�
// �Ű�����: �л� ����ü�� �����͸� �Է¹޾� �ش� �л��� ������ ���
void printStudent(struct Student* student) {
    printf("�̸�: %s, ����: %d, ����: %.2f\n", student->name, student->age, student->grade);
}

// �л� �迭�� ���� ����� ����ϴ� �Լ�
// �Ű�����: students - �л� �迭�� ������, numStudents - �迭�� �ִ� �л� ��
// ��ȯ��: ��ü �л��� ���� ���
float Average(struct Student* students, int numStudents) {
    float total = 0.0;
    // ��� �л��� ������ ����
    for (int i = 0; i < numStudents; i++) {
        total += students[i].grade;
    }
    // ������ �л� ���� ���� ����� ���
    return total / numStudents;
}

// main �Լ�: ���α׷��� ������
int main() {

    // ���� �޸� �Ҵ�: 3���� �л� ������ ������ ������ �Ҵ�
    struct Student* students = (struct Student*)malloc(3 * sizeof(struct Student));

    // �޸� �Ҵ翡 �����ϸ� ���� �޽����� ����ϰ� ���α׷� ����
    if (students == NULL) {
        printf("�޸� �Ҵ� ����!\n");
        return 1;
    }

    // ����ڷκ��� 3���� �л� ������ �Է¹���
    printf("�л� ������ �Է��ϼ���:\n");
    for (int i = 0; i < 3; i++) {
        printf("�л� %d:\n", i + 1);
        printf("�̸�: ");
        scanf("%s", students[i].name);  // �л��� �̸� �Է�
        printf("����: ");
        scanf("%d", &students[i].age);    // �л��� ���� �Է�
        printf("����: ");
        scanf("%f", &students[i].grade);  // �л��� ���� �Է�
    }

    // �Է¹��� �л� ������ �����
    printf("\n�л� ����:\n");
    for (int i = 0; i < 3; i++) {
        printStudent(&students[i]);  // printStudent �Լ��� ȣ���Ͽ� �� �л� ������ ���
    }

    // �л����� ���� ����� ����ϰ� �����
    float average = Average(students, 3);
    printf("\n��ü �л��� ���� ���: %.2f\n", average);

    // �������� �Ҵ��� �޸𸮸� �����Ͽ� �޸� ������ ����
    free(students);

    // ���α׷� ���� ����
    return 0;
}