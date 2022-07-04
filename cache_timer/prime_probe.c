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

// USER VARIABLES
#define HIT_THRESHOLD 80
#define MULTIPLIER 256
#define MAX_RUNS 1000
#define SECRET 124

/*
  This program messes with the prime + probe cache timing attack. The goal of this attack is to figure out which cache set the victim program uses. 
*/
int main(void) {
  // measuring cache line size
  register uint64_t start, elapsed;
  static int test[256 * MULTIPLIER];
  volatile int junk = 0;
  int result[256];
  for(int i = 0; i < 256; i++) result[i] = 0;

  for(int run = 0; run < MAX_RUNS; run++) {
    // prime
    for(int i = 0; i < 256; i++) {
      int mix_i = ((i * 167) + 13) & 255;
      int* addr = &test[mix_i * MULTIPLIER]; 
      junk = test[mix_i * MULTIPLIER];
      junk = *addr;
      junk = *addr;
      junk = *addr;
      junk = *addr;
      junk = *addr;
      junk = *addr;
      junk = *addr;
    }
  
    // make sure
    /*
    int hits = 0;
    for(int i = 0; i < 256; i++) {
      int mix_i = ((i * 167) + 13) & 255;
      start = __rdtscp(&junk); 
      junk = test[mix_i * MULTIPLIER]; 
      elapsed = __rdtscp(&junk) - start; // calculate elapsed cycles
      if(elapsed < HIT_THRESHOLD)
        hits++; 
    }
    INFO("Hits at start %d out of size 256\n", hits);
    */

    // secret is flushed out
    _mm_clflush(&test[SECRET * MULTIPLIER]); 

    // Measuring cache timing
    for(int i = 0; i < 256; i++) {
      int mix_i = ((i * 167) + 13) & 255;
      uint64_t* addr = &test[mix_i * MULTIPLIER]; 
      start = __rdtscp(&junk);
      junk = *addr;
      elapsed = __rdtscp(&junk) - start;
      if(elapsed > HIT_THRESHOLD) {
        result[mix_i]++;
      }
    }
  }

  // find max
  int max = 0;
  int idx = -1;
  int total = 0; 
  for(int i = 0; i < 256; i++) {
    total += result[i];
    if(result[i] > max) {
      max = result[i];
      idx = i; 
    }
  }
  INFO("User accessed %d, with a %f%% chance\n", idx, 100.0*(1.0*max/total));
  
  /*
  // flush i = 0
  for(int i = 0; i < 256; i++)
    _mm_clflush(&test[i * MULTIPLIER]); // flush index 0
  hits = 0;
  for(int i = 0; i < 256; i++) { // recalculate hits
    int mix_i = ((i * 167) + 13) & 255;
    start = __rdtscp(&junk); 
    junk = test[mix_i * MULTIPLIER];
    elapsed = __rdtscp(&junk) - start; // calculate elapsed cycles
    if(elapsed < HIT_THRESHOLD)
      hits++; 
  }
  INFO("Hits after flush %d out of size 256\n", hits);
  */

  return 0; 
}
