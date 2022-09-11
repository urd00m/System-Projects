/*
	hello2 c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test1(void) {
  printf("whats up\n");
  return;
}

void test2(void) {
  printf("test2 says hi\n");
  int* b = malloc(4);
  memset(b, 0, 4);

  return;
}

int main(void) {
  volatile int a = 5 + 6;
  printf("HELLO\n");
  test1();
  test2();
  volatile char b = 123 / 12;
  return 0;
}

