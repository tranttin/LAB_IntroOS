// 2021 June 2
// Author: 
// Demo using system call fork to create a child process and modify a global varible
#include<sys/types.h>

#include<stdio.h>

#include<unistd.h>

int value = 5;
int main() {
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    /* child process */
    value += 15;
    printf("CHILD: value = %d", value); /* LINE A1 */
    return 0;
  } else if (pid > 0) {
    /* parent process */
    wait(NULL);
    printf("PARENT: value = %d", value); /* LINE A */
    return 0;
  }
}
