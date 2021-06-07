#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/ff.1"
#define FIFO2 "/tmp/ff.2"
#define PM 0666
extern int errno;
#define PIPE_BUF 4096

int main(int argc, char* argv[])
{
   char s1[PIPE_BUF], s2[PIPE_BUF], buf[PIPE_BUF];
int childpid, readfd, writefd;
   if((mknod(FIFO2, S_IFIFO | PM, 0)<0)&&(errno!=EEXIST)){
      printf("Fail to create FIFO 2. Aborted.\n");
      return -1;
   }
      if((readfd=open(FIFO1, 0))<0)
         perror("Child cannot open readFIFO.\n");
      if((writefd=open(FIFO2, 1))<0)
         perror("Child cannot open writeFIFO.\n");
  do{
      read(readfd, s2, PIPE_BUF);
      printf("Parent said: %s", s2);
      printf("(me): ");
      fgets(s1, PIPE_BUF, stdin);
      if(strcmp(s1, "byebye\n") == 0) break;
      write(writefd, s1, strlen(s1));
 } while(1);
    close(readfd);
    close(writefd);
    return 1;
 }
