#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void generate_random_matrix(int n, int m, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %d\n", n, m); // Ghi kích thước ma trận
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            float random_value = (float)rand() / RAND_MAX; // Sinh số thực ngẫu nhiên từ 0 đến 1
            fprintf(file, "%.2f ", random_value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <N> <M> <Filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    const char *filename = argv[3];

    srand(time(NULL)); // Khởi tạo bộ sinh số ngẫu nhiên

    generate_random_matrix(n, m, filename);

    return EXIT_SUCCESS;
}
