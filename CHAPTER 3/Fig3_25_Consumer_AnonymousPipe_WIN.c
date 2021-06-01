#include <stdio.h>

#include <windows.h>

#define BUFFER_SIZE 25
int main(VOID) {
  HANDLE Readhandle;
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
