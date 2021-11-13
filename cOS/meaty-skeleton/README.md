# Meaty-Skeleton 

Initial code commit is from https://gitlab.com/sortie/meaty-skeleton. 
It contains the intial documents needed to set up a future OS. It contains
the features of the simpleOS but just organized so that more files can be 
added in the future. 

# Understanding the boot process
1. The first step is setting up the computer with the essentials 
	a. This includes adding a RSP stack pointer in `boot.S`
	b. This also includes calling the global constructors this is done by `boot.S` 
		i. The files used are `crti.S` `crtn.S` `crtbegin.S` `crtend.s` where the _init .init sections contain the constructors and _fini .fini contain the destructors 
		ii. `boot.S` contains the entry point, the part that GRUB will call 
	c. The kernel is then called by the `boot.S` after everything has been set up by calling `kernel_main` in `kernel.c` 
	d. `kernel.c` will then just print "hello world" to the screen 
2. Usually their are more steps but since this is a skeleton we have very minimal code to setup the processor and only can write to the VGA buffer 

# Compilation 
1. arch/i386 has its own make.config which will link boot.o and tty.o which are linked by `myos.kernel` build target in the makefile 
2. `kernel.o` is linked to it in the big makefile in kernel 
3. the makefile also includes targets to copy the headers over to the sysroot folder and contains code to move the myos.kernel file over to be created into an iso file. 
