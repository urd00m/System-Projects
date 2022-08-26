CC=gcc
CFLAGS=-Wall -g
INC=./includes
LIBS=-I$(INC) -L./lib

all: main.out

main.out: src/main.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	touch clean.o
	touch clean.out
	rm *.o
	rm *.out
