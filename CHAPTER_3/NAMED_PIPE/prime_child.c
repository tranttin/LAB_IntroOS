#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH1 "/tmp/myfifo1"
#define FIFO_PATH2 "/tmp/myfifo2"

// Hàm kiểm tra số nguyên tố
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int fd_read, fd_write;
    int number, result;

    // Mở đường ống để đọc (nhận số từ tiến trình cha)
    fd_read = open(FIFO_PATH1, O_RDONLY);

    // Mở đường ống để ghi (gửi kết quả lại cho tiến trình cha)
    fd_write = open(FIFO_PATH2, O_WRONLY);

    // Đọc từng số từ tiến trình cha và kiểm tra xem số đó có phải là số nguyên tố
    while (read(fd_read, &number, sizeof(number)) > 0) {
        result = is_prime(number);

        // Gửi kết quả lại cho tiến trình cha qua đường ống FIFO
        write(fd_write, &result, sizeof(result));
    }

    // Đóng đường ống
    close(fd_read);
    close(fd_write);

    return 0;
}
