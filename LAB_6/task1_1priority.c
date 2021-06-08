// 2021 June 7
// Author: Tran Trung Tin
// Calculating value of PI by Monte Carlo method
#include<pthread.h>

#include<stdio.h>

#include<stdlib.h>

/* gettimeofday */ #include <sys/time.h>

/* clock */ #include <time.h>

#include <sys/sysinfo.h>

#include <math.h>

#include <sys/syscall.h>

#include <unistd.h>
 // maximum number of threads 
#define MAX_THREAD 40
int counter = 0; /* this data is shared by the thread(s) */
void * runner(void * param); /* threads call this function */
int main(int argc, char * argv[]) {
  pthread_t tid[MAX_THREAD]; /* the thread identifier */
  pthread_attr_t attr; /* set of thread attributes */
  /* set the default attributes of the thread */
  pthread_attr_init( & attr);
  /* create the thread */

  struct timeval startwatch, endwatch;

  int n_thread = atoi(argv[1]);
 
//  https://man7.org/linux/man-pages/man2/gettid.2.html
	struct sched_param sd;
        cpu_set_t set;
	sd.sched_priority=50;   //Set real-time priority 50
	sched_setscheduler(0,SCHED_RR,&sd);
	CPU_ZERO(&set);
	CPU_SET(0,&set);
	sched_setaffinity(0,sizeof(cpu_set_t),&set);   //Set CPU affinity
  /* ### start section to be measured ### */
  /* gettimeofday() method */
  gettimeofday( & startwatch, NULL);

  for (int i = 0; i < n_thread; i++)
    pthread_create( & tid[i], NULL, runner, (argv[2]));
  /* wait for the thread to exit */
  for (int i = 0; i < n_thread; i++)
    pthread_join(tid[i], NULL);

  gettimeofday( & endwatch, NULL);
  /* ### end of section to be measured ### */

  printf("\nGettimeofday() method: %ldus", (endwatch.tv_sec - startwatch.tv_sec) * 1000000 + (endwatch.tv_usec - startwatch.tv_usec));

  printf("\nUoc tinh PI =  %f\n", (float) counter / (n_thread * atoi(argv[2])) * 4);

  return 0;
}

/* The thread will execute in this function */
void * runner(void * param) {
  srand((unsigned int) time(NULL));
  float x, y, distance;
  int a = atoi(param);

  pid_t tid = syscall(SYS_gettid);
  printf("\nThread %d is running.", tid);
  for (int i = 0; i < a; i++) {
    x = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;
    y = -1 + ((float) rand() / (float)(RAND_MAX)) * 2;

    distance = sqrt(x * x + y * y);
    if (distance <= 1.0) counter++;

  }
  printf("\nThread %d finished.", tid);
  pthread_exit(0);
}







#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
/* gettimeofday */
#include <sys/time.h>



#include <sched.h>
void Thread1()
{ 
struct timeval start, end;
    gettimeofday(&start, NULL);
    int i,j;
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(),&policy,&param);
    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");
    if(policy == SCHED_RR)
        printf("SCHED_RR\n");
    if(policy==SCHED_FIFO)
         printf("SCHED_FIFO\n");
    for(i=1;i<10;i++) 

    {
         for(j=1;j<500000000;j++)
        {
        }
       printf("thread 1\n"); //sleep(1);
    }
gettimeofday(&end, NULL);
   printf("Pthread 1 start at %ld.%ld and end at %ld.%ld\n", start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
}

void Thread2()
{  
struct timeval start, end;
    gettimeofday(&start, NULL);
    int i,j,m;
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(),&policy,&param);
    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");
    if(policy == SCHED_RR)
        printf("SCHED_RR\n");
    if(policy==SCHED_FIFO)
        printf("SCHED_FIFO\n");
sleep(1);
     for(i=1;i<10;i++) 

    {
        for(j=1;j<500000000;j++)
        {
        }
       printf("thread 2\n");// sleep(1);
    }

gettimeofday(&end, NULL);

   printf("Pthread 2 start at %ld.%ld and end at %ld.%ld\n", start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);



}

void Thread3()
{
struct timeval start, end;
    gettimeofday(&start, NULL);
    int i,j;
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(),&policy,&param);
    if(policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");
    if(policy == SCHED_RR)
        printf("SCHED_RR\n");
    if(policy==SCHED_FIFO)
        printf("SCHED_BATCH\n");

  for(i=1;i<10;i++) 
 
     {
        for(j=1;j<50000000;j++)
         {
         }

        printf("thread 3\n"); sleep(1);
     }
gettimeofday(&end, NULL);

   printf("Pthread 3 start at %ld.%ld and end at %ld.%ld\n", start.tv_sec, start.tv_usec, end.tv_sec, end.tv_usec);
}

int main()
{
    int i;
    i = getuid();
    if(i==0)
        printf("The current user is root\n");
    else
        printf("The current user is not root\n");

	struct sched_param sd;
        cpu_set_t set;
	sd.sched_priority=50;   //Set real-time priority 50
	sched_setscheduler(0,SCHED_RR,&sd);
	CPU_ZERO(&set);
	CPU_SET(0,&set);
	sched_setaffinity(0,sizeof(cpu_set_t),&set);   //Set CPU affinity




    pthread_t ppid1,ppid2,ppid3;
    struct sched_param param;

    pthread_attr_t attr3,attr1,attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    param.sched_priority = 50;
    pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
    pthread_attr_setschedparam(&attr1,&param);
    pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);

    param.sched_priority = 50;
    pthread_attr_setschedpolicy(&attr2,SCHED_FIFO);
    pthread_attr_setschedparam(&attr2,&param);
    pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);

    param.sched_priority = 50;
    pthread_attr_setschedpolicy(&attr3,SCHED_FIFO);
    pthread_attr_setschedparam(&attr3,&param);
    pthread_attr_setinheritsched(&attr3,PTHREAD_EXPLICIT_SCHED);

    pthread_create(&ppid3,&attr3,(void *)Thread3,NULL);
    pthread_create(&ppid2,&attr2,(void *)Thread2,NULL);
    pthread_create(&ppid1,&attr1,(void *)Thread1,NULL);

    pthread_join(ppid3,NULL);
    pthread_join(ppid2,NULL);
    pthread_join(ppid1,NULL);
    pthread_attr_destroy(&attr2);
    pthread_attr_destroy(&attr1);
    return 0;
}
