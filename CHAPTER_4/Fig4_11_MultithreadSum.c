// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 8th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

int sum; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthreadt tid; /* the thread identifier */
  pthreadattrt attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthreadattrinit( & attr);
  /* create the thread */
  pthreadcreate( & tid, & attr, runner, argv[1]);
  /* wait for the thread to exit */
  pthreadjoin(tid, NULL);
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
