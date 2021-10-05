// 2021 June 2
// Creator: Tran Trung Tin
// Demo using system call fork to create a child process which execute command ls by execlp.
#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

#include <sys/wait.h>

int main() {
  pid_t pid;
  
  // Khai báo biến n toàn cục
  // Nhận n từ lời gọi 
  
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) {
    /* child process */
    //Vòng lặp tính và in ra dãy Collatz
    //trong khi mà n > 0
      // nếu n chẵn thì .....
      // nếu n lẻ thì ......
      // in ra n
  } else {
    /* parent process */
    // Đơn giản là chỉ đứng chờ con:
    wait(NULL);
    
  }
  return 0;
}
