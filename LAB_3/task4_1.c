// 2021 June 3
// Creator: Tran Trung Tin
// Demo parent give a child an interval to complete or kill him.
#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>

#include <sys/wait.h>

#include <unistd.h>

int main() {

  pid_t pid, wpid;
  int status;
  _Bool flag = 0;
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) {
    /* child process */
    int n;
    printf("\nInput PIN: ");
    scanf("%d", & n);
    flag = 1; //Do not input anything when execute
  } else {
    /* parent process */
    int timer = 5;
    do {

      wpid = waitpid(pid, & status, WNOHANG);
      if (wpid == -1) {
        printf("\nChild exit.");
        break;
        //  exit(EXIT_FAILURE);
      }

      timer--;
      sleep(1);
      if (timer == 0) {
        kill(pid, SIGKILL);
        break;
      }
    } while (1);
  }
  if (flag == 1) printf("\nUser already input PIN.");
  else printf("\nTime out. No PIN input");
  return 0;
}
