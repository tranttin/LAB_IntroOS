CC = gcc
CFLAGS = -Wall -lrt

# Tên chương trình
PRODUCER = producer
CONSUMER = consumer

# Các file nguồn
PRODUCER_SRC = producer.c
CONSUMER_SRC = consumer.c

# File đối tượng
PRODUCER_OBJ = $(PRODUCER).o
CONSUMER_OBJ = $(CONSUMER).o

# Đích thực thi
all: $(PRODUCER) $(CONSUMER)

$(PRODUCER): $(PRODUCER_OBJ)
	$(CC) $(CFLAGS) -o $(PRODUCER) $(PRODUCER_OBJ)

$(CONSUMER): $(CONSUMER_OBJ)
	$(CC) $(CFLAGS) -o $(CONSUMER) $(CONSUMER_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Lệnh dọn dẹp
clean:
	rm -f $(PRODUCER_OBJ) $(CONSUMER_OBJ) $(PRODUCER) $(CONSUMER)

# Lệnh chạy chương trình với tham số N cho producer
run-producer:
	./$(PRODUCER) 20  # Bạn có thể thay đổi 20 bằng N khác nếu cần

run-consumer:
	./$(CONSUMER)
