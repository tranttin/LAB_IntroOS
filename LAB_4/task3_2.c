// 2021 June 2
// Author: Tran Trung Tin
// Demo using gen random matrix and write to file
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include <stdint.h>

#define M 10
#define N 10
#define MAX_INT 10000
#define MAX_LENGTH 100
int a[M][N];
char line[MAX_LENGTH];
char tokens[] = " \n";
char * key;
void * writerLCD(void * param);
void * reader(void * param);

int main(int argc, char * argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  void * status;

  memset(line, 0, MAX_LENGTH);

  /* create the thread */
  pthread_create( & tid, & attr, reader, argv[1]);
  /* wait for the thread to exit */
  pthread_join(tid, & status);
  if ((intptr_t) status != -1) {
    /* create the thread */
    pthread_create( & tid, & attr, writerLCD, NULL);
    /* wait for the thread to exit */
    pthread_join(tid, NULL);
  } else
    printf("\nProgram exit");
  return 0;
}
/* The thread will execute in this function */
void * reader(void * param) {
  FILE * fp;
  if ((fp = fopen(param, "r")) == NULL) {
    printf("\nCannot open file.");
    return (void * ) - 1;
  }
  for (int i = 0; i < M; i++) {
    fgets(line, MAX_LENGTH, fp);
    key = (char * ) strtok(line, tokens);
    int put1 = atoi(key);
    a[i][0] = put1;
    for (int j = 1; j < N; j++) {
      key = (char * ) strtok(NULL, tokens);
      int put2 = atoi(key);
      a[i][j] = put2;
    }
  }
  fclose(fp);
  pthread_exit(0);
}

void * writerLCD(void * arg) {

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++)
      fprintf(stdout, "%5d ", a[i][j]);
    fprintf(stdout, "\r\n");
  }

  pthread_exit(0);
}
