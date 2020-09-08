
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



int main(int argc, char** argv) {
	int i;
	time_t start1, end1;
	struct timeval start2, end2;


	/* ### start section to be measured ### */
	/* clock() method */
	start1 = clock();
	/* gettimeofday() method */
	gettimeofday(&start2, NULL);

// cv can do

	end1 = clock();
	gettimeofday(&end2, NULL);
	/* ### end of section to be measured ### */

	printf(" clock() method: %ldms\n", (end1 - start1) / (CLOCKS_PER_SEC/1000));
	printf(" gettimeofday() method: %ldms\n", (end2.tv_sec - start2.tv_sec) *1000 + (end2.tv_usec - start2.tv_usec)/1000);

	return 0;
}

