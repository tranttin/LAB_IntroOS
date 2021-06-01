#include <stdio.h>

#include <windows.h>

#define BUFFER SIZE 25
int main(VOID) {
  HANDLE Readhandle;
  CHAR buffer[BUFFER SIZE];
  DWORD read;
  /* get the read handle of the pipe */
  ReadHandle = GetStdHandle(STD INPUT HANDLE);
  /* the child reads from the pipe */
  if (ReadFile(ReadHandle, buffer, BUFFER SIZE, & read, NULL))
    printf("child read %s", buffer);
  else
    fprintf(stderr, "Error reading from pipe");
  return 0;
}
