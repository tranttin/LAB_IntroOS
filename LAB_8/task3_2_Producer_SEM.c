// 2021 June 2
// Author: Tran Trung Tin
// Demo Producer send via shared memory
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <sys/shm.h>

#include <sys/stat.h>

#include <sys/mman.h>

#include <unistd.h>

#include <semaphore.h>

#define SEM_MUTEX_NAME "/sem-mutex"

int main(int argc, char ** argv) {

  sem_t * mutex_sem; /*      synch semaphore         */

  unsigned int value = 1; /*      semaphore value         */

  mutex_sem = sem_open(SEM_MUTEX_NAME, O_CREAT, 0660, 1);

  /* the size (in bytes) of shared memory object */
  const int BUFFER_SIZE = 10;
  int in = 0;
  /* name of the shared memory object */
  const char * name = "OS1";
  /* shared memory file descriptor */
  int fd;
  /* pointer to shared memory obect */
  int * ptr;
  /* create the shared memory object */
  fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  /* configure the size of the shared memory object */
  ftruncate(fd, BUFFER_SIZE + 2);
  /* memory map the shared memory object */
  ptr = (int * ) mmap(0, BUFFER_SIZE + 2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ptr[BUFFER_SIZE] = 0; //count
  ptr[BUFFER_SIZE + 1] = 1; //sending
  /* write to the shared memory object */
  for (int i = 0; i < atoi(argv[1]); i++) {
    while (ptr[BUFFER_SIZE] == BUFFER_SIZE); //DONOTHING
    ptr[ in ] = 1;
    printf("\nSend item %d with out %d", i + 1, in ); in = ( in +1) % BUFFER_SIZE;
    sem_wait(mutex_sem);
    ptr[BUFFER_SIZE]++;
    sem_post(mutex_sem);
  }
  sleep(1);
  ptr[BUFFER_SIZE + 1] = 0; //finish
  return 0;
}
