
bool mem[1000000000]; //maximum of int
struct process { name, int start, int end }
array of struct process;

int option=1;

void function1()
      hỏi kích thước tiến trình cần cấp bao nhiêu? name, size.
      for i = 0 --> MAX-size
         if (mem[i] = false) then "mem[i] đến mem[i+size-1]" có trống hay không/có đều là false hay không. Nếu có thì cấp phát: gán toàn bộ mem[i] đoạn đó là true. Đồng thời ghi nhận lại "Tiến trình X đã được cấp mem từ i đến ..."
               
      Sau khi vòng lặp kết thúc vẫn không cấp được thì trả lời là không cấp được.
               
               
void function2()
      kiểm tra xem tiến trình X được cấp trong đoạn bộ nhớ i đến j nào, 
      for (k=i to j) mem[k]= false;  //coi như vùng nhớ này trống trở lại
     xóa thông tin "Tiến trình X đã được cấp mem từ i đến ..." ra khỏi danh mục (vì X coi như đã kết thúc)

void function3()
     CÁCH 1  for(i = 0 --> max)
             if(a[i] = false) then 
                  1. TÌM a[j] true tiếp theo
                  2. Dò danh sách xem a[j] là start của tiến trình nào --> xác định size.
                   3. Dòi mảng a[i] đến a[i+size-1] là true
                   4. Mảng a[i+size] đến a[j+size-1] sẽ là false (do bị dời nên thành trống).
                   5. Update start và end của tiến trình này/
                   
            
void function4()
               
     Cách 1:  for i = 0 --> MAX
         if (mem[i] = false) thì dò tiếp mem i++ cho đến khi gặp mem[j] là true. Print "Memory free from i to j-1" rồi tiếp tục dò.

     Cách 2: In ra danh mục "Tiến trình X đã được cấp mem từ i đến ..."
           
           
main(    ) // hàm chính
MAX = atoi(argv[1]);  // truyền kích thước vào khi gọi chạy 

for(0 --> MAX - 1)   mem[i] = false //ban đầu bộ nhớ coi như trống hết.


while(true)
{     print "Chọn option   1-Cap phat   2-Thu hoi   3-Gom cum   4-Thong ke  5-Exit"
      scanf   option
      switch (option) of
      1  tạo tiểu trình A chạy hàm fun 1
      
      
      2  tạo tiểu trình B chạy hàm fun 2
      
      
      
      3  tạo tiểu trình C chạy hàm fun 3
      
      
      
      4  tạo tiểu trình D chạy hàm fun 4

            
            
      5: return. //thoát
      






}
