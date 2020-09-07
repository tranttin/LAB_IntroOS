#include <stdio.h> 
#include <unistd.h> 
int main( /*parameter declare*/) 
{   pid_t pid;
    // reading value of n from parameter
    pid = fork();
    if(pid < 0) printf("Fork error! No child created\n");
    else if(pid == 0)  {
        // calculate all of divisors and output to screen
        
    }
    else { 
       // calculate value S = 1 + 2 + ... + n
       // output to screen.
       // wait for child
    }
    return 0; 
}
