CC=gcc
CFLAGS=-Wall -g -O0
INC=./includes
LIBS=-I$(INC) -L./libs

all: initial_test.out libs/libmeltdown.so out_of_bounds_read.out heap_test.out

initial_test.out: src/initial_test.c 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

libs/libmeltdown.so: src/libmeltdown.c 
	$(CC) $(CFLAGS) -fPIC -shared $(LIBS) $^ -o $@

out_of_bounds_read.out: src/out_of_bounds_read.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@ -lmeltdown -lm

heap_test.out: src/heap_test.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@ -lmeltdown -lm

clean:
	touch clean.o
	touch clean.out
	touch clean.dSYM
	touch clean.so
	rm *.so
	rm -rf *.dSYM
	rm *.o
	rm *.out
