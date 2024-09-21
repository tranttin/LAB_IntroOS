// 2021 June 2
// Creator: Tran Trung Tin
// Exercise
#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

#include <sys/wait.h>

int main() {
  pid_t pid;
  
  // khai báo biến toàn cục n
  // lấy giá trị n vào từ lời gọi
  
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) {
    /* child process */
    
    // vòng lặp tính tổng S
    // in ra S
    
  } else {
    /* parent process */
    // tính ước số 
    // in ra
    
    wait(NULL);
    
    
  }
  return 0;
}
