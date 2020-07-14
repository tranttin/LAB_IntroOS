/* Cấu trúc chương trình
Tập tin
- Có thể có từ 1 đến n tập tin .txt chứa dữ liệu đấu giá của một người.
- Mỗi tập tin chứa m dòng thể hiện m lần đặt giá, các giá trị này phải nguyên dương (do là số tiền).


Dữ liệu:

- Biến số Value toàn cục, ban đầu là 0.

main()
- Nhận đối số vào để xác định có bao nhiêu tập tin.
- Nếu không có tập tin: báo lỗi.
- Nếu có k tập tin thì tạo ra k tiểu trình, mỗi tiểu trình person() xử lý một tập tin dữ liệu.
- Sau khi hoàn tất các tiểu trình, in ra giá trị món hàng cuối cùng và kết thúc.

person()
- Đọc tập tin được chỉ định theo từng dòng.
- Nếu dòng có giá trị dương thì ra giá đấu theo qui tắc: giá đấu phải cao hơn giá hiện tại; Nếu dòng này có giá trị thấp hơn giá hiện tại thì bỏ qua.
- không đặt giá nếu giá cao nhất hiện tại là của chính mình; (nếu mình đang dẫn đầu thì tạm dừng chờ cho đến khi nào có người bỏ giá cao hơn).
- Nếu dòng chứa thông tin lỗi thì hủy bỏ tiểu trình (pthread_cancel).



Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, không tiến hành đồng bộ, đo thời gian.
2 - SV sử dụng mutex lock để đồng bộ và đo thời gian.
3 - SV sử dụng semaphore để đồng bộ và đo thời gian.
4 - SV dùng các biện pháp đồng bộ khác (có thể tự đề xuất) và đo thời gian.
*/
