# 📚 자료구조 요약 정리 (C언어 기반)

> 이 문서는 C언어로 자료구조를 학습하면서 정리한 개념 요약 노트입니다.

---

## 1️⃣ 배열 (Array)

- **정의**: 같은 자료형의 데이터를 연속적으로 저장하는 자료구조
- **장점**: 인덱스를 통한 빠른 접근 (`arr[3]`)
- **단점**: 크기 고정, 삽입/삭제 시 비효율적
- **예시**
  ```c
  int arr[5] = {1, 2, 3, 4, 5};
  ```

---

## 2️⃣ 연결 리스트 (Linked List)

- **정의**: 노드들이 포인터로 서로 연결된 자료구조
- **장점**: 동적 메모리 사용, 삽입/삭제 유리
- **단점**: 접근 속도가 느림 (순차 접근만 가능)
- **종류**: 단일 연결 리스트, 이중 연결 리스트, 원형 리스트

- **노드 구조 예시**
  ```c
  typedef struct Node {
      int data;
      struct Node* next;
  } Node;
  ```

---

## 3️⃣ 스택 (Stack)

- **정의**: 후입선출(LIFO)의 자료구조
- **기본 연산**: `push`, `pop`, `peek`, `isEmpty`
- **구현 방식**: 배열 또는 연결 리스트

- **사용 예시**: 수식 계산기, 되돌리기 기능(Undo), 함수 호출 스택
- **배열 기반 예시**
  ```c
  #define MAX 100
  int stack[MAX];
  int top = -1;
  ```

---

## 4️⃣ 큐 (Queue)

- **정의**: 선입선출(FIFO)의 자료구조
- **기본 연산**: `enqueue`, `dequeue`, `peek`, `isEmpty`
- **종류**:
  - 선형 큐: 삭제 후 공간이 낭비됨
  - 원형 큐: 공간 재활용 가능
  - 우선순위 큐: 높은 우선순위 먼저 처리

- **원형 큐 예시**
  ```c
  typedef struct {
      int front, rear, size, capacity;
      int* array;
  } Queue;
  ```

---


## 📌 기타 개념 요약

| 개념 | 설명 |
|------|------|
| ADT | Abstract Data Type, 추상 자료형 |
| 시간 복잡도 | 알고리즘 성능 측정 기준 (O(1), O(n) 등) |
| 메모리 관리 | `malloc`, `free`를 이용한 동적 메모리 할당 |

---

## ✅ 참고용 연산 정리

| 자료구조 | 주요 연산 |
|----------|-----------|
| Stack | push, pop, peek |
| Queue | enqueue, dequeue, peek |
| Linked List | insert, delete, traverse |

---
