// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 8th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

int sum; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid, & attr, runner, argv[1]);
  /* wait for the thread to exit */
  pthread_join(tid, NULL);
  printf("sum = %d∖n", sum);
}
/* The thread will execute in this function */
void * runner(void * param) {
  int i, upper = atoi(param);
  sum = 0;
  for (i = 1; i <= upper; i++)
    sum += i;
  pthread_exit(0);
}
