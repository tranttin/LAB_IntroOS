// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 10th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <fcntl.h>

#include <sys/shm.h>

#include <sys/stat.h>

#include <sys/mman.h>

int main() {
  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char * name = "OS";
  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory obect */
  char * ptr;
  /* open the shared memory object */
  fd = shm_open(name, O_RDONLY, 0666);
  /* memory map the shared memory object */
  ptr = (char * )
  mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  /* read from the shared memory object */
  printf("%s", (char * ) ptr);
  /* remove the shared memory object */
  shm_unlink(name);
  return 0;
}
