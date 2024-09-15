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
    int counter = 0;

    // Tạo pipe nếu chưa có
    mkfifo(pipe_path, 0666);

    // Mở pipe để ghi
    fd = open(pipe_path, O_WRONLY);

    while (1) {
        // Tạo thông điệp với độ dài tối đa MAX_MESSAGE_LENGTH
        snprintf(buffer, MAX_MESSAGE_LENGTH, "Thông điệp %d: Đây là một câu có thể dài tối đa 256 ký tự.", counter++);
        
        // Ghi thông điệp vào pipe
        write(fd, buffer, strlen(buffer) + 1);  // Ghi cả ký tự null kết thúc
        printf("Producer: %s\n", buffer);
        
        // Tạo thời gian giả lập cho việc sản xuất
        sleep(1);
    }

    close(fd);
    return 0;
}
