/*
	main c file
*/
#include "libmeltdown.c"

/*
  Main function
*/
int main(void) {
  char secret_byte = 'Z';
  meltdown_init();
  
  printf("Reading secret byte %c\n", meltdown_read_byte(&secret_byte));
  return 0;
}
