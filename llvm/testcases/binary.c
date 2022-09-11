/*
  binary c file
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  volatile int a = 5 + 6;
  a++;
  a++;
  a++;
  printf("HELLO\n");
  int val = second();
  val += 23;
  return 0;
}

int second(void) {
  printf("running second\n");
  int a = 1 + 2;
  int b = 2 + 3;
  int c = 3 + 5;
  printf("hello from second %d\n", (a + b));
  return 0;
}
