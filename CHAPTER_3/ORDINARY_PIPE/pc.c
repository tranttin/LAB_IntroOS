#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define N 100  // Giá trị n, mặc định là 100

// Hàm kiểm tra số nguyên tố
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int pipefd1[2];  // Đường ống 1: Cha -> Con
    int pipefd2[2];  // Đường ống 2: Con -> Cha
    pid_t pid;
    int number, result;

    // Tạo đường ống 1
    if (pipe(pipefd1) == -1) {
        perror("Pipe 1 failed");
        exit(EXIT_FAILURE);
    }

    // Tạo đường ống 2
    if (pipe(pipefd2) == -1) {
        perror("Pipe 2 failed");
        exit(EXIT_FAILURE);
    }

    // Tạo tiến trình con
    pid = fork();

    if (pid < 0) {
        // Lỗi khi tạo tiến trình con
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Tiến trình con
        close(pipefd1[1]);  // Đóng đầu ghi của đường ống 1
        close(pipefd2[0]);  // Đóng đầu đọc của đường ống 2

        // Đọc dữ liệu từ đầu đọc của đường ống 1
        while (read(pipefd1[0], &number, sizeof(number)) > 0) {
            result = is_prime(number);
            // Gửi kết quả lại cho cha qua đường ống 2
            write(pipefd2[1], &result, sizeof(result));
        }

        close(pipefd1[0]);  // Đóng đầu đọc của đường ống 1
        close(pipefd2[1]);  // Đóng đầu ghi của đường ống 2
        exit(EXIT_SUCCESS);

    } else {
        // Tiến trình cha
        close(pipefd1[0]);  // Đóng đầu đọc của đường ống 1
        close(pipefd2[1]);  // Đóng đầu ghi của đường ống 2

        // Gửi từng số từ 2 đến N cho tiến trình con qua đường ống 1
        for (int i = 2; i <= N; i++) {
            write(pipefd1[1], &i, sizeof(i));

            // Nhận kết quả từ tiến trình con qua đường ống 2
            read(pipefd2[0], &result, sizeof(result));

            if (result) {
                printf("%d là số nguyên tố\n", i);
            } else {
                printf("%d không phải là số nguyên tố\n", i);
            }
        }

        close(pipefd1[1]);  // Đóng đầu ghi của đường ống 1
        close(pipefd2[0]);  // Đóng đầu đọc của đường ống 2

        // Chờ tiến trình con kết thúc
        wait(NULL);
    }

    return 0;
}
