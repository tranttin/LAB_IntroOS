// 2021 June 2
// Author: 
// Demo using system call fork to create a thread and modify a global varible
#include<pthread.h>

#include<stdio.h>

#include<unistd.h>

int value = 5;
int main() {
  pthread_t tid; /* the thread identifier */
  pthread_create( & tid, NULL, runner, NULL);
  pthread_join(tid, NULL);
  printf("PARENT: value = %d", value); /* LINE A */
  return 0;
}

void * runner(void * param) {
  value += 15;
  pthread_exit(0);
}
