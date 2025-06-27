#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	int a[100]; // 100개 만큼 저장할 수 있는 변수a 라는 배열
	int b[10]; // 10개 만큼 저장할 수 있는 변수b 라는 배열
	int n = 0;

	int num;
	srand(time(0)); // 프로그램을 실행 할 때 마다 다른 수를 출력
	for (int i = 0; i < 100; i++) {
		num = rand() % 101;
		a[i] = num;
	}
	// 변수a 배열중 10개를 변수b 배열에 저장
	for (int i = 0; i < 10; i++) {
		b[i] = a[i];
		printf("%d ", b[i]);
	}
	printf("\n\n");
	// b 배열에서 최댓값 구하기
	int max = -99999; // 어떠한 값 보다 작은수로 초기화
	for (int i = 1; i < 10; i++) {    // 배열b의 인덱스를 각각 하나씩 비교
		if (max < b[i]) {
			max = b[i];
		}
	}
	printf("%d ", max);
}