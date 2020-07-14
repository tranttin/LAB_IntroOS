/* Cấu trúc chương trình
Tập tin
- Có thể có từ 1 đến n tập tin .txt chứa dữ liệu gửi rút tiền của 1 người.
- Mỗi tập tin chứa m dòng thể hiện m thao tác, mỗi thao tác là một số nguyên, nếu là số nguyên âm, người đó đang rút tiền. Nếu là số nguyên dương, người đó đang gửi tiền.


Dữ liệu:

- Biến số Balance toàn cục. Số dư ban đầu = 0.0

main()
- Nhận đối số vào để xác định có bao nhiêu tập tin.
- Nếu không có tập tin: báo lỗi.
- Nếu có k tập tin thì tạo ra k tiểu trình, mỗi tiểu trình person() xử lý một tập tin dữ liệu.
- Sau khi hoàn tất các tiểu trình, in ra số dư cuối cùng và kết thúc.

person()
- Đọc tập tin được chỉ định theo từng dòng.
- Nếu dòng có giá trị dương thì tác động nộp tiền vào biến Balance toàn cục.
- Nếu dòng có giá trị âm thì tác động rút tiền từ biến Balance toàn cục.
- Nếu dòng chứa thông tin lỗi thì hủy bỏ tiểu trình (pthread_cancel).

*/

*/ Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, không tiến hành đồng bộ, đo thời gian.
2 - SV sử dụng mutex lock để đồng bộ và đo thời gian.
3 - SV sử dụng semaphore để đồng bộ và đo thời gian.
4 - SV dùng các biện pháp đồng bộ khác (có thể tự đề xuất) và đo thời gian.
*/
