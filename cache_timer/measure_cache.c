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

  // Get x 
  int x[16384 * N + N * 64];
  INFO("Address x %p\n", x);

  // build addrs
  int* addrs[N];
  for(long i = 0; i < N; i++) {
    addrs[i] = (int*)x + i*stride + i*64;  //formula listed in i7_writeup.md
    INFO("Addr %p %p\n", addrs[i], &x[i*stride+i*64]);
  }
  INFO("Addrs built\n");

  // give value
  for(long i = 0; i < N; i++) {
    volatile int* point = (int*)addrs[i];
    *point = i;
  }

  WARN("%p, %p\tThese should differ by 4\n", &x[0], &x[1]); //should differ by 4
    
  return 0;
}
