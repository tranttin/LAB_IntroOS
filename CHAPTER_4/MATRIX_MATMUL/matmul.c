#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void read_matrix(const char *filename, float ***matrix, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Lỗi khi mở tệp");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", rows, cols);
    *matrix = (float **)malloc(*rows * sizeof(float *));
    for (int i = 0; i < *rows; i++) {
        (*matrix)[i] = (float *)malloc(*cols * sizeof(float));
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%f", &(*matrix)[i][j]);
        }
    }

    fclose(file);
}

void write_matrix(const char *filename, float **matrix, int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Lỗi khi mở tệp");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%.2f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void multiply_matrices(float **matrix1, int rows1, int cols1,
                       float **matrix2, int rows2, int cols2,
                       float ***result, int *result_rows, int *result_cols) {
    if (cols1 != rows2) {
        fprintf(stderr, "Lỗi: Kích thước ma trận không tương thích để nhân.\n");
        exit(EXIT_FAILURE);
    }

    *result_rows = rows1;
    *result_cols = cols2;
    *result = (float **)malloc(*result_rows * sizeof(float *));
    for (int i = 0; i < *result_rows; i++) {
        (*result)[i] = (float *)calloc(*result_cols, sizeof(float));
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                (*result)[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void print_memory_usage(size_t memory_usage) {
    if (memory_usage >= 1024 * 1024) {
        printf("Dung lượng bộ nhớ đã sử dụng: %.2f MB\n", memory_usage / (1024.0 * 1024.0));
    } else if (memory_usage >= 1024) {
        printf("Dung lượng bộ nhớ đã sử dụng: %.2f KB\n", memory_usage / 1024.0);
    } else {
        printf("Dung lượng bộ nhớ đã sử dụng: %zu bytes\n", memory_usage);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Cách sử dụng: %s <filename1> <filename2> <filename3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float **matrix1, **matrix2, **result;
    int rows1, cols1, rows2, cols2, result_rows, result_cols;

    // Đọc ma trận từ tệp
    read_matrix(argv[1], &matrix1, &rows1, &cols1);
    read_matrix(argv[2], &matrix2, &rows2, &cols2);

    // Tính thời gian bắt đầu
    clock_t start_time = clock();

    // Nhân ma trận
    multiply_matrices(matrix1, rows1, cols1, matrix2, rows2, cols2, &result, &result_rows, &result_cols);

    // Tính thời gian kết thúc
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Tính dung lượng bộ nhớ
    size_t memory_usage = 0;
    memory_usage += rows1 * cols1 * sizeof(float); // Dung lượng ma trận 1
    memory_usage += rows2 * cols2 * sizeof(float); // Dung lượng ma trận 2
    memory_usage += result_rows * result_cols * sizeof(float); // Dung lượng ma trận kết quả

    // Ghi kết quả vào tệp
    write_matrix(argv[3], result, result_rows, result_cols);

    // Giải phóng bộ nhớ
    for (int i = 0; i < rows1; i++) free(matrix1[i]);
    free(matrix1);
    for (int i = 0; i < rows2; i++) free(matrix2[i]);
    free(matrix2);
    for (int i = 0; i < result_rows; i++) free(result[i]);
    free(result);

    // Hiển thị thời gian thực hiện
    int minutes = (int)(time_taken / 60);
    double seconds = time_taken - (minutes * 60);
    
    if (minutes > 0) {
        printf("Thời gian thực hiện phép nhân ma trận: %d phút %.6f giây\n", minutes, seconds);
    } else {
        printf("Thời gian thực hiện phép nhân ma trận: %.6f giây\n", seconds);
    }

    // Hiển thị dung lượng bộ nhớ
    print_memory_usage(memory_usage);

    return EXIT_SUCCESS;
}
