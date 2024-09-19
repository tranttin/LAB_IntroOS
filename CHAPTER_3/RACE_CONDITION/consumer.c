#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define BUFFER_SIZE 5
#define MAX_MESSAGE_LENGTH 256
#define RUN_DURATION 10  // Thời gian chạy (giây)

// Cấu trúc cho bộ đệm chia sẻ
typedef struct {
    char buffer[BUFFER_SIZE][MAX_MESSAGE_LENGTH];
    int in;
    int out;
    int count;
} SharedMemoryBuffer;

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(SharedMemoryBuffer), 0666);
    SharedMemoryBuffer *shm_buffer = (SharedMemoryBuffer *) shmat(shmid, (void *)0, 0);

    char message[MAX_MESSAGE_LENGTH];
    int message_count = 0;  // Biến đếm số lượng thông điệp đã nhận

    time_t start_time = time(NULL);  // Lấy thời gian bắt đầu

    // Nhận các gói tin
    while (1) {
        if (shm_buffer->count > 0) {
            // Đọc thông điệp từ buffer
            strcpy(message, shm_buffer->buffer[shm_buffer->out]);
            printf("Consumer received: %s\n", message);

            shm_buffer->out = (shm_buffer->out + 1) % BUFFER_SIZE;
            shm_buffer->count--;

            message_count++;  // Tăng biến đếm khi nhận được thông điệp
        } else {
            // Nếu không có thông điệp, blocking received
        }

        // Kiểm tra nếu đã vượt quá thời gian RUN_DURATION
        if (difftime(time(NULL), start_time) >= RUN_DURATION) {
            break;
        }
    }

    printf("Consumer đã nhận tổng cộng %d thông điệp.\n", message_count);

    // Detach (thực tế có thể không cần nếu không xóa bộ nhớ)
    shmdt(shm_buffer);
    return 0;
}
