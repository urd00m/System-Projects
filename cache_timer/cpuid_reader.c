/*
	cpuid_reader c file
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
  Analysis on cpuid outputs
*/



// ret is a 4 uint64_t array
// a -> eax
// b -> ebx
// c -> ecx
// d -> edx
void cpuid(int leaf, int* ret) {
  // run cpuid 
  uint64_t a = leaf, b, c, d;
  asm ( "mov $3, %%ecx\n"
        "cpuid\n\t"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "0" (a)
        );
  ret[0] = a;
  ret[1] = b;
  ret[2] = c;
  ret[3] = d; 
}

int main(void) {
  INFO("Starting\n"); // starting test
  int cpuid_ret[4];
  enum cpuid_reg {eax, ebx, ecx, edx}; 

  cpuid(4, cpuid_ret);

  INFO("eax: %x\n", cpuid_ret[eax]);
  INFO("ebx: %x\n", cpuid_ret[ebx]);
  INFO("ecx: %x\n", cpuid_ret[ecx]);
  INFO("edx: %x\n", cpuid_ret[edx]);

  // bits 04-00 of eax
  uint64_t cache_level = 0;
  cache_level = (cpuid_ret[eax] & 0xf); // 1111
  printf("\n");
  INFO("Cache level: %d\n", cache_level);

  // cache information
  int ebx_ret = cpuid_ret[ebx];
  int ecx_ret = cpuid_ret[ecx];
  INFO("ways: %d\n", ((ebx_ret & 0xffc00000)>>22)+1); // 31:22, 0xffc0 0000
  INFO("partitions: %d\n", ((ebx_ret & 0x003ff000)>>12)+1); // 21:12, 0x003f f000
  INFO("line_size: %d\n", (ebx_ret & 0x00000fff)+1); // 11:0, 0x0000 0fff
  INFO("sets: %d\n", ecx_ret+1);
  return 0; 
}
