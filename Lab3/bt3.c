#include <stdio.h> 
#include <unistd.h> 
int main() 
{   pid_t pid;
    pid = fork();
    if(pid < 0) printf("Fork error! No child created\n");
    else if(pid > 0)  {
        printf("A\n");
        printf("My ID is %d! and my parent is %d\n", getpid(), getppid());
	// pid = fork()
        // SV hoan tat nhanh trai cua cay
	//while(1);
    }
    else { 
	pid = fork();
	if(pid < 0) printf("Fork error! No child created\n");
	else if(pid > 0) {
	printf("C\n");
        printf("My ID is %d! and my parent is %d\n", getpid(), getppid());
	//while(1);
	}
        else  {
		printf("H\n");
        	printf("My ID is %d! and my parent is %d\n", getpid(), getppid());
	}
    }
    return 0; 
}
