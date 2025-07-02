#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 scanf 등 사용 시 보안 경고 제거
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000  // 테스트할 배열/연결리스트의 기본 크기

typedef int element;  // 리스트에 저장될 데이터의 자료형 정의 (현재는 int형)

/* 단일 연결 리스트 노드를 정의하는 구조체 */
typedef struct listnode {
	element data;              // 노드에 저장된 데이터
	struct listnode* next;     // 다음 노드를 가리키는 포인터
} listnode;

/* 리스트의 맨 앞(head)에 새 노드를 삽입하는 함수 */
listnode* insert_head(listnode* head, element value)
{
	// 새 노드를 위한 동적 메모리 할당
	listnode* new_node = (listnode*)malloc(sizeof(listnode));
	new_node->data = value;     // 데이터 저장
	new_node->next = head;      // 새 노드의 next는 기존 head를 가리킴
	return new_node;            // 새 노드를 새로운 head로 반환
}

/* 리스트의 모든 노드를 메모리에서 해제하는 함수 */
void freelist(listnode* head)
{
	listnode* temp;
	while (head != NULL) {
		temp = head;           // 현재 head를 임시로 저장
		head = head->next;     // head를 다음 노드로 이동
		free(temp);            // 임시로 저장한 노드를 메모리 해제
	}
}

/* 리스트에서 특정 인덱스(index)에 위치한 데이터를 반환하는 함수 */
element get(listnode* head, int index)
{
	listnode* cur = head;       // 현재 노드를 가리킬 포인터
	for (int i = 0; i < index; i++) {
		cur = cur->next;        // index 위치까지 이동
	}
	return cur->data;           // index 번째 노드의 data 반환
}

/* 리스트에서 특정 위치(index)의 노드를 삭제하는 함수 */
listnode* delete_position(listnode* head, int index)
{
	// 첫 번째 노드를 삭제하는 경우
	if (index == 0) {
		listnode* temp = head;      // 삭제할 노드 저장
		head = head->next;          // head를 다음 노드로 변경
		free(temp);                 // 삭제한 노드 메모리 해제
		return head;                // 새로운 head 반환
	}

	// 삭제할 노드의 바로 이전 노드를 찾기
	listnode* cur = head;
	for (int i = 0; i < index - 1; i++) {
		cur = cur->next;            // index - 1 번째 노드까지 이동
	}

	// 삭제할 노드를 cur->next로 설정
	listnode* temp = cur->next;
	if (temp) {
		cur->next = temp->next;     // 이전 노드가 다음 노드를 건너뛰도록 설정
		free(temp);                 // 삭제 노드 해제
	}
	return head;                    // 변경된 리스트 반환
}

/* main 함수: 배열과 연결 리스트의 삽입/접근/삭제 속도 비교 */
int main()
{
	element array[SIZE];         // 정적 배열 선언
	clock_t start, end;          // 시간 측정용 변수
	double t;                    // 수행 시간 저장
	double sum;                  // 합계 저장
	int random[1000];            // 랜덤 인덱스 저장용 배열

	printf("\n=========================================\n\n");

	srand(time(NULL));           // 랜덤 시드 초기화

	/* 배열 초기화: 0부터 SIZE-1까지의 값 저장 */
	start = clock();
	for (int i = 0; i < SIZE; i++) {
		array[i] = i;
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Array 걸린 시간 : %f초 \n", t);

	/* 연결 리스트 초기화: 0부터 SIZE-1까지의 값 저장 */
	listnode* head = NULL;
	start = clock();
	for (int i = SIZE - 1; i >= 0; i--) {
		head = insert_head(head, i);  // 항상 앞에 삽입 → 최종 결과는 0 ~ SIZE-1 순서
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Linked list 걸린 시간 : %f초 \n", t);

	printf("\n=========================================\n\n");

	/* 0 ~ SIZE-1 범위의 랜덤 인덱스 1000개 생성 */
	for (int i = 0; i < 1000; i++) {
		random[i] = rand() % SIZE;
	}

	/* 배열에서 랜덤 인덱스 접근 */
	sum = 0;
	start = clock();
	for (int i = 0; i < 1000; i++) {
		sum += array[random[i]];  // O(1) 접근
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Array random access 걸린 시간 : %f초 \n", t);
	printf("Array random access index 합 : %.2f \n\n", sum);

	/* 연결 리스트에서 랜덤 인덱스 접근 */
	sum = 0;
	start = clock();
	for (int i = 0; i < 1000; i++) {
		sum += get(head, random[i]);  // O(n) 접근
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Linked List random access 걸린 시간 : %f초 \n", t);
	printf("Linked List random access index 합 : %.2f \n", sum);

	printf("\n=========================================\n\n");

	/* 배열에서 1000개의 요소를 무작위로 삭제 */
	int cur_size = SIZE; // 배열의 현재 유효 크기
	start = clock();
	for (int i = 0; i < 1000; i++) {
		int index = rand() % cur_size;
		for (int j = index; j < cur_size - 1; j++) {
			array[j] = array[j + 1]; // 삭제한 인덱스 이후의 요소를 왼쪽으로 한 칸씩 이동
		}
		cur_size--; // 배열 크기 감소
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("array random delete 걸린 시간 : %f초\n", t);

	/* 연결 리스트에서 1000개의 노드를 무작위로 삭제 */
	start = clock();
	cur_size = SIZE;
	for (int i = 0; i < 1000; i++) {
		int index = rand() % cur_size;
		head = delete_position(head, index);
		cur_size--;
	}
	end = clock();
	t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("linked list random delete 걸린 시간 : %f초 \n", t);

	printf("\n=========================================\n\n");

	/* 연결 리스트에 할당된 메모리 해제 */
	freelist(head);

	return 0;
}