#include <math.h>
#include "supportA.h"  // Bao gồm file header

// Hàm kiểm tra số nguyên tố
int is_prime(int number) {
    if (number < 2) {
        return 0;
    }
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return 0;  // Không phải số nguyên tố
        }
    }
    return 1;  // Là số nguyên tố
}
