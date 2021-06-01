#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <sys/shm.h>

#include <sys/stat.h>

#include <sys/mman.h>

int main() {
  /* the size (in bytes) of shared memory object */
  const int SIZE = 4096;
  /* name of the shared memory object */
  const char * name = "OS";
  /* strings written to shared memory */
  const char * message 0 = "Hello";
  const char * message 1 = "World!";
  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory obect */
  char * ptr;
  /* create the shared memory object */
  fd = shm open(name, O CREAT | O RDWR, 0666);
  /* configure the size of the shared memory object */
  ftruncate(fd, SIZE);
  /* memory map the shared memory object */
  ptr = (char * )
  mmap(0, SIZE, PROT READ | PROT WRITE, MAP SHARED, fd, 0);
  /* write to the shared memory object */
  sprintf(ptr, "%s", message 0);
  ptr += strlen(message 0);
  sprintf(ptr, "%s", message 1);
  ptr += strlen(message 1);
  return 0;
}
