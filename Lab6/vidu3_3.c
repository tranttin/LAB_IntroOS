#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 5

int main(int argc, char* argv[])
{
   FILE *fin;
   char buffer[PIPE_BUF], proj='A';
   int i, n, mid[MAX];
   key_t key;
   for(i=0; i<MAX; i++, proj++) {
      key = ftok(".", proj);
      if((mid[i]=msgget(key, IPC_CREAT | 0666))==-1){
         perror("Queue created.\n");
         return 1;
      }
   }
   fin=popen("ipcs","r");
   while((n=read(fileno(fin), buffer, PIPE_BUF))>0)
      write(fileno(stdout), buffer, n);
   pclose(fin);
   for(i=0; i<MAX; i++)
      msgctl(mid[i], IPC_RMID, (struct msqid_ds *)0);
   return 0;
}
