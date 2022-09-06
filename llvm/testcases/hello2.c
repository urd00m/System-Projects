/*
	hello2 c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  volatile int a = 5 + 6;
  printf("HELLO\m");
  volatile char b = 123 / 12;
  return 0;
}

void test1(void) {
  printf("whats up\n");
  return;
}

void test2(void) {
  int* b = malloc(4);
  memset(b, 0, 4);

  return;
}
