#include <stdio.h>

int main(int argc, char *argv[]) {
    // In ra tên chương trình
    printf("Tên chương trình: %s\n", argv[0]);

    // Kiểm tra xem có tham số nào được truyền vào không
    if (argc == 1) {
        printf("Không có tham số nào được truyền.\n");
    } else {
        // In ra các tham số được truyền
        for (int i = 1; i < argc; i++) {
            printf("Tham số %d: %s\n", i, argv[i]);
        }
    }

    return 0;
}
