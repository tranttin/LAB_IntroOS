#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/time.h>

// Hàm kiểm tra số nguyên tố
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm kiểm tra và in số nguyên tố trong tiến trình con
void check_prime_process(int number) {
    // Đình trệ 3 giây
    sleep(3);

    if (is_prime(number)) {
        printf("Tiến trình %d: %d là số nguyên tố.\n", getpid(), number);
    }
}

int main() {
    const int MAX_PROCESSES = 50;  // Giới hạn số lượng tiến trình con
    const int MAX = 100;  // Số nguyên lớn nhất
    int active_processes = 0;      // Số tiến trình con hiện tại
    pid_t pid;

    // Biến để lưu thời gian bắt đầu và kết thúc
    struct timeval start_time, end_time;

    // Bắt đầu đo thời gian
    gettimeofday(&start_time, NULL);

    for (int i = 2; i <= MAX; i++) {
        if (active_processes >= MAX_PROCESSES) {
            // Nếu đạt giới hạn, đợi một tiến trình con kết thúc
            wait(NULL);
            active_processes--;
        }

        // Tạo tiến trình con
        pid = fork();

        if (pid == 0) {  // Tiến trình con
            check_prime_process(i);
            exit(0); // Kết thúc tiến trình con
        } else if (pid > 0) {
            active_processes++;  // Tăng số tiến trình con hiện tại
        } else {
            // Lỗi khi tạo tiến trình con
            printf("Lỗi tạo tiến trình con!\n");
            exit(1);
        }
    }

    // Đợi tất cả các tiến trình con hoàn thành
    while (active_processes > 0) {
        wait(NULL);
        active_processes--;
    }

    // Kết thúc đo thời gian
    gettimeofday(&end_time, NULL);

    // Tính toán thời gian chạy (theo giây và micro giây)
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Hoàn thành kiểm tra các số nguyên tố.\n");
    printf("Thời gian chạy: %.6f giây\n", elapsed_time);

    return 0;
}
