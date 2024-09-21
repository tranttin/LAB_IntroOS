// 2021 June 2
// Creator: Tran Trung Tin
// Demo using system call fork to create a child process which execute command ls by execlp.
#include <sys/types.h>

#include <stdio.h>

#include <sys/wait.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/prctl.h>

int main() {
  pid_t pid[3];
  /* fork a child process */
  pid[0] = fork();
  if (pid[0] < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid[0] == 0) {
       const char * name = "B";
      if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");

pid[2] = fork();
  if (pid[2] < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid[2] == 0) {  const char * name = "D";
      if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()"); sleep(1); }
else{
wait(NULL);
}


  } else {
    /* parent process */
    /* parent will wait for the child to complete */
       const char * name = "A";
      if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");
    pid[1] = fork();
    if (pid[1] < 0) {
      /* error occurred */
      fprintf(stderr, "Fork Failed");
      return 1;
    } else if (pid[1] == 0) {
      /* child process */
      const char * name = "C";
      if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");


    } else {
 
     system("ps --forest");
    }
    for (int i = 0; i < 2; i++) wait(NULL);
    printf("All Child Complete");
  }
  return 0;
}
