// P3.c
#include <stdio.h> 
#include <unistd.h> 
#include <sys/prctl.h>   //Name PR_SET_NAME
int main() 
{   pid_t pid;
    const char * name = "A";
    if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");
    printf("Hello from Parent!\n");
    printf("Parent ID is %d!\n", getppid());
	sleep(10);
    pid = fork();
    if(pid < 0) printf("Fork error! No child created\n");
    else if(pid == 0)  {
	const char * name = "B";
	if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");

        printf("Hello from Child!\n");
        printf("Child ID is %d!\n", getpid());
        sleep(10);
    }
    else { 
	const char * name = "C";
	if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");
       printf("Hello from Parent!\n");
       printf("Parent ID is %d!\n", getppid());
	pid = fork();
    	if(pid < 0) printf("Fork error! No child created\n");
   	 else if(pid == 0) {
		const char * name = "H";
		if (prctl(PR_SET_NAME, (unsigned long) name) < 0) perror("prctl()");
		sleep(10);
		}

	sleep(10);
    }

    return 0; 
}
