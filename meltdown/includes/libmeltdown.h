#ifndef _MELTDOWN_SRC
#define _MELTDOWN_SRC
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "urd00m_output.h"
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

/*
  config information
*/
#define DEBUG 1
#define RETRIES 1000
#define THRESHOLD 250


/*
  Helper functions
*/
static inline void maccess(void *p);

static void flush(void *p);

static inline uint64_t rdtscp();

static inline int flush_reload(void *p);


/*
  Meltdown setup code
*/
void meltdown_init();

/*
  Read byte function 
 */
char* __attribute__((optimize("-Os"), noinline)) meltdown_read_string(char* addr); 

#endif
