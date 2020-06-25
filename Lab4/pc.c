
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h> 
 
#define MAX_BUFF   100
 
void *consume(void *arg);
void *produce(void *arg);
int buf[MAX_BUFF], front, rear;
/* Here lock is used to create a critical section
 *  full and empty used to signaling events to other threads
 */
sem_t lock, full, empty;
 
int main()
{
 pthread_t tid1,tid2;
 /* lock is a binary semaphore used to make a critical same as mutex 
 * To make sure only one thread accessing at a time*/
 sem_init(&lock, 0, 1);
 /* full is used to check queue is empty or not */
 sem_init(&full, 0, 1);
 /* empty is used to check queue is full or not */
 sem_init(&empty, 0, MAX_BUFF);
 pthread_create(&tid1, NULL, produce, NULL);
 pthread_create(&tid2, NULL, consume, NULL);
 pthread_join(tid1, NULL);
 pthread_join(tid2, NULL);
}
void *produce(void *arg)
{
 int i;
 for(i=0;i<10;i++)
 {
 /* Now this is same as is_queue_full() 
 * before storing value in queue */
 sem_wait(&empty);
 sem_wait(&lock);
 printf("produced item is %d\n", i);
 buf[(++rear)%MAX_BUFF] = i;
 sleep(1);
 sem_post(&lock);
 /* This is to inform consumer that data is available in queue */
 sem_post(&full);
 }
 return NULL;
}
void *consume(void *arg)
{
 int item, i;
 for(i = 0; i < 10; i++)
 {
 /* wait untill data is available in queue same as
 * is_queue_empty() */
 sem_wait(&full);
 sem_wait(&lock);
 item=buf[(++front) % MAX_BUFF];
 printf("consumed item is %d\n", item);
 sleep(1);
 sem_post(&lock);
 /* Notifynig consumer that data consumed and psition is available */
 sem_post(&empty);
 }
 return NULL;
}
