# cOS 
 
Basic OS to learn more about OS developement. Tutorial is followed from OS DEV here: https://wiki.osdev.org/Creating_an_Operating_System

## SimpleOS
This is a basic OS that can boot and has all the skeleton set up for the OS. This OS can only display characters on the screen with a VGA
text mode buffer. The implemenation that comes with the OS Dev Wiki doesn't come with new line support and doesn't come with scrolling 
features. The current implementation that exists in the simpleOS directory has both implemented now. It can boot and demonstrate text 
begin displayed on the screen with newlines and scrolling.  
Features:  
* Boot process 
* Stack setup 
* Basic skeleton 
* VGA text buffer 
* Text being displayed 
* Text scrolling
* New line support
 

#### Usage
**Building:**
1. `make all` to compile 
2. `make check` to check your iso file format
3. `make test` to test and see the file run 

**Make Clean:**
`make clean` will remove all object, bin, and iso files. 

## Meaty-skeleton
This is a basic OS (simpleOS) just more organized and set up for future additions and updates. It can display characters. It also has the global constructors (crti and crtn) and has all the makefiles
setup so that everything can be linked together. The organization also comes with a sysroot for when developing user space will be useful. It has sh files for quick install and building. The 
organization has a libc with headers and c files and also a kernel directory which contains the kernel files. So it separates kernel from the libc which is good organiztaion for the future. 

#### Usage
1. `./clean.sh` 
2. `./iso.sh`
3. `./qemu.sh`

#### File Explantion 
- `build.sh` 
	- This one will build the kernel.myso file which is used to create the iso file 
- `clean.sh` 
	- This will remove all the iso files, .o files, and anything that isn't important
- `headers.sh` 
	- This will setup all the header in sysroot 
- `iso.sh` 
	- This will create the iso file 
- `qemu.sh` 
	- This will test run the iso file in qemu 
- `kernel`
	- This houses the kernel files, including the terminal code and includes as well the boot process files 
- `libc` 
	- This houses the standard library files and headers.
- `sysroot`
	- This acts as the root directory for the OS and contains the the headers and the iso file 
- `config.sh` 
	- This sets up different makefile variables for us to use 
