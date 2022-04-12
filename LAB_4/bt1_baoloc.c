// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 8th Edition p.170
// Demo using how to speed up sum of sequence integer.
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

int min,max; /* this data is shared by the thread(s) */
float ave;
int a[100];
int n;

void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  
  // thêm data vào struct mang A;
  // scanf (c1)
  // argc va argv (c2)
  
  pthread_t tid[3]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */
  pthread_create( & tid[0], & attr, trungbinh, argv[0]);
      /* wait for the thread to exit */
  pthread_join(tid[0], NULL);

}
/* The thread will execute in this function */
void * trungbinh(void * param) {
  //for  tinh tong
  //tim tbc in man hinh
  pthread_exit(0);
}

/* The thread will execute in this function */
void * lonnhat(void * param) {

  pthread_exit(0);
}

/* The thread will execute in this function */
void * nhonhat(void * param) {

  pthread_exit(0);
}
