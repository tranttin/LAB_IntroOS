#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define PORT 8080
#define MAX_QUEUE 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct {
    int socket;
} request_t;

request_t request_queue[MAX_QUEUE];
int queue_start = 0;
int queue_end = 0;
int request_count = 0; // Số yêu cầu đang chờ

// Hàm kiểm tra thông tin đăng nhập
int check_credentials(const char* mssv, const char* password) {
    FILE* file = fopen("secret_key.txt", "r");
    if (!file) {
        perror("Không thể mở file secret_key.txt");
        return 0;
    }
    char file_mssv[10], file_password[10];
    while (fscanf(file, "%s %s", file_mssv, file_password) != EOF) {
        if (strcmp(mssv, file_mssv) == 0 && strcmp(password, file_password) == 0) {
            fclose(file);
            return 1; // Đúng
        }
    }
    fclose(file);
    return 0; // Sai
}

// Hàm tìm thời khóa biểu (TKB) theo MSSV
void get_schedule(const char* mssv, char* schedule) {
    sleep(1); // Chậm 1 giây cho mỗi truy vấn
    FILE* file = fopen("data.txt", "r");
    if (!file) {
        perror("Không thể mở file data.txt");
        strcpy(schedule, "Không tìm thấy TKB.");
        return;
    }
    char line[BUFFER_SIZE];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, mssv, strlen(mssv)) == 0) {
            strcpy(schedule, strchr(line, ':') + 2); // Lấy phần sau dấu ":"
            fclose(file);
            return;
        }
    }
    fclose(file);
    strcpy(schedule, "Không tìm thấy TKB.");
}

// Hàm xử lý từng yêu cầu từ student
void* handle_request(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Chờ cho đến khi có yêu cầu trong hàng đợi
        while (request_count == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Lấy yêu cầu từ hàng đợi
        request_t req = request_queue[queue_start];
        queue_start = (queue_start + 1) % MAX_QUEUE;
        request_count--;

        pthread_mutex_unlock(&mutex);

        char buffer[BUFFER_SIZE] = {0};
        read(req.socket, buffer, BUFFER_SIZE);

        // Tách MSSV và mật khẩu từ dữ liệu nhận được
        char mssv[10], password[10];
        sscanf(buffer, "%s %s", mssv, password);

        // Kiểm tra thông tin đăng nhập
        char schedule[BUFFER_SIZE];
        if (check_credentials(mssv, password)) {
            get_schedule(mssv, schedule);
        } else {
            strcpy(schedule, "Sai MSSV hoặc mật khẩu.\n");
        }

        send(req.socket, schedule, strlen(schedule), 0);
        close(req.socket);
        printf("Đã phục vụ yêu cầu cho MSSV: %s\n", mssv);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <max_threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int max_threads = atoi(argv[1]);
    if (max_threads <= 0) {
        fprintf(stderr, "Số lượng thread tối đa phải lớn hơn 0.\n");
        exit(EXIT_FAILURE);
    }

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t threads[max_threads];

    // Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Thiết lập địa chỉ server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Gán socket với địa chỉ
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Lắng nghe kết nối
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server đang lắng nghe tại cổng %d...\n", PORT);

    // Tạo các thread để xử lý yêu cầu
    for (int i = 0; i < max_threads; i++) {
        pthread_create(&threads[i], NULL, handle_request, NULL);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_lock(&mutex);
        if (request_count >= MAX_QUEUE) {
            printf("Hàng đợi đã đầy, từ chối kết nối mới.\n");
            close(new_socket);
        } else {
            // Thêm yêu cầu vào hàng đợi
            request_queue[queue_end].socket = new_socket; // Sửa lại chỉ số thêm yêu cầu
            queue_end = (queue_end + 1) % MAX_QUEUE;
            request_count++;
            pthread_cond_signal(&cond); // Thông báo cho thread đang chờ
            printf("Yêu cầu số %d đã được thêm vào hàng đợi.\n", request_count);
        }
        pthread_mutex_unlock(&mutex);
    }

    // Đợi tất cả các thread hoàn thành
    for (int i = 0; i < max_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
