/*
   C 프로그램: 동적 배열의 확장 방식 비교
   - mode 1: 배열이 가득 찰 때마다 현재 용량의 2배로 확장
   - mode 2: 배열이 가득 찰 때마다 용량을 1씩 증가
   1000개의 정수를 배열에 삽입하면서, 각 방식의 성능 (삽입 시간 및 확장 횟수)을 비교한다.
*/

#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 보안 경고를 비활성화하기 위한 매크로
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// element를 int로 정의 (배열 요소의 타입)
typedef int element;

// 동적 배열 구조체 정의
typedef struct {
    element* data;        // 실제 데이터를 저장할 동적 배열 메모리의 주소
    int size;             // 현재 저장된 데이터 개수
    int capacity;         // 현재 배열이 저장 가능한 총 용량
    int extension_count;  // 배열 확장(재할당) 횟수
} ArrayList;

// 초기화 함수: 동적 배열을 초기화한다.
// 초기 용량을 1로 설정하고, 배열 및 관련 변수들을 초기화한다.
void init(ArrayList* list) {
    list->data = (element*)malloc(sizeof(element) * 1);   // 초기 용량 1의 메모리 할당
    list->size = 0;              // 초기에는 저장된 데이터가 없으므로 0으로 설정
    list->capacity = 1;          // 초기 용량을 1로 설정
    list->extension_count = 0;   // 아직 확장이 이루어지지 않았으므로 0으로 초기화
}

// 삽입 함수: 배열의 마지막에 새 데이터를 추가한다.
// mode 매개변수에 따라 확장 전략을 선택 (mode 1: 2배 확장, mode 2: +1 확장)
void insert_last(ArrayList* list, element value, int mode) {
    // 배열이 가득 찬 경우, 확장이 필요함
    if (list->size == list->capacity) {
        // mode에 따른 확장 방법 선택
        if (mode == 1) {
            list->capacity *= 2;    // mode 1: 현재 용량의 2배로 확장 (더 효율적)
        }
        else if (mode == 2) {
            list->capacity += 1;    // mode 2: 현재 용량에서 1씩 증가 (덜 효율적)
        }
        // realloc을 사용하여 확장된 크기에 맞게 메모리를 재할당
        list->data = (element*)realloc(list->data, sizeof(element) * list->capacity);
        list->extension_count++;    // 확장이 발생했으므로, 횟수를 1 증가시킴
    }
    // 새 데이터를 배열의 마지막에 삽입하고, 배열의 크기를 증가시킴
    list->data[list->size++] = value;
}

// 메모리 해제 함수: 동적 배열에 할당된 메모리를 해제하여 메모리 누수를 방지한다.
void free_list(ArrayList* list) {
    free(list->data); // 동적으로 할당된 메모리 해제
}

// 실험 실행 함수: 지정된 확장 모드를 사용하여 배열에 1부터 1000까지의 데이터를 삽입하고, 실행 시간과 확장 횟수를 출력한다.
void run_test(int mode) {
    ArrayList list;  // 동적 배열 구조체 변수 선언
    init(&list);     // 동적 배열 초기화

    clock_t start = clock();  // 시작 시간 기록

    // 1부터 1000까지 정수를 배열에 삽입
    for (int i = 1; i <= 1000; i++) {
        insert_last(&list, i, mode);  // 선택한 확장 모드에 따라 데이터 삽입
    }

    clock_t end = clock();  // 종료 시간 기록
    // 삽입 작업에 걸린 총 시간을 초 단위로 계산
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // 사용된 확장 방식에 따라 제목 출력
    if (mode == 1) {
        printf("[2배 확장 방식]\n");
    }
    else if (mode == 2) {
        printf("[+1 확장 방식]\n");
    }

    // 삽입 실행 시간과 배열의 확장 횟수 출력
    printf("삽입 시간: %f초\n", elapsed_time);
    printf("배열 확장 횟수: %d회\n\n", list.extension_count);

    free_list(&list);  // 동적 배열에 할당된 메모리 해제
}

// main 함수: 두 가지 확장 방식을 순차적으로 테스트한다.
int main() {
    // 프로그램 시작 메시지 출력
    printf("=== Dynamic Array 확장 방식 비교 ===\n\n");

    run_test(1);  // 모드 1: 배열 용량을 2배 확장하는 방식 테스트
    run_test(2);  // 모드 2: 배열 용량을 +1씩 확장하는 방식 테스트

    return 0;     // 프로그램 종료
}