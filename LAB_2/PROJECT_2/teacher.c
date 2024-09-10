#include <stdio.h>
#include <stdlib.h>

// Hàm để chạy một lệnh hệ thống và trả về kết quả
int run_command(const char *command) {
    int result = system(command);
    return WEXITSTATUS(result);  // Trả về mã thoát của lệnh
}

// Hàm để chạy chương trình của sinh viên với một test case cụ thể
int run_student_program(const char *executable, int number) {
    char command[256];
    sprintf(command, "./%s %d > output.txt", executable, number);  // Gọi chương trình và lưu kết quả vào output.txt
    system(command);

    FILE *fp = fopen("output.txt", "r");
    if (!fp) {
        return 0;  // Nếu không mở được file, trả về lỗi
    }

    char result[256];
    fgets(result, sizeof(result), fp);  // Đọc kết quả từ file
    fclose(fp);

    // Xử lý kết quả
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
    sprintf(command, "gcc -o %s %s -lm", executable, source_file);  // Biên dịch chương trình
    if (run_command(command) != 0) {
        printf("Loi bien dich %s\n", source_file);
        return 0;
    }

    int score = 0;
    int test_cases[] = {2, 9, 25, 97};
    int total_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < total_tests; i++) {
        score += run_student_program(executable, test_cases[i]);
    }

    return score;
}

int main() {
    printf("Dang chay cac chuong trinh kiem tra...\n");

    // Chạy và tính điểm cho studentA.c
    int scoreA = grade_student_program("studentA.c", "studentA");
    printf("Diem cua studentA: %d / 4\n", scoreA);

    // Chạy và tính điểm cho studentB.c
    int scoreB = grade_student_program("studentB.c", "studentB");
    printf("Diem cua studentB: %d / 4\n", scoreB);

    // Chạy và tính điểm cho studentC.c
    int scoreC = grade_student_program("studentC.c", "studentC");
    printf("Diem cua studentC: %d / 4\n", scoreC);

    return 0;
}
