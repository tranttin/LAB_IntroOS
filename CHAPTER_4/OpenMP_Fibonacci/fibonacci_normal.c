#include <stdio.h>
#include <time.h>

// Hàm tính Fibonacci
long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n = 30; // Số Fibonacci cần tính
    long results[n + 1];

    // Đo thời gian bắt đầu
    clock_t start_time = clock();

    // Tính toán Fibonacci
    for (int i = 0; i <= n; i++) {
        results[i] = fibonacci(i);
    }

    // Đo thời gian kết thúc
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // In kết quả
    printf("Fibonacci sequence up to %d:\n", n);
    for (int i = 0; i <= n; i++) {
        printf("Fibonacci(%d) = %ld\n", i, results[i]);
    }

    // In thời gian thực thi
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
