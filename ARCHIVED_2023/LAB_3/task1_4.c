// 2021 June 2
// Creator: Tran Trung Tin
// Demo using system call to get ID of this process and its parent.
#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Current process ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid());
    return 0;
}
