#!/bin/bash

# Kiểm tra xem server có đang chạy không
if ! pgrep -x "server" > /dev/null; then
    echo "Khởi động server..."
    ./server &
    sleep 2  # Đợi server khởi động
fi

# Danh sách các tham số cho mỗi student
params=(
    "5001 1335"
    "5002 7761"
    "5003 2229"
    "5004 1583"
    "5005 1677"
    "5006 6625"
    "5007 7422"
    "5008 8949"
    "5009 5110"
    "5010 5157"
)

# Chạy 10 instance của student với các tham số
for param in "${params[@]}"
do
    echo "Khởi động student với tham số: $param..."
    ./student $param &
    sleep 0.1  # Đợi 0.5 giây trước khi gọi student tiếp theo
done

# Đợi tất cả các background jobs hoàn thành
wait

echo "Tất cả student đã hoàn thành."
