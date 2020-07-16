/* Cấu trúc chương trình
Tập tin
- Có 1 tập tin chứa n dòng thể hiện n người (có thể là R hay W) đến thao tác.
- Mỗi dòng chứa 2 thông tin: "W k" hoặc "R k". Với W là người ghi (giáo vụ/thư kí) hoặc R là người đọc và k là thời gian người đó cần để thao tác trong bảng tin chung. 
- Giả sử rằng số thứ tự dòng cũng là thời điểm người đó đến.
- VD tập tin
W 10
R 1
R 2
R 3
W 5

Cho thấy tại phút thứ 0 có một W đến và cần 10 phút ghi bảng tin. Phút thứ 1 có một R đến và cần 1 phút đọc. Phút thứ 2 có một R đến và cần 2 phút đọc. ....

Dữ liệu:
- Được nhập từ tập tin.

main()
- Với mỗi người đến tạo một luồng xử lý. Luồng này chạy, cho biết thời điểm người đó đến, thời điểm được phục vụ, ví dụ:
 T=0  W1 arrived    T=0 W1 begin writing ..
 T=1  R1 arrived    T=10 R1 reading ....
 T=2  R2 arrived    T=10 R2 reading ....
 

Yêu cầu:
1 - SV viết đoạn code mô tả bên trên, sử dung các kỹ thuật đồng bộ để hoàn thiện phiên bản 1 của bài toán.
*/
