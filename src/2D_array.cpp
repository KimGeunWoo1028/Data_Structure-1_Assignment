#define _CRT_SECURE_NO_WARNINGS   // 안전하지 않은 함수 사용 관련 경고 무시
#include <stdio.h>                // 표준 입출력 함수 사용을 위한 헤더 파일

// 함수: sum
// 역할: 주어진 1차원 배열의 모든 요소의 합을 계산함
// 매개변수:
//   arr[] - 합을 구할 정수형 배열
//   size  - 배열의 크기 (요소의 개수)
// 반환값: 배열 요소의 총 합
int sum(int arr[], int size)
{
    int sum = 0;                   // 합을 저장할 변수 초기화
    for (int i = 0; i < size; i++) // 배열의 모든 요소를 순회
        sum += arr[i];             // 각 요소를 누적 합에 더함
    return sum;                    // 최종 합을 반환
}

int main()
{
    int row = 3, col = 3;          // 2차원 배열의 행과 열의 크기를 정의
    // 3x3 크기의 배열을 미리 정의된 값으로 초기화
    int arr[3][3] = { {1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9} };

    char input;                  // 사용자 입력을 저장할 변수

    // 사용자에게 가로 합('a') 또는 세로 합('1') 입력을 요청하는 메시지 출력
    printf("원하는 합을 입력하세요 (a:가로 합, 1: 세로 합): ");
    scanf(" %c", &input);         // 공백을 포함하여 문자 하나를 입력받음

    if (input == 'a')            // 입력 값이 'a'인 경우 (가로 합)
    {
        // arr[0]는 2차원 배열의 첫 번째 행을 가리킴
        int rowsum = sum(arr[0], col);  // 첫 번째 행의 합을 계산
        printf("행 1의 합: %d\n", rowsum);  // 계산된 가로 합을 출력
    }
    else if (input == '1')       // 입력 값이 '1'인 경우 (세로 합)
    {
        int colsumarr[3];        // 첫 번째 열의 값을 담을 임시 배열 선언

        for (int i = 0; i < 3; i++) // 각 행의 첫 번째 요소를 임시 배열에 저장
        {
            colsumarr[i] = arr[i][0];
        }
        int colsum = sum(colsumarr, 3);  // 임시 배열을 이용해 첫 번째 열의 합을 계산
        printf("열 1의 합: %d\n", colsum);  // 계산된 세로 합을 출력
    }
    else                         // 위 두 조건에 해당하지 않는 잘못된 입력인 경우
        printf("잘못된 입력입니다.");  // 잘못된 입력임을 사용자에게 알림

    return 0;                    // 프로그램 종료 (정상 종료 시 0 반환)
}