CC=gcc 
CFLAGS=-Wall
LIBS=-I$(INC) -L.
INC=includes

all: cache_timing_test.out flush_reload.out

cache_timing_test.out: cache_timing_test.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

flush_reload.out: flush_reload.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	touch clean.o
	touch clean.out
	rm *.o
	rm *.out
