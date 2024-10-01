#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// Định nghĩa cấu trúc client_request
typedef struct {
    int mssv;
    int provided_key;
} client_request;

#define FIFO_NAME "request_fifo"
#define RESPONSE_FIFO "response_fifo"

// Giả sử có hàm này trả về khóa bí mật
int get_secret_key(int mssv) {
    // Giả lập việc lấy khóa bí mật từ cơ sở dữ liệu
    return 1234; // Ví dụ: khóa bí mật là 1234
}

// Giả sử có hàm này trả về thời khóa biểu dựa trên MSSV
void get_schedule(int mssv, char *response) {
    snprintf(response, 256, "Thời khóa biểu của MSSV %d: Lịch học tuần này", mssv);
}

void *handle_client(void *arg) {
    client_request *request = (client_request *)arg;
    char response[256];

    sleep(1); // Thêm độ trễ 1 giây để quan sát

    int key = get_secret_key(request->mssv);
    if (key == -1) {
        snprintf(response, sizeof(response), "MSSV %d không tồn tại", request->mssv);
    } else if (key != request->provided_key) {
        snprintf(response, sizeof(response), "Khóa bí mật không hợp lệ cho MSSV %d", request->mssv);
    } else {
        get_schedule(request->mssv, response);
    }

    int fd = open(RESPONSE_FIFO, O_WRONLY);
    if (fd == -1) {
        perror("open response fifo failed");
        free(request);
        return NULL;
    }

    write(fd, response, strlen(response) + 1);
    close(fd);

    free(request);
    return NULL;
}

int main() {
    int fd;
    char buffer[256];
    int mssv, provided_key;

    // Tạo FIFO yêu cầu
    if (mkfifo(FIFO_NAME, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Tạo FIFO phản hồi
    if (mkfifo(RESPONSE_FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    while (1) {
        fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK); // Chạy chế độ non-blocking
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read > 0) {
            sscanf(buffer, "%d %d", &mssv, &provided_key);
            printf("Đã nhận yêu cầu từ MSSV %d với khóa %d\n", mssv, provided_key);

            client_request *request = malloc(sizeof(client_request));
            request->mssv = mssv;
            request->provided_key = provided_key;

            pthread_t thread_id;
            pthread_create(&thread_id, NULL, handle_client, request);
            pthread_detach(thread_id); // Để tránh leak bộ nhớ
        }

        close(fd);
        sleep(0); // Thêm độ trễ để tránh CPU sử dụng quá nhiều
    }

    return 0;
}
