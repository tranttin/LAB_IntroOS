#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

void error_exit(const char *message) {
    fprintf(stderr, "%s: Error %lu\n", message, GetLastError());
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    HANDLE hSrcFile, hDestFile;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead, bytesWritten;

    // Check if correct number of arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file
    hSrcFile = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSrcFile == INVALID_HANDLE_VALUE) {
        error_exit("Failed to open source file");
    }

    // Open or create the destination file
    hDestFile = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDestFile == INVALID_HANDLE_VALUE) {
        CloseHandle(hSrcFile);
        error_exit("Failed to open or create destination file");
    }

    // Copy data from source file to destination file
    while (ReadFile(hSrcFile, buffer, BUFFER_SIZE, &bytesRead, NULL) && bytesRead > 0) {
        if (!WriteFile(hDestFile, buffer, bytesRead, &bytesWritten, NULL)) {
            CloseHandle(hSrcFile);
            CloseHandle(hDestFile);
            error_exit("Failed to write to destination file");
        }
        if (bytesWritten != bytesRead) {
            CloseHandle(hSrcFile);
            CloseHandle(hDestFile);
            error_exit("Mismatch in bytes written");
        }
    }

    if (GetLastError() != ERROR_HANDLE_EOF) {
        CloseHandle(hSrcFile);
        CloseHandle(hDestFile);
        error_exit("Failed to read from source file");
    }

    // Close both files
    if (!CloseHandle(hSrcFile)) {
        error_exit("Failed to close source file");
    }
    if (!CloseHandle(hDestFile)) {
        error_exit("Failed to close destination file");
    }

    // Final message
    printf("File copied successfully.\n");

    return EXIT_SUCCESS;
}