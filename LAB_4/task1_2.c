// 2021 June 2
// Author: Tran Trung Tin
// Demo using timming running threads
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

/* gettimeofday */ #include <sys/time.h>

/* clock */ #include <time.h>

#include <sys/sysinfo.h>

/* pid_t */ #include <sys/types.h>

int sum; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */

  time_t startCPU, endCPU;
  struct timeval startwatch, endwatch;

  /* ### start section to be measured ### */
  /* clock() method */
  startCPU = clock();
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  pthread_create( & tid, & attr, runner, argv[1]);
  /* wait for the thread to exit */
  pthread_join(tid, NULL);

  endCPU = clock();
  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nThis system has %d processors configured and %d processors available.", get_nprocs_conf(), get_nprocs());
  printf("\nClock() method: %ldus\n", (endCPU - startCPU) / (CLOCKS_PER_SEC / 1000000));
  printf("\nGettimeofday() method: %ldus", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));

  printf("\nSum = %d∖n", sum);
}

/* The thread will execute in this function */
void * runner(void * param) {
  int i, upper = atoi(param);
  sum = 0;
  for (i = 1; i <= upper; i++)
    sum += i;
  pthread_exit(0);
}
