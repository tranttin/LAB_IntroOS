#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CHARS 1000000000

int main() {
    FILE *file;
    char randomChar;
    struct timespec start, end;
    double wall_time_used;

    // Bắt đầu đo thời gian thực (wall clock)
    clock_gettime(CLOCK_REALTIME, &start);

    // Mở file để ghi
    file = fopen("writer_data.txt", "w");
    if (file == NULL) {
        printf("Không thể mở file để ghi!\n");
        return 1;
    }

    // Sinh 1,000,000 ký tự ngẫu nhiên
    for (int i = 0; i < NUM_CHARS; i++) {
        randomChar = 'A' + rand() % 26;
       // putchar(randomChar);
        fputc(randomChar, file);
    }

    // Đóng file sau khi ghi xong
    fclose(file);
    // Kết thúc đo thời gian thực (wall clock)
    clock_gettime(CLOCK_REALTIME, &end);

    // Tính toán thời gian chạy (tính bằng giây)
    wall_time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // In thời gian thực tế chạy chương trình
    printf("\nThời gian thực tế chạy chương trình: %f giây\n", wall_time_used);

    return 0;
}
