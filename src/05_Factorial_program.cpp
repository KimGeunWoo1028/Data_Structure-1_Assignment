#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Recursive 방식으로 팩토리얼을 계산하는 함수
// 매개변수: int n - 팩토리얼 계산에 사용할 정수 값
// 반환값: unsigned long long - n의 팩토리얼 값
unsigned long long Fact_recursive(int n)
{
    // 기본 조건: n이 1 이하이면 1을 반환 (0! 및 1! = 1)
    if (n <= 1)
        return 1;
    else
        // 재귀 호출: n * (n-1)! 을 계산
        return n * Fact_recursive(n - 1);
}

// Iterative 방식으로 팩토리얼을 계산하는 함수
// 매개변수: int n - 팩토리얼 계산에 사용할 정수 값
// 반환값: unsigned long long - n의 팩토리얼 값
unsigned long long Fact_iterative(int n)
{
    // 팩토리얼 결과를 저장할 변수, 초기값 1
    unsigned long long result = 1;
    // 1부터 n까지 곱하면서 factorial 값을 계산
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main()
{
    // n: 팩토리얼 계산에 사용할 값, 초기값은 0부터 시작
    int n = 0;
    // start와 end: 실행 시간 측정을 위한 clock_t 변수들
    clock_t start, end;
    // result_r와 result_i: 각각 recursive와 iterative 함수의 반환값을 저장
    unsigned long long result_r, result_i;
    // time_r와 time_i: 각각 recursive와 iterative 방식의 실행 시간을 초 단위로 저장
    double time_r, time_i;
    // max_r: 재귀 방식에서 stack overflow가 발생하기 전의 최대 n 값 저장 변수
    int max_r = 0;
    // repeat: 반복 실행 횟수로, 함수 실행 시간을 측정하기 위해 사용 (단위: 횟수)
    int repeat = 100000;

    // 무한 루프, n값을 증가시키면서 팩토리얼을 계산하고 비교함
    while (1)
    {
        // ---------- Recursive 방식 함수 실행 및 시간 측정 ---------- 
        start = clock(); // 실행 시작 시간 저장
        // repeat 횟수만큼 재귀 함수를 호출하여 계산
        for (int i = 0; i < repeat; i++)
        {
            result_r = Fact_recursive(n);
        }
        end = clock(); // 실행 종료 시간 저장
        // Recursive 방식의 실행 시간 계산 (초 단위)
        time_r = ((double)(end - start)) / CLOCKS_PER_SEC;

        // ---------- Iterative 방식 함수 실행 및 시간 측정 ----------
        start = clock(); // 실행 시작 시간 저장
        // repeat 횟수만큼 반복 함수를 호출하여 계산
        for (int i = 0; i < repeat; i++)
        {
            result_i = Fact_iterative(n);
        }
        end = clock(); // 실행 종료 시간 저장
        // Iterative 방식의 실행 시간 계산 (초 단위)
        time_i = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 현재 n값에 대해 재귀 및 반복 방식의 결과를 출력
        printf("%d : Recursive결과 : %llu  Iterative결과 : %llu\n", n, result_r, result_i);

        // 만약 재귀 방식의 결과가 0이면, stack overflow가 발생한 것으로 간주함
        if (result_r == 0)
        {
            // n값을 하나 줄여 overflow가 발생하지 않은 최대의 안정적인 n 값을 기록
            max_r = n - 1;
            printf("Stack Overflow: %d\n", max_r);
            break;
        }

        // 다음 n값에 대해 팩토리얼 계산을 수행하기 위해 n을 1 증가
        n++;
    }

    // 최종적으로 마지막에 측정된 실행 시간 출력
    printf("Recursive방식의 실행 시간: %f 초\n", time_r);
    printf("Iterative방식의 실행 시간: %f 초\n", time_i);
    // Iterative 방식이 max_r 값까지 정상적으로 실행되었음을 출력
    printf("Iterative방식에서 n = %d에서도 정상적으로 수행되었습니다.\n", max_r);

    return 0;
}