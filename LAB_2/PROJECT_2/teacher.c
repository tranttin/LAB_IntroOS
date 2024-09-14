#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 4

// Danh sách các sinh viên, tương ứng với tên file source của họ
const char* students[] = {"studentA", "studentB", "studentC", "studentD", "studentE"};
int num_students = sizeof(students) / sizeof(students[0]);

// Test cases
int test_cases[NUM_TESTS] = {2, 9, 25, 97};

// Hàm chạy lệnh hệ thống và trả về kết quả
int run_command(const char *command) {
    int result = system(command);
    return WEXITSTATUS(result);  // Trả về mã thoát của lệnh
}

// Hàm chạy chương trình của sinh viên với một test case cụ thể
int run_student_program(const char *executable, int number) {
    char command[256];
    sprintf(command, "./%s %d > output.txt", executable, number);  // Gọi chương trình và lưu kết quả vào output.txt
    system(command);

    FILE *fp = fopen("output.txt", "r");
    if (!fp) {
        return 0;  // Không mở được file, trả về lỗi
    }

    char result[256];
    fgets(result, sizeof(result), fp);  // Đọc kết quả từ file
    fclose(fp);

    // Kiểm tra kết quả
    if (number == 2 || number == 11 || number == 97) {  // Những số nguyên tố
        if (strstr(result, "la so nguyen to") != NULL) {
            return 1;  // Đúng
        }
    } else {  // Những số không phải nguyên tố
        if (strstr(result, "khong phai la so nguyen to") != NULL) {
            return 1;  // Đúng
        }
    }
    return 0;  // Sai
}

// Hàm tính điểm cho chương trình của sinh viên
int grade_student_program(const char *source_file, const char *executable) {
    char command[256];
    sprintf(command, "gcc -o %s %s.c -lm", executable, source_file);  // Biên dịch chương trình
    if (run_command(command) != 0) {
        printf("Loi bien dich %s.c\n", source_file);
        return 0;
    }

    int score = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        score += run_student_program(executable, test_cases[i]);
    }

    return score;
}

int main() {
    printf("Dang chay cac chuong trinh kiem tra...\n");

    for (int i = 0; i < num_students; i++) {
        printf("\nKiem tra chuong trinh cua sinh vien: %s\n", students[i]);
        int score = grade_student_program(students[i], students[i]);
        printf("Diem cua %s: %d / %d\n", students[i], score, NUM_TESTS);
    }

    return 0;
}
