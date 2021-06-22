//2021 March 15
//Author: G4G
//Demo of mutex loc
#include<stdio.h>

#include<string.h>

#include<pthread.h>

#include<stdlib.h>

#include<unistd.h>

#define MAX_FARMER 10
pthread_t tid[MAX_FARMER];

void * farmer(void * param) {
  int v = * (int * ) param;  free(param);
  printf("\n%d Arriving bridge ...", v);
  printf("\n%d Enter bridge ...", v);
  sleep(rand() % 5 + 3); //random time cost 2 --> 6 s
  printf("\n%d Leaving bridge ...", v);
  return NULL;
}

int main(void) {
  time_t t;
  /* Intializes random number generator */
  srand((unsigned) time( & t));
  for (int i = 0; i < MAX_FARMER; i++) {
    int * p = malloc(sizeof i);* p = i;
    pthread_create( & tid[i], NULL, farmer, p);
    sleep(rand() % 3); //random time cost 0-4 s
  }
  for (int i = 0; i < MAX_FARMER; i++)
    pthread_join(tid[i], NULL);
  return 0;
}
