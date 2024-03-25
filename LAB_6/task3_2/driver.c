// 2021 June 7
// Author: Tran Trung Tin
// Reading file and import to array to run scheduling algorithm

#ifndef TASK_H
#define TASK_H

// representation of a task
typedef struct task { //process
    char *name;
    int tid;
    int priority;
    int burst;
    int arrival;
} Task;

#endif

#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include <string.h>

/* gettimeofday */ #include <sys/time.h>

/* clock */ #include <time.h>

#include <sys/sysinfo.h>

#include <math.h>

#include <sys/syscall.h>

#include <unistd.h>
#define SIZE    100

Task task[SIZE];
void * FCFS(void * param);
void run(Task *task, int start, int slice);

 // maximum number of threads 
#define MAX_THREAD 5

int process = 0;

void * reader(void * param);
int main(int argc, char * argv[]) {
  void * status;
  pthread_t tid[MAX_THREAD]; /* the thread identifier */
  struct timeval startwatch, endwatch;

  /* ### start section to be measured ### */
  gettimeofday( & startwatch, NULL);
  pthread_create( & tid[0], NULL, reader, (argv[1]));
  pthread_join(tid[0], & status);

  if ((intptr_t) status == -1) return -1; //cannot open file
  pthread_create( & tid[0], NULL, FCFS, NULL);
  pthread_join(tid[0], NULL);

  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nRunning: %ldus\n", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));
  return 0;
}

/* The thread will execute in this function */
void * reader(void * param) {
  FILE * fp;
  if ((fp = fopen(param, "r")) == NULL) {
    printf("\nCannot open file.\n");
    return (void * ) - 1;
  }
  char * temp;
  char job[SIZE];
  while (fgets(job, SIZE, fp) != NULL) {
    temp = strdup(job);
    task[process].name = strsep( & temp, ",");
    task[process].priority = atoi(strsep( & temp, ","));
    task[process].arrival = atoi(strsep( & temp, ","));
    task[process].burst = atoi(strsep( & temp, ","));
    process++;
    free(temp);
  }
  fclose(fp);
  pthread_exit(0);
}

void run(Task * task, int start, int slice) {
  printf("Running task = [%s] [%d] [%d] [%d] from %d to %d.\n", task -> name, task -> priority, task -> arrival, task -> burst, start, slice + start);
}

void swap(Task * a, Task * b) {
  Task c;
  c = * a;
  * a = * b;
  * b = c;
  return;
}