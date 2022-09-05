# Meltdown Attack Project
Meltdown takes advantage of out-of-order execution to create a universal read gadget of memory. There are software patches that prevent it from doing too much damage. This project's goal is to simple attempt to see if we can replicate the original meltdown attack. 


## initial test
1. run `make` 
2. run `./initial_test.out`
This just reads from a byte from the stack

## out of bounds read test
1. run `make`
2. run `./out_of_bounds_read.out`
Reads several thousand bytes out of bounds for an area, provide a contrast with just the standard out of bounds read which eventually gets caught.

## libmeltdown shared library
1. run `make`
2. library is in `lib/libmeltdown.so`

## TODOS 
1. try on heap
2. try on other thread memory

#### by Alan Wang github: urd00m
