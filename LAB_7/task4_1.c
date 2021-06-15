/* 
 * Throughput measurement thread. Sleeps for a while then wakes up and measures
 * the throughput, resetting counters in the process.
 */
void
*measure_thread(void *arg)
{
	int c, i;
	unsigned long long throughput;
        for (c = 1 ;; c++) {
                sleep(1);
                throughput = 0;
                for (i = 0; i < ncounters; i++) {
                        if (counters[i]->c) {

#if defined(SYNC_FETCH_ADD)
                                throughput += \
					__sync_lock_test_and_set(&counters[i]->c, 0);

#elif defined(PTHREAD_SPIN)
				pthread_spin_lock(&counters[i]->spin);
				throughput += counters[i]->c;
				counters[i]->c = 0;
				pthread_spin_unlock(&counters[i]->spin);

#elif defined(PTHREAD_MUTEX)
				pthread_mutex_lock(&counters[i]->mutex);
				throughput += counters[i]->c;
				counters[i]->c = 0;
				pthread_mutex_unlock(&counters[i]->mutex);
#endif
			}
		}
		printf("%lld\n", throughput);
                fflush(stdout);
        }
}
