
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

#define NUM_THREADS 100

void* thread_function(void*);
long get_thread_time();

int main(int argc, char** argv) {
	int i;
	time_t start1, end1;
	struct timeval start2, end2;
	/* array pthreads_t */
	pthread_t threads[NUM_THREADS];

	/* ### start section to be measured ### */
	/* clock() method */
	start1 = clock();
	/* gettimeofday() method */
	gettimeofday(&start2, NULL);

	/* create and start threads */
	for(i=0; i<NUM_THREADS; i++) {
		pthread_create(&threads[i], NULL, &thread_function, NULL);
	}

	/* wait for threads end */
	for(i=0; i<NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	end1 = clock();
	gettimeofday(&end2, NULL);
	/* ### end of section to be measured ### */

	printf(" clock() method: %ldms\n", (end1 - start1) / (CLOCKS_PER_SEC/1000));
	printf(" gettimeofday() method: %ldms\n", (end2.tv_sec - start2.tv_sec) *1000 + (end2.tv_usec - start2.tv_usec)/1000);

	return 0;
}

void* thread_function(void* arg) {
	int i;
	double a = 0;
	long start, end;

	start = get_thread_time();

	for(i=0; i<500000000; i++) {
		a +=a;
	}

	end = get_thread_time();

	printf(" get_thread_time() method: %ld jiffies\n", (end - start));
	pthread_exit(NULL);
}



pid_t gettid( void )
{
	return syscall( __NR_gettid );
}


long get_thread_time()
{
	int i;
	char proc_filename[256] ;
	char buffer[1024] ;

	pid_t pid = getpid() ;
	pid_t tid = gettid() ;

	sprintf(proc_filename, "/proc/%d/task/%d/stat",pid,tid) ;
	int fd, num_read ;
	fd = open(proc_filename, O_RDONLY, 0);
	num_read = read(fd, buffer, 1023);
	close(fd);
	buffer[num_read] = '\0';

	char* ptr_usr = strrchr(buffer, ')') + 1 ;
	for(i = 3 ; i != 14 ; ++i) {
		ptr_usr = strchr(ptr_usr+1, ' ');
	}

	ptr_usr++;
	long jiffies_user = atol(ptr_usr) ;
	long jiffies_sys = atol(strchr(ptr_usr,' ') + 1) ;

	return jiffies_user ;
}
