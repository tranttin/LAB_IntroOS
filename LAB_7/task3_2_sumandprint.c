// 2021 June 12
// Author: Tran Trung Tin. Demo in [1] page 266
// Demo using memory barrier to make a point.
#define _GNU_SOURCE

#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include <unistd.h> // for sleep()

#include <stdbool.h>

void * accumulator(void * param); /* threads call this function */
void * printer(void * param); /* threads call this function */
bool flag = false;
int x = 83432; // random
int main(int argc, char * argv[]) {

  pthread_t tid[2]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid[0], & attr, accumulator, NULL);
  pthread_create( & tid[1], & attr, printer, NULL);
  /* wait for the thread to exit */
  for (int i = 0; i < 2; i++)
    pthread_join(tid[i], NULL);

  return 0;
}
/* The thread will execute in this function */
void * accumulator(void * param) {
  x = 100;
  __sync_synchronize();
  flag = true;
  pthread_exit(0);
}

/* The thread will execute in this function */
void * printer(void * param) {
  if (!flag)
    __sync_synchronize();
  printf("\nValue x = %d", x);
  pthread_exit(0);
}
