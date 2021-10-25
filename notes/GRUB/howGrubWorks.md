# BIOS boot method:

The BIOS boot sequence - RAM detection -> Hardware Detection/Initialization -> Boot Sequence  

The boot sequence is where the BIOS is done with initialization and tries to transfer control over to the next stage of the bootloader process. The device is bootable if it has the valid signature bytes 0x55 and 0xAA at offests 511 and 512 respectively. 0b1010101001010101 in binary.   

BIOS loads the first **512 bytes** and trasfers control to address **0x7C00**. The CPU is running in 16 bit real mode (default state). To execute 32 bit instructions we need to switch the CPU to protected mode. 

# What is GRUB
GNU GRUB = GNU GRand Unified Bootloader. It provides the user a choice of booting from mulitple operating systems installed on a computer. **GRUB is the first thing booted by a computer.** 