CC=gcc
CFLAGS=-Wall -g -O0
INC=./includes
LIBS=-I$(INC) -L./lib

all: initial_test.out lib/libmeltdown.so out_of_bounds_read.out

initial_test.out: src/initial_test.c 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

lib/libmeltdown.so: src/libmeltdown.c 
	$(CC) $(CFLAGS) -fPIC -shared $(LIBS) $^ -o $@

out_of_bounds_read.out: src/out_of_bounds_read.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	touch clean.o
	touch clean.out
	touch clean.dSYM
	touch clean.so
	rm *.so
	rm -rf *.dSYM
	rm *.o
	rm *.out
