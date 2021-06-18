/**
 * schedule_fcfs.c
**/

#include "cputask.h"
extern int i;


void * FCFS(void * param){

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
