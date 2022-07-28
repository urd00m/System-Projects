# I7-1068NG7 Cache Data
This is a 10th generation Intel I7 chip. 

## General Information 
Information according to Intel's datasheet for 10th generation processors. And CPUID informatino about cache and tlb information. Documentation here: https://c9x.me/x86/html/file_module_x86_id_45.html and here https://www.felixcloutier.com/x86/cpuid#tbl-3-12. 

L1 cache: 42KB data cache, 32KB instruction cache, 64 bit cache line, 8-way  
L2 cache: 512KB total, 8-way  
L3 cache: 8 MB shared (2 MB per core times 4 cores, 16-way)  

#### CPUID return information (eax=2, leaf 2):   
EAX - 0x 00 fe ff 01  
EBX - 0x 00 00 00 f0   
ECX - 0x 00 00 00 00   
EDX - 0x 00 00 00 00  
f0 = 64 byte prefetching  
f2 = use cpuid leaf 18h to query tlb parameters  
ff = cpuid doesn't support information use leaf 4h to query cache parameters  

#### CPUID return information (eax=4, leaf 4): 
