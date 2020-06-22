// A C program to demonstrate ignoring 
// SIGCHLD signal to prevent Zombie processes 
#include<stdio.h> 
#include<unistd.h> 
#include<sys/wait.h> 
#include<sys/types.h> 

int main() 
{ 
	int i; 
	int pid = fork(); 
	if (pid == 0) 
		for (i=0; i<20; i++) 
			printf("I am Child\n"); 
	else
	{ 
		signal(SIGCHLD,SIG_IGN); 
		printf("I am Parent\n"); 
		while(1); 
	} 
}
