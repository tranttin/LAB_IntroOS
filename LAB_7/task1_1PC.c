// 2021 June 7
// Author: Tran Trung Tin
// Calculating value of PI by Monte Carlo method
#define _GNU_SOURCE#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include <sys/sysinfo.h>

#include <sys/syscall.h>

#include <unistd.h>

#include <sched.h>

#include <sys/wait.h>

// maximum number of threads 
#define MAX_THREAD 2
int count = 0; /* this data is shared by the thread(s) */
void * producer(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */

  struct sched_param sd;
  sd.sched_priority = 50; //Set real-time priority 50
  sched_setscheduler(0, SCHED_RR, & sd);
  cpu_set_t set;
  CPU_ZERO( & set);
  CPU_SET(0, & set);
  if (sched_setaffinity(getpid(), sizeof(set), & set) == -1)
    printf("\nFailed to set affinity.");

    pthread_create( & tid[i], & attr[i], producer, (argv[1]));
    pthread_create( & tid[i], & attr[i], consumer, (argv[1]));
    pthread_join(tid[i], NULL);


printf("\nAfter all, count = %d\n", count);
  return 0;
}

/* The thread will execute in this function */
void *producer(void *arg)
{
 int i=0, max = *((int*) arg);
for(int i=0; i < max; i++)
 {
 while (count == BUFFER_SIZE);  //do nothing
  buffer[in] = 1;
 in = (in + 1) % BUFFER_SIZE;
 count++;
 
 }
  pthread_exit(0);
}
void *consumer(void *arg)
{
  int receive = 0;
 int i=0, max = *((int*) arg);
for(int i=0; i < max; i++)
 {
 while (count == 0);  //do nothing
 receive += buffer[out];
out = (out + 1) % BUFFER_SIZE;
 count--;
 
 }
  printf("\nAfter all, receive = %d\n", count);
  
  pthread_exit(0);
}
