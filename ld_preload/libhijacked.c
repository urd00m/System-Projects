#define _GNU_SOURCE
#include <dlfcn.h>

int (*orig_negateIfOdd)(int) = 0;

int setup_shims(void) {
#define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                ERROR("Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                        } 
	SHIMIFY_ERR(negateIfOdd);
	return 0;
}

static __attribute__((constructor)) void hijacked_init(void) {
	printf("I have taken over losers\n");
        int status = setup_shims(); 
	if(status == 0) {
		printf("Shims setup completed\n");
	}
	else {
		printf("Error occured in shims\n");
	}
}

int negateIfOdd(int inValue){
	printf("intercepted function call\n");
	return orig_negateIfOdd(inValue);
}
