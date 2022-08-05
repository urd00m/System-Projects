CC=gcc 
CFLAGS=-Wall -g -O0
LIBS=-I$(INC) -L.
INC=includes

all: cache_timing_test.out flush_reload.out prime_probe.out cpuid_reader.out measure_cache.out

cache_timing_test.out: cache_timing_test.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

flush_reload.out: flush_reload.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

prime_probe.out: prime_probe.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

cpuid_reader.out: cpuid_reader.c
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

measure_cache.out: measure_cache.c 
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	touch clean.o
	touch clean.out
	touch clean.out.dSYM
	rm *.o
	rm *.out
	rm -r *.out.dSYM
