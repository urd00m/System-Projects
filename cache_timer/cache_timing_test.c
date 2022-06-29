#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

/*
  This program shows the cycles it takes for a cache miss or a cache hit 
*/

int main(void) {
  int HIT_THRESHOLD = 40;                         // Cache hit cycle threshold 
  register uint64_t start, elapsed;               // timing variables 
  
  // finding the HIT_THREASHOLD
  uint64_t dummy = 32;                                                   
  uint64_t* temp = &dummy;
  int junk = -1;                                  // for rdtsc 
  while(1) {
    // Calculate miss
    _mm_clflush(temp);
    start = __rdtscp(&junk);
    junk = *temp; 
    elapsed = __rdtscp(&junk) - start; 
    printf("Run miss %u\n", elapsed);

    // calculate hit 
    start = __rdtscp(&junk);
    junk = *temp; 
    elapsed = __rdtscp(&junk) - start;
    printf("Run hit %u\n", elapsed);
  }
  return 0; 
}
