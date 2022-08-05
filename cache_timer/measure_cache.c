/*
	measure_cache c file
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
  asm("lfence;\n\tmfence\n");

  // read
  *time = counter; 

  // barrier
  asm("lfence;\n\tmfence\n");
}


/*
  Running cache measuring on the following processor(s)
  1. 2.3 GHz Intel Core i7 (I7-1068NG7) processor
  2. running PACMAN cache reverse engineering strategy
  3. form eviction set
*/
int main(void) {

  // bringup
  INFO("Measuring cache performance of current cpu\n");
  pthread_t tid;
  pthread_create(&tid, NULL, timerthread, NULL);
  
  // Hyper Variables
  int N = 30;
  uint64_t stride = 4 * 1048576; // 4 mb
  uint64_t num_trials = 10000;
  uint64_t start, elapsed;
  
  // Get x 
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

  // measure timing up to N (1000 trials)
  volatile int target = 0xdeadbeef;
  WARN("Target address %p\n", &target);

  // cache hit measurements
  int junktemp = 1;
  junktemp = *(&target); // make sure its in cache
  junktemp = *(&target);
  start = __rdtscp(&junktemp);
  junktemp = *(&target);
  elapsed = __rdtscp(&junktemp) - start;
  INFO("Hit cycle count %d\n", elapsed);

  // measure miss count
  _mm_clflush(&target);
  start = __rdtscp(&junktemp);
  junktemp = *(&target);
  elapsed = __rdtscp(&junktemp) - start;
  INFO("Miss cycle count %d\n", elapsed);

  // measure hit count with thread timer
  read_timer(&start);
  junktemp = *(&target);
  read_timer(&elapsed);
  elapsed -= start;
  INFO("Hit count thread timer %d\n", elapsed);

  // Start experiment
  for(int n = 1; n < N; n++) {
    int junk = 0;
    uint64_t start_data[num_trials], end_data[num_trials];
    
    // Run trials
    for(long t = 0; t < num_trials; t++) {
      asm("lfence\nmfence\n");
      // load x
      volatile int* p = &target;
      junk = *p; // load into cache
      start = __rdtscp(&junk);
      junk = *p;
      elapsed = __rdtscp(&junk) - start;
      start_data[t] = elapsed;
      asm("lfence\nmfence\n");
      // give value (access so it is in cache)
      for(long i = 0; i < n; i++) {
        //int mix_i = ((i * 167) + 13) % n; //mix to avoid prefetchers and other things 
        volatile int* point = (int*)addrs[i];
        junk = *point; 
      }
      asm("lfence\nmfence\n");
      // remeasure target
      start = __rdtscp(&junk);
      junk = *p;
      elapsed = __rdtscp(&junk) - start;
      end_data[t] = elapsed;
      //WARN("%p, %p\tThese should differ by 4\n", &x[0], &x[1]); //should differ by 4
      asm("lfence\nmfence\n");
    }

    // mean calculation
    double end_mean = 0, start_mean = 0;
    for(long i = 0; i < num_trials; i++) {
      end_mean += end_data[i];
      start_mean += start_data[i];
    }
    end_mean /= (double)num_trials;
    start_mean /= (double)num_trials;
    INFO("n %d, start_mean: %f \tend_mean: %f\n", n, start_mean, end_mean);

    // recauluate first addrs access time
    int rand_idx = rand()%N;
    start = __rdtscp(&junk);
    junk = addrs[rand_idx];
    elapsed = __rdtscp(&junk) - start;
    //INFO("First addr time: %d\n", elapsed);
  }

  // clean up
  pthread_join(&tid, NULL);
  return 0;
}


