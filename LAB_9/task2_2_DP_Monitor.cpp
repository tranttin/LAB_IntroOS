//2021 Jun 20
//Submitted by : Ashutosh Soni  // Edit by Tran Trung Tin for comparasion with previous method.
// Header file include
#include <bits/stdc++.h>

#include <pthread.h>

#include <unistd.h>

using namespace std;

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT(phnum + 4) % N
#define RIGHT(phnum + 1) % N

// Philosopher index
int phil[N];
int times = 200;

class monitor {

  // state of the philosopher
  int state[N];

  // Philosopher condition variable
  pthread_cond_t phcond[N];

  // mutex variable for synchronization
  pthread_mutex_t condLock;

  public:
    // Test for the desired condtion
    // i.e. Left and Right philosopher are not reading
    void test(int phnum) {

      if (state[(phnum + 1) % 5] != EATING and state[(phnum + 4) % 5] != EATING and state[phnum] == HUNGRY) {
        cout << "Philospher " << phnum << " takes fork " << phnum << " and " << (phnum + 1) % 5 << endl;

        state[phnum] = EATING;

        pthread_cond_signal( & phcond[phnum]);
      }
    }

  // Take Fork function
  void take_fork(int phnum) {

    pthread_mutex_lock( & condLock);

    // Indicates it is hungry

    state[phnum] = HUNGRY;
    cout << "Philospher " << phnum << " is hungry ..." <<
      endl;
    // test for condition
    test(phnum);

    // If unable to eat.. wait for the signal
    if (state[phnum] != EATING) {
      pthread_cond_wait( & phcond[phnum], & condLock);
    }
    cout << "Philospher " << phnum << " is Eating" <<
      endl;

    pthread_mutex_unlock( & condLock);
  }

  // Put Fork function
  void put_fork(int phnum) {

    pthread_mutex_lock( & condLock);

    // Indicates that I am thinking
    state[phnum] = THINKING;

    test(RIGHT);
    test(LEFT);

    pthread_mutex_unlock( & condLock);
  }

  // constructor
  monitor() {

      for (int i = 0; i < N; i++) {
        state[i] = THINKING;
      }

      for (int i = 0; i < N; i++) {
        pthread_cond_init( & phcond[i], NULL);
      }

      pthread_mutex_init( & condLock, NULL);
    }

    // destructor
    ~monitor() {

      for (int i = 0; i < N; i++) {
        pthread_cond_destroy( & phcond[i]);
      }

      pthread_mutex_destroy( & condLock);
    }
}

// Global Object of the monitor
phil_object;

void * philospher(void * arg) {
  int c = 0;
  while (c < times) {
    int i = * (int * ) arg;
    cout << "Philospher " << i << " is thinking..." <<
      endl;
    sleep(1);
    phil_object.take_fork(i);
    sleep(0.5);
    phil_object.put_fork(i);
    c++;
  }
}

int main() {

  // Declaration...
  pthread_t thread_id[N];
  pthread_attr_t attr;

  // Initialization...
  pthread_attr_init( & attr);
  pthread_attr_setdetachstate( & attr,
    PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < N; i++) {
    phil[i] = i;
  }

  // Creating...
  for (int i = 0; i < N; i++) {
    pthread_create( & thread_id[i], & attr, philospher, &
      phil[i]);

  }

  // Joining....
  for (int i = 0; i < N; i++) {
    pthread_join(thread_id[i], NULL);
  }

  // Destroying
  pthread_attr_destroy( & attr);
  pthread_exit(NULL);

  return 0;
}
