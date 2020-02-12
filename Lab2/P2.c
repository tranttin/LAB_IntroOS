// P2.c
#include <stdio.h>
#include <sys/types.h> //Có thể không cần thiết
#include <unistd.h>
int main()
{ // make two process which run same
 // program after this instruction
 fork();
 printf("Hello world!\n");
 return 0;
}
