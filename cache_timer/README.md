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

# TODOs
- [x] Cache timing basic
- [x] flush + reload (basic one done)
- [ ] evict + reload
- [ ] prime + probe 
