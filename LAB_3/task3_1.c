// 2021 June 2
// Creator: Tran Trung Tin
// Demo using system call fork to create a child process which execute command ls by execlp.
#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

int main() {
  pid_t pid;
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) {
    /* child process */
    int;
    printf("\nInput PIN: ");
    scanf("%d", &n);
  } else {
    /* parent process */
    /* parent will wait for the child to complete */
    wait(NULL);
    printf("Child Complete");
  }
  return 0;
}
