/*
  testing out of bounds read on heap
 */

#include "libmeltdown.h"

#define MELTDOWN_ON 0

/*
  Main Function
 */
int main(void) {
  INFO("Starting heap test\n");
  meltdown_init();


  // creating heap
  char* buffer = (char *) malloc(100); //100 chars
  memset(buffer, 10, 100);

  // testing buffer
  for(int i = 0; i < 10; i++) {
    INFO("Reading %d: %d\n", i, buffer[i]);
  }

  // doing meltdown
  for(int i = 100; i < 12421; i++) {
    char *p = buffer + i;
#if MELTDOWN_ON
    char value = meltdown_read_byte(p);
    printf("reading %p value %d offset %d\n", p, value, i);
#else
    char value = *p;
    printf("reading %p value %d offset %d\n", p, value, i);    
#endif
  }

  return 0;
}
