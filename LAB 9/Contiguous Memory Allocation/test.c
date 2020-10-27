#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool mem[1000000000]; //maximum of int
struct process {
	int iPid;
	int iBase;
	int iSize;
};
struct process P[100];
int iProcessCount = 0;
int iProcessID = 0;
int MAX;
pthread_t tid[4];


void function1() {
	int iSize;
	printf("\nSize of process: ");
	scanf("%d", &iSize);
        
	for(int i = 0; i < MAX - iSize; i++) {
		if(mem[i] == false) {
			bool bFlag = false;
			for(int j = i; j < i + iSize - 1; j++) {
				if(mem[j] == true) {
				      bFlag = true; i+= j; break;
				}  
			}

			if (bFlag == false) {
				for(int j = i; j < i + iSize; j++) 
					mem[j] = true;
				
				
			P[iProcessCount].iPid = ++iProcessID;
			P[iProcessCount].iBase = i;
			P[iProcessCount].iSize = iSize;
printf("New process allocated Pid = %d from %d to %d\n", P[iProcessCount].iPid, P[iProcessCount].iBase, P[iProcessCount].iBase + P[iProcessCount].iSize-1); 	
			iProcessCount++;
return;

			}
		}  
	}
	


printf("Khong cap phat duoc");

}

void function2(){
	function4();
	int iTerminated;
	printf("\nWhich Pid terminate? ");
	scanf("%d",&iTerminated);
 	for(int i = 0; i < iProcessCount; i++) {
		if(iTerminated == P[i].iPid)
			{ 
			printf("\nProcess %d has been removed. Memory from %d to %d is free.", P[i].iPid, P[i].iBase , P[i].iBase + P[i].iSize - 1);
			for(int j=i ; j< iProcessCount ; j++)
				P[i] = P[i+1];
			iProcessCount--;
			for(int k=P[i].iBase ; k<P[i].iBase + P[i].iSize; k++) mem[k] = false; return;
		}
	}

	printf("Process %d cannot be found.", iTerminated);




}       
       
void function4(){

	printf("\nList of %drunning process: \n", iProcessCount);
	
	for(int i = 0; i < iProcessCount; i++) {
		printf("Process %d allocated from %d to %d\n", P[i].iPid, P[i].iBase, P[i].iBase + P[i].iSize - 1);
	}

}

/*void function3()
void function4()
               
      for i = 0 --> MAX
         if (mem[i] = false) thì dò tiếp mem i++ cho đến khi gặp mem[j] là true. Print "Memory free from i to j-1" rồi tiếp tục dò. */


int main(int argc, char* argv[]) {
	int iOption; //Chon lua trong menu	
	MAX = atoi(argv[1]);  // truyền kích thước vào khi gọi chạy 
       
	for(int i = 0; i < MAX - 1; i++) {
		mem[i] = false;
	}

	for(int i = 100; i < 200; i++) {
		mem[i] = true;
	}
	while(true) {     
		printf("Chon option:   1-Cap phat   2-Thu hoi   3-Gom cum   4-Thong ke  5-Thoat  \n");
		scanf("%d", &iOption);
      		switch (iOption) {
      		case 1: 
			
      			pthread_create(&tid[1],NULL,function1, NULL);
			pthread_join(tid[1],NULL);
			break;
      		case 2:  pthread_create(&tid[2],NULL,function2, NULL);
			pthread_join(tid[2],NULL);
			break;
      
      		//case 3:  tạo tiểu trình C chạy hàm fun 3
      
      
      
      		case 4:  	pthread_create(&tid[3],NULL,function4, NULL);
			pthread_join(tid[3],NULL);
			break;
            
      		case 5: 
			return 0;
		}
      }
}
