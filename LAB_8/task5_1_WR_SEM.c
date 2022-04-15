// 2021 Apr 21
// Author: Tran Trung Tin based on Book Operating System Concepts 10th, p.270
// Writer-Reader (Variation 1) by sem_t
# include <stdio.h>

# include <stdlib.h>

# include <time.h>

# include <sys/types.h>

# include <pthread.h>

# include <semaphore.h>

# include <string.h>

# include <unistd.h>

//semaphores
sem_t RWMutex, mutex;
int readCount;

struct data {
  int id;
  int opTime;
  int lastTime;
};

//reader
void * Reader(void * param) {
  int id = ((struct data * ) param) -> id;
  int lastTime = ((struct data * ) param) -> lastTime;
  int opTime = ((struct data * ) param) -> opTime;

  sleep(opTime);
  printf("Thread %d: waiting to read\n", id);

  sem_wait( &mutex);
  readCount++;
  if (readCount == 1)
    sem_wait( &RWMutex);
  sem_post( &mutex);

  printf("Thread %d: start reading\n", id);
  /* reading is performed */
  sleep(lastTime);
  printf("Thread %d: end reading\n", id);

  sem_wait( &mutex);
  readCount--;
  if (readCount == 0)
    sem_post( &RWMutex);
  sem_post( &mutex);
  pthread_exit(0);
}

//Writer
void * Writer(void * param) {
  int id = ((struct data * ) param) -> id;
  int lastTime = ((struct data * ) param) -> lastTime;
  int opTime = ((struct data * ) param) -> opTime;
  sleep(opTime);
  printf("Thread %d: waiting to write\n", id);
  sem_wait( &RWMutex);
  printf("Thread %d: start writing\n", id);
  /* writing is performed */
  sleep(lastTime);
  printf("Thread %d: end writing\n", id);
  sem_post( &RWMutex);
  pthread_exit(0);
}

int main() {
  //pthread
  pthread_t tid; // the thread identifier
  pthread_attr_t attr; //set of thread attributes

  /* get the default attributes */
  pthread_attr_init( &attr);

  //initial the semaphores
  sem_init( &mutex, 0, 1);
  sem_init( &RWMutex, 0, 1);
  readCount = 0;

  int id = 0;
  while (scanf("%d", &id) != EOF) {
  printf("CC");
    char role; //producer or consumer
    int opTime; //operating time
    int lastTime; //run time

    scanf("%c%d%d", &role, &opTime, &lastTime);
    struct data* d = (struct data* ) malloc (sizeof(struct data));

    d->id = id;
    d->opTime = opTime;
    d->lastTime = lastTime;

    if (role == 'R') {
      printf("Create the %d thread: Reader\n", id);
      pthread_create( &tid, &attr, Reader, d);

    } else if (role == 'W') {
      printf("Create the %d thread: Writer\n", id);
      pthread_create( &tid, &attr, Writer, d);
    }
  }
  sem_destroy( &mutex);
  sem_destroy( &RWMutex);
  return 0;
}
