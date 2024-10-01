#include <stdio.h>
#include <omp.h>

#define SIZE 2000000 // Kích thước mảng

int main() {
    float sum = 0;
    float array[SIZE];

    // Khởi tạo mảng
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1.010101; // Giá trị từ 1 đến SIZE
    }

    // Đo thời gian bắt đầu
    double start_time = omp_get_wtime();

    // Tính tổng sử dụng OpenMP
 //   #pragma omp parallel num_threads(4) // Chỉ định số lượng luồng
    #pragma omp parallel             // Chỉ định số lượng luồng ngầm
    {
        long long local_sum = 0;

        #pragma omp for
        for (int i = 0; i < SIZE; i++) {
            local_sum += array[i];
        }

        // Cộng dồn kết quả từ các thread
        #pragma omp atomic
        sum += local_sum;
    }

    // Đo thời gian kết thúc
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // In kết quả
    printf("Total sum = %f\n", sum);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
