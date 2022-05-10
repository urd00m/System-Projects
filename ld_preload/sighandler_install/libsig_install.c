#define _GNU_SOURCE
#include <signal.h>
#include <dlfcn.h>
#include <ucontext.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// capstone
#include <capstone/capstone.h>

// Original functions and hijack flag
int hijack = 0;
int (*orig_get_y2)(void) = 0;

// Capstone handler
static csh handle;

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

        // cs_insn stores capstone disasm information
        cs_insn *inst;

	// Get ucontext so we can modified the signal context
	ucontext_t *uc = (ucontext_t *)context;

	// turn on LD_PRELOAD hijack get_y2() function
	hijack = 1;

	// Hardcoded fixes
	//uc->uc_mcontext.gregs[REG_RIP] += 2; // skip the dividing instruction
	//uc->uc_mcontext.gregs[REG_RCX] = 0x1; // set the dividing register to 1 instead of 0

	// Dynamically skip over instruction
	void* rip = (void *)uc->uc_mcontext.gregs[REG_RIP];
        size_t count = cs_disasm(handle,rip,16,(ulong)rip,1,&inst);
        if(count <= 0) {
                fprintf(stdout, "Unable to dissassemble code\n");
                return -1;
        }

	// skip over the instruction
	uc->uc_mcontext.gregs[REG_RIP] += inst->size;

        // get information
        fprintf(stdout, "instruction: %s %s\t\t\tinstruction size: %d\n", inst->mnemonic, inst->op_str, inst->size);
}

// sets up the signal handler
int setup_sig(void) {
	struct sigaction sa; 
	memset(&sa, 0, sizeof(sa));

	sa.sa_sigaction = fpe_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
        sigaddset(&sa.sa_mask, SIGFPE);
	int status = sigaction(SIGFPE, &sa, 0);
	if(status == -1) {
		fprintf(stdout, "Signal setup failed\n");
		return -1;
	}
	return 0;
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

// Setup capstone
int setup_capstone(void) {
	// open capstone
	int status = cs_open(CS_ARCH_X86, CS_MODE_64, &handle); 
        if(status != CS_ERR_OK) {
                fprintf(stdout, "Failed capstone open\n");
                return -1;
        }

        // set options
        status = cs_option(handle, CS_OPT_SYNTAX, 2); // turns off intel syntax
        if (status != CS_ERR_OK) {
                fprintf(stdout, "Failed to set cs_options\n");
                return -1;
        }

	return 0;
}

static __attribute__((constructor)) void libsig_init(void) {
	fprintf(stdout, "I have taken over haha\n");
	if(setup_sig() == -1) {
		fprintf(stdout, "Signal setup failed\n");
	}
	if(setup_shims() == -1) {
		fprintf(stdout, "shims setup failed\n");
	}
	if(setup_capstone() == -1) {
		fprintf(stdout, "capstone setup failed\n");
	}
	fprintf(stdout, "lib sig setup complete\n");
}
