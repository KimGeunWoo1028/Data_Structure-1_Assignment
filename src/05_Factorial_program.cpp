#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Recursive ������� ���丮���� ����ϴ� �Լ�
// �Ű�����: int n - ���丮�� ��꿡 ����� ���� ��
// ��ȯ��: unsigned long long - n�� ���丮�� ��
unsigned long long Fact_recursive(int n)
{
    // �⺻ ����: n�� 1 �����̸� 1�� ��ȯ (0! �� 1! = 1)
    if (n <= 1)
        return 1;
    else
        // ��� ȣ��: n * (n-1)! �� ���
        return n * Fact_recursive(n - 1);
}

// Iterative ������� ���丮���� ����ϴ� �Լ�
// �Ű�����: int n - ���丮�� ��꿡 ����� ���� ��
// ��ȯ��: unsigned long long - n�� ���丮�� ��
unsigned long long Fact_iterative(int n)
{
    // ���丮�� ����� ������ ����, �ʱⰪ 1
    unsigned long long result = 1;
    // 1���� n���� ���ϸ鼭 factorial ���� ���
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main()
{
    // n: ���丮�� ��꿡 ����� ��, �ʱⰪ�� 0���� ����
    int n = 0;
    // start�� end: ���� �ð� ������ ���� clock_t ������
    clock_t start, end;
    // result_r�� result_i: ���� recursive�� iterative �Լ��� ��ȯ���� ����
    unsigned long long result_r, result_i;
    // time_r�� time_i: ���� recursive�� iterative ����� ���� �ð��� �� ������ ����
    double time_r, time_i;
    // max_r: ��� ��Ŀ��� stack overflow�� �߻��ϱ� ���� �ִ� n �� ���� ����
    int max_r = 0;
    // repeat: �ݺ� ���� Ƚ����, �Լ� ���� �ð��� �����ϱ� ���� ��� (����: Ƚ��)
    int repeat = 100000;

    // ���� ����, n���� ������Ű�鼭 ���丮���� ����ϰ� ����
    while (1)
    {
        // ---------- Recursive ��� �Լ� ���� �� �ð� ���� ---------- 
        start = clock(); // ���� ���� �ð� ����
        // repeat Ƚ����ŭ ��� �Լ��� ȣ���Ͽ� ���
        for (int i = 0; i < repeat; i++)
        {
            result_r = Fact_recursive(n);
        }
        end = clock(); // ���� ���� �ð� ����
        // Recursive ����� ���� �ð� ��� (�� ����)
        time_r = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ---------- Iterative ��� �Լ� ���� �� �ð� ���� ----------
        start = clock(); // ���� ���� �ð� ����
        // repeat Ƚ����ŭ �ݺ� �Լ��� ȣ���Ͽ� ���
        for (int i = 0; i < repeat; i++)
        {
            result_i = Fact_iterative(n);
        }
        end = clock(); // ���� ���� �ð� ����
        // Iterative ����� ���� �ð� ��� (�� ����)
        time_i = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ���� n���� ���� ��� �� �ݺ� ����� ����� ���
        printf("%d : Recursive��� : %llu  Iterative��� : %llu\n", n, result_r, result_i);

        // ���� ��� ����� ����� 0�̸�, stack overflow�� �߻��� ������ ������
        if (result_r == 0)
        {
            // n���� �ϳ� �ٿ� overflow�� �߻����� ���� �ִ��� �������� n ���� ���
            max_r = n - 1;
            printf("Stack Overflow: %d\n", max_r);
            break;
        }

        // ���� n���� ���� ���丮�� ����� �����ϱ� ���� n�� 1 ����
        n++;
    }

    // ���������� �������� ������ ���� �ð� ���
    printf("Recursive����� ���� �ð�: %f ��\n", time_r);
    printf("Iterative����� ���� �ð�: %f ��\n", time_i);
    // Iterative ����� max_r ������ ���������� ����Ǿ����� ���
    printf("Iterative��Ŀ��� n = %d������ ���������� ����Ǿ����ϴ�.\n", max_r);

    return 0;
}