// 2021 June 2
// Author: Tran Trung Tin
// Demo using timming running threads
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>
/* gettimeofday */ 
#include <sys/time.h>
/* clock */ 
#include <time.h>

#include <sys/sysinfo.h>
/* pid_t */ 
#include <sys/types.h>

#include <fcntl.h>
/* strrchr */ 
#include <string.h>
/* syscall */ 
#include <sys/syscall.h>

#include <unistd.h>

void * thread_function(void * );
long get_thread_time();
int sum; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */

  time_t startCPU, endCPU;
  struct timeval startwatch, endwatch;

  /* ### start section to be measured ### */
  /* clock() method */
  startCPU = clock();
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  pthread_create( & tid, & attr, runner, argv[1]);
  /* wait for the thread to exit */
  pthread_join(tid, NULL);

  endCPU = clock();
  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nThis system has %d processors configured and %d processors available.", get_nprocs_conf(), get_nprocs());
  printf("\nClock() method: %ldus\n", (endCPU - startCPU) / (CLOCKS_PER_SEC / 1000000));
  printf("\nGettimeofday() method: %ldus", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));

  printf("\nSum = %d∖n", sum);
}

/* The thread will execute in this function */
void * runner(void * param) {
  int i, upper = atoi(param);
  sum = 0;
  long start, end;

  start = get_thread_time();
  for (i = 1; i <= upper; i++)
    sum += i;

  end = get_thread_time();

  printf("\nBy get_thread_time() method: %ld jiffies\n", (end - start));
  pthread_exit(0);
}

pid_t gettid(void) {
  return syscall(__NR_gettid);
}

long get_thread_time() {
  int i;
  char proc_filename[256];
  char buffer[1024];

  pid_t pid = getpid();
  pid_t tid = gettid();

  sprintf(proc_filename, "/proc/%d/task/%d/stat", pid, tid);
  int fd, num_read;
  fd = open(proc_filename, O_RDONLY, 0);
  num_read = read(fd, buffer, 1023);
  close(fd);
  buffer[num_read] = '\0';

  char * ptr_usr = strrchr(buffer, ')') + 1;
  for (i = 3; i != 14; ++i) {
    ptr_usr = strchr(ptr_usr + 1, ' ');
  }

  ptr_usr++;
  long jiffies_user = atol(ptr_usr);
  long jiffies_sys = atol(strchr(ptr_usr, ' ') + 1);

  return jiffies_user;
}
