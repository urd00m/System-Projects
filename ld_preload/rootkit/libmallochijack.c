#define _GNU_SOURCE
#include "urd00m_output.h"
#include <dlfcn.h>
#include <unistd.h>

void* (*orig_malloc)(size_t) = 0;


void *malloc(size_t size) {
	WARN("Hijacked malloc call!\n");

	// redirect to orig
	return orig_malloc(size);
}

// Sets up shims
int setup_shims(void) {
        #define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                fprintf(stdout, "Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                        }
        SHIMIFY_ERR(malloc);
        return 0;
}

// constructor
static __attribute__((constructor)) void malloc_hijacker_init(void) {
	INFO("Init of libmallochijack.so\n");
        if(setup_shims() == -1) {
                ERROR("shims setup failed\n");
        }
	INFO("Init succeeded\n");
}
