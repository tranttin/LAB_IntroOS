#include <stdio.h>
#include <omp.h>
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
    double start_time = omp_get_wtime();

    // Sử dụng OpenMP để tính toán song song
    #pragma omp parallel for
    for (int i = 0; i <= n; i++) {
        results[i] = fibonacci(i);
    }

    // Đo thời gian kết thúc
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // In kết quả
    printf("Fibonacci sequence up to %d:\n", n);
    for (int i = 0; i <= n; i++) {
        printf("Fibonacci(%d) = %ld\n", i, results[i]);
    }

    // In thời gian thực thi
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
