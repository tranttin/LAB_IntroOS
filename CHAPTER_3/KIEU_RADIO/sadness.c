#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#define SHM_NAME "/shm_radio"
#define SHM_SIZE 256

int main() {
    // Mở bộ nhớ chia sẻ
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(1);
    }

    // Ánh xạ bộ nhớ chia sẻ
    char *shared_memory = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    char last_message[SHM_SIZE] = "";

    while (1) {
        // Nếu thông điệp mới khác thông điệp cũ, in ra
        if (strcmp(last_message, shared_memory) != 0) {
            printf("[Listen]: %s\n", shared_memory);
            strncpy(last_message, shared_memory, SHM_SIZE);
        }

        // Đợi một chút trước khi kiểm tra lại
        usleep(500000);  // 500ms
    }

    // Hủy ánh xạ vùng nhớ chia sẻ
    munmap(shared_memory, SHM_SIZE);

    return 0;
}
