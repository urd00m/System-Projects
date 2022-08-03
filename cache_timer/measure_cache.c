/*
	measure_cache c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "urd00m_output.h"
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

/*
  Running cache measuring on the following processor(s)
  1. 2.3 GHz Intel Core i7 (I7-1068NG7) processor
  2. running PACMAN cache reverse engineering strategy
  3. form eviction set
*/
int main(void) {
  INFO("Measuring cache performance of current cpu\n");
  
  // Hyper Variables
  int N = 10;
  uint64_t stride = 16384; // 16kb
  uint64_t num_trials = 1000;
  register uint64_t start, elapsed;
  
  // Get x 
  int x[16384 * N + N * 64];
  INFO("Address x %p\n", x);

  // build addrs
  int* addrs[N];
  for(long i = 0; i < N; i++) { // divide stride by 4 to account for the *4 attached by compiler 
    addrs[i] = (int*)x + i*(stride/4) + i*16;  //formula listed in i7_writeup.md
    INFO("Addr %p %p\n", addrs[i], &x[i*(stride/4)+i*16]);
  }
  INFO("Addrs built\n");

  // measure timing up to N (1000 trials)
  volatile int target = 0xdeadbeef;
  volatile int* p = &target;
  for(N = 1; N < 10; N++) {
    int junk = 0;
    uint64_t data[num_trials];
    for(long t = 0; t < num_trials; t++) {
      // load x
      *p = 0xdeadbeef; 
      
      // give value (access so it is in cache)
      for(long i = 0; i < N; i++) {
        //int mix_i = ((i * 167) + 13) % N; //mix to avoid prefetchers and other things 
        volatile int* point = (int*)addrs[i];
        *point = i;
      }

      // remeasure target
      start = __rdtscp(&junk);
      *p = 0xdeadbeef; 
      elapsed = __rdtscp(&junk) - start;

      data[t] = elapsed; 
      //WARN("%p, %p\tThese should differ by 4\n", &x[0], &x[1]); //should differ by 4
    }

    // mean calculation
    double mean = 0;
    for(long i = 0; i < num_trials; i++) mean += data[i];
    mean /= (double)num_trials;
    INFO("N %d, mean: %f\n", N, mean);
  }
  
  return 0;
}
