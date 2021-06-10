
#include <pthread.h>
#include <stdio.h>

pthread_barrier_t barrier;

void* thread_func(void* aArgs)
{
  pthread_barrier_wait(&barrier);

  printf("Entering thread %p\n", (void*)pthread_self());
  int i;
  for(i = 0 ; i < 5; i++)
    printf("val is %d in thread %p \n", i, (void*)pthread_self());
}

int main()
{
  pthread_t thread_1, thread_2;
  pthread_barrier_init(&barrier, NULL, 2);

  pthread_create(&thread_1, NULL, (void*)thread_func, NULL);
  printf("Thread %p created\n", (void*)thread_1);

  usleep(500);

  pthread_create(&thread_2, NULL, (void*)thread_func, NULL);
  printf("Thread %p created\n", (void*)thread_2);

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

  pthread_barrier_destroy(&barrier);

  return 0;
}
