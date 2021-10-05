// 2021 June 2
// Creator: Tran Trung Tin
// Exercise
#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

#include <sys/wait.h>

int main() {
  pid_t pid;
  
  // khai báo biến toàn cục n và biến tổng S
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
    
  } else {
    /* parent process */
    wait(NULL);
    
    // in tổng S ra màn hình.
  }
  return 0;
}
