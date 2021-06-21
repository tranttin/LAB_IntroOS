// 2021 June 12
// Author: Tran Trung Tin
// Demo using memory barrier to make a point.
#define _GNU_SOURCE

#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include <sys/time.h>

#include <unistd.h> // for sleep()

#include <sys/syscall.h>  //for gettid

pthread_barrier_t barrier;
void * runner(void * param); /* threads call this function */
void * CGV(void * param); /* threads call this function */

int main(int argc, char * argv[]) {
  pthread_barrier_init( & barrier, NULL, 4);
  pthread_t tid[4]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  for (int i = 0; i < 3; i++)
    pthread_create( & tid[i], & attr, runner, argv[i + 1]);
  pthread_create( & tid[3], & attr, CGV, NULL);
  /* wait for the thread to exit */
  for (int i = 0; i < 4; i++)
    pthread_join(tid[i], NULL);
  return 0;
}
/* The thread will execute in this function */
void * runner(void * param) {
  pid_t tid = syscall(SYS_gettid);
  int i, run = atoi(param);
  for (i = 1; i <= run; i++) {
    printf("\nSV %d da di %d giay.",tid, i);
    sleep(1);
  }
printf("\nSV %d da den CV.",tid);
  pthread_barrier_wait( & barrier);
  pthread_exit(0);
}

/* The thread will execute in this function */
void * CGV(void * param) {
  struct timeval startwatch, endwatch;
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);
  pthread_barrier_wait( & barrier);
  printf("\nCGV: Ban ve xem phim, sau ");
  gettimeofday( & endwatch, NULL);
  printf("%ld giay.\n", (endwatch.tv_sec - startwatch.tv_sec));
  pthread_exit(0);
}
