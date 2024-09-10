#include <stdio.h>
#include "supportA.h"  // Bao gồm hàm kiểm tra số nguyên tố
#include "supportB.h"  // Bao gồm hàm tính diện tích hình tròn

#define N 100  // Đặt hằng số N = 100

int main() {
    printf("Cac so nguyen to tu 2 den %d la:\n", N);

    for (int i = 2; i <= N; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    
    printf("\n");

    // Gọi hàm tính diện tích hình tròn với bán kính r = 5
    double radius = 5.0;
    printf("Dien tich hinh tron co ban kinh %.2f la: %.2f\n", radius, circle_area(radius));

    return 0;
}
