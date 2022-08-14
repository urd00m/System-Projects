# Cache Timing Attack Exploration 
This project explores cache timing attacks and just playing with them. 

## Cache Timing Basic
The files for this test are located below,  
- `cache_timing_test.c`

The command to compile this is `make cache_timing_test.out` or `make` or `make all`.  
To run this test run `./cache_timing_test.out`.  
  
This test simply measures the cycles it costs if there is a cache miss and the cycles it costs if there is a cache hit. 

## Flush + Reload
The files for this test are located below,  
- `flush_reload.c`

The command to compile this is `make flush_reload.out` or `make` or `make all`.  
To run this test run `./flush_reload.out`.  

This test will continously flush then reload the user secret into an array. It will then collect which indexes passed the threshold and at the end print out what it thinks the secret is based on what index was accessed the most as well its percentage. Some interesting notes! I intially did only one MAX_RUN but this turned out to be inaccurate due to other things happening on the computer some things might be brought into cache while others evicted its somewhat random, so if MAX_RUN wasn't high enough you had a chance of mispredicting what the correct result which at first was surprising but makes sense after further thought. 

## Prime + Probe 
The files for this test are located below,  
- `prime_probe.c`

The command to compile this is `make prime_probe.out` or `make` or `make all`.  
To run this test run `./prime_probe.out`.  

This test will prime an array (load into cache) then simulating the victim program running (by clflush'ing a SECRET from the array) then remeasuring the time to figure out hte secret. It does a set amount of trials then finds the highest probabiliy index. This attack is very accurate and able to find the secret a lot of the times. 

## Measuring Cache 
see `i7_writeup.md`  
**tlb graph**
![tlb graph](https://raw.githubusercontent.com/urd00m/System-Projects/master/cache_timer/tlb_measurements.png)

## Evict + reload 
The files for this test are located below,  
- `evict_reload.c` 
- `evict_reload2.c`

The command to compile this is `make evict_reload.out` or `make` or `make all`.  
To run this test run `./evict_reload.out`. This test will load a secret address and on even number trials it will access that secret address. This program will then determine if that address was accessed or not. The way it will do that is by evicting out the accessed address from cache by using 70 eviction addresses determined using the strategy from "Measuring Cache". If the address was accessed we should see the difference from the high resolution thread timer. 

The command to compile this is `make evict_reload2.out` or `make` or `make all`.  
To run this test run `./evict_reload2.out`. This test will use the evict + reload attack to determine a secret address that was accessed. In progress.


# TODOs
- [x] Cache timing basic
- [x] flush + reload (basic one done)
- [x] evict + reload
- [x] prime + probe 
- [x] measuring cache 
- [x] high resolution timer MIT ISCA'22 PACMAN attack 
- [ ] prime + probe reading (find the paper) 

