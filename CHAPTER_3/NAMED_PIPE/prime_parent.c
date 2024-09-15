#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH1 "/tmp/myfifo1"
#define FIFO_PATH2 "/tmp/myfifo2"
#define N 100  // Giá trị n mặc định là 100

int main() {
    int fd_write, fd_read;
    int number, result;

    // Tạo đường ống đặt tên (FIFO)
    mkfifo(FIFO_PATH1, 0666);
    mkfifo(FIFO_PATH2, 0666);

    // Mở đường ống để ghi (gửi số đi)
    fd_write = open(FIFO_PATH1, O_WRONLY);

    // Mở đường ống để đọc (nhận kết quả từ con)
    fd_read = open(FIFO_PATH2, O_RDONLY);

    // Gửi từng số từ 2 đến N cho tiến trình con qua đường ống FIFO
    for (int i = 2; i <= N; i++) {
        write(fd_write, &i, sizeof(i));

        // Nhận kết quả kiểm tra từ con
        read(fd_read, &result, sizeof(result));

        if (result) {
            printf("%d là số nguyên tố\n", i);
        } else {
            printf("%d không phải là số nguyên tố\n", i);
        }
    }

    // Đóng đường ống và xóa các file FIFO
    close(fd_write);
    close(fd_read);
    unlink(FIFO_PATH1);
    unlink(FIFO_PATH2);

    return 0;
}
