#ifndef URD00M_OUTPUT
#define URD00M_OUTPUT

// Includes
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

//#include <config.h>

// Color functions
void red () {
  printf("\033[1;31m");
}
void yellow() {
  printf("\033[1;33m");
}
void reset () {
  printf("\033[0m");
}


#define INFO(msg, ...) fprintf(stderr, "[INFO]  [Thread: %d] " msg, gettid(), ##__VA_ARGS__)
#define WARN(msg, ...) yellow(); fprintf(stderr, "[WARN]  [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define ERROR(msg, ...) fprintf(stderr, "[ERROR] [Thread: %d] " msg, gettid(), ##__VA_ARGS__)
#define FATAL(msg, ...) fprintf(stderr, "[FATAL] [Thread: %d] " msg, gettid(), ##__VA_ARGS__)

// Get thread id
static inline int gettid()
{
  return syscall(SYS_gettid);
}

#endif
