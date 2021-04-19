#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
  const char* file = "./fifoChannel";
  int fd = open(file, O_RDONLY);
  if (fd < 0) return -1; /* no point in continuing */
  unsigned count = 0, total = 0, primes_count = 0;

  while (1) {
    char str[100];
    ssize_t count = read(fd, &str, 100);
    if (0 == count) continue;                  /* end of stream */
    printf("\nProducer: %s", str);
    }


  close(fd);       /* close pipe from read end */
  unlink(file);    /* unlink from the underlying file */
  printf("Received ints: %u, primes: %u\n", total, primes_count);

  return 0;
}
