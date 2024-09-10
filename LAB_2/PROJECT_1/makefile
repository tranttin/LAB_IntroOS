# Tên chương trình
TARGET = prime_program

# Các file nguồn và header
SRCS = primary.c supportA.c supportB.c
HEADERS = supportA.h supportB.h

# Cờ biên dịch
CFLAGS = -Wall -lm  # Kích hoạt cảnh báo và liên kết thư viện math.h

# Biến đối tượng từ các file nguồn
OBJS = $(SRCS:.c=.o)

# Quy tắc mặc định để build chương trình
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

# Quy tắc biên dịch file .o từ file .c
%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)

# Quy tắc dọn dẹp file tạm sau khi biên dịch
clean:
	rm -f $(OBJS) $(TARGET)

# Quy tắc chạy chương trình
run: $(TARGET)
	./$(TARGET)

