// P3.c
#include <stdio.h> 
#include <unistd.h> 
int main() 
{   pid_t pid;
    pid = fork();
    if(pid < 0) printf("Fork error! No child created\n");
    else if(pid == 0)  {
        printf("Hello from Child!\n");
        printf("Child ID is %d!\n", getpid());
        sleep(10);
    }
    else { 
       printf("Hello from Parent!\n");
       printf("Parent ID is %d!\n", getppid());

    }
    return 0; 
}
