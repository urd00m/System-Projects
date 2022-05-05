#define _GNU_SOURCE
#include <signal.h>
#include <dlfcn.h>

// Original functions and hijack flag
int hijack = 0;
int (*orig_get_y2)(void) = 0;

// Our LD_PRELOAD hijack function, that will hijack the get_y2() function call
int get_y2(void) {
	printf("running our hijacked get_y2\n");
	if(!hijack) {
		return orig_get_y2();
	}
	else {
		hijack = 0;
		return 0;
	}
}

// exception handler
void fpe_handler(int signum) {
	if(signum == SIGFPE) {
		signal(SIGFPE, SIG_IGN);
		printf("Signal handler hit enabling hijack %d\n", hijack);
		hijack = 1;
		signal(SIGFPE, fpe_handler);
	}
}

// sets up the signal handler
void sig_install(void) {
	signal(SIGFPE, fpe_handler);
}

// Sets up shims
int setup_shims(void) {
	#define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                ERROR("Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                        }
	SHIMIFY_ERR(get_y2);
	return 0;
}

static __attribute__((constructor)) void libsig_init(void) {
	printf("I have taken over haha\n");
	sig_install();
	setup_shims();
	printf("signal and shims setup complete %d\n", orig_get_y2());
}
