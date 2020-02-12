// P_template.c
#include <stdio.h>
#include <unistd.h>
int main()
{ pid_t pid;
 pid = fork();
 if(pid < 0) printf(“fork error! No child created\n”);
 else if(pid == 0) {//code of parent process }
 else { // code of the new child process }
 return 0;
}
