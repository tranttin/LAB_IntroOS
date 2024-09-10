#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Hàm kiểm tra số nguyên tố, có lỗi cố ý
int is_prime(int number) {
    if (number < 2) {
        return 0;  // Không phải số nguyên tố
    }
    for (int i = 2; i < sqrt(number); i++) {  // Sai ở đây: cần <= sqrt(number)
        if (number % i == 0) {
            return 0;  // Không phải số nguyên tố
        }
    }
    return 1;  // Là số nguyên tố
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <so_can_kiem_tra>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);

    // Kiểm tra và in kết quả
    if (is_prime(num)) {
        printf("%d la so nguyen to\n", num);
    } else {
        printf("%d khong phai la so nguyen to\n", num);
    }

    return 0;
}
