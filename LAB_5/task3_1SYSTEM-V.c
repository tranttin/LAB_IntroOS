// 2021 June 2
// Author: Tran Trung Tin
// Demo using shared memory.
#include <stdio.h>

#include <unistd.h>

#include <limits.h>

#include <string.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#define SIZE 256

int main(int argc, char * argv[]) {
  int * shm, shmid, k, pid;
  key_t key;
  if ((key = ftok(".", 'a')) == -1) {
    perror("Key created.\n");
    return 1;
  }
  if ((shmid = shmget(key, SIZE, IPC_CREAT | 0666)) == -1) {
    perror("Shared memory created.\n");
    return 2;
  }
  shm = (int * ) shmat(shmid, 0, 0);
  pid = fork();
  if (pid == 0) { // child
    shm[0] = atoi(argv[1]);
    shm[1] = atoi(argv[2]);
    sleep(1);
    printf("%d + %d = %d\n", shm[0], shm[1], shm[2]);
    shmdt((void * ) shm);
    shmctl(shmid, IPC_RMID, (struct shmid_ds * ) 0);
    return 0;
  } else if (pid > 0) { // parent
    sleep(1);
    shm[2] = shm[1] + shm[0];
    shmdt((void * ) shm);
    sleep(1);
    return 0;
  } else {
    perror("Fork failed.");
    return 4;
  }
  return 0;
}
