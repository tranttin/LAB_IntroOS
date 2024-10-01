#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    float **matrix1;
    float **matrix2;
    float **result;
    int rows1;
    int cols1;
    int cols2;
    int start_row;
    int end_row;
} thread_data;

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

void* multiply_matrices(void* arg) {
    thread_data* data = (thread_data*)arg;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->cols2; j++) {
            for (int k = 0; k < data->cols1; k++) {
                data->result[i][j] += data->matrix1[i][k] * data->matrix2[k][j];
            }
        }
    }
    return NULL;
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
    if (argc != 5) {
        fprintf(stderr, "Cách sử dụng: %s <filename1> <filename2> <filename3> <number_of_threads>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float **matrix1, **matrix2, **result;
    int rows1, cols1, rows2, cols2, result_rows, result_cols;
    int num_threads = atoi(argv[4]);

    // Đọc ma trận từ tệp
    read_matrix(argv[1], &matrix1, &rows1, &cols1);
    read_matrix(argv[2], &matrix2, &rows2, &cols2);

    if (cols1 != rows2) {
        fprintf(stderr, "Lỗi: Kích thước ma trận không tương thích để nhân.\n");
        return EXIT_FAILURE;
    }

    result_rows = rows1;
    result_cols = cols2;
    result = (float **)malloc(result_rows * sizeof(float *));
    for (int i = 0; i < result_rows; i++) {
        result[i] = (float *)calloc(result_cols, sizeof(float));
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    thread_data *threadData = malloc(num_threads * sizeof(thread_data));

    int rows_per_thread = result_rows / num_threads;
    int remainder = result_rows % num_threads;

    // Tính thời gian bắt đầu
    clock_t start_time = clock();

    for (int i = 0; i < num_threads; i++) {
        threadData[i].matrix1 = matrix1;
        threadData[i].matrix2 = matrix2;
        threadData[i].result = result;
        threadData[i].rows1 = rows1;
        threadData[i].cols1 = cols1;
        threadData[i].cols2 = cols2;
        threadData[i].start_row = i * rows_per_thread;
        threadData[i].end_row = (i == num_threads - 1) ? (i + 1) * rows_per_thread + remainder : (i + 1) * rows_per_thread;

        pthread_create(&threads[i], NULL, multiply_matrices, (void*)&threadData[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Tính thời gian kết thúc
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Ghi kết quả vào tệp
    write_matrix(argv[3], result, result_rows, result_cols);

    // Giải phóng bộ nhớ
    for (int i = 0; i < rows1; i++) free(matrix1[i]);
    free(matrix1);
    for (int i = 0; i < rows2; i++) free(matrix2[i]);
    free(matrix2);
    for (int i = 0; i < result_rows; i++) free(result[i]);
    free(result);
    free(threads);
    free(threadData);

    // Hiển thị thời gian thực hiện
    int minutes = (int)(time_taken / 60);
    double seconds = time_taken - (minutes * 60);
    
    if (minutes > 0) {
        printf("Thời gian thực hiện phép nhân ma trận: %d phút %.6f giây\n", minutes, seconds);
    } else {
        printf("Thời gian thực hiện phép nhân ma trận: %.6f giây\n", seconds);
    }

    // Hiển thị dung lượng bộ nhớ
    size_t memory_usage = 0;
    memory_usage += rows1 * cols1 * sizeof(float); // Dung lượng ma trận 1
    memory_usage += rows2 * cols2 * sizeof(float); // Dung lượng ma trận 2
    memory_usage += result_rows * result_cols * sizeof(float); // Dung lượng ma trận kết quả
    print_memory_usage(memory_usage);

    return EXIT_SUCCESS;
}
