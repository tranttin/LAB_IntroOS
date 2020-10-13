// CPP Program to find sum of array 
#include <math.h>
/* printf */
#include <stdio.h>
/* pthread_* */
#include <pthread.h>
/* clock */
#include <time.h>
/* gettimeofday */
#include <sys/time.h>
/* syscall */
#include <sys/syscall.h>
/* pid_t */
#include <sys/types.h>
/* open */
#include <sys/stat.h>
#include <fcntl.h>
/* strrchr */
#include <string.h>
  

#include <stdlib.h>

  
// maximum number of threads 
#define MAX_THREAD 4
int counter=0;
pthread_mutex_t lock; 
  
void* seedpoint(void *arg) 
{ 
srand((unsigned int)time(NULL));
float x,y,distance;
    int a = *((int *) arg);
    

  for(int i = 0; i< a ; i++ )
{   x = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
    y = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
 
 distance = sqrt(x*x + y*y);
if(distance <= 1.0) {
// 
counter++;
// }

}

} 
  
// Chương trình chính.
int main(int argc, char *argv[]) 
{ 
  int n_thread = atoi(argv[1]);
  int n_seed = atoi(argv[2]);
  int *arg = malloc(sizeof(*arg));
*arg = atoi(argv[2]);
        clock_t t1, t2; 
  struct timeval start2, end2;
    t1 = clock(); 
gettimeofday(&start2, NULL);
    pthread_t threads[n_thread]; 
  
    // Creating MAX_THREAD threads 
    for (int i = 0; i < n_thread  ; i++) 
        pthread_create(&threads[i], NULL, seedpoint, arg);
  
    // joining MAX_THREAD threads  
    for (int i = 0; i < n_thread ; i++) 
        pthread_join(threads[i], NULL); 


   
   printf("Uoc tinh PI =  %f\n", (float)counter / (n_thread*(int) *arg) *4);
  
  
      t2 = clock(); 
       gettimeofday(&end2, NULL);
    printf(" clock() method: %ld clocks.\n", (t2 - t1) );
	printf(" gettimeofday() method: %ldms\n", (end2.tv_sec - start2.tv_sec) *1000 + (end2.tv_usec - start2.tv_usec)/1000);
    return 0; 
} 
