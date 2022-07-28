/*
	measure_cache c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "urd00m_output.h"
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt", on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif

/*
  Running cache measuring on the following processor(s)
  1. 2.3 GHz Intel Core i7 (I7-1068NG7) processor
  2. TODO 
*/
int main(void) {
  INFO("Measuring cache performance of current cpu")
  

  
  return 0;
}
