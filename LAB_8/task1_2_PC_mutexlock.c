// 2021 June 7
// Author: Tran Trung Tin
// Producer / Consumer share count varible. Peterson applied to critical section.
#define _GNU_SOURCE

#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#include <sys/sysinfo.h>

#include <sys/syscall.h>

#include <unistd.h>

#include <sched.h>

#include <sys/wait.h>

#include <stdbool.h>

/* gettimeofday */ #include <sys/time.h>
 // maximum number of threads 
#define BUFFER_SIZE 10
#define MAX_THREAD 2
int count = 0; /* this data is shared by the thread(s) */
int in = 0;
int out = 0;
int buffer[BUFFER_SIZE];
pthread_mutex_t lock;
void * producer(void * param); /* threads 0 call this function */
void * consumer(void * param); /* threads 1 call this function */
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */

  struct sched_param sd;
  sd.sched_priority = 50; //Set real-time priority 50
  sched_setscheduler(0, SCHED_RR, & sd);
  cpu_set_t set;
  CPU_ZERO( & set);
  CPU_SET(0, & set);
  CPU_SET(1, & set);
  if (sched_setaffinity(getpid(), sizeof(set), & set) == -1)
    printf("\nFailed to set affinity.");

  if (pthread_mutex_init( & lock, NULL) != 0) {
    printf("\n mutex init has failed\n");
    return 1;
  }
  struct timeval startwatch, endwatch;
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);
  pthread_create( & tid[0], NULL, producer, (argv[1]));
  pthread_create( & tid[1], NULL, consumer, (argv[1]));
  pthread_join(tid[0], NULL);
  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */
  printf("\nGettimeofday() method: %ldus\n", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));
  sleep(1);
  pthread_cancel(tid[1]);
  pthread_mutex_destroy( & lock);
  return 0;
}

/* The thread will execute in this function */
void * producer(void * param) {
  int i = 0, max = atoi(param);
  for (int i = 0; i < max; i++) {
    while (count == BUFFER_SIZE); //do nothing
    buffer[ in ] = 1;
    printf("\nJust sent in = %d and count = %d.", in , count); in = ( in +1) % BUFFER_SIZE;

    pthread_mutex_lock( & lock);
    /* critical section */
    count++;
    /* end of critical section */
    pthread_mutex_unlock( & lock);
  }
  pthread_exit(0);
}
void * consumer(void * param) {
  int receive = 0;
  while (1) {
    while (count == 0); //do nothing
    receive += buffer[out];

    pthread_mutex_lock( & lock);
    /* critical section */
    count--;
    /* end of critical section */
    pthread_mutex_unlock( & lock);
    printf("\nJust received = %d and count = %d.", receive, count);
    out = (out + 1) % BUFFER_SIZE;
  }
  pthread_exit(0);
}
