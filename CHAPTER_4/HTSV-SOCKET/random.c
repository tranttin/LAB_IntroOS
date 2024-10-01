#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_STUDENTS 100
#define MIN_COURSES 3
#define MAX_COURSES 5
#define MAX_PERIODS 20 // 5 ngày x 4 ca

const char *days_of_week[] = {
    "Thứ Hai", "Thứ Ba", "Thứ Tư", "Thứ Năm", "Thứ Sáu"
};

// Hàm tạo lịch học ngẫu nhiên
void generate_schedule(int student_id) {
    FILE *fp = fopen("data.txt", "a");
    FILE *key_fp = fopen("secret_key.txt", "a");
    if (fp == NULL || key_fp == NULL) {
        perror("Lỗi mở tệp");
        exit(EXIT_FAILURE);
    }

    int num_courses = MIN_COURSES + rand() % (MAX_COURSES - MIN_COURSES + 1);
    int period_assigned[MAX_PERIODS] = {0}; // Mảng theo dõi các ca đã được phân

    fprintf(fp, "%d:", student_id);
    for (int i = 0; i < num_courses; i++) {
        int period;
        do {
            period = rand() % MAX_PERIODS; // Chọn một ca học ngẫu nhiên
        } while (period_assigned[period] != 0); // Đảm bảo ca học chưa được phân

        period_assigned[period] = 1; // Đánh dấu ca học đã được phân
        int day = period / 4;
        int slot = period % 4;

        fprintf(fp, " %s Ca %d", days_of_week[day], slot + 1);
    }
    fprintf(fp, "\n");

    // Tạo khóa bí mật ngẫu nhiên
    int secret_key = 1000 + rand() % 9000;
    fprintf(key_fp, "%d %d\n", student_id, secret_key);

    fclose(fp);
    fclose(key_fp);
}

int main() {
    srand(time(NULL));

    // Xóa nội dung cũ của file trước khi ghi mới
    FILE *fp = fopen("data.txt", "w");
    fclose(fp);

    fp = fopen("secret_key.txt", "w");
    fclose(fp);

    for (int i = 5001; i <= 5100; i++) {
        generate_schedule(i);
    }

    return 0;
}
