#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

pthread_t tid[2]; 
int counter; 

void* trythis(void *arg) 
{ 
	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for(i=0; i<(0xFFFFFFFF);i++); 
	printf("\n Job %d has finished\n", counter); 

	return NULL; 
} 

int main(void) 
{ 
	int i = 0; 
	int error; 

	while(i < 2) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
		if (error != 0) 
			printf("\nThread can't be created : [%s]", strerror(error)); 
		i++; 
	} 

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 

	return 0; 
} 
