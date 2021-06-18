// 2021 June 7
// Author: Tran Trung Tin
// Calculating value of PI by Monte Carlo method

#include "cputask.h"
 // maximum number of threads 
#define MAX_THREAD 5

int i = 0;

void * reader(void * param);
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */

  struct timeval startwatch, endwatch;

  /* ### start section to be measured ### */
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  pthread_create( & tid[0], NULL, reader, (argv[1]));
  pthread_join(tid[0], NULL);

  pthread_create( & tid[0], NULL, FCFS, NULL);
  pthread_join(tid[0], NULL);

  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nGettimeofday() method: %ldus\n", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));

  return 0;
}

/* The thread will execute in this function */
void * reader(void * param) {

  FILE * fp;
  if ((fp = fopen(param, "r")) == NULL) {
    printf("\nCannot open file.");
    return (void * ) - 1;
  }

  char * temp;
  char job[SIZE];

  while (fgets(job, SIZE, fp) != NULL) {
    temp = strdup(job);
    task[i].name = strsep( & temp, ",");
    task[i].priority = atoi(strsep( & temp, ","));
    task[i].arrival = atoi(strsep( & temp, ","));
    task[i].burst = atoi(strsep( & temp, ","));
    i++;
    free(temp);
  }
  fclose(fp);
  pthread_exit(0);
}

void run(Task * task, int start, int slice) {
  printf("Running task = [%s] [%d] [%d] [%d] from %d to %d.\n", task -> name, task -> priority, task -> arrival, task -> burst, start, slice + start);
}
