#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
void* thr1(void* ar){
	int count;
	printf("this is thread %d\n",*((int*)ar));
	sleep(2);
}
int main (int argc, char* argv[]){
	int i;
	pthread_t tid[3];
	int status, *pstatus = &status;
	for(i=0;i<3;i++)
		pthread_create(&tid[i],NULL,thr1,(void*) &tid[i]);
	for(i=0;i<3;i++){
		if(pthread_join(tid[i],(void**) pstatus)>0){
			printf("pthread_join for thread %d failure\n", (int)tid[i]);
		}
	printf("pthread_waited of %d OK, return code: %d\n", (int)tid[i], status);
	sleep(1);
	}
	sleep(1);
return 0;
}

