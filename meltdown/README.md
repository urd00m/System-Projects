# Meltdown Attack Project
Meltdown takes advantage of out-of-order execution to create a universal read gadget of memory. There are software patches that prevent it from doing too much damage. This project's goal is to simple attempt to see if we can replicate the original meltdown attack. 


## initial test
1. run `make` 
2. run `./initial_test.out`
This just reads from a byte from the stack

## libmeltdown shared library
1. run `make`
2. library is in `lib/libmeltdown.so`

## TODOS 
1. add in signal handler
2. read memory that process can't access 

#### by Alan Wang github: urd00m
