// _CRT_SECURE_NO_WARNINGS를 정의하여 일부 컴파일러에서 보안 경고를 비활성화
#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>      // 표준 입출력 함수 사용
#include <stdlib.h>     // 동적 메모리 할당 함수 사용
#include <malloc.h>     // malloc 함수를 사용하기 위한 헤더 (일부 컴파일러 필요)

// Student 구조체 정의: 학생의 이름, 나이, 성적 정보를 저장
struct Student {
    char name[50];   // 학생 이름 (최대 49자 + 널 종료 문자)
    int age;         // 학생 나이
    float grade;     // 학생 성적
} student;           // student 변수 선언 (이 예제에서는 사용되지 않음)

// 학생 정보를 출력하는 함수
// 매개변수: 학생 구조체의 포인터를 입력받아 해당 학생의 정보를 출력
void printStudent(struct Student* student) {
    printf("이름: %s, 나이: %d, 성적: %.2f\n", student->name, student->age, student->grade);
}

// 학생 배열의 성적 평균을 계산하는 함수
// 매개변수: students - 학생 배열의 포인터, numStudents - 배열에 있는 학생 수
// 반환값: 전체 학생의 성적 평균
float Average(struct Student* students, int numStudents) {
    float total = 0.0;
    // 모든 학생의 성적을 더함
    for (int i = 0; i < numStudents; i++) {
        total += students[i].grade;
    }
    // 총합을 학생 수로 나눠 평균을 계산
    return total / numStudents;
}

// main 함수: 프로그램의 시작점
int main() {

    // 동적 메모리 할당: 3명의 학생 정보를 저장할 공간을 할당
    struct Student* students = (struct Student*)malloc(3 * sizeof(struct Student));

    // 메모리 할당에 실패하면 에러 메시지를 출력하고 프로그램 종료
    if (students == NULL) {
        printf("메모리 할당 실패!\n");
        return 1;
    }

    // 사용자로부터 3명의 학생 정보를 입력받음
    printf("학생 정보를 입력하세요:\n");
    for (int i = 0; i < 3; i++) {
        printf("학생 %d:\n", i + 1);
        printf("이름: ");
        scanf("%s", students[i].name);  // 학생의 이름 입력
        printf("나이: ");
        scanf("%d", &students[i].age);    // 학생의 나이 입력
        printf("성적: ");
        scanf("%f", &students[i].grade);  // 학생의 성적 입력
    }

    // 입력받은 학생 정보를 출력함
    printf("\n학생 정보:\n");
    for (int i = 0; i < 3; i++) {
        printStudent(&students[i]);  // printStudent 함수를 호출하여 각 학생 정보를 출력
    }

    // 학생들의 성적 평균을 계산하고 출력함
    float average = Average(students, 3);
    printf("\n전체 학생의 성적 평균: %.2f\n", average);

    // 동적으로 할당한 메모리를 해제하여 메모리 누수를 방지
    free(students);

    // 프로그램 정상 종료
    return 0;
}