#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int pnum, count, retval, child_no;
    pnum = atoi(argv[1]);
    if(pnum <= 0) {
        printf("So tien trinh con phai lon hon 0");
        return -1;
    }
    else {
        retval=1;
        for(count=0; count<pnum; count++) {
            if(retval!=0) retval=fork();
            else break;
        }
        if(retval == 0) {
            child_no = count;
            printf("Tien trinh %d, PID %d\n",child_no, getpid());
        } else {
        for(count=0; count<pnum; count++) wait(NULL);   //số lần gọi wait bằng số đứa con đã sinh ra (là pnum)
        printf("Tien trinh cha PID %d", getppid());
        }
    }

    return 0;
} 
