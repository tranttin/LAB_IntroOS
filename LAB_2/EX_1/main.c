#include <stdio.h>
#include "util.h"

int main() {
    int a = 5, b = 7;
    printf("%d + %d = %d\n", a, b, add(a,b));
    return 0;
}
