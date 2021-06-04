// 2021 June 2
// Creator: Tran Trung Tin
// Demo zoombie process, the child exit but parent doesn't know.
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	// Fork returns process id 
	// in parent process 
	pid_t child_pid = fork(); 

	// Parent process 
	if (child_pid > 0) 
		sleep(50); 

	// Child process 
	else		
		exit(0); 

	return 0; 
} 
