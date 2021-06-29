#include <pthread.h>

#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include<time.h>

#define PAGE_TABLE_SIZE 256
#define OFFSET 256
#define TLB_SIZE 16
int FRAME_SIZE = 100;
char MEM[PAGE_TABLE_SIZE * OFFSET];

struct PageEntry {
  bool bVaild;
  int iFrame; ////Page p in frame f  is presented by iPage[p] = f
  bool bDirty;
};

struct TLBEntry {
  int iPage;
  int iFrame;
  bool bVaild;
};

struct PageEntry PageTable[PAGE_TABLE_SIZE];
struct TLBEntry TLB[TLB_SIZE];

int CLOCK_TLB = 0;
int CLOCK_PTB = 0;
int iPageFault = 0;

//Declaration function
void fFIFO(int iPage);
void fSwapIn(int iPage, int iMemPosition);
void fSwwapOut(int iPage);

int fTLBLook(int param) {
  for (int i = 0; i < TLB_SIZE; i++)
    if (TLB[i].iPage == param && TLB[i].bVaild == true)
      return TLB[i].iFrame;

  return -1;
}

int fPageTable(int param) {
  usleep(500);
  if (PageTable[param].bVaild == false) return -1;
  return PageTable[param].iFrame;

}

void initalizer(void) {
  for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
    PageTable[i].bVaild = false;
    PageTable[i].bDirty = false;
  }
  for (int i = 0; i < TLB_SIZE; i++) TLB[i].bVaild = false;
}

void fTranslate(int iVirtualAdd) {
  printf("\n@ %5d", iVirtualAdd);
  int iPage = iVirtualAdd / OFFSET;
  int iOffset = iVirtualAdd % OFFSET;

  int iFrame1 = fTLBLook(iPage);
  int iFrame2 = fPageTable(iPage);
  if (iFrame1 != -1) {
    printf(" TLB hit  ");
    int PhysicAdd = iFrame1 * OFFSET + iOffset;
    printf(" Memory 0x%05d, Content = %c ", PhysicAdd, MEM[PhysicAdd]);
    return;
  } else {
    printf(" TLB_miss ");
    if (iFrame2 != -1) { //Page in memory
      int PhysicAdd = iFrame2 * OFFSET + iOffset;
      printf(" Memory 0x%05d, Content = %c ", PhysicAdd, MEM[PhysicAdd]);
      return;
    } else {
      //Page Fault
      printf(" Page_fault ");
      iPageFault++;
      fFIFO(iPage);

      //Restart
      fTranslate(iVirtualAdd);
    }
  }

}
void fSwapIn(int iPage, int iMemPosition) {
  FILE * fp;
  char str[OFFSET];
  if ((fp = fopen("BACKINGSTORE.bin", "r")) == NULL) {
    printf("\nCannot open file.\n");
    return;
  }
  fseek(fp, iPage * OFFSET, SEEK_SET);
  fgets(str, OFFSET, fp);
  for (int i = 0; i < OFFSET; i++) MEM[iMemPosition + i] = str[i];
  fclose(fp);

}
void fSwapOut(int param) {}
void fFIFO(int iPage) {
  printf(" Victim=%d ", CLOCK_PTB);

  for (int i = 0; i < PAGE_TABLE_SIZE; i++)
    if (PageTable[i].iFrame == CLOCK_PTB) PageTable[i].bVaild = false; //Clear Victim from Page Table
  for (int i = 0; i < TLB_SIZE; i++)
    if (TLB[i].iFrame == CLOCK_PTB) TLB[i].bVaild = false; //Clear Victim from TLB

  if (PageTable[iPage].bDirty == true) fSwapOut(iPage); //Swap out if the victim page has been modified

  PageTable[iPage].iFrame = CLOCK_PTB; //CLOCK_PTB is the frame
  PageTable[iPage].bVaild = true;
  PageTable[iPage].bDirty = false;

  fSwapIn(iPage, CLOCK_PTB * OFFSET);

  TLB[CLOCK_TLB].bVaild = true;
  TLB[CLOCK_TLB].iFrame = CLOCK_PTB;
  TLB[CLOCK_TLB].iPage = iPage;

  CLOCK_PTB = (CLOCK_PTB + 1) % FRAME_SIZE;
  CLOCK_TLB = (CLOCK_TLB + 1) % TLB_SIZE;

}
void fLRU(int iPage) {}
void fSecondChane(int iPage) {}

int main(int argc, char * argv[]) {
  FRAME_SIZE = atoi(argv[2]);
  int SEQ = atoi(argv[1]);
  if (SEQ > 0) {

    int LogicMem[SEQ];
    // Use current time as seed for random generator
    srand(time(0));
    initalizer();
    for (int i = 0; i < SEQ; i++) LogicMem[i] = rand() % 65536;

    for (int i = 0; i < SEQ; i++) fTranslate(LogicMem[i]);
    printf("\nOverall PageFault Rate = %f\n", iPageFault * 1.0 / SEQ);
  } else {
    FILE * fp;
    int SEQ = 0;
    int LogicMem[1000];
    if ((fp = fopen("data.txt", "r")) == NULL) {
      printf("\nCannot open file.\n");
      return 0;
    }
    while (!feof(fp)) {
      fscanf(fp, "%d", & LogicMem[SEQ]);
      SEQ++;
    }

    fclose(fp);
    for (int i = 0; i < SEQ - 1; i++) fTranslate(LogicMem[i]);
    printf("\n\nOverall Page Fault Rate = %f\n", iPageFault * 1.0 / SEQ);

  }

  return 0;
}
