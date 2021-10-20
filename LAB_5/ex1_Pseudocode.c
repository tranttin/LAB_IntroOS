// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 10th Edition p.170
// Demo using ordinary pipe
#include <sys/types.h>

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
int main(void) {
  int fd[2];   // Đường ống gửi đi
               // Đường ống nhận về
  pid_t pid;
  int giaithua;  // khai báo biến chứa giá trị giai thừa
  /* create the pipe */
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
                // Khởi tạo đường ống thứ hai, đặt tên là fe (tên khác cũng được)
  /* fork a child process */
  pid = fork();
  if (pid < 0) {
    /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  if (pid > 0) {
    /* parent process */
    // Gửi chuỗi kí số n vào đường ống thứ nhất fd
    // write_msg sẽ thay bằng ???
    /* close the unused end of the pipe */
    close(fd[READ_END]);
    /* write to the pipe */
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    /* close the write end of the pipe */
    close(fd[WRITE_END]);
    // chờ 1 giây cho tiến trình con xử lý.
    // đọc đường ống thứ hai fe
    // read(......., &giaithua, sizeof(giaithua));
    // in n! ra màn hình
    // chờ đợi con kết thúc
    
  } else {
    /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE_END]);
    /* read from the pipe */
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("read %s", read_msg);
    /* close the read end of the pipe */
    close(fd[READ_END]);
    // chuyển chuỗi nhận thành giá trị số.
    // tính giá trị n!
    // gửi giá trị n! đã tính vào đường ống thứ hai fe
    // write(......., &giaithua, sizeof(giaithua));
    // kết thúc con.
  }
  return 0;
}
