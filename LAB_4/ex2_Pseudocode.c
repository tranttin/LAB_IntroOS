// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 8th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

int ave,min,max; /* this data is shared by the thread(s) */

struct partition {
int start;
int end;
};

struct partition A;
struct partition B;

// nguyên mẫu các hàm con

int main(int argc, char * argv[]) {
  
  // xác định n
  // xác định phân đoạn A
  // xác định phân đoạn B
  
  pthread_t tid[2]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid[0], & attr, songuyento, (void *) &A);
  pthread_create( & tid[1], & attr, songuyento, (void *) &B);
  /* wait for the thread to exit */
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
}

/* The thread will execute in this function */
void * songuyento(void * param) {
struct partition X * = (struct partition *) param;
int start = X->start;
int end = X->end;
 for(i=start; i < end ; i++) //do something
  //nếu i là số nguyên tố thì in ra màn hình.
  pthread_exit(0);
}
