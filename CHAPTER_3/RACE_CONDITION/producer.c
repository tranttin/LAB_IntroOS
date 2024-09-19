#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER_SIZE 5
#define MAX_MESSAGE_LENGTH 256

// Cấu trúc cho bộ đệm chia sẻ
typedef struct {
    char buffer[BUFFER_SIZE][MAX_MESSAGE_LENGTH];
    int in;
    int out;
    int count;
} SharedMemoryBuffer;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_messages>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_messages = atoi(argv[1]);
    if (num_messages <= 0) {
        fprintf(stderr, "Number of messages must be greater than 0\n");
        exit(EXIT_FAILURE);
    }

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(SharedMemoryBuffer), 0666 | IPC_CREAT);
    SharedMemoryBuffer *shm_buffer = (SharedMemoryBuffer *) shmat(shmid, (void *)0, 0);

    // Gửi các gói tin
    for (int i = 0; i < num_messages; i++) {
        while (shm_buffer->count == BUFFER_SIZE); 
            // Đợi nếu buffer đầy
        // Tạo thông điệp và ghi vào buffer
        snprintf(shm_buffer->buffer[shm_buffer->in], MAX_MESSAGE_LENGTH, "Message %d", i);
        shm_buffer->in = (shm_buffer->in + 1) % BUFFER_SIZE;
        shm_buffer->count++;

        printf("Producer sent: Message %d\n", i);
    }

    // Detach and clean up
    shmdt(shm_buffer);
    return 0;
}
