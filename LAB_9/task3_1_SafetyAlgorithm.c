// 2021 Jun 14
// Author :Tran Trung Tin
// Banker's Algorithm
#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    { 7, 5, 3  }, // P0 // MAX Matrix
    { 3, 2, 2  }, // P1
    { 9, 0, 2  }, // P2
    { 2, 2, 2  }, // P3
    { 4, 3, 3  }   }; // P4

/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES] = {
    { 0, 1, 0  }, // P0 // Allocation Matrix
    { 2, 0, 0  }, // P1
    { 3, 0, 2  }, // P2
    { 2, 1, 1  }, // P3
    { 0, 0, 2  }   }; // P4

/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int safety_algorithm(int * available);

int main(int argc, char ** argv) {
  // 
  if (argc < NUMBER_OF_RESOURCES + 1) {
    printf("Not enough param.\n");
    return -1;
  } else {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) available[i] = atoi(argv[i + 1]);
  }
  safety_algorithm(available);
  return 0;
}

int safety_algorithm(int * available) {
  int i, j, k;
  int ans[NUMBER_OF_CUSTOMERS], ind = 0;
  bool Finish[NUMBER_OF_CUSTOMERS] = {  false  };
  int work[NUMBER_OF_CUSTOMERS];
  //STEP 1
  for (i = 0; i < NUMBER_OF_RESOURCES; i++) work[i] = * (available + i);

  for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
      need[i][j] = maximum[i][j] - allocation[i][j];
  }
  
  //STEP 2
  int y = 0;
  for (k = 0; k < NUMBER_OF_CUSTOMERS; k++) {
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
      if (Finish[i] == false) {

        int flag = 0;
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
          if (need[i][j] > work[j]) {
            flag = 1;
            break;
          }
        }
        if (flag == 0) {  //STEP 3
          ans[ind++] = i;
          for (y = 0; y < NUMBER_OF_RESOURCES; y++)
            work[y] += allocation[i][y];
          Finish[i] = true;
        }
      }
    }
  }
  //STEP 4
  bool bSafe = true;
  for (i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    if (Finish[i] == false) bSafe = false;
  if (bSafe) {
    printf("Following is the SAFE Sequence: ");
    for (i = 0; i < NUMBER_OF_CUSTOMERS - 1; i++)
      printf(" P%d ->", ans[i]);
    printf(" P%d.\n", ans[NUMBER_OF_CUSTOMERS - 1]);
    return (0);
  } else {
    printf("The system is UNSAFE.\n");
    return -1;
  }
}
