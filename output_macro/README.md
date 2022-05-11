# Instructions
To test `make test`  
To configure `make menuconfig`

# Notes
This contains DEBUG output macros to easily output debug information. This is following the format of ROS 2 logs including, INFO, WARN, ERROR, FATAL.

# Features
4 Macros 
* INFO
* WARN
* ERROR
* FATAL 

It will output to stderr (IP) and a file (TODO)

It will include time of day (TODO), and TID (IP)

# To use
* `includes/` must be copied
* `Makefile` the menuconfig sections must be there
* `Kconfig` must also be copied
* `scripts/` must also be copied
