/* Cấu trúc chương trình
Dữ liệu:
- Mảng toàn cục chứa 1 triệu phần tử nguyên.
- Biến số Index kiểm soát phần tử ở đỉnh Stack.

main()
- Sinh ngẫu nhiên giá trị cho mọi phần từ cho mảng. Mỗi giá trị nếu là âm thì coi như POP, nếu là dương thì coi như là PUSH.
- Sinh ra 2 thread gọi 2 hàm pop và push.
- Chờ thread kết thúc.
- Đo thời gian chạy chương trình từ lúc sinh thread đến khi thread kết thúc.

pop()
- Nếu phần tử mảng có giá trị âm thì lấy một phần tử trên đỉnh stack ra và hiển thị "POP: x" với x là giá trị vừa lấy.
- Nếu stack rỗng thì báo "Stack empty".

push()
- Nếu phần tử mảng có giá trị dương thì đẩy phần tử này vào stack.


 Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, không tiến hành đồng bộ, đo thời gian.
2 - SV sử dụng mutex lock để đồng bộ và đo thời gian.
3 - SV sử dụng semaphore để đồng bộ và đo thời gian.
4 - SV dùng các biện pháp đồng bộ khác (có thể tự đề xuất) và đo thời gian.
*/
