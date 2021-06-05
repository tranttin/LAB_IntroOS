// 2021 June 2
// Author: Tran Trung Tin
// Demo using timming running threads
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>
/* gettimeofday */
#include <sys/time.h>
/* clock */
#include <time.h>

#include <sys/sysinfo.h>

int sum; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthreadt tid; /* the thread identifier */
  pthreadattrt attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthreadattrinit( & attr);
  /* create the thread */
  
  time_t startwatch, endwatch;
  struct timeval startCPU, endCPU;
  
  /* ### start section to be measured ### */
	/* clock() method */
	startCPU = clock();
	/* gettimeofday() method */
	gettimeofday(&startwatch, NULL);
  
  pthreadcreate( & tid, & attr, runner, argv[1]);
  /* wait for the thread to exit */
  pthreadjoin(tid, NULL);

  endCPU = clock();
	gettimeofday(&endwatch, NULL);
	/* ### end of section to be measured ### */

  printf("This system has %d processors configured and %d processors available.\n",   get_nprocs_conf(), get_nprocs());
  printf("\nClock() method: %ldms\n", (endCPU - startCPU) / (CLOCKS_PER_SEC/1000));
	printf(" gettimeofday() method: %ldms\n", (endwatch.tv_sec - startwatch.tv_sec) *1000 + (endwatch.tv_usec - startwatch.tv_usec)/1000);
  
  printf("sum = %d∖n", sum);
}

/* The thread will execute in this function */
void * runner(void * param) {
  int i, upper = atoi(param);
  sum = 0;
  for (i = 1; i <= upper; i++)
    sum += i;
  pthreadexit(0);
}
