// CPP Program to find sum of array 
#include <iostream> 
#include <pthread.h> 
  
// kích thước array 
#define MAX 16    
  
// maximum number of threads 
#define MAX_THREAD 4 
  
using namespace std; 
  
int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };   //Khởi tạo giá trị ngẫu nhiên
int sum[4] = { 0 }; 
int part = 0; 
  
void* sum_array(void* arg) 
{ 
  
    // Part là "đoạn" trong dãy. Ta chia làm 4 đoạn  // Làm sao đánh đoạn tự động tăng từ 1 đến 4 (hay từ 0 đến 3)

    //
    for(int i=         ; i++ ) // xác định giới hạn của đoạn.
    sum[part] += a[i];
      

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
  
    // tổng lại các tổng đoạn
    int total_sum = 0; 
    for () 
        total_sum +=  
  
    cout << "sum is " << total_sum << endl; 
  
  
      t2 = clock(); 
          // time taken by merge sort in seconds 
    cout << "Time taken: " << (t2 - t1) /  
              (double)CLOCKS_PER_SEC << endl; 
    return 0; 
} 
