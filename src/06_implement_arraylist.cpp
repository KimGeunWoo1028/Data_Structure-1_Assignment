// _CRT_SECURE_NO_WARNINGS: Visual Studio에서 보안 경고를 무시하기 위한 매크로
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>    // 표준 입출력 함수 사용
#include <stdlib.h>   // 동적 메모리 할당 함수 사용

// element: 배열 리스트에 저장할 데이터 타입 (여기서는 int)
typedef int element;

// ArrayList 구조체는 동적 배열 리스트를 표현합니다.
// size: 리스트의 최대 크기
// count: 현재 저장된 요소의 개수
// capacity: 정수 데이터를 저장하는 동적 배열 포인터
typedef struct
{
    int size;
    int count;
    element* capacity;
} ArrayList;

// create: 지정한 크기로 동적 배열 리스트를 생성하여 초기화합니다.
// 메모리 할당 실패 시 오류 메시지를 출력하고 프로그램을 종료합니다.
ArrayList* create(int size)
{
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    if (list == NULL)
    {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    list->size = size;
    list->count = 0;
    list->capacity = (element*)malloc(sizeof(element) * size);
    if (list->capacity == NULL)
    {
        printf("메모리 할당 실패\n");
        free(list);
        exit(1);
    }
    return list;
}

// is_full: 리스트가 가득 찼는지 판단합니다.
// 현재 count가 최대 크기 size와 같으면 리스트가 가득 찬 상태
int is_full(ArrayList* list)
{
    return list->count == list->size;
}

// is_empty: 리스트가 비어있는지 판단합니다.
// count가 0이면 리스트가 비어있습니다.
int is_empty(ArrayList* list)
{
    return list->count == 0;
}

// print_list: 리스트에 저장된 모든 요소들을 출력합니다.
// 리스트가 비어있으면 아무것도 출력하지 않습니다.
void print_list(ArrayList* list)
{
    printf("리스트: ");
    for (int i = 0; i < list->count; i++)
        // 각 요소를 순서대로 출력
        printf("%d ", list->capacity[i]);
    printf("\n");
}

// insert_first: 리스트의 첫 번째 위치에 값을 삽입합니다.
// 리스트가 가득 찬 경우 삽입하지 않고 경고 메시지를 출력합니다.
// 삽입 전 기존 요소들을 오른쪽으로 이동시킵니다.
void insert_first(ArrayList* list, element value)
{
    if (is_full(list))
    {
        printf("리스트가 가득 찼습니다.\n");
        return;
    }

    // 기존 요소들을 오른쪽으로 한 칸씩 이동
    for (int i = list->count; i > 0; i--)
        list->capacity[i] = list->capacity[i - 1];
    // 첫 번째 위치에 새 값을 삽입
    list->capacity[0] = value;
    list->count++;
}

// insert: 지정된 index(pos) 위치에 값을 삽입합니다.
// index 이후의 요소들을 오른쪽으로 한 칸씩 이동시켜 삽입 공간을 마련합니다.
void insert(ArrayList* list, int pos, element value)
{
    if (is_full(list))
    {
        printf("리스트가 가득 찼습니다.\n");
        return;
    }

    // pos 위치 이후의 요소를 오른쪽으로 이동
    for (int i = list->count; i > pos; i--)
        list->capacity[i] = list->capacity[i - 1];
    // 지정한 위치에 값을 삽입
    list->capacity[pos] = value;
    list->count++;
}

// insert_last: 리스트의 마지막 위치에 값을 삽입합니다.
// 리스트 끝에 값을 추가하고, count 값을 1 증가시킵니다.
void insert_last(ArrayList* list, element value)
{
    if (is_full(list))
    {
        printf("리스트가 가득 찼습니다.\n");
        return;
    }

    // 마지막 위치에 새 값을 삽입
    list->capacity[list->count] = value;
    list->count++;
}

// delete_first: 리스트의 첫 번째 요소를 삭제합니다.
// 삭제 후 나머지 요소들을 왼쪽으로 이동시켜 공간을 메웁니다.
void delete_first(ArrayList* list)
{
    if (is_empty(list))
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    // 첫 번째 요소를 삭제하고 나머지 요소들을 왼쪽으로 이동
    for (int i = 0; i < list->count - 1; i++)
        list->capacity[i] = list->capacity[i + 1];
    list->count--;
}

// delete_: 지정한 index(pos) 위치의 요소를 삭제합니다.
// 삭제 후, 해당 위치 이후의 요소들을 한 칸씩 왼쪽으로 이동합니다.
void delete_(ArrayList* list, int pos)
{
    if (is_empty(list))
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    // pos 위치의 요소 삭제 후, 뒤의 요소들을 이동
    for (int i = pos; i < list->count - 1; i++)
        list->capacity[i] = list->capacity[i + 1];
    list->count--;
}

// delete_last: 리스트의 마지막 요소를 삭제합니다.
// count 값을 1 감소시켜 마지막 요소를 제거합니다.
void delete_last(ArrayList* list)
{
    if (is_empty(list))
    {
        printf("리스트가 비어있습니다.\n");
        return;
    }

    // 마지막 요소 삭제를 위해 count 값만 감소
    list->count--;
}

// free_arraylist: 리스트의 동적으로 할당된 메모리를 해제합니다.
// capacity 배열을 먼저 해제한 후, ArrayList 구조체 메모리를 해제합니다.
void free_arraylist(ArrayList* list)
{
    free(list->capacity);
    free(list);
}

// main: 프로그램의 메인 함수. 사용자 입력을 받아 리스트를 생성하고,
// 다양한 삽입 및 삭제 연산을 수행합니다.
// 각 연산 후 리스트 상태를 출력하여 결과를 확인합니다.
// 프로그램 종료 전에 할당한 메모리를 free_arraylist 호출로 해제합니다.
int main()
{
    int size;
    printf("리스트의 크기를 입력하시오: ");
    scanf("%d", &size);
    ArrayList* list = create(size);

    // 첫 번째 위치에 연속적으로 값 삽입 (뒤로 미는 방식)
    insert_first(list, 40);
    insert_first(list, 30);
    insert_first(list, 20);
    insert_first(list, 10);
    print_list(list);  // 삽입 결과 출력

    // 인덱스 2에 값 25 삽입 (중간 삽입)
    insert(list, 2, 25);
    print_list(list);  // 삽입 결과 출력

    // 마지막 위치에 값 50 삽입
    insert_last(list, 50);
    print_list(list);  // 삽입 결과 출력

    // 첫 번째 요소 삭제
    delete_first(list);
    print_list(list);  // 삭제 결과 출력

    // 인덱스 3의 요소 삭제
    delete_(list, 3);
    print_list(list);  // 삭제 결과 출력

    // 마지막 요소 삭제
    delete_last(list);
    print_list(list);  // 삭제 결과 출력

    // 메모리 해제
    free_arraylist(list);

    return 0;
}