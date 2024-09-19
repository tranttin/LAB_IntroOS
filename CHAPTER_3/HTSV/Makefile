# Makefile cho chương trình POSIX với 3 file .c và 1 file data.txt

# Tên các file chương trình
CC = gcc
CFLAGS = -Wall
TARGETS = student server random

# Phần biên dịch các file .c
all: $(TARGETS)

student: student.c
	$(CC) $(CFLAGS) -o student student.c

server: server.c
	$(CC) $(CFLAGS) -o server server.c

random: random.c
	$(CC) $(CFLAGS) -o random random.c

# Phần chạy chương trình
run_random:
	./random

run_server:
	./server

run_student:
	./student

# Dọn dẹp các file đã biên dịch
clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean run_random run_server run_student
