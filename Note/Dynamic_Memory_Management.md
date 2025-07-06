# 📚 동적 메모리 사용법 및 관리

---

### ✅ 개요

C에서 **동적 메모리 관리**란, 실행 도중 필요할 때 메모리를 할당/해제하는 기술입니다.  
주요 함수는 `malloc`, `calloc`, `realloc`, `free`.

---

### 🔧 주요 함수 정리

#### 🔹 `malloc`

> 메모리 블록을 지정한 크기만큼 할당. 초기화는 되지 않음.

```c
int* ptr = (int*)malloc(sizeof(int) * 5);
if (ptr == NULL) {
    // 메모리 할당 실패 처리
}
```

---

#### 🔹 `calloc`

> 메모리 블록을 할당하고 0으로 초기화.

```c
int* arr = (int*)calloc(5, sizeof(int));
```

---

#### 🔹 `realloc`

> 기존 메모리 블록의 크기 변경. 기존 데이터 유지됨.

```c
ptr = (int*)realloc(ptr, sizeof(int) * 10);
```

---

#### 🔹 `free`

> 동적으로 할당된 메모리를 해제함.

```c
free(ptr);
ptr = NULL; // 댕글링 포인터 방지
```

---

### 💡 메모리 관리 팁

- ✔️ `NULL` 체크 필수 (`malloc` 실패 시)  
- ✔️ `free` 안 하면 메모리 누수 발생  
- ✔️ `realloc` 실패 시 원래 포인터 유지됨  
- ✔️ 초기화 필요 시 `calloc` 사용  
- ✔️ `free` 후 반드시 `NULL`로 초기화  
- ✔️ `sizeof`로 정확한 크기 계산

---

### 🧪 예제 코드

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* arr = (int*)malloc(sizeof(int) * 5);
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 5; i++)
        arr[i] = i * 10;

    arr = (int*)realloc(arr, sizeof(int) * 10);
    if (!arr) {
        printf("Reallocation failed\n");
        return 1;
    }

    for (int i = 5; i < 10; i++)
        arr[i] = i * 10;

    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    arr = NULL;

    return 0;
}
```
