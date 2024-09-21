// 2021 June 2
// Creator: Tran Trung Tin
// Demo orphan process, parent exit right after fork, the child live more 30s.
#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	// Create a child process	 
	int pid = fork(); 

	if (pid > 0) 
		printf("in parent process"); 

	// Note that pid is 0 in child process 
	// and negative if fork() fails 
	else if (pid == 0) 
	{ 
		sleep(30); 
		printf("in child process"); 
	} 

	return 0; 
} 
