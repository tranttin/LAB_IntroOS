// CPP Program to find sum of array 
#include <iostream> 
#include <pthread.h> 
#include <cstdlib>
#include <ctime>
  
// kích thước array 
#define MAX 16    
  
// maximum number of threads 
#define MAX_THREAD 4 
#define MAX_POINT 10000
  
using namespace std; 
  
int counter = 0; // tổng số điểm trong vòng tròn
  
void* random(void* arg) 
{ 
  
    // Part là "đoạn" trong dãy. Ta chia làm 4 đoạn  // Làm sao đánh đoạn tự động tăng từ 1 đến 4 (hay từ 0 đến 3)
   for(int i=0; i<MAX_POINT;i++)
   {
   
   // This will generate a number from some arbitrary LO to some arbitrary HI:
   // srand (static_cast <unsigned> (time(0)));
   //float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
   
   // random tọa độ X từ -1 đến 1, 
     // random tọa độ Y từ -1 đến 1,
     // tính khoảng cách (X,Y) đến gốc (0,0)
     // nếu khoảng cách <= 1 thì nó thuộc hình tròn, tăng count.
      

} 
  
// Chương trình chính.
int main() 
{ 
        clock_t t1, t2; 
  
    t1 = clock(); 
    pthread_t threads[MAX_THREAD]; 
  
    // Creating 4 threads 
    for (int i = 0; i <   ; i++) 
        pthread_create(  ); 
  
    // joining 4 threads i.e. waiting for all 4 threads to complete 
    for (int i = 0; i <  ; i++) 
        p 
  
    // tính và in ra giá trị số PI là  count / MAX_POINT * MAX_THREAD

      t2 = clock(); 
          // time taken by merge sort in seconds 
    cout << "Time taken: " << (t2 - t1) /  
              (double)CLOCKS_PER_SEC << endl; 
    return 0; 
} 
