// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 8th Edition p.320
// Demo avoid deadlock by try_lock
#include<pthread.h>

#include <semaphore.h>

#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void * do_work_one(void * param); /* threads call this function */
void * do_work_two(void * param); /* threads call this function */
int main(int argc, char * argv[]) {

  pthread_mutex_init( & first_mutex, NULL);
  pthread_mutex_init( & second_mutex, NULL);
  pthread_t tid[2]; /* the thread identifier */
  /* create the thread */
  pthread_create( & tid[0], NULL, do_work_two, NULL);
  pthread_create( & tid[1], NULL, do_work_one, NULL);
  /* wait for the thread to exit */
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  return 0;
}

/* thread_one runs in this function */
void * do_work_one(void * param) {

  int done = 0;
  while (!done) {

    pthread_mutex_lock( & first_mutex);
    sleep(1);
    if (pthread_mutex_trylock( & second_mutex)) {
      // Do some work
      printf("\nThread 1 reached this point.");

      pthread_mutex_unlock( & second_mutex);
      pthread_mutex_unlock( & first_mutex);
      done = 1;
    } else

      pthread_mutex_unlock( & first_mutex);
  }
  pthread_exit(0);
}
/* threadtwo runs in this function */
void * do_work_two(void * param) {

  int done = 0;
  while (!done) {

    pthread_mutex_lock( & second_mutex);
    sleep(1);
    if (pthread_mutex_trylock( & first_mutex)) {
      // Do some work
      printf("\nThread 2 reached this point.");
      pthread_mutex_unlock( & first_mutex);
      pthread_mutex_unlock( & second_mutex);
      done = 1;
    } else

      pthread_mutex_unlock( & second_mutex);
  }
  pthread_exit(0);
}
