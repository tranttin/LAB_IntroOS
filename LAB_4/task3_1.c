// 2021 June 2
// Author: Tran Trung Tin
// Demo using gen random matrix and write to file
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#define M 10
#define N 10
#define MAX_INT 10000
#define MAX_LENGTH 100
int a[M][N];
void * writer(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);

  /* Intializes random number generator */
  time_t t;
  srand((unsigned) time( & t));
  char line[MAX_LENGTH];
  char tokens[] = " \n";
  char * key;
  memset(line, 0, MAX_LENGTH);

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++)
      a[i][j] = rand() % MAX_INT;
  }
  /* create the thread */
  pthread_create( & tid, & attr, writer, argv[1]);
  /* wait for the thread to exit */
  pthread_join(tid, NULL);

}
/* The thread will execute in this function */
void * writer(void * param) {
  FILE * fp;
  if ((fp = fopen(param, "w")) == NULL) {
    printf("\nCannot open file.");
    return 0;
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++)
      fprintf(fp, "%d ", a[i][j]);
    fprintf(fp, "\r\n");
  }
  fclose(fp);
  pthread_exit(0);
}
