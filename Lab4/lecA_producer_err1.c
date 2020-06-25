#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
static int n=10;
static char a[1000]="ABCDEFGHIJKLMNOPQRSTUVXYZ";
const int BUFFER_SIZE = 10;
char buff[10];
int in =0, out=0;

int main() 
{   pid_t pid;
    pid = fork();
    if(pid < 0) printf("Fork error! No child created\n");
    else if(pid == 0)  {
        while(1) {
printf("%d and %d\n", in, out);
		while(in==out);
printf("test2\n");
	   printf("CW: %c ", buff[out]);
		out = (out+1)%BUFFER_SIZE;
	}
    }
    else { 
       printf("Hello from Parent!\n");
       for(int k=0; k<n ; k++){
	while (((in + 1) % BUFFER_SIZE) == out);
printf("test\n");		
buff[in] = a[k];
		in = (in+1) % BUFFER_SIZE;
	}
    }
    wait(NULL);
    return 0; 
}
