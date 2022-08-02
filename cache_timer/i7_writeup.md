# I7-1068NG7 Cache Data
This is a 10th generation Intel I7 chip. 

## General Information 
Information according to Intel's datasheet for 10th generation processors. And CPUID informatino about cache and tlb information. Documentation here: https://c9x.me/x86/html/file_module_x86_id_45.html and here https://www.felixcloutier.com/x86/cpuid#tbl-3-12. 

L1 cache: 42KB (48KB reading CPUID) data cache, 32KB instruction cache, 64 byte cache line, 8-way  
L2 cache: 512KB total, 64 byte lines, 8-way  
L3 cache: 8 MB shared (2 MB per core times 4 cores), 64 byte lines, 16-way  

#### CPUID return information (eax=2, leaf 2):   
EAX - 0x 00 fe ff 01  
EBX - 0x 00 00 00 f0   
ECX - 0x 00 00 00 00   
EDX - 0x 00 00 00 00  
f0 = 64 byte prefetching  
f2 = use cpuid leaf 18h to query tlb parameters  
ff = cpuid doesn't support information use leaf 4h to query cache parameters  

#### CPUID return information (eax=4, leaf 4): 
ecx=0, the data cache (L1d):  
ways: 12  
partitions: 1  
line size: 64 bytes  
sets: 64  
total size: 48KB  

ecx=1, the instruction cache (l1i):  
ways: 8  
partitions: 1  
line size: 64 bytes  
sets: 64  
total size: 32KB  

ecx=2, the L2 cache (unified cache):  
ways: 8  
partitions: 1  
line size: 64  
sets: 1024  
total size: 512KB  

ecx=3, the L3 cache (unified cache):  
ways: 16  
partitions: 1  
line size: 64  
sets: 8192  
total size: 8MB  

#### CPUID return information (eax=0x18, leaf 18) 
ecx=0 reports eax=0x7, meaning the max ecx value we can have is 7.  

ecx=1  
Exists TLB that supports 4k, 2m, and 4m  
8-way (fully associative) 1-set TLB, Instruction TLB (level 1)  

ecx=2  
Exists TLB that supports 4k, 2m, 4m, and 1g  
16-way (fully associative) 1-set TLB, Unknown type TLB (level 1) (type id was 5, but only goes from 0-3 others are reserved so unknown what this means)  

ecx=3  
Exists TLB that supports 4k  
4-way 16-set TLB, unknown type (level 1) (type id was 4)  

ecx=4  
Exists TLB that supports 2m and 4m  
4-way 8-set TLB, unknown type (level 1) (type id was 4)  

ecx=5  
Exists TLB that supports 1g  
8-way (fully associative) 1-set TLB, Unknown type TLB (level 1) (type id was 4)  

ecx=6  
Exists TLB that supports 4k, 2m, and 4m  
8-way 128-set TLB, Unified TLB (level 2)  

ecx=7  
Exists TLB that supports 4k and 1g 
8-way 128-set TLB, Unified TLB (level 2) 


# Forming Cache Eviction Set 
