# Meltdown Attack Project
Meltdown takes advantage of out-of-order execution to create a universal read gadget of memory. There are software patches that prevent it from doing too much damage. This project's goal is to simple attempt to see if we can replicate the original meltdown attack. 


## initial test
1. run `make` 
2. run `./initial_test.out`
This just reads from global memory 

## TODOS 
1. Move everything into a shared library (move important items to .h)
2. add in signal handler
3. read memory that process can't access 

#### by Alan Wang github: urd00m
