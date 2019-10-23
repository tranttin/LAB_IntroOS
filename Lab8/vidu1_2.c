#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

pthread_t tid[2]; 
int counter=0; 

void* trythis(void *arg) 
{ 
        counter++;
        sleep(1);
        counter--;

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
	printf("\n Final counter = %d\n", counter);
	return 0; 
} 
