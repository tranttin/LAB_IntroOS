#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/student_to_server_fifo"
#define RESPONSE_FIFO "/tmp/server_to_student_fifo"

// Hàm đọc secret_key từ tệp
int get_secret_key(int mssv) {
    FILE *fp = fopen("secret_key.txt", "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    int id, key;
    while (fscanf(fp, "%d %d", &id, &key) != EOF) {
        if (id == mssv) {
            fclose(fp);
            return key;
        }
    }
    fclose(fp);
    return -1; // MSSV không tồn tại
}

// Hàm đọc thời khóa biểu từ tệp
void get_schedule(int mssv, char *schedule) {
    FILE *fp = fopen("data.txt", "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    int id;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d:", &id) == 1) {
            if (id == mssv) {
                strcpy(schedule, strchr(line, ':') + 2); // Bỏ qua dấu ":" và khoảng trắng sau dấu ":"
                fclose(fp);
                return;
            }
        }
    }
    strcpy(schedule, "Không tìm thấy lịch học\n");
    fclose(fp);
}

int main() {
    char buffer[256], mssv_str[10], key_str[10], response[256];
    int mssv, key, provided_key;
    int fd;

    // Tạo đường ống đặt tên nếu chưa tồn tại
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_NAME, 0666) != 0) {
            perror("mkfifo failed");
            exit(EXIT_FAILURE);
        }
    }

    if (access(RESPONSE_FIFO, F_OK) == -1) {
        if (mkfifo(RESPONSE_FIFO, 0666) != 0) {
            perror("mkfifo failed");
            exit(EXIT_FAILURE);
        }
    }

    int query_count = 0;

    while (1) {
        // Mở đường ống nhận dữ liệu từ student
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open fifo failed");
            exit(EXIT_FAILURE);
        }

        // Đọc dữ liệu từ student
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            perror("read failed or no data");
            close(fd);
            continue;
        }
        buffer[bytes_read] = '\0';  // Null-terminate the string
        close(fd);

        sscanf(buffer, "%s %s", mssv_str, key_str);
        mssv = atoi(mssv_str);
        provided_key = atoi(key_str);

        // Thông báo nhận yêu cầu
        printf("Đã nhận yêu cầu từ MSSV %d với khóa %d\n", mssv, provided_key);

        // Kiểm tra khóa bí mật
        key = get_secret_key(mssv);
        if (key == -1) {
            snprintf(response, 256, "MSSV %d không tồn tại", mssv);
        } else if (key != provided_key) {
            snprintf(response, 256, "Khóa bí mật không hợp lệ cho MSSV %d", mssv);
        } else {
            // Lấy thời khóa biểu
            get_schedule(mssv, response);
        }

        // Gửi phản hồi lại cho student
        fd = open(RESPONSE_FIFO, O_WRONLY);
        if (fd == -1) {
            perror("open response fifo failed");
            exit(EXIT_FAILURE);
        }

        ssize_t bytes_written = write(fd, response, strlen(response) + 1);
        if (bytes_written == -1) {
            perror("write failed");
        }
        close(fd);

        // Thông báo xử lý truy vấn
        printf("Đã xử lý truy vấn cho MSSV %d\n", mssv);

        // Cập nhật thống kê số lượng truy vấn
        query_count++;
        printf("Tổng số truy vấn: %d\n", query_count);
    }

    return 0;
}
