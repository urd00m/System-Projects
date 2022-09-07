/*
  Testing out of bounds reads with meltdown
 */
#include "libmeltdown.h"

#define MELTDOWN_ON 1
#define FIND_VALUES 0

/*
  Main Function
 */
int main(void) {
  INFO("Starting out of bounds read\n");
  meltdown_init();
  
  // testing stack
  char buffer[10];
  memset(buffer, 0, 10);

  // read first 10 values
  for(int i = 0; i < 10; i++) {
    INFO("Reading %p value %d\n", (buffer + i), buffer[i]);
  }
  //  sleep(3);

#if FIND_VALUES
  // plant values to find
  char empty[100];
  memset(empty, 68, 100); 
  //free(empty);
#endif
  
  // reading out of bounds
  for(int i = 10; i < 100000; i++) {
    char* p = buffer + i;
#if MELTDOWN_ON
    char value = meltdown_read_byte(p);
    INFO("Reading %p value %d offset %d\n", p, value, i);
#else
    char value = buffer[i];
    INFO("Reading %p value %d offset %d\n", p, value, i);
#endif 
  }
  
  return 0;
}
