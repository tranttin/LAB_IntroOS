#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
struct arr{
	int n;
	int a[10];
};


void* thr1(void* ar){
	struct arr *ap = (struct arr*) ar;
	int MAX = ap->a[0];	
	for(int i = 0; i < ap->n; i++ )
		if( MAX < ap->a[i]) MAX = ap->a[i];
	printf("\nMAX = %d", MAX );
}

void* thr2(void* ar){

}

void* thr3 (void* ar){

}

int main (int argc, char * argv[]){
	int i;
	pthread_t tid[3];
	struct arr ar;
	int status, *pstatus= &status;

        // get from argv into array ar
	
	pthread_create(&tid[0],NULL,thr1,(void*) &ar);	
	pthread_create(&tid[1],NULL,thr1,(void*) &ar);
	pthread_create(&tid[2],NULL,thr1,(void*) &ar);

	pthread_join(tid[0],(void**) pstatus);	
	pthread_join(tid[1],(void**) pstatus);
	pthread_join(tid[2],(void**) pstatus);

	return 0;
}
