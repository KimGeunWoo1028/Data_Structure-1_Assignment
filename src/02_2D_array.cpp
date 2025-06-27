#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 함수: sum
// --------------------------------------------------
// 목적: 정수형 배열의 요소들의 합을 계산한다.
// 매개변수:
//   arr  - 정수형 배열
//   size - 배열의 요소 개수
// 반환값: 배열 요소들의 합을 반환한다.
int sum(int arr[], int size)
{
    int sum = 0; // 합계를 저장할 변수를 0으로 초기화

    // 배열의 각 요소를 순회하며 합계를 계산한다.
    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum; // 계산된 합계를 반환한다.
}

int main()
{
    // 3x3 행렬의 행과 열의 크기를 정의
    int row = 3, col = 3;
    // 3x3 행렬을 미리 정의된 값으로 초기화
    int arr[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };

    char input; // 사용자로부터 입력받을 문자형 변수

    // 사용자에게 입력을 요청:
    // 'a'는 가로(행) 합, '1'은 세로(열) 합을 의미한다.
    printf("원하는 합을 입력하세요 (a:가로 합, 1: 세로 합): ");
    scanf(" %c", &input);

    // 입력값이 'a'인 경우: 첫 번째 행의 합을 계산
    if (input == 'a')
    {
        // 첫 번째 행(arr[0])의 합을 계산하기 위해 sum() 함수를 호출
        int rowsum = sum(arr[0], col);
        // 첫 번째 행의 합을 출력
        printf("행 1의 합: %d\n", rowsum);
    }
    // 입력값이 '1'인 경우: 첫 번째 열의 합을 계산
    else if (input == '1')
    {
        // 각 행의 첫 번째 요소를 저장할 배열 선언 (첫 번째 열)
        int colsumarr[3];

        // 2차원 배열의 각 행에서 첫 번째 열 요소를 추출
        for (int i = 0; i < 3; i++)
        {
            colsumarr[i] = arr[i][0];
        }
        // 추출된 첫 번째 열의 요소들의 합을 계산하기 위해 sum() 함수를 호출
        int colsum = sum(colsumarr, 3);

        // 첫 번째 열의 합을 출력
        printf("열 1의 합: %d\n", colsum);
    }
    // 'a' 또는 '1'이 아닌 다른 입력에 대해 에러 메시지 출력
    else
        printf("잘못된 입력입니다.");

    return 0; // 프로그램 종료
}