// 2021 June 7
// Author: Tran Trung Tin
// Calculating value of PI by Monte Carlo method
#define _GNU_SOURCE

#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>
/* gettimeofday */
#include <sys/time.h>
/* clock */
#include <time.h>

#include <sys/sysinfo.h>

#include <math.h>

#include <sys/syscall.h>

#include <unistd.h>

#include <sched.h>

#include <sys/wait.h>
// maximum number of threads 
#define MAX_THREAD 40
int counter = 0; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */
  struct timeval startwatch, endwatch;
  int n_thread = 3;
  struct sched_param sd;
  sd.sched_priority = 50; //Set real-time priority 50
  sched_setscheduler(0, SCHED_RR, & sd);
  cpu_set_t set;
  CPU_ZERO( & set);
  CPU_SET(0, & set);
  if (sched_setaffinity(getpid(), sizeof(set), & set) == -1)
    printf("\nFailed to set affinity.");

  struct sched_param shparam;
  pthread_attr_t attr[3];
  shparam.sched_priority = 50;
  pthread_attr_init( & attr[0]);
  pthread_attr_setschedpolicy( & attr[0], SCHED_FIFO);
  pthread_attr_setschedparam( & attr[0], & shparam);
  pthread_attr_setinheritsched( & attr[0], PTHREAD_EXPLICIT_SCHED);

  shparam.sched_priority = 50;
  pthread_attr_init( & attr[1]);
  pthread_attr_setschedpolicy( & attr[1], SCHED_FIFO);
  pthread_attr_setschedparam( & attr[1], & shparam);
  pthread_attr_setinheritsched( & attr[1], PTHREAD_EXPLICIT_SCHED);

  shparam.sched_priority = 50;
  pthread_attr_init( & attr[2]);
  pthread_attr_setschedpolicy( & attr[2], SCHED_FIFO);
  pthread_attr_setschedparam( & attr[2], & shparam);
  pthread_attr_setinheritsched( & attr[2], PTHREAD_EXPLICIT_SCHED);

  /* ### start section to be measured ### */
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  for (int i = 0; i < n_thread; i++)
    pthread_create( & tid[i], & attr[i], runner, (argv[1]));

  /* wait for the thread to exit */
  for (int i = 0; i < n_thread; i++) {
    pthread_join(tid[i], NULL);
    pthread_attr_destroy( & attr[i]);
  }
  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nGettimeofday() method: %ldus", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));
  printf("\nUoc tinh PI =  %f\n", (float) counter / (n_thread * atoi(argv[1])) * 4);
  return 0;
}

/* The thread will execute in this function */
void * runner(void * param) {
  srand((unsigned int) time(NULL));
  float x, y, distance;
  int a = atoi(param);
  pid_t tid = syscall(SYS_gettid);
  struct timeval start, end;
  printf("\nThread %d is running ", tid);

  int policy;
  struct sched_param shparam;
  pthread_getschedparam(pthread_self(), & policy, & shparam);
  if (policy == SCHED_OTHER)
    printf("SCHED_OTHER\n");
  if (policy == SCHED_RR)
    printf("SCHED_RR\n");
  if (policy == SCHED_FIFO)
    printf("SCHED_BATCH\n");

  gettimeofday( & start, NULL);
  for (int i = 0; i < a; i++) {
    x = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;
    y = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;
    distance = sqrt(x * x + y * y);
    if (distance <= 1.0) counter++;
  }
  gettimeofday( & end, NULL);
  printf("\nThread %d start at %ld.%ld and end at %ld.%ld\n", tid, start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
  pthread_exit(0);
}
