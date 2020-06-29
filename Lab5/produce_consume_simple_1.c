#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h> 
 
#define BUFFER_SIZE  20
 
void *consume(void *arg);
void *produce(void *arg);
int buffer[BUFFER_SIZE], in=0, out=0;

 
int main(int argc, char *argv[])
{
 pthread_t tid1,tid2;

 int sleep1 = atoi(argv[1]); int sleep2 = atoi(argv[2]);
 pthread_create(&tid1, NULL, produce, (void*)&sleep1);
 pthread_create(&tid2, NULL, consume, (void*)&sleep2);
 pthread_join(tid1, NULL);
 pthread_join(tid2, NULL);
}

void *produce(void *arg)
{
 int i=0;
 while(1)
 {
 while (((in + 1) % BUFFER_SIZE) == out);
 printf("Sending %d with in = %d and out = %d\n", i,in, out);
 buffer[in] = i;
 in = (in + 1) % BUFFER_SIZE;
 i++;
 sleep(*((int*) arg));
 
 }
 return NULL;
}
void *consume(void *arg)
{
 int item, i;
 while(1) {
 while (in == out); /* do nothing */
 item = buffer[out];
 printf("Receive %d\n", item);
 out = (out + 1) % BUFFER_SIZE;

/* consume the item in next consumed */
 sleep(*((int*) arg));

 }
 return NULL;
}
