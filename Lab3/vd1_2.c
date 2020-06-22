// P2.c
#include <stdio.h> 
#include <sys/types.h>   
#include <unistd.h> 
int main() 
{   // make two process which run same 
    // program after this instruction 
    // Thêm một vài lệnh printf và theo dõi.
    fork(); 
    // thêm một vài lệnh fork vào đây và xem thay đổi.
    printf("Hello world! from Process ID: %d\n", getpid()); 
    return 0; 
}
