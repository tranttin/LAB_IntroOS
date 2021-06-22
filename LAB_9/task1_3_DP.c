// 2021 Jun 20
// Author Tran Trung Tin based on [1] p. 294
// Demo Dining philosophers

#include <pthread.h>

#include <semaphore.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#define N 5

sem_t chopstick[N];

void * philospher(void * p) {
  int i = * (int * ) p;
  free(p);
  while (1) {
    printf("\nPhilosopher %d is thinking ...", i);
    sleep(1); //thinking
    printf("\nPhilosopher %d is hungry ...", i);
    sem_wait( & chopstick[i]);
    sem_wait( & chopstick[(i + 1) % 5]);
    printf("\nPhilosopher %d is eating ...", i);
    sleep(1); //eating
    sem_post( & chopstick[i]);
    sem_post( & chopstick[(i + 1) % 5]);
  }
}

int main() {

  int i;
  pthread_t tid[N];
  for (i = 0; i < N; i++)
    sem_init( & chopstick[i], 0, 1);

  for (i = 0; i < N; i++) {
    int * p = malloc(sizeof i);
    * p = i;
    // create philosopher processes
    pthread_create( & tid[i], NULL, philospher, p);
  }
  for (i = 0; i < N; i++)
    pthread_join(tid[i], NULL);
  return 0;
}
