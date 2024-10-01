#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/student_to_server_fifo"
#define RESPONSE_FIFO "/tmp/server_to_student_fifo"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <mssv> <secret_key>\n", argv[0]);
        return 1;
    }

    // Lấy MSSV và secret_key từ dòng lệnh
    char *mssv = argv[1];
    char *secret_key = argv[2];
    char query[256];

    // Gửi truy vấn đến server qua đường ống đặt tên
    snprintf(query, sizeof(query), "%s %s", mssv, secret_key);
    int fd = open(FIFO_NAME, O_WRONLY);
    write(fd, query, strlen(query) + 1);
    close(fd);

    // Nhận phản hồi từ server
    fd = open(RESPONSE_FIFO, O_RDONLY);
    char response[256];
    read(fd, response, sizeof(response));
    printf("Server response: %s\n", response);
    close(fd);

    return 0;
}
