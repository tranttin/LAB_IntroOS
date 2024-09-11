#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define PIN "1234"
#define TIMEOUT 5

// Hàm xử lý khi hết thời gian
void timeout_handler(int signum) {
    printf("\nThời gian nhập mã PIN đã hết.\n");
    exit(1); // Thoát chương trình
}

int main() {
    char pin_input[10];
    
    // Đăng ký hàm xử lý tín hiệu cho SIGALRM
    signal(SIGALRM, timeout_handler);

    // Đặt thời gian chờ 5 giây
    alarm(TIMEOUT);

    printf("Nhập mã PIN: ");
    fgets(pin_input, sizeof(pin_input), stdin);

    // Hủy báo động nếu người dùng nhập trong thời gian cho phép
    alarm(0);

    // Xóa ký tự xuống dòng nếu có
    pin_input[strcspn(pin_input, "\n")] = 0;

    // Kiểm tra mã PIN
    if (strcmp(pin_input, PIN) == 0) {
        printf("Mã PIN chính xác.\n");
    } else {
        printf("Mã PIN sai.\n");
    }

    return 0;
}
