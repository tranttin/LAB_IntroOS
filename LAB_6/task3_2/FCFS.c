// 2021 Jun 15
// Author: Tran Trung Tin, based on [1] Chapter 5 Programming Assignment.
// FCFS running an array already read from file by driver.c

#include "task.h"
extern int process;

void * FCFS(void * param){
    int t_wait = 0, t_taround = 0;
    int j=0;
    int time=0;
//SORTING ARRIVAL TIME
    for(j=0 ; j < process ; j++) {
        run(&task[j],time,task[j].burst); //Run from time to time+burst
        time += task[j].burst; //moving to next P
        t_wait += time - task[j].burst - task[j].arrival ;
        t_taround += time - task[j].arrival ;
    }
  printf("\nFCFS Time wait ave = %.2f", t_wait * 1.0 / process);
  printf("\nFCFS Time turn around ave = %.2f", t_taround * 1.0 / process);
  pthread_exit(0);
}
