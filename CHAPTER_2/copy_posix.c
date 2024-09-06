#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;

    // Check if correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        error_exit("Failed to open source file");
    }

    // Open the destination file (create or overwrite if necessary)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        close(src_fd);
        error_exit("Failed to open destination file");
    }

    // Copy from source file to destination file
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            close(src_fd);
            close(dest_fd);
            error_exit("Failed to write to destination file");
        }
    }

    if (bytes_read == -1) {
        close(src_fd);
        close(dest_fd);
        error_exit("Failed to read from source file");
    }

    // Close both files
    if (close(src_fd) == -1) {
        error_exit("Failed to close source file");
    }
    if (close(dest_fd) == -1) {
        error_exit("Failed to close destination file");
    }

    // Final message
    printf("File copied successfully.\n");

    return EXIT_SUCCESS;
}
