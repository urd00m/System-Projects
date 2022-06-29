#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

// USER VARIABLES
#define HIT_THRESHOLD 80
#define MULTIPLIER 512
#define MAX_RUNS 1000
#define SECRET 124

/*
  This program messes with the flush + reload attach that uses clflush 
*/
int main(void) {
  // Timing and testing array
  register uint64_t start, elapsed;                                // timing variables 
  static int test[256 * MULTIPLIER];

  // Array to get results
  int result[256];
  for(int i = 0; i < 256; i++) result[i] = 0;

  // Measure MAX_RUN times to ensure smaller error
  for(int run = 0; run < MAX_RUNS; run++) {
    // Flush everything and access the secret one
    for(int i = 0; i < 256; i++) _mm_clflush(&test[i * MULTIPLIER]); // flush it
    test[SECRET * MULTIPLIER] = 12421;
    uint64_t* taddr = &test[SECRET * MULTIPLIER];
    volatile int temp = *taddr;

    // Measuring cache timing
    int junk = 0; 
    for(int i = 0; i < 256; i++) {
      int mix_i = ((i * 167) + 13) & 255;
      uint64_t* addr = &test[mix_i * MULTIPLIER]; 
      start = __rdtscp(&junk);
      junk = *addr;
      elapsed = __rdtscp(&junk) - start;
      if(elapsed <= HIT_THRESHOLD) {
        result[mix_i]++;
      }
    }
  }

  // find max
  int max = 0;
  int idx = -1;
  for(int i = 0; i < 256; i++) {
    if(result[i] > max) {
      max = result[i];
      idx = i; 
    }
  }
  printf("User accessed %d, with a %f%% chance\n", idx, 100.0*(1.0*max/MAX_RUNS));

  return 0; 
}
 
