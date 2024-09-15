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

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key, sizeof(SharedMemoryBuffer), 0666|IPC_CREAT);
    SharedMemoryBuffer *shm_buffer = (SharedMemoryBuffer*) shmat(shmid, (void*)0, 0);

    char message[MAX_MESSAGE_LENGTH];

    while(1) {
        if (shm_buffer->count > 0) { // Kiểm tra có thông điệp trong buffer
            strcpy(message, shm_buffer->buffer[shm_buffer->out]);
            printf("Consumer received: %s\n", message);

            shm_buffer->out = (shm_buffer->out + 1) % BUFFER_SIZE;
            shm_buffer->count--;
        }

        sleep(1); // Giả lập thời gian tiêu thụ
    }

    shmdt(shm_buffer);
    return 0;
}
