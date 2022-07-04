#ifndef URD00M_OUTPUT
#define URD00M_OUTPUT

// Includes
#include <unistd.h>
#include <sys/syscall.h>
#include "color.h" // My color function
#include "config.h"

/*
	------ DEBUG LEVEL ------
	0 All debug allowed 
	1 Only warnings and higher 
	2 Only errors and higher 
	3 Fatal only
	4 all debug disabled
*/
#define DEBUG_LEVEL CONFIG_DEBUG_LEVEL

#if DEBUG_LEVEL==0
#define INFO(msg, ...) fprintf(stderr, "[INFO]  [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define WARN(msg, ...) bold_yellow(); fprintf(stderr, "[WARN]  [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define ERROR(msg, ...) bold_red(); fprintf(stderr, "[ERROR] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define FATAL(msg, ...) bold_purple(); fprintf(stderr, "[FATAL] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#elif DEBUG_LEVEL==1
#define INFO(msg, ...)
#define WARN(msg, ...) bold_yellow(); fprintf(stderr, "[WARN]  [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define ERROR(msg, ...) bold_red(); fprintf(stderr, "[ERROR] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define FATAL(msg, ...) bold_purple(); fprintf(stderr, "[FATAL] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#elif DEBUG_LEVEL==2
#define INFO(msg, ...)
#define WARN(msg, ...)
#define ERROR(msg, ...) bold_red(); fprintf(stderr, "[ERROR] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#define FATAL(msg, ...) bold_purple(); fprintf(stderr, "[FATAL] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#elif DEBUG_LEVEL==3
#define INFO(msg, ...)
#define WARN(msg, ...)
#define ERROR(msg, ...)
#define FATAL(msg, ...) bold_purple(); fprintf(stderr, "[FATAL] [Thread: %d] " msg, gettid(), ##__VA_ARGS__); reset()
#else
#define INFO(msg, ...)
#define WARN(msg, ...)
#define ERROR(msg, ...)
#define FATAL(msg, ...)
#endif

// Get thread id
static inline int gettid()
{
  return syscall(SYS_gettid);
}

#endif
