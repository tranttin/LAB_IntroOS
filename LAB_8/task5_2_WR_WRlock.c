// 2021 Apr 21
// Author: Tran Trung Tin based on Book Operating System Concepts 10th, p.270
// Writer-Reader (Variation 1) by WR-lock
# include < stdio.h >
  
# include < stdlib.h >
  
# include < time.h >
  
# include < sys / types.h >
  
# include < pthread.h >
 
# include < semaphore.h >
  
# include < string.h >
 
# include < unistd.h >

  pthread_rwlock_t lock;

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

  pthread_rwlock_rdlock( & lock);

  printf("Thread %d: start reading\n", id);
  /* reading is performed */
  sleep(lastTime);
  printf("Thread %d: end reading\n", id);

  pthread_rwlock_unlock( & lock);
  pthread_exit(0);
}

//Writer
void * Writer(void * param) {
  int id = ((struct data * ) param) -> id;
  int lastTime = ((struct data * ) param) -> lastTime;
  int opTime = ((struct data * ) param) -> opTime;
  sleep(opTime);
  printf("Thread %d: waiting to write\n", id);

  pthread_rwlock_wrlock( & lock);

  printf("Thread %d: start writing\n", id);
  /* writing is performed */
  sleep(lastTime);
  printf("Thread %d: end writing\n", id);

  pthread_rwlock_unlock( & lock);
  pthread_exit(0);
}

int main() {
  //pthread
  pthread_t tid; // the thread identifier

  pthread_attr_t attr; //set of thread attributes
  /* get the default attributes */
  pthread_attr_init( & attr);
  /* to be used within this process only */
  pthread_rwlock_init( & lock, NULL);

  readCount = 0;

  int id = 0;
  while (scanf("%d", & id) != EOF) {

    char role; //producer or consumer
    int opTime; //operating time
    int lastTime; //run time

    scanf("%c%d%d", & role, & opTime, & lastTime);
    struct data * d = (struct data * ) malloc(sizeof(struct data));

    d -> id = id;
    d -> opTime = opTime;
    d -> lastTime = lastTime;

    if (role == 'R') {
      printf("Create the %d thread: Reader\n", id);
      pthread_create( & tid, & attr, Reader, d);
    } else if (role == 'W') {
      printf("Create the %d thread: Writer\n", id);
      pthread_create( & tid, & attr, Writer, d);
    }
  }
  pthread_rwlock_destroy( & lock);
  return 0;
}
