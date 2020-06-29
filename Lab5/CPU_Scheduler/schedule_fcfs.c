/**
 * schedule_fcfs.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "cpu.h"
#include "schedulers.h"

#define SIZE    100


static int i=0;
Task task[SIZE];
// add a task to the list 
void add(char *name, int priority, int arrival, int burst) {
    task[i].name = name;
    task[i].burst = burst;
    i++;
}

// invoke the scheduler
void schedule(){
    int j=0;
    int time=0;
    for(j=0 ; j < i ; j++) {
        run(&task[j],time,task[j].burst);
        time += task[j].burst;
    }
    /*C1: tạo mảng lưu trữ thời gian chờ của từng P, mảng khác lưu trữ thời gian quay vòng
     rồi tính trung bình cộng và in ra màn hình.
    C2: tính gộp trong vòng lặp. Vì arrival của mọi P là 0 nên thời gian chờ của mỗi P là tổng thời gian chạy của các P trước nó.
    */
}
