#ifndef COLOR
#define COLOR
#include <stdio.h>

// enable color
#define COLOR_ON 1 

// Basic color functions
#define red() fprintf(stderr, "\033[0;31m")
#define yellow() fprintf(stderr, "\033[0;33m")
#define black() fprintf(stderr, "\033[0;30m")
#define green() fprintf(stderr, "\033[0;32m")
#define blue() fprintf(stderr, "\033[0;34m")
#define cyan() fprintf(stderr, "\033[0;36m")
#define purple() fprintf(stderr, "\033[0;35m")
#define white() fprintf(stderr, "\033[0;37m")

// Bold color functions
#define bold_red(b) fprintf(stderr, "\033[1;31m")
#define bold_yellow(b) fprintf(stderr, "\033[1;33m")
#define bold_black(b) fprintf(stderr, "\033[1;30m")
#define bold_green(b) fprintf(stderr, "\033[1;32m")
#define bold_blue(b) fprintf(stderr, "\033[1;34m")
#define bold_cyan(b) fprintf(stderr, "\033[1;36m")
#define bold_purple(b) fprintf(stderr, "\033[1;35m")
#define bold_white(b) fprintf(stderr, "\033[1;37m")

// Background color functions
#define back_red() fprintf(stderr, "\033[40;31m")
#define back_yellow() fprintf(stderr, "\033[41;33m")
#define back_black() fprintf(stderr, "\033[41;30m")
#define back_green() fprintf(stderr, "\033[41;32m")
#define back_blue() fprintf(stderr, "\033[41;34m")
#define back_cyan() fprintf(stderr, "\033[41;36m")
#define back_purple() fprintf(stderr, "\033[41;35m")
#define back_white() fprintf(stderr, "\033[41;37m")

// Bold and background color functions
#define bold_and_back_red() fprintf(stderr, "\033[1;40;31m")
#define bold_and_back_yellow() fprintf(stderr, "\033[1;41;33m")
#define bold_and_back_black() fprintf(stderr, "\033[1;41;30m")
#define bold_and_back_green() fprintf(stderr, "\033[1;41;32m")
#define bold_and_back_blue() fprintf(stderr, "\033[1;41;34m")
#define bold_and_back_cyan() fprintf(stderr, "\033[1;41;36m")
#define bold_and_back_purple() fprintf(stderr, "\033[1;41;35m")
#define bold_and_back_white() fprintf(stderr, "\033[1;41;37m")

// Reset colors
#define reset() fprintf(stderr, "\033[0m")

#endif
