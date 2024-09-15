#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 5  // Số lượng thông điệp tối đa trong buffer
#define MAX_MESSAGE_LENGTH 256  // Độ dài tối đa của một thông điệp

int main() {
    int fd;
    char *pipe_path = "/tmp/my_pipe";
    char buffer[MAX_MESSAGE_LENGTH];
    int message_count = 0;  // Đếm số lượng thông điệp đã nhận

    // Mở pipe để đọc
    fd = open(pipe_path, O_RDONLY);

    while (1) {
        // Đọc thông điệp từ pipe
        int bytes_read = read(fd, buffer, MAX_MESSAGE_LENGTH);
        
        // Nếu có dữ liệu thì in ra
        if (bytes_read > 0) {
            printf("Consumer received (%d): %s\n", ++message_count, buffer);
        }

        // Giả lập thời gian tiêu thụ
        sleep(1);
    }

    close(fd);
    return 0;
}
