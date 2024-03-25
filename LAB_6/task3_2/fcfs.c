// 2021 Jun 15
// Author: Tran Trung Tin, based on [1] Chapter 5 Programming Assignment.
// FCFS running an array already read from file by driver.c

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

extern Task task[SIZE];
void * FCFS(void * param);
void run(Task *task, int start, int slice);

extern int process;

void * FCFS(void * param) {
  int t_wait = 0, t_taround = 0;
  int time = 0;
  //SORTING ARRIVAL TIME
  //Sáº¯p xáº¿p máº£ng cáº¥u trÃºc task vá»›i key lÃ  thá»i Ä‘iá»ƒm Ä‘áº¿n
  for (int i = 0; i < process; i++) {
    run( & task[i], time, task[i].burst); //Run from time to time+burst
    time += task[i].burst; //moving to next P
    t_wait += time - task[i].burst - task[i].arrival;
    t_taround += time - task[i].arrival;
  }
  printf("\nFCFS Time wait ave = %.2f", t_wait * 1.0 / process);
  printf("\nFCFS Time turn around ave = %.2f", t_taround * 1.0 / process);
  pthread_exit(0);
}