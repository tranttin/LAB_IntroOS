#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHARS 1000000000

void write_to_file() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Không thể mở file để ghi!\n");
        exit(1);
    }

    char randomChar;
    for (int i = 0; i < NUM_CHARS; i++) {
        randomChar = 'A' + rand() % 26;
        fputc(randomChar, file);
    }

    fclose(file);
    exit(0); // Kết thúc tiến trình con
}

void measure_time() {
    struct timespec start, end;
    double wall_time_used;

    // Bắt đầu đo thời gian thực
    clock_gettime(CLOCK_REALTIME, &start);

    // Chờ tiến trình con ghi file kết thúc
    wait(NULL);

    // Kết thúc đo thời gian thực
    clock_gettime(CLOCK_REALTIME, &end);

    // Tính toán thời gian thực tế
    wall_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nThời gian thực tế chạy chương trình: %f giây\n", wall_time_used);
    exit(0);
}

int main() {
    pid_t writer_pid, timer_pid;

    // Tạo tiến trình con để đo thời gian
    if ((timer_pid = fork()) == 0) {
        measure_time();
    }

    // Tạo tiến trình con để ghi file
    if ((writer_pid = fork()) == 0) {
        write_to_file();
    }

    // Chờ cả hai tiến trình con kết thúc
    wait(NULL);
    wait(NULL);

    return 0;
}
