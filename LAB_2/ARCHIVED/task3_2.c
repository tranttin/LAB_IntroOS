// 2021 June 2
// Author: Tran Trung Tin
// Demo using our "libd.a"  CODE THE SAME WITH task3_1.c
#include <stdio.h>

#include <stdlib.h>
int main(int argc, char ** argv) {
  if(argc == 3){
    printf("\nFact %s! = %d", argv[1], fac_n(atoi(argv[1])));
    printf("\nSum %s = %d", argv[2], sum_n(atoi(argv[2])));
  }
  else
    printf("\nNot enough parameters.");
  return 0;
}
