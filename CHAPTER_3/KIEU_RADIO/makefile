CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lrt

all: radio sadness

radio: radio.c
	$(CC) $(CFLAGS) -o radio radio.c $(LDFLAGS)

sadness: sadness.c
	$(CC) $(CFLAGS) -o sadness sadness.c $(LDFLAGS)

clean:
	rm -f radio sadness
