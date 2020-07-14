/* Cấu trúc chương trình
Tập tin
- Có thể có từ 1 đến n tập tin .txt chứa dữ liệu thao tác với stack
- Mỗi tập tin chứa m dòng thể hiện m thao tác, mỗi thao tác là pop() hoặc push(x).


Dữ liệu:
- Biến số mảng stack[MAX] toàn cục.
- Biến số index chỉ ra vị trí đỉnh stack, ban đầu là 0 (đỉnh stack ở là stack[0]).

main()
- Nhận đối số vào để xác định có bao nhiêu tập tin.
- Nếu không có tập tin: báo lỗi.
- Nếu có k tập tin thì tạo ra k tiểu trình, mỗi tiểu trình stack_op() xử lý một tập tin dữ liệu.
- Sau khi hoàn tất các tiểu trình, in ra những gì còn trong stack và kết thúc.

person()
- Đọc tập tin được chỉ định theo từng dòng.
- Nếu dòng là pop() thì lấy một phần tử từ đỉnh stack ra, in giá trị phần tử này ra màn hình; hoặc thông báo "stack empty" nếu stack rỗng.
- Nếu dòng là push(k) thì thêm một phần tử vào đỉnh stack.
- Nếu dòng chứa thông tin lỗi thì hủy bỏ tiểu trình (pthread_cancel).



Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, không tiến hành đồng bộ, đo thời gian.
2 - SV sử dụng mutex lock để đồng bộ và đo thời gian.
3 - SV sử dụng semaphore để đồng bộ và đo thời gian.
4 - SV dùng các biện pháp đồng bộ khác (có thể tự đề xuất) và đo thời gian.
*/
