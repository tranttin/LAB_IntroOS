# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf fcfs
	rm -rf sjf
	rm -rf rr
	rm -rf priority
	rm -rf priority_rr

rr: driver.o rr.o
	$(CC) $(CFLAGS) -o rr driver.o rr.o -lpthread

sjf: driver.o sjf.o
	$(CC) $(CFLAGS) -o sjf driver.o sjf.o -lpthread

fcfs: driver.o fcfs.o
	$(CC) $(CFLAGS) -o fcfs driver.o fcfs.o -lpthread

priority: driver.o priority.o
	$(CC) $(CFLAGS) -o priority driver.o priority.o -lpthread

priority_rr: driver.o priority_rr.o
	$(CC) $(CFLAGS) -o priority_rr driver.o priority_rr.o -lpthread
	
fcfs.o: fcfs.c
	$(CC) $(CFLAGS) -c fcfs.c -lpthread

driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c -lpthread

schedule_sjf.o: schedule_sjf.c
	$(CC) $(CFLAGS) -c sjf.c -lpthread

priority.o: schedule_priority.c
	$(CC) $(CFLAGS) -c schedule_priority.c -lpthread

schedule_rr.o: schedule_rr.c
	$(CC) $(CFLAGS) -c schedule_rr.c
