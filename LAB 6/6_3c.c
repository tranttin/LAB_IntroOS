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

  
int counter=;   // FILL OUT

  
void* seedpoint(void *arg) 
{ 
srand((unsigned int)time(NULL));   //WHY?
float x,y,distance;
    int a = *((int *) arg);
    
  for(int i = 0; i< a ; i++ )
{   x = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
    y = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
 
 distance = sqrt(x*x + y*y);
if(distance <= ???) counter++;   // FILL OUT

}

} 
  
// Chương trình chính.
int main(int argc, char *argv[]) 
{ 
  int n_seed = atoi(argv[1]);
  int *arg = malloc(sizeof(*arg));
  *arg = atoi(argv[1]);
       
       
     
    pthread_t th1; 
 
        pthread_create(&th1, NULL, seedpoint, arg);
 
        pthread_join(th1, NULL); 


   
   printf("Uoc tinh PI =  %f\n", (float)counter / ((int) *arg) *4);
  
  

    return 0; 
} 
