// 2021 June 12
// Author: Tran Trung Tin. Demo in [1] page 268
// Demo using compare_and_swap
#define _GNU_SOURCE

#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include <unistd.h> // for sleep()

#include <stdbool.h>

#include <stdatomic.h>

void * urgent(void * param); /* threads call this function */
void * interrupt(void * param); /* threads call this function */
int owner = 0; //share

int main(int argc, char * argv[]) {

  pthread_t tid[2]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid[0], & attr, urgent, argv[1]);
  pthread_create( & tid[1], & attr, interrupt, argv[1]);
  /* wait for the thread to exit */
  for (int i = 0; i < 2; i++)
    pthread_join(tid[i], NULL);

  return 0;
}
/* The thread will execute in this function */
void * urgent(void * param) {
  printf("\n(0-Share  1-Urgent  2-Interrupt)\nRoom for %d.", owner);
  if (__sync_bool_compare_and_swap( & owner, 0, 1) == true) {
    printf("\nRoom for %d in %d sec.", owner, atoi(param));
    sleep(atoi(param)); //try after interval 1 sec
  }

  if (__sync_bool_compare_and_swap( & owner, 1, 0) == true)
    printf("\nUrgent leaving room.");
  pthread_exit(0);
}

/* The thread will execute in this function */
void * interrupt(void * param) {
  sleep(1); // come late.
  while (__sync_bool_compare_and_swap( & owner, 0, 2) == false) {

    printf("\nB: I'm waiting ...");

    sleep(1); //try after interval 1 sec
  }
  printf("\nB: I'm in ....\n");
  printf("\n(0-Share  1-Urgent  2-Interrupt)\nRoom for %d.", owner);
  sleep(1);
  if (__sync_bool_compare_and_swap( & owner, 2, 0) == true) printf("\nInterrupt leaving room.");
  printf("\n(0-Share  1-Urgent  2-Interrupt)\nRoom for %d.", owner);
  pthread_exit(0);
}
