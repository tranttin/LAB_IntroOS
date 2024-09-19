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
#define PRIVATE_KEY 2753
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

// Function to decrypt data
int decrypt(int encrypted) {
    return mod_exp(encrypted, PRIVATE_KEY, N);
}

// Function to read secret key from file
int get_secret_key(int mssv) {
    FILE *fp = fopen("secret_key.txt", "r");
    int id, key;
    while (fscanf(fp, "%d %d", &id, &key) != EOF) {
        if (id == mssv) {
            fclose(fp);
            return key;
        }
    }
    fclose(fp);
    return -1; // MSSV not found
}

// Function to read schedule from file
void get_schedule(int mssv, char *schedule) {
    FILE *fp = fopen("data.txt", "r");
    int id;
    while (fscanf(fp, "%d:", &id) != EOF) {
        if (id == mssv) {
            fgets(schedule, 256, fp);
            fclose(fp);
            return;
        }
    }
    strcpy(schedule, "Không tìm thấy thời khóa biểu\n");
    fclose(fp);
}

int main() {
    char buffer[256], mssv_str[10], key_str[10], response[256];
    int mssv, decrypted_key;

    // Create named pipes
    if (access(FIFO_NAME, F_OK) == -1) {
        mkfifo(FIFO_NAME, 0666);
    }

    if (access(RESPONSE_FIFO, F_OK) == -1) {
        mkfifo(RESPONSE_FIFO, 0666);
    }

    int query_count = 0;

    while (1) {
        // Open pipe to read data from student
        int fd = open(FIFO_NAME, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        sscanf(buffer, "%s %s", mssv_str, key_str);
        mssv = atoi(mssv_str);
        int encrypted_key = atoi(key_str);

        // Decrypt the key
        decrypted_key = decrypt(encrypted_key);

        printf("Nhận yêu cầu từ MSSV %d với khóa mã hóa %d (giải mã thành %d)\n", mssv, encrypted_key, decrypted_key);

        // Process query
        int key = get_secret_key(mssv);
        if (key == -1) {
            snprintf(response, 256, "MSSV %d không tồn tại", mssv);
        } else if (key != decrypted_key) {
            snprintf(response, 256, "Khóa không hợp lệ cho MSSV %d", mssv);
        } else {
            // Get schedule
            get_schedule(mssv, response);
        }

        // Send response back to student
        fd = open(RESPONSE_FIFO, O_WRONLY);
        write(fd, response, strlen(response) + 1);
        close(fd);

        query_count++;
        printf("Số truy vấn đã xử lý: %d\n", query_count);
    }

    return 0;
}
