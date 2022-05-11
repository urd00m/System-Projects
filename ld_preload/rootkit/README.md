# Instructions
* `make all` - builds the simple call_malloc.c program (just calls malloc)
* `make test` - runs the simple call_malloc program (nothing special)
* `make libmallochijack.so` - builds the malloc hijack function 
* `./malloc_hijack_run.sh` - runs the hijacked malloc call_malloc.out program
* `make rootkit1.so` - builds the readdir() rootkit, hijacks readdir() to hit rootkit1 files 
* `./run_rootkit1.sh` - Runs the hijacked ls program, you can see rootkit1 files are invisible
* `. setup.sh` - (need to source it `./setup.sh` will not work) Sets LD_PRELOAD environment variable to `rootkit1.so` (hiding rootkit1 files)
* `make clean` - cleans the directory 

# Notes
Creating a rootkit using the LD preload library.  

## rootkit1 
Files: `rootkit1.so` and `rkit1.c`  
Hijacks `ls` by intercepting `readdir(...)` calls and hides the files listed above from `ls` commands

# urd00m_output.h configuration
in `includes/config.h` there is only one field you can set the output level.
0 - ALL
1 - WARN+
2 - ERROR+
3 - FATAL+
4 - NONE

# Websites used
* https://rucore.net/en/creating-a-linux-rootkit-using-ld_preload/ 
