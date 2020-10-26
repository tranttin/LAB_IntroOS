#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
bool mem[1000000000]; //maximum of int
int option=1;
int MAX;
pthread_t tid[4];
void function1() {
	int size;
	printf("Size: ");
	scanf("%d", &size);
        bool flag = false;
	for(int i = 0; i < MAX - size; i++) {
		if(mem[i] == false) {
			
			for(int j = i; j < i + size - 1; j++) {
				if(mem[j] == true) {
				      flag = true; break;
				}  
			}

			if (flag == false) {
				for(int j = i; j < i + size; j++) 
					mem[j] = true;
				
				printf("Cap phat duoc tu %d den %d\n", i, i+size-1); return;	
			//them 1 struct : name start --> end


}
		}  
	}
	


printf("Khong cap phat duoc");

}

/*              
void function2()
void function3()
void function4()
               
      for i = 0 --> MAX
         if (mem[i] = false) thì dò tiếp mem i++ cho đến khi gặp mem[j] là true. Print "Memory free from i to j-1" rồi tiếp tục dò. */


int main(int argc, char* argv[]) {
	MAX = atoi(argv[1]);  // truyền kích thước vào khi gọi chạy 
       
	for(int i = 0; i < MAX - 1; i++) {
		mem[i] = false;
	}

	while(option != 5) {     
		printf("Chon option:   1-Cap phat   2-Thu hoi   3-Gom cum   4-Thong ke");
		scanf("%d", &option);
      		switch (option) {
      		case 1: 
			
      			pthread_create(&tid[1],NULL,function1, NULL);
			pthread_join(tid[1],NULL);
			break;
      		//case 2:  tạo tiểu trình B chạy hàm fun 2
      
      
      
      		//case 3:  tạo tiểu trình C chạy hàm fun 3
      
      
      
      		//case 4:  tạo tiểu trình D chạy hàm fun 4

            
            
      		case 5: 
			return 0;
		}
      }
}
