#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	int a[100]; // 100�� ��ŭ ������ �� �ִ� ����a ��� �迭
	int b[10]; // 10�� ��ŭ ������ �� �ִ� ����b ��� �迭
	int n = 0;

	int num;
	srand(time(0)); // ���α׷��� ���� �� �� ���� �ٸ� ���� ���
	for (int i = 0; i < 100; i++) {
		num = rand() % 101;
		a[i] = num;
	}
	// ����a �迭�� 10���� ����b �迭�� ����
	for (int i = 0; i < 10; i++) {
		b[i] = a[i];
		printf("%d ", b[i]);
	}
	printf("\n\n");
	// b �迭���� �ִ� ���ϱ�
	int max = -99999; // ��� �� ���� �������� �ʱ�ȭ
	for (int i = 1; i < 10; i++) {    // �迭b�� �ε����� ���� �ϳ��� ��
		if (max < b[i]) {
			max = b[i];
		}
	}
	printf("%d ", max);
}