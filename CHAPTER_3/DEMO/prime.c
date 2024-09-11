#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

// Hàm kiểm tra số nguyên tố
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void check_prime_process(int number) {
    // Đình trệ 3 giây trước khi trả lời
    sleep(3);

    if (is_prime(number)) {
        printf("Tiến trình %d: %d là số nguyên tố.\n", getpid(), number);
    } else {
        printf("Tiến trình %d: %d không phải là số nguyên tố.\n", getpid(), number);
    }
}

int main() {
    int number;

    while (1) {
        printf("Nhập một số (nhập số âm để kết thúc): ");
        scanf("%d", &number);

        if (number < 0) {
            printf("Số âm được nhập, chương trình sẽ kết thúc sau khi các tiến trình con hoàn thành.\n");
            break;
        }

        // Tạo tiến trình con để kiểm tra số nguyên tố
        pid_t pid = fork();

        if (pid == 0) {  // Tiến trình con
            check_prime_process(number);
            exit(0); // Kết thúc tiến trình con
        } else if (pid > 0) {
            // Tiến trình cha quay lại nhận số tiếp theo
            printf("Tiến trình cha %d: Đã gửi yêu cầu kiểm tra số %d\n", getpid(), number);
        } else {
            printf("Lỗi tạo tiến trình con!\n");
            exit(1);
        }
    }

    // Đợi các tiến trình con kết thúc
    while (wait(NULL) > 0);

    printf("Chương trình kết thúc.\n");
    return 0;
}
