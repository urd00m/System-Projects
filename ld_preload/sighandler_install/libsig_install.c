#define _GNU_SOURCE
#include <signal.h>
#include <dlfcn.h>
#include <ucontext.h>
#include <stdio.h>

#include <unistd.h>
#include <stdint.h>

// Original functions and hijack flag
int hijack = 0;
int (*orig_get_y2)(void) = 0;

// Our LD_PRELOAD hijack function, that will hijack the get_y2() function call
int get_y2(void) {
	fprintf(stdout, "running our hijacked get_y2\n");
	if(!hijack) {
		return orig_get_y2();
	}
	else {
		hijack = 0;
		return 0;
	}
}


// exception handler
void fpe_handler(int signum, siginfo_t *si, void *context) {
	fprintf(stdout, "Signal handler hit enabling hijack %d\n", hijack);

	// convert to ucontext
	ucontext_t *uc = (ucontext_t *)context;
	hijack = 1;
	//uc->uc_mcontext.gregs[REG_RIP] += 2; // skip the dividing instruction
	uc->uc_mcontext.gregs[REG_RCX] = 0x1; // set the dividing register to 1 instead of 0

	// Dynamically dtermine instruction size and skip over it TODO: need to add in a decoder to do this
	


	//asm("mov $0x1, %ecx"); //TODO: doesn't work need to modify the processes context to modify everything
}

// sets up the signal handler
void sig_install(void) {
	struct sigaction sa; 
	memset(&sa, 0, sizeof(sa));

	sa.sa_sigaction = fpe_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
        sigaddset(&sa.sa_mask, SIGFPE);
	int status = sigaction(SIGFPE, &sa, 0);
	if(status == -1) {
		fprintf(stdout, "Signal setup failed\n");
	}
}

// Sets up shims
int setup_shims(void) {
	#define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                fprintf(stdout, "Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                        }
	SHIMIFY_ERR(get_y2);
	return 0;
}

static __attribute__((constructor)) void libsig_init(void) {
	fprintf(stdout, "I have taken over haha\n");
	sig_install();
	setup_shims();
	fprintf(stdout, "signal and shims setup complete\n");
}
