#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char* argv[])
{
   key_t key;  char i;
   for(i='a'; i<'e'; i++) {
      key = ftok(".", i);
      printf("Proj = %c key = %d.\n", i, key);
   } 
   return 0;
}
