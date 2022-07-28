/*
	cpuid_reader c file
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
  Analysis on cpuid eax=2 outputs
*/
int main(void) {
  INFO("Starting\n"); // starting test

  asm("mov $4, %eax"); // prime eax=4 for tlb and cache information
  asm("mov $1, %ecx"); // prime ecx=0 for leaf 4
  asm("cpuid"); // call cpuid
  return 0;
}
