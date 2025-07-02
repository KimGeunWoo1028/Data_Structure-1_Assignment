#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 큐의 최대 크기, 전체 태스크 개수, 태스크 생성 주기(초)
#define MAX_QUEUE_SIZE 3
#define TOTAL_TASKS 6
#define TASK_GEN_INTERVAL 7

// Task 구조체: 태스크의 id, 남은 처리 시간, 생성 시간을 저장
typedef struct {
    int id;            // 태스크 고유 번호
    int remain_time;   // 태스크의 처리에 필요한 남은 시간
    int gen_time;      // 태스크가 생성된 시각 (clock 값)
} Task;

// Queue 구조체: 원형 큐를 이용하여 태스크들을 관리
typedef struct {
    Task data[MAX_QUEUE_SIZE]; // 태스크들을 저장할 배열
    int front;                 // 큐의 시작 인덱스
    int rear;                  // 새로운 태스크가 들어갈 위치의 인덱스
    int count;                 // 현재 큐에 저장된 태스크 수
} Queue;

// 큐를 초기 상태로 설정하는 함수
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(Queue* q) {
    return q->count == MAX_QUEUE_SIZE;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* q) {
    return q->count == 0;
}

// 큐에 태스크를 삽입하는 함수
// 큐가 가득 차면 0을 리턴하여 삽입 실패를 알림
int enqueue(Queue* q, Task t) {
    if (isFull(q)) return 0; // 큐가 가득 차면 태스크 손실 발생
    q->data[q->rear] = t;    // 현재 rear 위치에 태스크를 저장
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // 원형 큐 방식으로 rear 갱신
    q->count++;              // 큐에 저장된 태스크 수 증가
    return 1;                // 정상적으로 태스크를 삽입함
}

// 큐에서 태스크를 제거하는 함수
// 큐가 비어있으면 0을 리턴하여 제거 실패를 알림
int dequeue(Queue* q, Task* t) {
    if (isEmpty(q)) return 0; // 큐가 비어있으면 제거 불가
    *t = q->data[q->front];   // front 위치의 태스크를 가져옴
    q->front = (q->front + 1) % MAX_QUEUE_SIZE; // 원형 큐 방식으로 front 갱신
    q->count--;               // 큐에 저장된 태스크 수 감소
    return 1;                 // 정상적으로 태스크를 제거함
}

int main() {
    srand(time(NULL)); // 난수 생성을 위한 시드 설정

    Queue q;
    initQueue(&q); // 큐 초기화

    int clock = 0;             // 전체 시뮬레이션 시간을 나타내는 clock 변수
    int tasks_generated = 0;   // 생성된 태스크 수
    int tasks_finished = 0;    // 완료된 태스크 수

    Task current_task;         // 현재 실행중인 태스크를 저장하는 변수
    int processing = 0;        // 태스크 처리 상태 (0: 처리 중 아님, 1: 처리 중)

    int processing_time_left = 0;   // 현재 태스크의 남은 처리 시간
    int total_processing_time = 0;  // 현재 태스크의 총 처리 시간 (출력용)

    // 전체 태스크가 완료될 때까지 시뮬레이션을 진행
    while (tasks_finished < TOTAL_TASKS) {
        // 1. 태스크 생성 단계
        // 조건: 전체 생성 태스크 수가 TOTAL_TASKS보다 적으며, clock이 TASK_GEN_INTERVAL의 배수일 때
        if (tasks_generated < TOTAL_TASKS && clock % TASK_GEN_INTERVAL == 0) {
            int t_id = tasks_generated + 1;            // 태스크 id는 생성 순서대로 지정
            int t_remain = (rand() % 11) + 5;            // 5초 이상 15초 이하의 랜덤 처리 시간 결정
            Task new_task = { t_id, t_remain, clock };   // 새로운 태스크 구조체 생성

            // 큐에 태스크 삽입 시도, 실패 시 태스크 손실 메시지 출력
            if (!enqueue(&q, new_task)) {
                printf("[ Task Loss 발생 at clock %d ]\n", clock);
            }
            else {
                // 삽입 성공 시 태스크 정보 출력
                printf("task enqueue at clock %d : task %d, remain_time %d\n", clock, new_task.id, new_task.remain_time);
            }
            tasks_generated++; // 생성된 태스크 수 증가
        }

        // 2. 태스크 처리 시작 단계
        if (!processing) { // 현재 처리중인 태스크가 없으면
            if (!isEmpty(&q)) { // 대기 중인 태스크가 있는 경우
                dequeue(&q, &current_task);   // 큐에서 태스크를 제거하여 가져옴
                processing = 1; // 태스크 처리 상태 활성화
                processing_time_left = current_task.remain_time; // 남은 처리 시간을 해당 태스크의 remain_time으로 설정
                total_processing_time = current_task.remain_time; // 총 처리 시간 기록 (출력용)
                printf("\n지금 처리할 task : %d\n", current_task.id);
            }
        }

        // 3. 현재 태스크 처리 진행
        if (processing) {
            // 남은 처리 시간을 출력 (진행 상태 표시)
            printf("%d ", processing_time_left);

            // 큐에 대기중인 태스크가 있고, 남은 시간이 전체 처리 시간의 절반에 도달했을 때
            if (q.count > 0 && processing_time_left == total_processing_time / 2) {
                // 다음 처리될 태스크 id를 예비 출력
                printf("\n[ 다음 task 생성 : %d ]\n", q.data[q.front].id);
            }

            // 남은 시간이 1초인 경우, 0을 출력하여 종료 직전임을 알림
            if (processing_time_left == 1) {
                printf("0\n");
            }

            processing_time_left--; // 1초 처리 진행 후 남은 시간 감소

            // 태스크 처리 완료 시
            if (processing_time_left == 0) {
                printf("<Task를 %d초 동안 처리완료>\n\n", total_processing_time);
                processing = 0;   // 처리 상태를 해제
                tasks_finished++; // 완료된 태스크 수 증가
            }
        }

        clock++; // 시뮬레이션 clock 1초 증가
    }

    // 전체 시뮬레이션 소요 시간(초) 출력
    printf("전체 연산시간 : %d초\n", clock);

    return 0; // 프로그램 정상 종료
}
