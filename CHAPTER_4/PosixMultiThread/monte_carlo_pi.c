#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

long inside_circle = 0; // Biến toàn cục để đếm số điểm trong hình tròn
pthread_mutex_t mutex;  // Khóa để bảo vệ biến inside_circle

void *monte_carlo(void *arg) {
    long n = (long)arg;
    long count = 0;

    unsigned int seed = time(NULL) ^ pthread_self(); // Tạo seed ngẫu nhiên

    for (long i = 0; i < n; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX; // Sinh điểm ngẫu nhiên
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            count++; // Điểm nằm trong hình tròn
        }
    }

    // Cập nhật biến toàn cục với khóa
    pthread_mutex_lock(&mutex);
    inside_circle += count;
    pthread_mutex_unlock(&mutex);

    // In ra số điểm trong hình tròn của thread này
    printf("Số điểm trong hình tròn của luồng: %ld\n", count);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Cách sử dụng: %s <N> <M>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long N = strtol(argv[1], NULL, 10); // Số điểm ngẫu nhiên
    long M = strtol(argv[2], NULL, 10); // Số luồng

    pthread_t threads[M];
    pthread_mutex_init(&mutex, NULL);

    // Bắt đầu đo thời gian thực
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Khởi động M luồng
    for (long i = 0; i < M; i++) {
        pthread_create(&threads[i], NULL, monte_carlo, (void *)(N / M));
    }

    // Chờ tất cả các luồng hoàn thành
    for (long i = 0; i < M; i++) {
        pthread_join(threads[i], NULL);
    }

    // Kết thúc đo thời gian thực
    gettimeofday(&end, NULL);

    // Tính giá trị của PI
    double pi = (double)(inside_circle) / (N) * 4.0;

    printf("Giá trị ước lượng của PI: %lf\n", pi);
    
    // Tính và in ra thời gian thực
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Thời gian thực: %lf giây\n", time_spent);

    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}
