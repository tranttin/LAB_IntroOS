void* thread_func() {
  int i = 0;
  long long prev = 0;
  long long sum = 0;

  for (i = 0; i < num_iterations; i++) {
    switch (opt_sync) {
      case 'c':
        do {
          prev = counter;
          sum = prev + 1;
          if (opt_yield) {
            pthread_yield();
          }
        } while (__sync_val_compare_and_swap(&counter, prev, sum) != prev);
        break;
      case 'm':
        pthread_mutex_lock(&add_mutex);
        add(&counter, 1);
        pthread_mutex_unlock(&add_mutex);
        break;
      case 's':
        while (__sync_lock_test_and_set(&add_spin, 1));
        add(&counter, 1);
        __sync_lock_release(&add_spin);
        break;
      default:
        add(&counter, 1);
        break;
    }
  }

  for (i = 0; i < num_iterations; i++) {
    switch (opt_sync) {
      case 'c':
        do {
          prev = counter;
          sum = prev - 1;
          if (opt_yield) {
            pthread_yield();
          }
        } while (__sync_val_compare_and_swap(&counter, prev, sum) != prev);
        break;
      case 'm':
        pthread_mutex_lock(&add_mutex);
        add(&counter, -1);
        pthread_mutex_unlock(&add_mutex);
        break;
      case 's':
        while (__sync_lock_test_and_set(&add_spin, 1));
        add(&counter, -1);
        __sync_lock_release(&add_spin);
        break;
      default:
        add(&counter, -1);
        break;  
    }
  }
  return NULL;
}
