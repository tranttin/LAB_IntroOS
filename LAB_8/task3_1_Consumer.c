// 2021 June 2
// Author: Tran Trung Tin
// Demo Producer send via shared memory
#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <sys/shm.h>

#include <sys/stat.h>

#include <sys/mman.h>

#include <unistd.h>

int main() {
  /* the size (in bytes) of shared memory object */
  const int BUFFER_SIZE = 10;
  int out = 0;
  int receive = 0;
  /* name of the shared memory object */
  const char * name = "OS1";
  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory obect */
  int * ptr;
  /* create the shared memory object */
  fd = shm_open(name, O_RDWR, 0666);
  /* memory map the shared memory object */
  ptr = (int * ) mmap(0, BUFFER_SIZE + 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  while (ptr[BUFFER_SIZE + 1]) {
    printf("\nReceving.... ");
    while (ptr[BUFFER_SIZE] == 0 && ptr[BUFFER_SIZE + 1]); //do nothing
    if (ptr[BUFFER_SIZE + 1] == 0) break;
    receive += ptr[out];
    printf("\nReceive %d with out %d", receive, out);
    out = (out + 1) % BUFFER_SIZE;
    ptr[BUFFER_SIZE]--;
  }
  shm_unlink(name);
  return 0;
}
