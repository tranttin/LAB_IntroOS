// 2021 June 7
// Author: Tran Trung Tin
// Reading define Task structure and all lib.

#ifndef TASK_H
#define TASK_H

// representation of a task
typedef struct task {
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

