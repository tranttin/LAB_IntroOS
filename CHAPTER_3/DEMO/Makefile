CC = gcc
CFLAGS = -Wall -g
TARGETS = atm atm_timer prime prime_pipeline writer writer_fork

all: $(TARGETS)

atm: atm.o
	$(CC) $(CFLAGS) -o atm atm.o

atm_timer: atm_timer.o
	$(CC) $(CFLAGS) -o atm_timer atm_timer.o

prime: prime.o
	$(CC) $(CFLAGS) -o prime prime.o

prime_pipeline: prime_pipeline.o
	$(CC) $(CFLAGS) -o prime_pipeline prime_pipeline.o

writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

writer_fork: writer_fork.o
	$(CC) $(CFLAGS) -o writer_fork writer_fork.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)
