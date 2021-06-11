// 2021 June 2
// Author: Tran Trung Tin
// Demo using shared memory.
#include <stdio.h>

#include <unistd.h>

#include <limits.h>

#include <string.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/shm.h>

#include <fcntl.h>

#include <sys/stat.h>

#include <sys/mman.h>

#define SIZE 256

int main(int argc, char * argv[]) {
  int * shm, shm_id, k, pid;
  const char * key = "sharedkey";
  if ((shm_id = shm_open(key, O_CREAT | O_RDWR, 0666)) == -1) {
    perror("Shared memory created.\n");
    return 2;
  }
  /* configure the size of the shared memory object */
  ftruncate(shm_id, SIZE);
  /* memory map the shared memory object */
  shm = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_id, 0);

  pid = fork();
  if (pid == 0) { // child
    shm[0] = atoi(argv[1]);
    shm[1] = atoi(argv[2]);
    sleep(2);
    printf("%d + %d = %d\n", shm[0], shm[1], shm[2]);
    shm_unlink(key);
    return 0;
  } else if (pid > 0) { // parent
    sleep(1);
    shm[2] = shm[1] + shm[0];
    shm_unlink(key);   
    sleep(1);
    return 0;
  } else {
    perror("Fork failed.");
    return 4;
  }
  return 0;
}
