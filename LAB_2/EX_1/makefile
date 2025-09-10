CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -L.
LIBS = -lstr

all: hello app use_static use_shared

hello: hello.c
	$(CC) $(CFLAGS) hello.c -o hello

app: main.o util.o
	$(CC) $(CFLAGS) main.o util.o -o app

main.o: main.c util.h
util.o: util.c util.h

libcalc.a: calc.o
	ar rcs libcalc.a calc.o

use_static: main_static.c libcalc.a
	$(CC) $(CFLAGS) main_static.c -L. -lcalc -o use_static

libstr.so: strutil.o
	$(CC) -shared -o libstr.so strutil.o

use_shared: main_shared.c libstr.so
	$(CC) $(CFLAGS) main_shared.c -L. -lstr -Wl,-rpath='$ORIGIN' -o use_shared

clean:
	rm -f *.o hello app use_static use_shared libcalc.a libstr.so
