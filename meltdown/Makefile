CC=gcc
CFLAGS=-Wall -g -O0
INC=./includes
LIBS=-I$(INC) -L./lib

all: initial_test.out

initial_test.out: src/initial_test.c 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	touch clean.o
	touch clean.out
	touch clean.dSYM
	rm -rf *.dSYM
	rm *.o
	rm *.out
