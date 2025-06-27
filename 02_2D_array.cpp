#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 함수: sum
// 목적: 정수 배열의 모든 요소의 합을 계산한다.
// 매개변수:
//    arr  - 정수 배열
//    size - 배열의 요소 개수
// 반환값:
//    배열 요소의 총합
int sum(int arr[], int size)
{
    int sum = 0; // 합을 저장할 변수를 0으로 초기화
    // 배열의 각 요소를 순회하며 합을 계산
    for (int i = 0; i < size; i++)
        sum += arr[i]; // 현재 요소를 합계에 더함
    return sum; // 계산된 총합 반환
}

int main()
{
    // 2차원 배열의 행과 열의 크기를 선언
    int row = 3, col = 3;

    // 3x3 크기의 2차원 배열을 1부터 9까지의 값으로 초기화
    int arr[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };

    // 사용자로부터 입력을 받을 문자형 변수
    char input;

    // 사용자에게 합산 방식을 선택하도록 안내
    // 'a'는 가로(행) 합, '1'은 세로(열) 합을 의미함
    printf("원하는 합을 입력하세요 (a:가로 합, 1: 세로 합): ");
    scanf(" %c", &input);  // 공백을 포함하여 문자 하나 입력 받아옴

    // 사용자가 가로 합을 선택한 경우
    if (input == 'a')
    {
        // 첫 번째 행의 합을 계산하기 위해 배열의 첫 번째 행을 인자로 전달
        int rowsum = sum(arr[0], col);
        // 첫 번째 행의 합 출력
        printf("행 1의 합: %d\n", rowsum);
    }
    // 사용자가 세로 합을 선택한 경우
    else if (input == '1')
    {
        // 첫 번째 열의 요소들을 저장할 임시 배열 선언
        int colsumarr[3];

        // 각 행에서 첫 번째 열의 요소를 추출
        for (int i = 0; i < 3; i++)
        {
            colsumarr[i] = arr[i][0];  // 각 행의 첫 번째 열 값을 배열에 저장
        }
        // 임시 배열을 이용해 첫 번째 열의 합 계산
        int colsum = sum(colsumarr, 3);
        // 첫 번째 열의 합 출력
        printf("열 1의 합: %d\n", colsum);
    }
    // 올바르지 않은 입력을 처리하는 부분
    else
        printf("잘못된 입력입니다.");  // 잘못된 입력에 대한 오류 메시지 출력

    return 0;  // 프로그램 종료
}