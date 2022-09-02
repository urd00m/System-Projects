CC=gcc
CFLAGS=-Wall -g -O0
INC=./includes
LIBS=-I$(INC) -L./lib

all: initial_test.out lib/libmeltdown.so

initial_test.out: src/initial_test.c 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

lib/libmeltdown.so: src/libmeltdown.c 
	$(CC) $(CFLAGS) -fPIC -shared $(LIBS) $^ -o $@

clean:
	touch clean.o
	touch clean.out
	touch clean.dSYM
	touch clean.so
	rm *.so
	rm -rf *.dSYM
	rm *.o
	rm *.out
