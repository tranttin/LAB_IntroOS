#include <stdio.h>
#include <time.h> // Thêm thư viện này

#define SIZE 2000000 // Kích thước mảng

int main() {
    float sum = 0.0;
    float array[SIZE];

    // Khởi tạo mảng
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1.010101; // Giá trị từ 1 đến SIZE
    }

    // Đo thời gian bắt đầu
    clock_t start_time = clock();

    // Tính tổng
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    // Đo thời gian kết thúc
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // In kết quả
    printf("Total sum = %f\n", sum);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
