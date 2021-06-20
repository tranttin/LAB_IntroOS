// 2021 June 7
// Author: Tran Trung Tin
// Calculating value of PI by Monte Carlo method
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

/* gettimeofday */ #include <sys/time.h>

/* clock */ #include <time.h>

#include <sys/sysinfo.h>

#include <math.h>

#include <sys/syscall.h>

#include <unistd.h>
 // maximum number of threads 
#define MAX_THREAD 40
int counter = 0; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */

  struct timeval startwatch, endwatch;

  int n_thread = atoi(argv[1]);

  /* ### start section to be measured ### */
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  for (int i = 0; i < n_thread; i++)
    pthread_create( & tid[i], NULL, runner, (argv[2]));
  /* wait for the thread to exit */
  for (int i = 0; i < n_thread; i++)
    pthread_join(tid[i], NULL);

  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nGettimeofday() method: %ldus", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));

  printf("\nUoc tinh PI =  %f\n", (float) counter / (n_thread * atoi(argv[2])) * 4);

  return 0;
}

/* The thread will execute in this function */
void * runner(void * param) {
  srand((unsigned int) time(NULL));
  float x, y, distance;
  int a = atoi(param);

  pid_t tid = syscall(SYS_gettid);
  printf("\nThread %d is running.", tid);
  for (int i = 0; i < a; i++) {
    x = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;
    y = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;

    distance = sqrt(x * x + y * y);
    if (distance <= 1.0) counter++;

  }
  printf("\nThread %d finished.", tid);
  pthread_exit(0);
}
© 2021 GitHub, Inc.
