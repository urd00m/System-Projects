#ifndef _MELTDOWN_SRC
#define _MELTDOWN_SRC
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
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
#define DEBUG 0
#define RETRIES 10
#define THRESHOLD 250
#define NULL_IGNORED 1

/*
  Helper functions
*/
static inline void maccess(void *p);

static void flush(void *p);

static inline uint64_t rdtscp();

static inline int flush_reload(void *p);

/*
  Segfault handler 
 */
static void meltdown_seg_handler(int sig, siginfo_t *info, void* context);


/*
  Meltdown setup code
*/
void init();

/*
  Read byte function 
 */
char* __attribute__((optimize("-Os"), noinline)) read_string(char* addr); 

#endif
