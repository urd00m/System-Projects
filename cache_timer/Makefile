CC=gcc 
CFLAGS=-Wall -g
LIBS=-I$(INC) -L.
INC=includes

all: cache_timing_test.out flush_reload.out prime_probe.out cpuid_reader.out

cache_timing_test.out: cache_timing_test.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

flush_reload.out: flush_reload.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

prime_probe.out: prime_probe.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

cpuid_reader.out: cpuid_reader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	touch clean.o
	touch clean.out
	rm *.o
	rm *.out
