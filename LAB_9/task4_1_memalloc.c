// 2021 June 20
// Author: Tran Trung Tin
// Demo of Continuous Allocation in Memory
#include <pthread.h>

#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

struct hole {
  int iPID; //-1 unused
  int iBase;
  int iSize;
  char sName[20];
};
struct hole M[100];
int iHoleCount = 0;
int iPIDcount = 1000;
pthread_t tid[5];

void * fAllocation(void * param) {
  int iSizeNew;
  printf("\nSize of process: ");
  scanf("%d", & iSizeNew);

  for (int i = 0; i < iHoleCount; i++) {
    if (M[i].iPID == -1) {
      if (M[i].iSize < iSizeNew) continue;
      if (M[i].iSize == iSizeNew) {
        // allocate to replace this hole, no new hole left.
        M[i].iPID = iPIDcount++;
        //M[i].iBase and   iSize no change
        printf("\nNew process allocated PID = %d from %d to %d\n", M[i].iPID, M[i].iBase, M[i].iBase + M[i].iSize - 1);
        return 0;
      } 
      else if (M[i].iSize > iSizeNew) { // allocate to this hole, but left a new smaller hole 
        iHoleCount++;
        for (int j = iHoleCount; j > i + 1; j--) M[j] = M[j - 1]; //shift right all hole to make new hole.
        M[i + 1].iPID = -1;
        M[i + 1].iSize = M[i].iSize - iSizeNew;
        M[i + 1].iBase = M[i].iBase + iSizeNew;
        M[i].iPID = iPIDcount++;
        //M[i].iBase no change;
        M[i].iSize = iSizeNew;
        printf("\nNew process allocated PID = %d from %d to %d", M[i].iPID, M[i].iBase, M[i].iBase + M[i].iSize - 1);
        printf("\nNew hole left over from %d to %d\n", M[i + 1].iBase, M[i + 1].iBase + M[i + 1].iSize - 1);
        return 0;
      }
    } // end of hole found
  } // end of for
  printf("\nFailure to allocate memory.\n");  // no hole fit
}

void * fTerminate(void * param) {
  int iTerminated;
  printf("\nWhich PID terminate? ");
  scanf("%d", & iTerminated);
  for (int i = 0; i < iHoleCount; i++) {
    if (iTerminated == M[i].iPID) {
      M[i].iPID = -1;
      printf("\nProcess %d has been removed. Memory from %d to %d is free.", M[i].iPID, M[i].iBase, M[i].iBase + M[i].iSize - 1);
      return 0;
    }
  }
  printf("Process %d cannot be found.", iTerminated);
  return 0;
}

void * fCompact(void * param) {}

void * fStatic(void * param) {
  printf("\nStatic of memory \n");
  for (int i = 0; i < iHoleCount; i++) {
    if (M[i].iPID == -1)
      printf("Address [%d : %d]: Unused\n", M[i].iBase, M[i].iBase + M[i].iSize - 1);
    else printf("Address [%d : %d]: ProcessID %d\n", M[i].iBase, M[i].iBase + M[i].iSize - 1, M[i].iPID);
  }
}

int main(int argc, char * argv[]) {
  int iOption; //Chon lua trong menu	
  M[iHoleCount].iSize = atoi(argv[1]); // truyền kích thước vào khi gọi chạy   
  M[iHoleCount].iPID = -1;
  M[iHoleCount].iBase = 0; // start of memory
  iHoleCount=1;
  while (true) {
    printf("\nChon option:   1-Cap phat   2-Thu hoi   3-Gom cum   4-Thong ke  5-Thoat  \n");
    scanf("%d", & iOption);
    switch (iOption) {
    case 1:
      pthread_create( & tid[1], NULL, fAllocation, NULL);
      pthread_join(tid[1], NULL);
      break;
    case 2:
      pthread_create( & tid[2], NULL, fTerminate, NULL);
      pthread_join(tid[2], NULL);
      break;
    case 3:
      pthread_create( & tid[3], NULL, fCompact, NULL);
      pthread_join(tid[3], NULL);
      break;
    case 4:
      pthread_create( & tid[4], NULL, fStatic, NULL);
      pthread_join(tid[4], NULL);
      break;
    case 5:
      return 0;
    default:
      printf("\nVui long chon 1 - 5.\n");
    }
  }
}
