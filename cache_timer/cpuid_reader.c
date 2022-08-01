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


// cpuid stuff
typedef union {
  int val;
  struct {
    uint16_t line_size:12;
    uint16_t partitions:10;
    uint16_t ways:10;
  } __attribute((packed));
} __attribute((packed)) ebx_t;
enum cpuid_reg {eax, ebx, ecx, edx};


/*
  cpuid function
  ret is a 4 uint64_t array
  a -> eax
  b -> ebx
  c -> ecx
  d -> edx
*/
void cpuid(int leaf, int ecx, int* ret) {
  // run cpuid 
  uint64_t a = leaf, b, c, d;
  asm ( "mov %5, %%ecx\n"
        "cpuid\n\t"
        : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
        : "0" (a), "r" (ecx)
        );
  ret[0] = a;
  ret[1] = b;
  ret[2] = c;
  ret[3] = d; 
}


/*
  Main function
*/
int main(void) {
  INFO("Starting\n"); // starting test
  int cpuid_ret[4];

  // call cpuid leaf 4, ecx, then return array
  cpuid(4, 3, cpuid_ret);

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
  ebx_t ebx_ret = (ebx_t)cpuid_ret[ebx];
  int ecx_ret = cpuid_ret[ecx];
  INFO("ways: %d\n", (ebx_ret.ways+1)); 
  INFO("partitions: %d\n", (ebx_ret.partitions+1)); 
  INFO("line_size: %d\n", (ebx_ret.line_size+1)); 
  INFO("sets: %d\n", ecx_ret+1);
  return 0; 
}
