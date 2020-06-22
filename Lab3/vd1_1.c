// P1.c
#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Current process ID: %d\n", getpid());
    printf("Parent process ID: %d\n", getppid())
    return 0;
}
