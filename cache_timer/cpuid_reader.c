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
} __attribute((packed)) ebx_leaf4_t;

// EBX for leaf 18
typedef union {
  int val;
  struct {
    uint8_t page4k:1;
    uint8_t page2m:1;
    uint8_t page4m:1;
    uint8_t page1g:1;
    uint8_t res1:4;
    uint8_t partition:3;
    uint8_t res2:5;
    uint16_t ways:16;
  } __attribute((packed));
} __attribute((packed)) ebx_leaf18_t;

// EDX for leaf 18
typedef union {
  int val;
  struct {
    uint8_t type:5;
    uint8_t level:3;
    uint8_t assoc:1;
    uint8_t res1:5;
    uint16_t addressible:12;
    uint8_t res2:6;
  } __attribute((packed));
} __attribute((packed)) edx_leaf18_t;

// enum for cpuid_ret
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
  uint32_t leaf = 0x18;
  uint32_t ecx_value = 0x7; 
  cpuid(leaf, ecx_value, cpuid_ret);

  INFO("eax: %x\n", cpuid_ret[eax]);
  INFO("ebx: %x\n", cpuid_ret[ebx]);
  INFO("ecx: %x\n", cpuid_ret[ecx]);
  INFO("edx: %x\n", cpuid_ret[edx]);
  printf("\n");
    
  // cache information for leaf 0x4
  if(leaf == 0x4) {
    // bits 04-00 of eax
    uint64_t cache_level = 0;
    cache_level = (cpuid_ret[eax] & 0xf);
    INFO("Cache level: %d\n", cache_level);

    // printing out sizes 
    ebx_leaf4_t ebx_ret = (ebx_leaf4_t)cpuid_ret[ebx];
    int ecx_ret = cpuid_ret[ecx];
    INFO("ways: %d\n", (ebx_ret.ways+1)); 
    INFO("partitions: %d\n", (ebx_ret.partitions+1)); 
    INFO("line_size: %d\n", (ebx_ret.line_size+1)); 
    INFO("sets: %d\n", ecx_ret+1);
    return 0;
  }

  // cache information for leaf 0x18
  if(leaf == 0x18) {
    // ebx register
    ebx_leaf18_t ebx_reg = (ebx_leaf18_t)cpuid_ret[ebx];
    INFO("4k page: %d\n", ebx_reg.page4k);
    INFO("2m page: %d\n", ebx_reg.page2m);
    INFO("4m page: %d\n", ebx_reg.page4m);
    INFO("1g page: %d\n", ebx_reg.page1g);
    INFO("Partition: %d\n", ebx_reg.partition);
    INFO("ways: %d\n", ebx_reg.ways);

    // Ecx register
    uint32_t ecx_reg = cpuid_ret[ecx];
    INFO("Sets: %d\n", ecx_reg);
    
    // edx register 
    edx_leaf18_t edx_reg = (edx_leaf18_t)cpuid_ret[edx];
    INFO("Type: %d\n", edx_reg.type); // 1 data TLB, 2 instruction TLB, 3 unifed TLB
    INFO("Level: %d\n", edx_reg.level);
    INFO("Fully Associative: %d\n", edx_reg.assoc);
    INFO("Addressible Adresses: %d\n", edx_reg.addressible);
  }
}
