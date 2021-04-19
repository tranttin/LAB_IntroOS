#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxLoops         12000   /* outer loop */
#define ChunkSize           100   /* how many written at a time */
#define IntsPerChunk         1   /* for 4-byte ints per chunk */
#define MaxZs              250   /* max microseconds to sleep */

int main() {
  char str[10];
  const char* pipeName = "./fifoChannel";
  mkfifo(pipeName, 0666);                      /* read/write for user/group/others */
  int fd = open(pipeName, O_CREAT | O_WRONLY); /* open as write-only */
  if (fd < 0) return -1;                       /* can't go on */

  int i;
  while(1) {          /* write MaxWrites times */
      printf ("\nProduer: ");
      scanf(STDIN, "%s", str);
      if(strcmp(str, "END") break;
      write(fd, str, sizeof(str));
    }
    usleep((rand() % MaxZs) + 1);           /* pause a bit for realism */
  }

  close(fd);           /* close pipe: generates an end-of-stream marker */
  unlink(pipeName);    /* unlink from the implementing file */

  return 0;
}
