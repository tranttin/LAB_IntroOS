/* Cấu trúc chương trình

Dữ liệu:
- Mảng toàn cục chứa 1 triệu phần tử nguyên.
- Biến số Balance toàn cục.

main()
- Sinh ngẫu nhiên giá trị 1000 phần từ cho mảng. Mỗi giá trị nếu là âm thì coi như rút tiền, nếu là dương thì coi như nộp tiền vào tài khoản.
- Tỉnh tổng các giá trị của toàn bộ phần tử mảng. Đây cũng là giá trị số dư tài khoản sau cùng. (1)
- Sinh ra 2 thread gọi 2 hàm deposit và withdraw.
- Chờ thread kết thúc, so sánh giá trị Balance và Giá trị tính tại (1).
- Đo thời gian chạy chương trình từ lúc sinh thread đến khi thread kết thúc.

deposit()
- Nếu phần tử mảng có giá trị dương thì tác động nộp tiền vào biến Balance toàn cục.

withdraw()
- Nếu phần tử mảng có giá trị âm thì tác động rút tiền từ biến Balance toàn cục.



 Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, không tiến hành đồng bộ, đo thời gian.
2 - SV sử dụng mutex lock để đồng bộ và đo thời gian.
3 - SV sử dụng semaphore để đồng bộ và đo thời gian.
4 - SV dùng các biện pháp đồng bộ khác (có thể tự đề xuất) và đo thời gian.
*/
