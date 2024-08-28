# Overview

Code demo của Chương 1

Cách 1: Tải về toàn bộ thư mục, mở file Jupyter notebook trong môi trường Bash (Linux) và có thể thực thi trực tiếp.
Cách 2: Tải về toàn bộ thư mục, mở Terminal (Linux) và gõ lệnh make để biên dịch toàn bộ, sau đó thực thi từng lời gọi.
```
prompt> make
```

Demo "cpu" mô tả quá trình phân phối quyền sử dụng CPU trong 2 trường hợp: đơn tác vụ và đa tác vụ.

```
prompt> ./cpu A
```

Demo "mem" mô tả địa chỉ ảo của chương trình và địa chỉ vật lý khi hệ điều hành cấp phát.

```
prompt> ./mem 1
```

Demo "threads" mô tả vấn đề cạnh tranh và sai dữ liệu khi nhiều luồng chạy đồng thời.
```
prompt> ./threads 10000
```
Demo "io" mô tả vấn đề nhập xuất bằng các thiết bị ngoại vi.
```
prompt> ./io
```


