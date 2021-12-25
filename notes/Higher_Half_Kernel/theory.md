# Higher Half Kernel 
A higher half kernel is a kernel where it is mapped to the higher half of the virtual address space, but mapped to the lower half of the physical address space. 

## How it does this 
In the boot.S file as well as linker.ld, what happens is it adds an offset to the virtual address of the 0xC0000000 + 0x00100000 (3 GB + 1 MB), but mapped to the 0x00100000 (1 MB) in physical address space. 
It creates a page table which maps the physical addresses of the kernel to the higher half virtual addresses of the kernel. 

## Modifcations 
The kernel.c file needs to modified so that the address used for the VGA buffer relates to the now higher half kernel of 0xC0000000.  
The change would be setting the terminal_buffer to  ```terminal_buffer = (uint16_t*) 0xC03FF000;```
