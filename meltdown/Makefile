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
	rm *.o
	rm *.out
