// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 10th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include <sys/types.h>

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#define BUFFER SIZE 25
#define READ END 0
#define WRITE END 1
int main(void) {
  char write msg[BUFFER SIZE] = "Greetings";
  char read msg[BUFFER SIZE];
  int fd[2];
  pid t pid;
  /* create the pipe */
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  if (pid > 0) {
    /* parent process */
    /* close the unused end of the pipe */
    close(fd[READ END]);
    /* write to the pipe */
    write(fd[WRITE END], write msg, strlen(write msg) + 1);
    /* close the write end of the pipe */
    close(fd[WRITE END]);
  } else {
    /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE END]);
    /* read from the pipe */
    read(fd[READ END], read msg, BUFFER SIZE);
    printf("read %s", read msg);
    /* close the read end of the pipe */
    close(fd[READ END]);
  }
  return 0;
}
