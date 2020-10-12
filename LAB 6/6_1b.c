#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h> 
 
#define BUFFER_SIZE  10
 
void *consume(void *arg);
void *produce(void *arg);
int buffer[BUFFER_SIZE], in=0, out=0, counter=0;

 
int main(int argc, char *argv[])
{
 pthread_t tid1,tid2;

 int sleep1 = atoi(argv[1]); int sleep2 = atoi(argv[2]);
 pthread_create(&tid1, NULL, produce, (void*)&sleep1);
 pthread_create(&tid2, NULL, consume, (void*)&sleep2);
 pthread_join(tid1, NULL);
 sleep(5); //stop program if nothing sent after 5 seconds.
}

void *produce(void *arg)
{
 int i=0;
 for(int k=0; k<1000000; k++)
 {
 while (counter == BUFFER_SIZE);
 printf("Sending %d with counter = %d\n", k,counter);
 buffer[in] = 1;

 in = (in + 1) % BUFFER_SIZE;
  

counter++;

 sleep(*((int*) arg));
 
 }
 return NULL;
}
void *consume(void *arg)
{
 int item, i=0;
 while(1) {
 while (counter == 0); /* do nothing */

 item = buffer[out];
 i+= item;
out = (out + 1) % BUFFER_SIZE;
 printf("Receive %d with counter = %d\n", i, counter);
 counter--;
 

/* consume the item in next consumed */
 sleep(*((int*) arg));

 }
 return NULL;
}
