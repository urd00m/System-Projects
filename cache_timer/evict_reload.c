/*
	evict + reload c file
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


volatile uint64_t counter;

// thread timer
void timerthread() {
  while(1) {
    counter++;
  }
}

// after tests same as rdtscp
void read_timer(uint64_t* time) {
  // barrier
  asm("lfence;\n\tmfence\nsfence\n");

  // read
  *time = counter; 

  // barrier
  asm("lfence;\n\tmfence\nsfence\n");
}

#define SECRET 678
#define THRESHOLD 55

int main(void) {
  INFO("Evict + reload test\n");

  // timing items
  pthread_t tid;
  pthread_create(&tid, NULL, timerthread, NULL);

  // using 1 gb stride
  int N = 100; // 50 eviction addresses
  uint64_t stride = 1024 * 1048576;
  uint64_t num_trials = 10000; // 1000 trials
  uint64_t start, elapsed;
  
  // data items
  uint64_t data[num_trials];
  uint64_t correct = 0;
  
  // Get x and addrs 
  int* x;
  x = (int *)malloc(sizeof(*x)*(N*(stride/4) + N*16 + 100)); 
  INFO("Address x %p\n", x);
  
  // build addrs
  volatile int* addrs[N];
  for(long i = 0; i < N; i++) { // divide stride by 4 to account for the *4 attached by compiler 
    addrs[i] = (int*)x + i*(stride/4) + i*16;  //formula listed in i7_writeup.md
    INFO("Addr %p %p %d\n", addrs[i], &x[i*(stride/4)+i*16], i*(stride/4)+i*16);
  }
  INFO("Addrs built\n");
  
  // creating shared memory component
  int shared[1024];
  volatile int *p = &shared[SECRET];
  shared[SECRET] = 0xdeadbeef;

  // testing (only use eviction on even idx)
  volatile int junk = 0;
  for(int i = 0; i < num_trials; i++) {
    // isb
    asm("lfence\nmfence\nsfence\n");
      
    // access (bring to cache) 
    junk = *p;

    // DELETE
    read_timer(&start);
    junk = *p;
    read_timer(&elapsed);
    elapsed -= start;
    INFO("idx: %d, cycles: %d, miss: %d\n", i, elapsed, elapsed > THRESHOLD); // want misses on evens
    data[i] = elapsed;
    // DELETE
    
    // isb
    asm("lfence\nmfence\nsfence\n");
      
    // evict on evens
    if(i%2 == 0) {
      for(long i = 0; i < N; i++) {
        int mix_i = ((i * 167) + 13) % N; //mix to avoid prefetchers and other things 
        volatile int* point = (int*)addrs[mix_i];
        junk = *point;
      }
    }
    
    // isb
    asm("lfence\nmfence\nsfence\n");
      
    // measure access latency (evicted or not)
    read_timer(&start);
    junk = *p;
    read_timer(&elapsed);
    elapsed -= start;
    WARN("idx: %d, cycles: %d, miss: %d\n", i, elapsed, elapsed > THRESHOLD); // want misses on evens
    data[i] = elapsed;

    // calculate correctness
    if(i%2 == 0 && elapsed > THRESHOLD) correct++;
    else if(i%2 == 1 && elapsed < THRESHOLD) correct++;
    
    // isb
    asm("lfence\nmfence\nsfence\n");      
  }

  // calculate average
  double mean = 0.0;
  for(int i = 0; i < num_trials; i++) mean += (double)data[i];
  mean /= (double)num_trials;
  ERROR("mean %f\n", mean);
  ERROR("Correct %llu, percentage accuracy %f%%\n", correct, ((double)correct)/num_trials * 100);

  // clean up
  pthread_join(&tid, NULL);
  return 0;
}
