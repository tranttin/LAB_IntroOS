#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

#define FIFO_NAME "/tmp/student_to_server_fifo"
#define RESPONSE_FIFO "/tmp/server_to_student_fifo"

// RSA parameters
#define PUBLIC_KEY 17
#define N 3233

// Function to perform modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to encrypt data
int encrypt(int data) {
    return mod_exp(data, PUBLIC_KEY, N);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <MSSV> <key>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *mssv = argv[1];
    int key = atoi(argv[2]);

    // Encrypt the key
    int encrypted_key = encrypt(key);

    // Create named pipes if not exists
    if (access(FIFO_NAME, F_OK) == -1) {
        mkfifo(FIFO_NAME, 0666);
    }

    if (access(RESPONSE_FIFO, F_OK) == -1) {
        mkfifo(RESPONSE_FIFO, 0666);
    }

    // Open pipe to send data to server
    int fd = open(FIFO_NAME, O_WRONLY);
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s %d", mssv, encrypted_key);
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    printf("Đã gửi yêu cầu đến server:\n");
    printf("MSSV: %s\n", mssv);
    printf("Khóa gốc: %d\n", key);
    printf("Khóa mã hóa: %d\n", encrypted_key);

    // Open pipe to receive response from server
    fd = open(RESPONSE_FIFO, O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    close(fd);

    printf("Phản hồi từ server: %s\n", buffer);

    return 0;
}
