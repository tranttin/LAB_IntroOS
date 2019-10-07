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
	int count;
	struct arr *ap=(struct arr*) ar;
	for(count=0;count<ap->n; count++)
		printf("%d\t",ap->a[count]);
	printf("\n");
}

int main(int argc, char* argv[]){
	struct arr ar;
	ar.n=5;
	int i;
	for(i=0;i<ar.n;i++)
		ar.a[i]=i+1;
	pthread_t tid;
	pthread_create(&tid,NULL,&thr1,&ar);
	sleep(2);
	return 0;
}
