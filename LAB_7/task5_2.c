// 2021 June 7
// Author: Tran Trung Tin
// Producer / Consumer share count varible. Peterson applied to critical section.
#include <stdio.h>

#include <stdlib.h>

#ifndef __STDC_NO_ATOMICS__

#include <stdatomic.h>

#endif

int main(int argc, char ** argv) {
  _Atomic int a;
  atomic_init( & a, 42);
  atomic_store( & a, 5);
  int b = atomic_load( & a);
  printf("b = %i\n", b);
  return EXIT_SUCCESS;
}
