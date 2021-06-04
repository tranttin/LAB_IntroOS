// 2021 June 2
// Author: Abraham Silberschatz  in book Operating System Concepts 10th Edition p.170
// Demo using how to speed up sum of sequence integer.#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 25
int main(VOID) {
  HANDLE ReadHandle;
  CHAR buffer[BUFFER_SIZE];
  DWORD read;
  /* get the read handle of the pipe */
  ReadHandle = GetStdHandle(STD_INPUT_HANDLE);
  /* the child reads from the pipe */
  if (ReadFile(ReadHandle, buffer, BUFFER_SIZE, &read, NULL))
    printf("child read %s", buffer);
  else
    fprintf(stderr, "Error reading from pipe");
  return 0;
}
